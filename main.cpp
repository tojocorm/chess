#include "main.h"
#include "globals.h"
#include "gui.h"


std::vector< std::unordered_map< pieceType, int > > takenPieces;

// this is stored from whites perspective -- this means that a1 is indexed at [1][1]
std::vector< std::vector< pieceType > > board;

int move = White;


int main(int argc, char *argv[])
{
    std::vector<pieceType> empty;
    std::vector<pieceType> pawns;
    std::vector<pieceType> row;
    row.push_back(Rook);
    row.push_back(Knight);
    row.push_back(Bishop);
    row.push_back(Queen);
    row.push_back(King);
    row.push_back(Bishop);
    row.push_back(Knight);
    row.push_back(Rook);

    for(int i = 0; i < 8; ++i){
        empty.push_back(Blank);
        pawns.push_back(Pawn);
    }
    std::unordered_map < pieceType, int > temp_map;
    takenPieces.push_back(temp_map);
    takenPieces.push_back(temp_map);

    for(int i = 8; i < 8; i ++){
        board.push_back(empty);
    }
    board[1] = pawns;
    board[6] = pawns;
    board[0] = row;
    board[7] = row;
    print_board(White);
}