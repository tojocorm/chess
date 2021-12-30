#include "globals.h"
#include "gui.h"


std::vector< std::unordered_map< pieceType, int > > takenPieces;

// this is stored from whites perspective -- this means that a1 is indexed at [1][1]
std::vector< std::vector< piece > > board;

int move = White;

void run_game(){
    cout << "Let's play chess: White moves first!" << endl;
    cout << "Usage: in order to move a piece from a5 to a6, type command a5 a6." << endl;
    cout << "ie src dst;" << endl << endl;
    std::string play;
    move = White;
    std::vector<std::string > move_vec;
    move_vec.push_back("");
    move_vec.push_back("");
    move_vec[White] = "White's ";
    move_vec[Black] = "Black's ";

    cout << move_vec[White] << "move: ";
    while(cin >> play){
        
        while(!valid_move(play)){
            cout << "Invalid Move -- try again: ";
        }
        move = !move;
        cout << move_vec[move] << "move: ";
    }
    
}



int main(int argc, char *argv[])
{
    std::vector<piece> empty;
    std::vector<piece> pawns;
    std::vector<piece> row;
    piece rook(White, Rook);
    piece bishop(White, Bishop);
    piece queen(White, Queen);
    piece king(White, King);
    piece knight(White, Knight);

    row.push_back(rook);
    row.push_back(knight);
    row.push_back(bishop);
    row.push_back(queen);
    row.push_back(king);
    row.push_back(bishop);
    row.push_back(knight);
    row.push_back(rook);
    
    piece blank(White, Blank);
    piece pawn(White, Pawn);
    for(int i = 0; i < 8; ++i){
        empty.push_back(blank);
        pawns.push_back(pawn);
    }
    std::unordered_map< pieceType, int > map;
    takenPieces.push_back(map);
    takenPieces.push_back(map);

    board.push_back(row);
    board.push_back(pawns);
    for(int i = 0; i < 4; i ++){
        board.push_back(empty);
    }
    for(int i = 0; i < 8; ++i){
        pawns[i].color = Black;
        row[i].color = Black;
    }
    board.push_back(pawns);
    board.push_back(row);
    print_board(White);
    print_board(Black);
    
    // run_game();
}
