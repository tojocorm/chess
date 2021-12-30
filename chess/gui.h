#ifndef GUI_H
#define GUI_H

#include "globals.h"

// prints the board from the perspective of turn
void print_board(const int turn);
// prints a specific square on the board
void print_space(pieceType type);

void pieces_taken(int this_turn);
#endif
