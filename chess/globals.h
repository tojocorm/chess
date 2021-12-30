#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <cmath>
#include <assert.h>
#include <vector>

using std::cout;
using std::endl;
using std::min;
enum pieceType {Pawn = 0, Bishop = 1, Knight = 2, Rook = 3, Queen = 4, King = 5, Blank = 6};

class piece
{
    public:
    piece(int Color, pieceType Type){
        type = Type;
        color = Color;
    };
    pieceType type;
    int color;
};

// for indexing into data structures
const int White = 0;
const int Black = 1;
// length 2, taken[White] is the map of pieces to quantity that white has taken from Black
extern std::vector< std::unordered_map< piece, int > > takenPieces;
// this is stored from whites perspective -- this means that a1 is indexed at [1][1]
extern std::vector< std::vector< piece > > board;

extern int move;
// return string of the piece
std::string get_type(piece type);
// return the points of the vector
int get_points(std::vector< piece > vec);
// cout the space followed by an empty space
void print_space(piece type);
// return the symbol to be printed on the board
char get_board_symbol(piece type);

#endif
