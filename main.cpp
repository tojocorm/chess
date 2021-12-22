#include "main.h"
#include "globals.h"

using std::cout;
using std::endl;
using std::min;

std::vector<bool> serviced_requesters;
// maps from requester to track
std::unordered_map<int, int> request_queue;

bool all_requesters_started = false;

int max_requests = 0;
int current_requests = 0;

int active_requesters = 0;

int current_track = 0;

// struct for holding args for requester
struct requesterArgs {
    std::string filename;
    int requester_num;
};

struct parentArgs {
    std::vector<std::string> filenames;
};

// returns whether the queue is full
bool queue_full_check(){
    return (current_requests == min(max_requests, active_requesters));
}

// returns whether all requesters have exited
bool all_done(){
    return (active_requesters == 0);
}

// returns whether a specific requester's most recent request was serviced yet
bool serviced(int requester){
    assert(requester < (int)serviced_requesters.size());

    return serviced_requesters[requester];
}

// finds the next request to service based on SSTF
int next_request_to_service(){
    int min_dist = 1001;
    int requester = -1;

    // go through all requests and find the one with the shortest distance from current track
    for (auto it = request_queue.begin(); it != request_queue.end(); ++it ){
        if(std::abs(it->second - current_track) < min_dist){
            min_dist = abs(it->second - current_track);
            requester = it->first;
        }
    }

    return requester;
}

// add a requester's request to the queue and increase the number of current requests
void add_to_queue(int requester, int track){
    request_queue[requester] = track;
    ++current_requests;
    return;
}

// remove a request from the queue by the requester
void remove_from_queue(int requester) {
    request_queue.erase(requester);
    --current_requests;
    return;
}

// servicer thread
void servicer(void *arg){
    // lock
    queue_lock.lock();
    while(!all_requesters_started){
        all_started.wait(queue_lock);
    }
    
    // while not all of the requesters are done requesting
    int counter = 0;
    while(!all_done()){
        ++counter;

        // while the queue is not full, wait
        while(!queue_full_check()){
            queue_full.wait(queue_lock);
        }

        // get the next request and the next track
        int next_request = next_request_to_service();
        if (next_request == -1){
            break;
        }
        int new_track = request_queue[next_request];

        // remove that request from the queue
        remove_from_queue(next_request);

        // update that that request has been serviced
        serviced_requesters[next_request] = true;

        // update the current track
        current_track = new_track;

        // it has been serviced
        print_service(next_request, new_track);

        // broadcast: some cannot, some can
        queue_empty.broadcast();

    }

    queue_lock.unlock();
}

void requester(void *arg){
    // get the args from the void*
    requesterArgs *args_ptr = (requesterArgs*)arg;
    std::string filename = args_ptr->filename;
    int requester_num = args_ptr->requester_num;

    std::ifstream myfile(filename);
    
    std::vector<int> tracks; 
    // read in the tracks from the file and add to a vector of tracks
    if (myfile.is_open()){
        std::string line;
        while(getline(myfile, line)){
            tracks.push_back(stoi(line));
        }
    }

    myfile.close();

    // for all the tracks, we want to service those requests. 
    for(size_t i = 0; i < tracks.size(); ++i){
        int track = tracks[i];
        request_service(requester_num, track);
    }

    // close the requester
    close_requester(requester_num);
}

void request_service(int requester_num, int track){
    // aquire lock
    queue_lock.lock();

    // when the queue is full or we have not yet had our most recent request serviced, we want to wait
    while(queue_full_check() || !serviced(requester_num)){
        queue_empty.wait(queue_lock);
    }
    // add our request to the queue. 
    add_to_queue(requester_num, track);


    // we want our most recent request seen as not serviced
    serviced_requesters[requester_num] = false;

    // we have requested
    print_request(requester_num, track);

    // signal: only the servicer can make progress and is listening
    queue_full.signal();

    queue_lock.unlock();

}

void close_requester(int requester_num){
    queue_lock.lock();

    // wait until the last request we sent has been serviced
    while(!serviced(requester_num)){
        queue_empty.wait(queue_lock);
    }

    // decrease the number of active requesters. 
    --active_requesters;
    
    queue_full.signal();  // this feels wrong... FIXME
    queue_lock.unlock();
}

void parent(void *arg)
{
    // get the args from the void*
    parentArgs *args_ptr = (parentArgs*)arg;
    std::vector<std::string> filenames = args_ptr->filenames;

    std::vector<thread> thread_vec;

    // start the servicer

    std::string args= "";
    thread_vec.push_back(thread((thread_startfunc_t) servicer, (void*)&args));

    std::vector<requesterArgs *> args_vec;

    // for all the requesters
    for (size_t i = 0; i < filenames.size(); ++i){
        // aquire the lock so that we can increase the active requesters. 
        queue_lock.lock();
        ++active_requesters;

        requesterArgs * args = new requesterArgs;
        args->filename = filenames[i];
        args->requester_num = (int)i;
        args_vec.push_back(args);
        // FIXME thread threadi((thread_startfunc_t) requester, (void*)&args);
        thread_vec.push_back(thread((thread_startfunc_t) requester, (void*)args));
        queue_lock.unlock();
    }

    queue_lock.lock();

    all_requesters_started = true;
    // only the servicer is waiting
    all_started.signal();

    queue_lock.unlock();
    // join all the threads
    for(size_t i = 0; i < thread_vec.size(); ++i){
        thread_vec[i].join();
    }

    for(int i = 0; i < (int)args_vec.size(); ++i){
        delete args_vec[i];
    }
    return;
}

int main(int argc, char *argv[])
{
    // get the information from the arg
    max_requests = atoi(argv[1]);

    std::vector<std::string> filenames;

    // get all filenames
    int count = 0;
    while(argv[count + 2] != NULL){
        filenames.push_back(argv[count + 2]);
        ++count;
    }


    // create the vector of serviced requesters
    for(size_t i = 0; i < filenames.size(); ++i){
        serviced_requesters.push_back(true);
    }

    parentArgs args = {filenames};
    // start the servicer thread: this does not return until all others have 
    // FIXME: THIS WILL START AND THEN FINISH IMMEDIATELY
    (cpu::boot((thread_startfunc_t) parent, (void*)&args, 0));
}

// start new thread from maiun, main does very little
// create bool for when all requesters have started
// only exit servicer when all requesters have started.
