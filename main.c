#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

// 3x3 => 9 squares x 1 bit per square => 9 bits => 16 bit number
// 2 boards for full state:
//   1 for X's
//   1 for O's
typedef uint16_t player_t;

struct board_t {
    player_t player1;
    player_t player2;
};

#define IS_SET(board, bit) ((board) & (1 << (bit)))
#define SET(board, bit) ((board) |= (1 << (bit)))

/*
 X | X | X 
-----------
 O | O | O
-----------
 X | X | X
*/

void print_board(struct board_t board)
{
    int i = 0;
    for (; i < 9; ++i) {
        if (IS_SET(board.player1, i)) {
            printf(" X ");
        }
        else if (IS_SET(board.player2, i)) {
            printf(" O ");
        }
        else {
            printf("   ");
        }

        if (i == 2 || i == 5) {
            printf("\n-----------\n");
        }
        else if (i == 8) {
            printf("\n");
        }
        else {
            printf("|");
        }
    }
}

int get_move(struct board_t board) {
    char* line = 0;
    size_t n = 0;
    int ret;

    printf("Enter a move: ");
    ret = getline(&line, &n, stdin);
    if (ret < 1) {
        printf("getline failed!\n");
        return -1;
    }
    else {
        ret = line[0];
        free(line);
        if (isdigit(ret)) {
            ret = ret - '0' - 1;
            if (ret < 0) {
                return -1;
            }
            else {
                return IS_SET(board.player1 | board.player2, ret) ? -1 : ret;
            }
        }
        return -1; 
    }
}

int main(int argc, char **argv)
{
    struct board_t board;
    int move;
    int turn;
    int i;

    board.player1 = 0;
    board.player2 = 0;
    turn = 0;

    for (i = 0; i < 2; ++i) {

        print_board(board);

        while ((move = get_move(board)) == -1) {
            printf("Invalid move!\n");
        }

        if (turn) {
            SET(board.player1, move);
        }
        else {
            SET(board.player2, move);
        }

        turn ^= 1;

    }

    print_board(board);
    printf("Bye.\n");

    return 0;
}
