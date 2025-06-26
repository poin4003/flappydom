# Flappy Dom

A simple Flappy Bird clone written in C using the Raylib graphics library.

## Overview

Flappy Dom is a classic side-scrolling game where the player controls a green square (Dom) that must navigate through gaps between red and yellow columns. The objective is to survive as long as possible while collecting points.

## Features

- **Simple Controls**: Press spacebar to make Dom jump
- **Physics-based Movement**: Dom falls due to gravity and jumps with velocity
- **Obstacle Generation**: Randomly generated columns with gaps
- **Collision Detection**: Game ends when Dom hits a column or the ground
- **Score System**: Points are awarded based on columns passed
- **Game Over Screen**: Visual feedback when the game ends

## Game Mechanics

- **Dom (Player)**: A 30x30 green rectangle that falls with gravity (1000 units/s²)
- **Jump**: Spacebar applies upward velocity of 300 units/s
- **Columns**: Red (top) and yellow (bottom) rectangles with a 200-pixel gap
- **Movement**: Columns move left at 100 pixels/second
- **Collision**: Game ends if Dom touches any column or falls below the screen

## Project Structure

```
flappydom/
├── main.c          # Main game source code
├── makefile        # Build configuration
├── include/        # Header files
│   └── raylib.h    # Raylib library header
├── lib/            # Library files
│   └── libraylib.a # Raylib static library
├── bin/            # Compiled executable (created during build)
│   └── game.exe    # Game executable
└── README.md       # This file
```

## Dependencies

- **Raylib**: Graphics and game development library
- **GCC**: C compiler
- **Windows Libraries**: OpenGL32, GDI32, WinMM (for Windows builds)

## Building and Running

### Prerequisites

- GCC compiler
- Make utility
- Windows environment (current build configuration)

### Build Instructions

1. Clone or download the repository
2. Navigate to the project directory
3. Run the build command:

```bash
make
```

This will:
- Create the `bin/` directory if it doesn't exist
- Compile `main.c` with optimizations and necessary flags
- Link against Raylib and required Windows libraries
- Automatically run the game after compilation

### Manual Build

If you prefer to build manually:

```bash
mkdir -p bin
gcc main.c -o bin/game.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Clean Build

To remove compiled files:

```bash
make clean
```

## Controls

- **Spacebar**: Make Dom jump
- **Close Window**: End the game

## Code Structure

### Main Components

1. **Dom Structure**: Player character with physics properties
   - Position, velocity, gravity, and jump strength
   
2. **Column Structure**: Obstacle pairs with scoring
   - Two rectangles (top and bottom) with a gap between them
   
3. **Game Loop**: 60 FPS game cycle handling:
   - Input processing
   - Physics updates
   - Collision detection
   - Rendering

### Key Functions

- `InitDom()`: Initialize player character
- `InitCollumn()`: Create new column pair with random gap position
- `updateDom()`: Apply gravity and update position
- `updateCol()`: Move columns left and respawn when off-screen
- `updateJump()`: Apply upward velocity when spacebar is pressed
- `checkCollision()`: Detect collisions between Dom and columns
- `toString()`: Convert integer scores to string for display

## Game Constants

- **Window Size**: 1000x1000 pixels
- **Target FPS**: 60
- **Column Gap**: 200 pixels
- **Column Width**: 50 pixels
- **Column Speed**: 100 pixels/second
- **Dom Size**: 30x30 pixels
- **Gravity**: 1000 pixels/second²
- **Jump Strength**: 300 pixels/second

## Development Notes

- The game uses a fixed timestep with `GetFrameTime()` for smooth movement
- Columns are managed in an array of 5 elements for continuous gameplay
- Random column heights ensure varied gameplay
- Memory management includes dynamic allocation for score display

## Future Enhancements

Potential improvements could include:
- Sound effects and background music
- High score persistence
- Difficulty progression
- Visual effects and animations
- Menu system
- Different character sprites

## License

This project uses Raylib, which is licensed under the zlib/libpng license. Please refer to Raylib's documentation for licensing details.

## Credits

- Built with [Raylib](https://www.raylib.com/) graphics library
- Inspired by the original Flappy Bird game
