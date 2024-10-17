# 🎮 The Mighty Game Of 2048

## Overview
Welcome to **The Mighty Game Of 2048**—my unique take on the classic 2048 game. This version includes a game menu, control displays, music, and auto-move animations, all wrapped in a terminal-based package. Achieve the ultimate goal by reaching 2048, but beware of the loss condition where no valid moves are left!

## 🚀 Features

### Fast Response Time
- **Graphics and UI**: Uses the `curses` library for sleek terminal-based graphics, showcasing the game grid, menu, and controls.
- **Game Menu**: Options to start a new game, resume a paused game, or quit.
- **Controls Display**: Information on movement, game, and music controls.
- **Auto-Move Animation**: Animated arrows indicating the next automatic move direction.
- **Music**: Background tunes with mute/unmute, skip forward, and go back options. Powered by:
  - `SDL2/SDL.h`
  - `SDL2/SDL_mixer.h`
- **Time Display**: Current date and time in the upper right corner, using `time.h`.
- **Game Logic**: Core mechanics including tile movements, merging, random tile generation, and win/lose conditions.
- **Auto-Move**: Automatic moves if user input isn't detected after a set period.

## 🎮 How to Play

### Run
1. Execute the MAKEFILE.
2. Run `./2048`.

### Menu Navigation
- Use arrow keys to navigate the menu.
- Press `Enter` to select an option.

### Gameplay
- Move tiles with `W`, `A`, `S`, `D` keys.
- Press `Q` to access the menu.
- **Music Controls**: 
  - `M` to mute/unmute.
  - `O` to skip back in the playlist.
  - `P` to skip forward.
- **Auto-Move**: The game automatically makes a move after a certain period of inactivity.

## 💡 Acknowledgments
- The music may have a slight delay due to the clock used for AUTO-MOVE.
- The game is best played in a full terminal without other tabs open in Visual Studio Code (VSC).
- Adjust zoom to 9 levels out from maximum zoom-in for optimal display.
- Lines longer than 80 characters may appear due to ASCII art.
- If AUTO-MOVE doesn't work, restart VSC or your laptop—it's an `ncurses` and `SDL` library issue.

## 🛠️ Functions

### Music Functions
- `initMusic`: Starts the music.
- `musicFinished`
- `StopMusic`
- `changeSong`

### Colors
- `initColors`

### Print Functions
- `printCentered`: Centers the given text.
- `printControls`: Displays the control menu for 5 seconds.
- `printMenu`: Prints the menu.
- `displayCurrentTime`: Shows the current time and date, updated every second using `time.h`.
- `prtMat`: Prints the game board.
- `arrows`: Animates an arrow to show the most efficient move direction.

### Game Functions
- `nrElem`: Counts the number of elements in a vector.
- `valid`: Checks if the move is valid.
- `poz`: Places an element in a random empty cell.
- `eMoves`: Checks if the player can make moves.
- `input`: Handles player input, calculates scores, and validates moves.
- `verify`: Determines if the player can make valid moves.
- `commands`: Manages player input, makes moves, controls music, and checks for win/loss conditions.

Try running the code and enjoy your improved 2048 experience!
