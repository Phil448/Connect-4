#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct board{
  char posn[6][7];
};
// these are constant board dimensions
const int X = 7;
const int Y = 6;

// print_board(cur_board)
// effects: prints accepts and prints out a connect 4 board
void print_board(struct board cur_board) {

  for (int i = 0; i < 6; ++i) {
    printf("|");
    for (int j = 0; j < 7; ++j) {
      printf("%c|",cur_board.posn[i][j]);
    }
    printf("\n");
  }
  printf(" 0 1 2 3 4 5 6\n\n");
}
// board_create(): creates and returns an empty boars
// effects: creates a board
struct board create_board (void) {
  struct board curr_board;
  for (int i = 0; i < Y; ++i) {
    for (int j = 0; j < X; ++j) {
      curr_board.posn[i][j] = '_';
    }
  }
  return curr_board;
}

// make_play(symbol, column, curr_board): this functitons accepts
// a move from a player and updated the game board accordingly
// effercts: may manipulate curr_board
void make_play(char symbol, int column, struct board *curr_board) {

  for (int i = Y - 1; i >= 0; --i) {
    if (curr_board->posn[i][column] == '_') {
      curr_board->posn[i][column] = symbol;
      break;
    }
  }
}



// horizontal_win(player, curr_board): checks to see if the player
// has won the game via a horizontal connect 4
bool horizontal_win (char player, struct board *curr_board) {
  for (int i = 0; i < Y; ++i){
    for (int j = 0; j < 4; ++j) {
      if (curr_board->posn[i][j] == player &&
          curr_board->posn[i][j + 1] == player &&
          curr_board->posn[i][j + 2] == player &&
          curr_board->posn[i][j + 3] == player) {
        return true;
      }
    }
  }
  return false;
}

// vertical_win(player, curr_board): checks to see if the player
// has won the game via a vertival connect 4
bool vertical_win (char player, struct board *curr_board) {
  for (int i = 0; i < 3; ++i){
    for (int j = 0; j < X; ++j) {
      if (curr_board->posn[i][j] == player &&
          curr_board->posn[i + 1][j] == player &&
          curr_board->posn[i + 2][j] == player &&
          curr_board->posn[i + 3][j] == player) {
        return true;
      }
    }
  }
  return false;
}

// diagonal_win_l(player, curr_board): checks to see if the player
// has won the game via a diagonal connect 4
bool diagonal_win_l (char player, struct board *curr_board) {
  for (int i = 0; i < 3; ++i){
    for (int j = 0; j < 4; ++j) {
      if (curr_board->posn[i][j] == player &&
          curr_board->posn[i + 1][j + 1] == player &&
          curr_board->posn[i + 2][j + 2] == player &&
          curr_board->posn[i + 3][j + 3] == player) {
        return true;
      }
    }

  }
  return false;
}


// diagonal_win_l(player, curr_board): checks to see if the player
// has won the game via a diagonal connect 4 (bottom left to top
// right)
bool diagonal_win_r(char player, struct board *curr_board) {
  for (int i = 0; i < 3; ++i){
    for (int j = 3; j <= 6; ++j) {
      if (curr_board->posn[i][j] == player &&
          curr_board->posn[i - 1][j - 1] == player &&
          curr_board->posn[i - 2][j - 2] == player &&
          curr_board->posn[i - 3][j - 3] == player) {
        return true;
      }
    }
  }
  return false;
}


int main(void) {
  struct board curr_board = create_board();
  char symbol = 'a';
  int column = 0;
  int count = 0;

  print_board(curr_board);
  while (true) {
    printf("please enter a player code (X / O)\n");
    if (scanf(" %c", &symbol) != 1) {
      printf("ERROR: cannot read player code\n");
      break;
    }
    printf("player code: '%c'\n", symbol);
    printf("please enter a player slot (0, 1, 2, 3 ...6)\n");
    if (scanf("%d", &column) != 1) {
      printf("ERROR: cannot read slot number\n");
      break;

    }

    if (symbol != 'X' && symbol != 'O') {
      printf("ERROR: invalid player code: %c\n", symbol);
      break;
    }
    // checks if the input is outside the range 0 - 6
    if (column > 6 || column < 0) {
      printf("ERROR: cannot read slot number\n");
      break;
    }
    // checks if the column is full
    if (curr_board.posn[0][column] != '_') {
      printf("ERROR: invalid slot number: %d\n", column);
      break;
    }

    // makes a player move
    make_play(symbol, column, &curr_board);
    print_board(curr_board);
    ++count;

    if (horizontal_win(symbol, &curr_board)) {
      printf("Victory! Player %c has won!\n", symbol);
      break;
    }
    if (vertical_win(symbol, &curr_board)) {
      printf("Victory! Player %c has won!\n", symbol);
      break;
    }
    if (diagonal_win_l(symbol, &curr_board)) {
      printf("Victory! Player %c has won!\n", symbol);
      break;
    }
    if (diagonal_win_r(symbol, &curr_board)) {
      printf("Victory! Player %c has won!\n", symbol);
      break;
    }
    if (count >= (X * Y)) {
      printf("Draw! No player has won!\n");
      break;
    }
  }
  return EXIT_SUCCESS;
}
