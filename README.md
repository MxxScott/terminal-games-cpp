# terminal-games-cpp

Two classic arcade games built from scratch in C++ for the Windows terminal — no external libraries, no game engines. Just raw C++ logic.

## Games

### Snake
`snake/snake.cpp`

Terminal Snake with a difficulty menu (Easy / Medium / Hard / Custom ms), growing tail, food spawning, and wall/self-collision detection.

**Controls:** `W A S D` to move · `Q` to quit

**Compile:**
```bash
g++ snake/snake.cpp -o snake.exe
./snake.exe
```

### Pac-Man
`pacman/pacman.cpp`

Terminal Pac-Man with a procedurally generated maze, pellet scoring, and two ghosts using a hybrid AI: they chase Pac-Man using Manhattan distance minimisation for two moves, then move randomly for three — giving them unpredictable but non-trivial behaviour.

**Controls:** `W A S D` to move · `Q` to quit

**Compile:**
```bash
g++ pacman/pacman.cpp -o pacman.exe
./pacman.exe
```

## Requirements

- Windows (uses `<conio.h>` and `<windows.h>` for keyboard input and `Sleep()`)
- Any C++11-compatible compiler (MSVC, MinGW, Clang on Windows)

## Notes

These were built as exercises in game loop architecture, grid-based collision detection, and rudimentary AI movement. No SDL, no SFML — everything rendered with `cout`.
