#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 50
#define HEIGHT 20
#define MAX_LENGTH 100

typedef struct Point {
    int x, y;
} Point;

typedef struct Snake {
    Point body[MAX_LENGTH];
    int length;
    int dx, dy;        // direction
} Snake;

// Global variables
Snake snake;
Point food;
Point bonusFood;
int score = 0;
int highScore = 0;
int level = 1;
int speed = 150;
int gameOver = 0;
int bonusActive = 0;
clock_t bonusTimer;

// Function declarations
void setup();
void draw();
void input();
void logic();
void saveHighScore();
void loadHighScore();
void generateFood();
void generateBonusFood();

int main() {
    loadHighScore();
    setup();
    
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(speed);
    }
    
    printf("\n\nGame Over! Score: %d\n", score);
    if (score > highScore) {
        highScore = score;
        saveHighScore();
        printf("NEW HIGH SCORE!!!\n");
    }
    return 0;
}
