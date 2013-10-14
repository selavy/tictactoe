#ifndef __BOARD_H__
#define __BOARD_H__

#include<stdint.h>
#include<stdio.h>

typedef int16_t board;

#define SIZE 9
#define BITSNBRD 16
#define NUMMASKS 8

/*
 0: top lft -> btm rgt
 1: btm lft -> top rgt
 2: top row
 3: mid row
 4: btm row
 5: lft col
 6: mid col
 7: rgt col
*/

static const board MASKS[NUMMASKS] = { 0x54, 0x111, 0x7, 0x38, 0x1c0, 0x124, 0x92, 0x49 };

#define DRAW( x, y ) ( ( ( x ) | ( y ) ) == 0x1ff )
#define ISSET( x, pos ) ( ( x ) >> ( pos ) & 1 )
#define SET( x, pos ) ( ( x ) |= ( 1 << ( pos ) ) )

inline void
clear( board* );

void
print_board( board, board );

int
win( board );

#endif
