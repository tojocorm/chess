#include <string>

bool queue_full_check();

// returns whether all requesters have exited
bool all_done();

// returns whether a specific requester's most recent request was serviced yet
bool serviced(int requester);

// finds the next request to service based on SSTF
int next_request_to_service();

// add a requester's request to the queue and increase the number of current requests
void add_to_queue(int requester, int track);

// remove a request from the queue by the requester
void remove_from_queue(int requester);

// servicer thread
void servicer(void *arg);

void requester(void *arg);

void request_service(int requester_num, int track);

void close_requester(int requester_num);

void parent(void *arg);

int main(int argc, char *argv[]);