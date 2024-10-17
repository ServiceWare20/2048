The Mighty Game Of 2048
Overview
This is my unique abordation on the 2048 game. 

 The code includes features like a game menu, controls display, music, 
and auto-move animations. It also has a win condition (reaching 2048)
and a loss condition (no valid moves left).

----------------------------------Features------------------------------------

Fast Response Time

Graphics and UI:
 Utilizes the curses library for terminal-based graphics, displaying the 
game grid, menu, and controls.

Game Menu:
 Offers options to start a new game, resume a paused game, or quit the game.

Controls Display:
 Provides a screen with control information, including movement controls, 
game controls, and music controls.

Auto-Move Animation:
 Displays animated arrows indicating the next automatic move direction.

Music:
 Incorporates background music with options to mute/unmute, go back,
or move forward in the music playlist.
    This feature was possible with the help of the following libraries:
     SDL2/SDL.h
     SDL2/SDL_mixer.h
     

Time Display:
 Shows the current date and time in the upper right corner of the screen.
 This feature was possible with the help of the following libraries:
    time.h

Game Logic: 
Implements the core game logic, including tile movements, merging,
random tile generation, and win/lose conditions.


Auto-Move:
 Automatically makes a move if the user doesn't input any
action after a certain period. The mentioned period is
calculated by subtracting the time from the beginning of the 
input request and the current time and dividing that by the 
time of a cycle. I used timeset(0) to not wait for input.

--------------------------------How to Play-----------------------------------

Run:
 Execute the MAKEFILE and then ./2048.

Menu:
 Use the arrow keys to navigate the menu and press Enter to select an option.

Gameplay:
 During the game, use the 'W', 'A', 'S', and 'D' keys to move tiles. Press 'Q' to access the menu.

Music Controls:
 Press 'M' to toggle mute, 'O' to go back into the music playlist, and 'P' to move forward.

Auto-Move:
 If no input is detected after a certain period, the game will automatically make a move.

Acknowledgments
 + The music won't start exactly at the time of the press, it has a bit of
lab because of the clock used for AUTO-MOVE
 + The game should be played in full terminal, NOT fullscreen, without any
Explorer tab or code tab or other type of tab/partition open in the VSC.
 + The size of the zoom should be 9 times the zoom out from the MAX 
 zoom-in point (zoom in as much as possible and then zoom out 9 times)
 + I have certain lines with more than 80 chr/line because of the ASCII art.
 + If the AUTO-MOVE doesn't work, try restarting the VSC or the laptop.
  This is a problem I've encountered and the ncurses lib causes it
  and SDL lib bugging

----------------------------------Functions-----------------------------------
  ==> Music functions:
    + initMusic- starts the music 
    + musicFinished
    + StopMusic
    + changeSong
  
  ==> Colors:
    *initCokors
  
  ==> Print:
    + printCentered- centers the given text.
    
    + printControls- prints the control menu, that stays on the screen for 5sec.
    
    + printMenu- prints the menu.
    
    + displayCurrentTime- uses the time.h library to take the current Time and
    Date. I put a 1-second sleep to make it wait 1 second until the next call(update).

    + prtMat-prints the board.

    + arrows- it slowly displays an arrow that points in the direction that the
    auto-move decided to be the most efficient move.

  ==> Game:
    + nrElem- gets the nr of elements of each time in a vector.
    
    + valid- verifies if the move is valid(the matrix changes after the move)
    
    + poz- puts an element in a random empty cell.
    
    + eMoves- verifies if the player can make moves.
    
    + input- Input is an interesting concoction I've come up with, hear me out:
    This function does a lot of things.
        ~ if y=0,  it is used  for moving on the matrix.
    else     it is used for verifying if the player can make moves.
        ~ it calculates the score.
        ~ it verifies if the move is valid using  **mat and valid function
      does the moves on a temporary matrix named tmp and if they are 
      different, it copies the tmp matrix in the mat.

    + verify- this function does a lot of hard work too, it verifies if the
    the player can make moves and if those moves are valid, their role is to
    see when the player is blocked(player lost).

    + commands- this function is the solo carry clutch of the game, it does:
        ~ Verifies if the player can make any move.
        ~ Takes the player's input.
        ~ Counts how much the has passed since the game started to listen for
        player input, so the AUTO-MOVE can enter the scene at 12 sec of
        inactivity.
        ~ It makes the moves.
        ~ It takes and manages the controls for music.
        ~ It verifies if the player lost/won and displays the appropriate 
        screen and music for the case.
        
!The MakeFile may not work as expected, excuse me on that, if it bugs, try
running the proper code

    
    
    
    
