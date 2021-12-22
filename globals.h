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

enum pieceType {Pawn = 0, Bishop = 1, Knight = 2, Rook = 3, Queen = 4, King = 5};
// for indexing into data structures
const int White = 0;
const int Black = 1;
// length 2, taken[White] is the map of pieces to quantity that white has taken from Black
extern std::vector< std::unordered_map< pieceType, int > > takenPieces;
extern std::vector< std::vector< pieceType > > board;

extern int move;
