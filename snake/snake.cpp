#include <iostream>
#include <conio.h>  // For kbhit() and getch() (Windows only)
#include <windows.h> // For Sleep() (Windows only)

using namespace std;

// Game settings
const int width = 20;
const int height = 10;
bool gameOver;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
int gameSpeed = 200; // Default speed in milliseconds

void Setup() {
    gameOver = false;
    dir = STOP;  // Snake starts stationary
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls"); // Clear screen

    // Top border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Game area
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";  // Left border

            if (i == y && j == x)
                cout << "O";  // Snake head
            else if (i == foodY && j == foodX)
                cout << "+";  // Food
            else {
                bool tailPrinted = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Snake tail
                        tailPrinted = true;
                    }
                }
                if (!tailPrinted) cout << " ";  // Empty space
            }

            if (j == width - 1) cout << "#";  // Right border
        }
        cout << endl;
    }

    // Bottom border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {  // Check if a key is pressed
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'q': gameOver = true; break; // Quit game
        }
    }
}

void Logic() {
    // Move tail
    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move head
    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        case STOP: break; // Do nothing when the game starts
    }

    // Collision detection
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // Check if snake hits itself
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // Check if food is eaten
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++; // Grow snake
    }
}

// Function to display the menu and set difficulty
void ShowMenu() {
    int choice;
    system("cls");
    cout << "========================\n";
    cout << "   Welcome to SNAKE!   \n";
    cout << "========================\n";
    cout << "Controls: \n";
    cout << " - Move: W A S D\n";
    cout << " - Quit: Q\n\n";
    
    cout << "Choose difficulty:\n";
    cout << "1. Easy   (Speed: Slow)\n";
    cout << "2. Medium (Speed: Normal)\n";
    cout << "3. Hard   (Speed: Fast)\n";
    cout << "4. Custom (Enter speed in ms)\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: gameSpeed = 300; break; // Slow
        case 2: gameSpeed = 200; break; // Normal
        case 3: gameSpeed = 100; break; // Fast
        case 4:
            cout << "Enter speed (in milliseconds, lower = faster): ";
            cin >> gameSpeed;
            break;
        default:
            cout << "Invalid choice, defaulting to Medium.\n";
            gameSpeed = 200;
    }
}

int main() {
    ShowMenu();
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(gameSpeed); // Adjust game speed
    }
    cout << "Game Over!\n";
    return 0;
}
