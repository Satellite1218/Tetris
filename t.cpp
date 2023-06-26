/*
W : 회전 S : 빨리 떨어트리기
A : 왼쪽이동, D : 오른쪽 이동
Q : 게임종료
*/
#pragma warning(disable:4996)
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

int board[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
int currentPiece[4][4] = { 0 };
int currentPieceX = 0;
int currentPieceY = 0;
int score = 0;

int pieces[7][4][4] = {
    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
    {{1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // J
    {{1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // L
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // O
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // S
    {{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}  // Z
};

void drawBoard() {
    system("cls");
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j])
                printf("[]");
            else
                printf("  ");
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

int checkCollision(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece[i][j] && (board[y + i][x + j] || x + j < 0 || x + j >= BOARD_WIDTH || y + i >= BOARD_HEIGHT))
                return 1;
        }
    }
    return 0;
}

void mergePiece() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece[i][j])
                board[currentPieceY + i][currentPieceX + j] = 1;
        }
    }
}

void checkLines() {
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
        int fullLine = 1;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (!board[i][j]) {
                fullLine = 0;
                break;
            }
        }
        if (fullLine) {
            score += 10;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    board[k][j] = board[k - 1][j];
                }
            }
            i++;
        }
    }
}

void rotatePiece() {
    int tempPiece[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tempPiece[i][j] = currentPiece[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            currentPiece[i][j] = tempPiece[3 - j][i];
        }
    }

    if (checkCollision(currentPieceX, currentPieceY)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentPiece[i][j] = tempPiece[i][j];
            }
        }
    }
}

void movePiece(int deltaX, int deltaY) {
    if (!checkCollision(currentPieceX + deltaX, currentPieceY + deltaY)) {
        currentPieceX += deltaX;
        currentPieceY += deltaY;
    }
}

void generatePiece() {
    int pieceIndex = rand() % 7;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            currentPiece[i][j] = pieces[pieceIndex][i][j];
        }
    }
    currentPieceX = BOARD_WIDTH / 2 - 2;
    currentPieceY = 0;
}

int main() {
    srand(time(NULL));

    while (1) {
        drawBoard();
        if (checkCollision(currentPieceX, currentPieceY + 1)) {
            mergePiece();
            checkLines();
            generatePiece();
            if (checkCollision(currentPieceX, currentPieceY)) {
                break;
            }
        }
        else {
            movePiece(0, 1);
        }

        if (_kbhit()) {
            char key = _getch();
            switch (key)
            {
            case 'a':
                movePiece(-1, 0);
                break;
            case 'd':
                movePiece(1, 0);
                break;
            case 's':
                movePiece(0, 1);
                break;
            case 'w':
                rotatePiece();
                break;
            case 'q':
                exit(0);
                break;
            }
        }
        Sleep(100);
    }

    printf("Game Over\n");
    return 0;
}