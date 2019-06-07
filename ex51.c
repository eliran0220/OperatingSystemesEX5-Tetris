//
// Created by eliran on 6/7/19.
//
#include <stdio.h>
#include <termio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

#define DRAW "./draw.out"
#define EXIT_FAIL -1
#define FAILURE -1
#define ERROR_SIZE 21
#define ERROR_MESSAGE "Error in system call\n"
#define STDERR 2
#define SIZE 2
#define QUIT 'q'
#define W 'w'
#define D 'd'
#define S 's'
#define A 'a'

char getch();

void runCharWriting(int Pipe[SIZE], int pid);

void callDraw(int Pipe[SIZE]);

void displayError();

int main() {
    int Pipe[SIZE];
    int status;
    pid_t pid;
    if (pipe(Pipe) < 0) {
        displayError();
    }
    if ((pid = fork()) < 0) {
        displayError();
    }
    if (pid > 0) {
        runCharWriting(&Pipe[SIZE], pid);
    } else {
        callDraw(&Pipe[SIZE]);
    }
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

void displayError() {
    write(STDERR, ERROR_MESSAGE, ERROR_SIZE);
    exit(EXIT_FAIL);
}

void callDraw(int Pipe[SIZE]) {
    dup2(Pipe[0], 0);
    char *args[SIZE] = {DRAW, NULL};
    if (execvp(args[0], &args[0]) < 0) {
        displayError();
    }
}

void runCharWriting(int Pipe[SIZE], int pid) {
    char c;
    while ((c = getch()) != QUIT) {
        if (c == W || c == D || c == S || c == A) {
            if (write(Pipe[1], &c, 1) == FAILURE) {
                displayError();
            }
        }
    }
    if (kill(pid, SIGUSR2) == FAILURE) {
        displayError();
    }
}





