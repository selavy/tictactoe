#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
#define FULLBOARD(board) (board.player1 | board.player2)
#define CHECK(board, square) (FULLBOARD(board) & (1 << (square)))
#define WIN_I(player, mask) (((player) & (mask)) == (mask))
#define IS_WIN(player) \
    ( \
    WIN_I(player, 0x54)  || \
    WIN_I(player, 0x111) || \
    WIN_I(player, 0x7)   || \
    WIN_I(player, 0x38)  || \
    WIN_I(player, 0x1c0) || \
    WIN_I(player, 0x124) || \
    WIN_I(player, 0x92)  || \
    WIN_I(player, 0x49)     \
    )
/*
 ** Must check that !IS_WIN(board.player1) && !IS_WIN(board.player2) before
 ** calling CATSGAME(board) check
 */
#define CATSGAME(board) (FULLBOARD(board) == 0b111111111)
#define BOARDSZ 9

void print_board(struct board_t board)
{
    /*
     X | X | X 
    -----------
     O | O | O
    -----------
     X | X | X
    */
    int i = 0;
    for (; i < BOARDSZ; ++i) {
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

int ask_for_move(struct board_t board) {
    char* line = 0;
    size_t n = 0;
    int ret;

    printf("Enter a move: ");
    ret = getline(&line, &n, stdin);
    if (ret < 1) {
        exit(0);
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
                return CHECK(board, ret) ? -1 : ret;
            }
        }
        return -1; 
    }
}

int *generate_moves(struct board_t board, int *generated) {
    static int buffer[BOARDSZ];
    int i;
    *generated = 0;
    for (i = 0; i < BOARDSZ; ++i) {
        if (!CHECK(board, i)) {
            buffer[(*generated)++] = i;
        }
    }
    return &(buffer[0]);
}

void create_child(struct board_t *cpy, struct board_t *board, int is_player1, int move) {
    memcpy(cpy, board, sizeof(*board));
    if (is_player1) {
        SET(cpy->player1, move);
    } else {
        SET(cpy->player2, move);
    }
}

int alphabeta(struct board_t board, int is_player1, int depth, int alpha, int beta, char maximizing)
{
    int v = 0;
    int i;
    int *moves;
    int poss;
    int score;
    struct board_t cpy;
    
    if (depth == 0) {
        //TODO(plesslie): evaluate position
        return 0;
    }
    else if (IS_WIN(board.player1)) {
        /* DEBUG */
        printf("Found win for player1!\n");
        print_board(board);
        /* GUBED */
        return is_player1 ? 1 : -1;
    }
    else if (IS_WIN(board.player2)) {
        /* DEBUG */
        printf("Found win for player2!\n");
        print_board(board);
        /* GUBED */
        return is_player1 ? -1 : 1;
    }
    else if (CATSGAME(board)) {
        /* DEBUG */
        printf("Found cats game!\n");
        print_board(board);
        /* GUBED */
        return 0;
    }

    moves = generate_moves(board, &poss);
    assert(poss > 0);

    if (maximizing) {
        v = -1000;
        for (i = 0; i < poss; ++i) {
            create_child(&cpy, &board, is_player1, moves[i]);
            score = alphabeta(cpy, is_player1 ^ 1, depth - 1, alpha, beta, 0);
            v = score > v ? score : v;
            alpha = alpha > v ? alpha : v;
            if (beta <= alpha) {
                break;
            }
        }
    }
    else {
        v = 1000;
        for (i = 0; i < poss; ++i) {
            create_child(&cpy, &board, is_player1, moves[i]);
            score = alphabeta(cpy, is_player1 ^ 1, depth - 1, alpha, beta, 1);
            v = score < v ? score : v;
            beta = v < beta ? v : beta;
            if (beta < alpha) {
                break;
            }
        }
    }

    return v;
}


int choose_move(struct board_t board, char is_player1) {
    int *moves;
    int poss;
    int best;
    int move;
    int i;
    int score;
    struct board_t cpy;

    moves = generate_moves(board, &poss);
    assert(poss > 0);

    best = 0;
    move = moves[0];

    for (i = 0; i < poss; ++i) {
        create_child(&cpy, &board, is_player1, moves[i]);
        score = alphabeta(cpy, is_player1, 9, -10000, 10000, 1);
        if (score > best) {
            best = score;
            move = moves[i];
        }
    }

    /* DEBUG */
    printf("Best move's score was: %d\n", score);
    /* GUBED */
    return move;
}

/* get_human_player_choice(): ask if the player would like to move first
 ** 1  => human moves first
 ** 0  => ai moves first
 ** -1 => error
 */
int get_human_player_choice() {
    char* line = 0;
    size_t n = 0;
    int ret;
    printf("Would you like to move first? ");
    ret = getline(&line, &n, stdin);
    if (ret < -1) {
        return -1;
    }
    else if (line[0] == 'y' || line[0] == 'Y') {
        return 1;
    }
    else {
        return 0;
    }
}

int get_move(struct board_t board, int human_player, int turn) {
    int move;
    if (human_player == turn) {    
        while ((move = ask_for_move(board)) == -1) {
            printf("Invalid move!\n");
        }
    }
    else {
        move = choose_move(board, human_player != 1);
    }
    return move;
}

int main(int argc, char **argv)
{
    struct board_t board;
    int move;
    int turn;
    int i;
    int human_player;

    board.player1 = 0;
    board.player2 = 0;
    turn = 1;

    human_player = get_human_player_choice();
    if (human_player == -1) {
        exit(0);
    }

    for (i = 0; i < 9; ++i) {
        print_board(board);
        if (turn) {
            move = get_move(board, human_player, turn);
            SET(board.player1, move);

            if (IS_WIN(board.player1)) {
                printf("Player #1 wins!\n");
                break;
            }
        }
        else {
            move = get_move(board, human_player, turn);
            SET(board.player2, move);

            if (IS_WIN(board.player2)) {
                printf("Player #2 wins!\n");
                break;
            }
        }
        turn ^= 1;
        if (CATSGAME(board)) {
            printf("Cat's game!\n");
        }
    }

    print_board(board);
    printf("Bye.\n");

    return 0;
}
