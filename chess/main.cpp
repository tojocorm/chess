#include "globals.h"
#include "gui.h"


std::vector< std::unordered_map< pieceType, int > > takenPieces;

// this is stored from whites perspective -- this means that a1 is indexed at [1][1]
std::vector< std::vector< piece > > board;

int move = White;


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
}
