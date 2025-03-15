// Snake Game in C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>   // For kbhit() and getch()
#include <windows.h> // For Sleep()

#define WIDTH 20
#define HEIGHT 20
#define MAX_TAIL 100  // Prevents buffer overflow

int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[MAX_TAIL], tailY[MAX_TAIL];
int tailLength;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

void setup() {
    gameOver = 0;
    dir = RIGHT;  // Snake starts moving
    x = WIDTH / 2;
    y = HEIGHT / 2;
    
    srand(time(0));  // Randomize fruit placement
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    tailLength = 0;
}

void draw() {
    system("cls");  // Clear screen (Windows)
    
    for (int i = 0; i < WIDTH + 2; i++) 
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) 
                printf("#");

            if (i == y && j == x)
                printf("O");  // Snake head
            else if (i == fruitY && j == fruitX)
                printf("F");  // Fruit
            else {
                int isTail = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");  // Snake tail
                        isTail = 1;
                        break;
                    }
                }
                if (!isTail) printf(" ");
            }

            if (j == WIDTH - 1) 
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) 
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': gameOver = 1; break;
        }
    }
}

void logic() {
    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default:    break;
    }

    // Wrap around the screen (Snake doesn't die at borders)
    if (x >= WIDTH) x = 0; else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0; else if (y < 0) y = HEIGHT - 1;

    // Check collision with tail
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = 1;
            break;
        }
    }

    // Check fruit collision
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;

        // Grow the tail (limit it to MAX_TAIL)
        if (tailLength < MAX_TAIL) {
            tailLength++;
        }
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100);  // Speed control
    }
    
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}
