#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <cmath>
#include <assert.h>
#include <vector>

using std::cout;
using std::endl;
using std::min;

enum pieceType {Pawn = 1, Bishop = 3, Knight = 3, Rook = 5, Queen = 9, King = 0};

extern std::vector< std::vector< pieceType > > board;