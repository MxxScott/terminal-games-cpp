#include <iostream>
#include <conio.h> // For _getch() on Windows
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 20, HEIGHT = 20;
char grid[HEIGHT][WIDTH];
int pacX, pacY, ghostX1, ghostY1, ghostX2, ghostY2, score = 0;
bool gameOver = false;
int ghostMoveCounter = 0; // Counter for ghost movement pattern

void InitGame() {
    srand(time(0));
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1 || 
                (i % 4 == 0 && j % 4 != 0) || (j % 6 == 0 && i % 6 != 0))
                grid[i][j] = '#';  // Symmetrical maze walls
            else
                grid[i][j] = '.';  // Pellets
        }
    }
    pacX = WIDTH / 2;
    pacY = HEIGHT / 2;
    grid[pacY][pacX] = 'P';
    ghostX1 = 1; ghostY1 = 1;
    ghostX2 = WIDTH - 2; ghostY2 = HEIGHT - 2;
    grid[ghostY1][ghostX1] = 'G';
    grid[ghostY2][ghostX2] = 'G';
}

void PrintGrid() {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void MovePacman(char direction) {
    int newX = pacX, newY = pacY;
    if (direction == 'w') newY--;
    if (direction == 's') newY++;
    if (direction == 'a') newX--;
    if (direction == 'd') newX++;
    if (grid[newY][newX] == '#') return;  // Can't move into walls
    if (grid[newY][newX] == '.') score++; // Eat pellet
    grid[pacY][pacX] = ' ';
    pacX = newX; pacY = newY;
    grid[pacY][pacX] = 'P';
}

void MoveGhost(int &ghostX, int &ghostY) {
    if (ghostMoveCounter % 5 < 2) {  // Follow Pac-Man for two moves, then random for three
        int bestX = ghostX, bestY = ghostY;
        int minDist = abs(pacX - ghostX) + abs(pacY - ghostY);
        int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        for (int i = 0; i < 4; i++) {
            int newX = ghostX + directions[i][0];
            int newY = ghostY + directions[i][1];
            int newDist = abs(pacX - newX) + abs(pacY - newY);
            if (grid[newY][newX] != '#' && newDist < minDist) {
                bestX = newX;
                bestY = newY;
                minDist = newDist;
            }
        }
        grid[ghostY][ghostX] = ' ';
        ghostX = bestX; ghostY = bestY;
    } else {  // Move randomly for three moves
        int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        int randomDir = rand() % 4;
        int newX = ghostX + directions[randomDir][0];
        int newY = ghostY + directions[randomDir][1];
        if (grid[newY][newX] != '#') {
            grid[ghostY][ghostX] = ' ';
            ghostX = newX; ghostY = newY;
        }
    }
    grid[ghostY][ghostX] = 'G';
    ghostMoveCounter++;
}

void CheckGameOver() {
    if ((pacX == ghostX1 && pacY == ghostY1) || (pacX == ghostX2 && pacY == ghostY2)) {
        gameOver = true;
    }
}

void Menu() {
    system("cls");
    cout << "================= PAC-MAN =================\n";
    cout << "1. Start Game\n";
    cout << "2. Quit\n";
    cout << "Use WASD to move. Press Q to quit during the game.\n";
    cout << "==========================================\n";
    cout << "Enter your choice: ";
    char choice;
    cin >> choice;
    if (choice != '1') exit(0);
}

void PlayGame() {
    while (!gameOver) {
        PrintGrid();
        if (_kbhit()) {
            char move = _getch();
            if (move == 'q') break;
            MovePacman(move);
            MoveGhost(ghostX1, ghostY1);
            MoveGhost(ghostX2, ghostY2);
            CheckGameOver();
        }
    }
    system("cls");
    cout << "Game Over! Final Score: " << score << endl;
}

int main() {
    Menu();
    InitGame();
    PlayGame();
    return 0;
}