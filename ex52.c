#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define BOARD_ROW 20
#define BOARD_HEIGHT 20
#define BLOCK '*'
#define BLANK ' '



void changeState();

void moveDown();

void moveLeft();

void moveRight();

void displayBoard();

typedef enum State {STANDING, LAYING} State;

typedef struct Position{
    int x;
    int y;
} Position;

typedef struct Shape{
    State state;
    Position position;
} Shape;

int main() {
    displayBoard();
    return 0;
}

void displayBoard() {
    char board[BOARD_ROW][BOARD_HEIGHT];
    int i, j;
    for (i = 0; i < BOARD_ROW; i++) {
        for (j = 0; j < BOARD_HEIGHT; j++) {
            if (j == 0 || j == BOARD_HEIGHT - 1 || i == BOARD_ROW - 1) {
                board[i][j] = BLOCK;
            } else {
                board[i][j] = BLANK;
            }

        }
    }
    /*
     *  THE PRINT OF THE BOARD ITELSE
     */
    for (i = 0; i < BOARD_ROW; i++) {
        for (j = 0; j < BOARD_HEIGHT; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void signal_hand(int sig) {
    char c;
    scanf("%c", &c);
    switch (c) {
        case 'a':
            moveLeft();
            break;
        case 's':
            moveDown();
            break;
        case 'd':
            moveRight();
            break;
        case 'w':
            changeState();
            break;
        case 'q':
            exit(0);
        default:
            break;
    }
    displayBoard();
    signal(SIGUSR2, signal_hand);
}

void changeState() {

}

void moveDown() {

}

void moveLeft() {

}

void moveRight() {

}
