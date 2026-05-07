#include <stdio.h>
#include <conio.h>  // Windows e
#include <windows.h> // Sleep() ar gotoxy() er jonno
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

// Snake er position, food, score etc variables

int main() {
    // Game loop
    while(!gameOver) {
        draw();      // Map + snake + food draw
        input();     // Arrow key detect
        logic();     // Move, eat, collision
        Sleep(speed); // Level onujayi
    }
    return 0;
}
