#include <stdio.h>
//-------------------
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//------NEW--------
// TIME STUFF
#include <time.h>
#include <unistd.h>
// MUSIC
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
// VISUAL INTERFACE
#include <curses.h>

// defines
#define MUSIC_FILE "MenuMusic.wav"
#define MUSIC_FILE1 "InGameChill.wav"
#define MUSIC_FILE2 "InGameSong2.wav"
#define MUSIC_FILE3 "InGameMusic.wav"
#define MUSIC_FILE4 "EndScreen.wav"
#define MUSIC_FILE5 "Win.wav"
Mix_Music *music = NULL;

// MUSIC
void musicFinished(void)
{
    Mix_PlayMusic(music, 0); // 0 means play once
}

int initMusic(int x)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
        return EXIT_FAILURE;
    }

    if (!x)
        music = Mix_LoadMUS(MUSIC_FILE);
    else if (x == 1)
        music = Mix_LoadMUS(MUSIC_FILE1);
    else if (x == 2)
        music = Mix_LoadMUS(MUSIC_FILE2);
    else if (x == 3)
        music = Mix_LoadMUS(MUSIC_FILE3);
    else if (x == 4)
        music = Mix_LoadMUS(MUSIC_FILE4);
    else if (x == 5)
        music = Mix_LoadMUS(MUSIC_FILE5);

    if (music == NULL)
    {
        fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
        Mix_CloseAudio();
        return EXIT_FAILURE;
    }

    // Set the music volume (adjust as needed)
    Mix_VolumeMusic(100);

    // Set up the callback function for music completion
    Mix_HookMusicFinished(musicFinished);

    // Play the music
    Mix_PlayMusic(music, 1);

    return EXIT_SUCCESS;
}

void StopMusic()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}

// Define color pairs for each power of 2
enum
{
    COLOR_PAIR_0 = 1,
    COLOR_PAIR_1,
    COLOR_PAIR_2,
    COLOR_PAIR_3,
    COLOR_PAIR_4,
    COLOR_PAIR_5,
    COLOR_PAIR_6,
    COLOR_PAIR_7,
    COLOR_PAIR_8,
    COLOR_PAIR_9,
    COLOR_PAIR_10,
    COLOR_PAIR_11,
    COLOR_PAIR_12,
};

void initColors()
{
    // Initialize colors
    start_color();

    // Define color pairs
    init_pair(COLOR_PAIR_0, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_PAIR_1, COLOR_WHITE, COLOR_BLUE);
    init_pair(COLOR_PAIR_2, COLOR_WHITE, COLOR_GREEN);
    init_pair(COLOR_PAIR_3, COLOR_WHITE, COLOR_RED);
    init_pair(COLOR_PAIR_4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(COLOR_PAIR_5, COLOR_WHITE, COLOR_CYAN);
    init_pair(COLOR_PAIR_6, COLOR_WHITE, COLOR_YELLOW);
    init_pair(COLOR_PAIR_7, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_PAIR_8, COLOR_BLACK, COLOR_CYAN);
    init_pair(COLOR_PAIR_9, COLOR_BLACK, COLOR_RED);
    init_pair(COLOR_PAIR_10, COLOR_BLACK, COLOR_YELLOW);
    init_pair(COLOR_PAIR_11, COLOR_BLACK, COLOR_BLUE);
    init_pair(COLOR_PAIR_12, COLOR_BLACK, COLOR_GREEN);
}

// digit number
int nrCif(int x)
{
    int p = 0;
    if (!x)
        return 1;
    else
        while (x)
            p++, x /= 10;

    return p;
}

// takes the exponent of 2
int expon(int x)
{
    int nr = 0;
    while (x)
    {
        x >>= 1;
        nr++;
    }
    return nr;
}

// Center when print
void printCentered(const char *text, int row, int colorPair)
{
    int width, height;
    getmaxyx(stdscr, height, width);

    int start_col = (width - strlen(text)) / 2;

    attron(COLOR_PAIR(colorPair));
    mvprintw(row, start_col, "%s", text);
    attroff(COLOR_PAIR(colorPair));
}

void printMenu(int highlight)
{
    int height, width;
    getmaxyx(stdscr, height, width);

    // Center vertically
    int midH = height / 2 - 5;
    int midW = width / 2 - 5;

    mvprintw(midH - 10, midW - 8, "The Mighty Game Of\n");
    mvprintw(midH - 9, midW - 16, " _______  _______     ___    _____");
    mvprintw(midH - 8, midW - 16, "/ ___   )(  __   )   /   )  / ___ \\ ");
    mvprintw(midH - 7, midW - 16, "\\/   )  || (  )  |  / /) | ( (___) )");
    mvprintw(midH - 6, midW - 16, "    /   )| | /   | / (_) (_ \\     / ");
    mvprintw(midH - 5, midW - 16, "  _/   / | (/ /) |(____   _)/ ___ \\ ");
    mvprintw(midH - 4, midW - 16, " /   _/  |   / | |     ) ( ( (   ) )");
    mvprintw(midH - 3, midW - 16, "(   (__/\\|  (__) |     | | ( (___) )");
    mvprintw(midH - 2, midW - 16, "\\_______/(_______)     (_)  \\_____/ ");

    char *menuOptions[] = {"START ", "RESUME", " QUIT "};

    for (int i = 0; i < 3; i++)
    {
        if (i == highlight)
            attron(A_REVERSE);

        mvprintw(midH + i + 4, midW, "%s", menuOptions[i]);
        midH++;
        if (i == highlight)
            attroff(A_REVERSE);
    }

    refresh();
}

// controll menu
void printControls()
{
    int height, width;
    getmaxyx(stdscr, height, width);

    // Center vertically
    int start_row = height / 2 - 5;
    printCentered("Welcome to The Mighty Game Of 2048", start_row - 4, 1);
    printCentered("Game Menu Controls:", start_row - 3, 1);
    printCentered("UP-KEY - Move Up", start_row - 2, 1);
    printCentered("DOWN-KEY - Move Left", start_row - 1, 1);
    printCentered("Game Controls:", start_row, 1);
    printCentered("W - Move Up", start_row + 2, 1);
    printCentered("A - Move Left", start_row + 3, 1);
    printCentered("S - Move Down", start_row + 4, 1);
    printCentered("D - Move Right", start_row + 5, 1);
    printCentered("Q - Quit", start_row + 7, 1);
    printCentered("Music Controlls:", start_row + 9, 1);
    printCentered("O - Back Music", start_row + 11, 1);
    printCentered("P - Forword Music", start_row + 12, 1);
    printCentered("M - Mute/Unmute", start_row + 13, 1);

    printCentered("Loading...", height - 2, 1);

    refresh();
    // 3 sec sleep
    usleep(3000000);
}

// Function to display the current time
void displayCurrentTime()
{
    time_t currentTime;
    struct tm *localTime;

    // Get the current time
    time(&currentTime);

    // Convert the current time to the local time structure
    localTime = localtime(&currentTime);

    // Get the formatted time and date as strings
    char timeString[9];  // HH:MM:SS + null terminator
    char dateString[11]; // YYYY-MM-DD + null terminator
    strftime(timeString, sizeof(timeString), "%H:%M:%S", localTime);
    strftime(dateString, sizeof(dateString), "%d-%m-%Y", localTime);

    // Display the time and date in the upper right corner
    int height, width;
    getmaxyx(stdscr, height, width);

    // Use these coordinates for displaying the time
    mvprintw(0, width - 20, "Date: %s", dateString);
    mvprintw(1, width - 20, "Time: %s", timeString);
}

// MENU
int Menu(int x)
{
    initMusic(0);

    int highlight = 0;
    int choice = -1;
    int c;

    clear();
    printMenu(highlight);

    while (1)
    {
        c = getch();

        switch (c)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
                highlight = 2;
            break;

        case KEY_DOWN:
            highlight++;
            if (highlight == 3)
                highlight = 0;
            break;

        case 10: // Enter key
            choice = highlight;
            break;

        default:
            break;
        }

        // Print the menu with updated highlight
        printMenu(highlight);

        if (choice != -1)
        {
            break;
        }
    }

    clear();

    if (choice == 0)
    {
        // START
        StopMusic();
        return 0;
    }
    else if (choice == 1)
    {
        StopMusic();
        if (x)
        {
            printw("RESUME option selected (inactive).\n");
            getch();
            return 1;
        }
    }
    else if (choice == 2)
    {
        // QUIT
        StopMusic();
        printw("QUIT option selected. Exiting...\n");
        getch();
        return 2;
    }
    return 0;
}

// verifys if exists more of the same elemnt to determin if there are
// posible moves
void nrElem(int **mat, int *v)
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            v[expon(mat[i][j])]++;
}

void prtMat(int **mat, char *v)
{
    int i, j, x, k = 15, pz = 0, res, h;
    int height, width;
    getmaxyx(stdscr, height, width);

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            // Calculate the position inside the big box
            int y_position = i * 2 + k;
            int x_position = j * 7 + width / 2 - 12;

            // move(x, y) moves the cursor to the specified position
            move(y_position, x_position);

            x = expon(mat[i][j]);

            // Use different color pairs based on the power of 2
            attron(COLOR_PAIR(x));

            // Print the cell border and background
            addch(ACS_ULCORNER);
            for (int l = 0; l < 4; l++)
                addch(ACS_HLINE);

            addch(ACS_URCORNER);

            move(y_position + 1, x_position);

            addch(ACS_VLINE);

            // CELL
            pz = ((6 - nrCif(mat[i][j])) / 2);
            res = 5 - pz;

            for (h = 1; h < pz; h++)
            {
                move(y_position + 1, x_position + h);
                printw(" ");
            }
            printw("%d", mat[i][j]);

            for (h = pz + nrCif(mat[i][j]); h < res + pz; h++)
            {
                move(y_position + 1, x_position + h);
                printw(" ");
            }

            addch(ACS_VLINE);

            move(y_position + 2, x_position);
            addch(ACS_LLCORNER);
            for (int l = 0; l < 4; l++)
                addch(ACS_HLINE);

            addch(ACS_LRCORNER);

            // Turn off color attribute
            attroff(COLOR_PAIR(x));
        }

        // Move the cursor to the next line for the next row of cells
        k++;
    }

    refresh();
}

void copy(int **aux, int **mat)
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            aux[i][j] = mat[i][j];
}

// verifys if the move is valid
int valid(int **aux, int **mat)
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (aux[i][j] != mat[i][j])
                return 1;
    return 0;
}

// pozitions the start numbers
void poz(int **mat)
{
    int val = rand() % 2 == 0 ? 2 : 4;
    int randX = rand() % 4;
    int randY = rand() % 4;

    while (mat[randY][randX] != 0)
    {
        randX = rand() % 4;
        randY = rand() % 4;
    }
    // val = 1024;
    mat[randY][randX] = val;
}

// existent moves
int eMoves(int **mat, int x)
{
    int i, v[13];
    v[12] = 0;
    nrElem(mat, v);

    if (x >= 0)
    {

        if (v[12] > 0)
            return 2;

        // Use the correct array size
        for (i = 0; i < 12; i++)
        {
            if (v[i] >= 1)
                return 1;
        }

        return 0;
    }
    else
    {
        return v[0];
    }
}

// reset matrix
void reset(int **mat)
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            mat[i][j] = 0;

    for (i = 0; i < 3; i++)
        poz(mat);
}

// moves the elements in the direction that was given by the player
// if y=1, it verifys if one move is valid
int input(int x, int z, int **mat, int y, int *score)
{
    // x is the move ID, z is used to veify if the move is valid
    // y is used to switch between just verifying or move
    int i, j, k, nr = 0, ok = 0;
    int e;

    /*
    to verify if the move is valid, I will create a temporary matrix that
    will act like the normal mamtrix, and if, after the move, the temp matrix
    is diferent than the original, the original matrix will take temps value
    */

    int **tmp = (int **)calloc(4, sizeof(int *));
    for (i = 0; i < 4; i++)
        tmp[i] = (int *)calloc(4, sizeof(int));
    copy(tmp, mat);

    while (x < z)
    {
        if (!x)
        { // W
            // move all the elements up, starting from the top
            // e = 0;
            for (i = 1; i < 4; i++)
            {
                // e = 0;
                for (j = 0; j < 4; j++)
                    if (tmp[i][j])
                    {
                        e = 0;
                        k = i;

                        // iff the next caracter is 0, move up
                        while (k - 1 >= 0 && !tmp[k - 1][j])
                        {
                            tmp[k - 1][j] = tmp[k][j];
                            tmp[k][j] = 0;
                            k--;
                        }

                        // if 2 elements are the same while moving
                        if (k - 1 >= 0 && tmp[k - 1][j] == tmp[k][j] && !e)
                            tmp[k - 1][j] <<= 1,
                                *score += tmp[k - 1][j],
                                tmp[k][j] >>= 12,
                                e++,
                                nr++;
                    }
            }
            //------------------------------------------
            if (y)
            {
                if (eMoves(tmp, 0))
                    nr++;
            }
            //-------------------------------------------
        }
        else if (x == 1)
        { // A
            // e = 0;
            for (i = 0; i < 4; i++)
            {
                // e = 0;
                for (j = 1; j < 4; j++)
                {

                    if (tmp[i][j])
                    {
                        e = 0;
                        k = j;

                        while (k - 1 >= 0 && !tmp[i][k - 1])
                        {
                            tmp[i][k - 1] = tmp[i][k];
                            tmp[i][k] = 0;
                            k--;
                            nr++;
                        }

                        if (k - 1 >= 0 && tmp[i][k - 1] == tmp[i][k] && !e)
                        {
                            tmp[i][k - 1] <<= 1;
                            *score += tmp[i][k - 1];
                            tmp[i][k] >>= 12;
                            e++;
                            nr++;
                        }
                    }
                }
            }
            //------------------------------------------
            if (y)
            {
                if (eMoves(tmp, 0))
                    nr++;
            }
            //-------------------------------------------
        }
        else if (x == 2)
        { // S
            // e = 0;
            for (i = 2; i >= 0; i--)
            {
                // e = 0;

                for (j = 0; j < 4; j++)
                    if (tmp[i][j])
                    {
                        e = 0;
                        k = i;
                        while (k + 1 <= 3 && !tmp[k + 1][j])
                        {
                            tmp[k + 1][j] = tmp[k][j];
                            tmp[k][j] = 0;
                            k++;
                        }

                        if (k + 1 <= 3 && tmp[k + 1][j] == tmp[k][j] && !e)
                            tmp[k + 1][j] <<= 1,
                                *score += tmp[k + 1][j],
                                tmp[k][j] >>= 12,
                                e++,
                                nr++;
                    }
            }
            //------------------------------------------
            if (y)
            {
                if (eMoves(tmp, 0))
                    nr++;
            }
            //-------------------------------------------
        }
        else if (x == 3)
        { // D
            // e = 0;

            for (j = 2; j >= 0; j--)
            {

                for (i = 0; i < 4; i++)
                    if (tmp[i][j])
                    {
                        e = 0;
                        k = j;

                        while (k + 1 <= 3 && !tmp[i][k + 1])
                        {
                            tmp[i][k + 1] = tmp[i][k];
                            tmp[i][k] = 0;
                            k++;
                            nr++;
                        }

                        if (k + 1 <= 3 && tmp[i][k + 1] == tmp[i][k] && !e)
                            tmp[i][k + 1] <<= 1,
                                *score += tmp[i][k + 1],
                                tmp[i][k] >>= 12,
                                e++,
                                nr++;
                    }
            }
            //------------------------------------------
            if (y)
            {
                if (eMoves(tmp, 0))
                    nr++;
            }
            //-------------------------------------------
        }
        x++;
    }

    //  Here we'll verify if mat and tmp are differrent and if they are
    if (valid(tmp, mat))
    {
        copy(mat, tmp);
        poz(mat);
        ok = 1;
    }

    for (i = 0; i < 4; i++)
        free(tmp[i]);
    free(tmp);

    // for verifying
    if (nr && y && ok)
    {
        return 1;
    }
    else
        return 0;
}

// verifys if the moves are posible
int verif(int **mat)
{
    int i, j = 1, k = 0, brn = 0, h = 0, w = 0, v[4] = {0}, ok = 0;
    int vf = -1;
    int height, width;
    char keys[] = "WASD";
    getmaxyx(stdscr, height, width);

    h = height / 2 - 5;
    w = width / 2 + 20;

    // Allocate and initialize auxiliary matrix
    int **aux = (int **)calloc(4, sizeof(int *));
    for (i = 0; i < 4; i++)
        aux[i] = (int *)calloc(4, sizeof(int));

    copy(aux, mat);

    mvprintw(h + j, w, "VALID MOVES");
    // Loop through possible moves
    mvprintw(h + 4, w, " ");
    mvprintw(h + 5, w, " ");
    for (i = 0; i < 4; i++)
    {
        if (input(i, i + 1, aux, 1, &brn))
        {
            if (vf != i)
            {
                j++;
                mvprintw(h + j, w, "%c", keys[i]);
                vf = i;
            }
            v[i] = eMoves(aux, -1);
            ok = 1;
        }
        else
        {
            v[i] = 0;
        }
        copy(aux, mat);
    }

    // Free memory for the auxiliary matrix
    for (i = 0; i < 4; i++)
        free(aux[i]);
    free(aux);

    // Find the best move
    if (ok)
    {
        j = k = 0;
        for (i = 0; i < 4; i++)
        {
            if (v[i] > j)
            {
                j = v[i];
                k = i;
            }
        }
        return k + 1;
    }
    else
    {
        // No valid move found
        return 0;
    }
}

void arrows(int nextMove, unsigned long millis)
{
    int height, width;
    getmaxyx(stdscr, height, width);

    switch (nextMove)
    {
    case 1:
        switch (millis)
        {
        case 10000:
            mvprintw(height / 2 - 9, width / 4 + 20, "      ^");
            mvprintw(height / 2 - 9, width / 4 + 20, "     /\\");
            mvprintw(height / 2 - 8, width / 4 + 20, "    /  \\");
            mvprintw(height / 2 - 7, width / 4 + 20, "   /    \\");
            mvprintw(height / 2 - 6, width / 4 + 20, "  /      \\");
            mvprintw(height / 2 - 5, width / 4 + 20, " /        \\");
            mvprintw(height / 2 - 4, width / 4 + 20, "/__      __\\");
            break;

        case 8000:

            mvprintw(height / 2 - 3, width / 4 + 20, "   |    |");
            mvprintw(height / 2 - 2, width / 4 + 20, "   |    |");
            break;

        case 6000:

            mvprintw(height / 2 - 1, width / 4 + 20, "   |    |");
            mvprintw(height / 2, width / 4 + 20, "   |    |");
            break;

        case 4000:
            mvprintw(height / 2 + 1, width / 4 + 20, "   |    |");
            mvprintw(height / 2 + 2, width / 4 + 20, "   |    |");
            break;

        default:
            break;
        }
        break;
    case 2:
        switch (millis)
        {

        case 10000:
            mvprintw(height / 2 + 3, width / 3 + 30, "/|");
            mvprintw(height / 2 + 4, width / 3 + 28, "/");
            mvprintw(height / 2 + 5, width / 3 + 28, "\\");
            mvprintw(height / 2 + 6, width / 3 + 30, "\\|");
            break;

        case 8000:

            mvprintw(height / 2 + 3, width / 3 + 32, "____");
            mvprintw(height / 2 + 5, width / 3 + 32, "____");
            break;

        case 6000:

            mvprintw(height / 2 + 3, width / 3 + 37, "____");
            mvprintw(height / 2 + 5, width / 3 + 37, "____");
            break;

        case 4000:
            mvprintw(height / 2 + 3, width / 3 + 42, "____");
            mvprintw(height / 2 + 5, width / 3 + 42, "____");
            break;

        default:
            break;
        }
        break;
    case 3:
        switch (millis)
        {
        case 10000:
            mvprintw(height / 2 + 2, width / 4 + 20, "      ^");
            mvprintw(height / 2 + 2, width / 4 + 20, "     \\/");
            mvprintw(height / 2 + 1, width / 4 + 20, "    \\  /");
            mvprintw(height / 2, width / 4 + 20, "   \\    /");
            mvprintw(height / 2 - 1, width / 4 + 20, "  \\      /");
            mvprintw(height / 2 - 2, width / 4 + 20, " \\        /");
            mvprintw(height / 2 - 3, width / 4 + 20, "\\          /");
            mvprintw(height / 2 - 4, width / 4 + 20, " __|    |__");
            break;

        case 8000:

            mvprintw(height / 2 - 5, width / 4 + 20, "   |    |");
            mvprintw(height / 2 - 4, width / 4 + 20, "   |    |");
            break;

        case 6000:

            mvprintw(height / 2 - 6, width / 4 + 20, "   |    |");
            mvprintw(height / 2 - 7, width / 4 + 20, "   |    |");
            break;

        case 4000:
            mvprintw(height / 2 - 8, width / 4 + 20, "   |    |");
            mvprintw(height / 2 - 9, width / 4 + 20, "   |    |");
            break;

        default:
            break;
        }

        break;
    case 4:
        switch (millis)
        {

        case 10000:
            mvprintw(height / 2 + 3, width / 3 + 42, "|\\");
            mvprintw(height / 2 + 4, width / 3 + 44, "\\");
            mvprintw(height / 2 + 5, width / 3 + 44, "/");
            mvprintw(height / 2 + 6, width / 3 + 42, "|/");
            break;

        case 8000:

            mvprintw(height / 2 + 3, width / 3 + 37, " ____");
            mvprintw(height / 2 + 5, width / 3 + 37, " ____");
            break;

        case 6000:

            mvprintw(height / 2 + 3, width / 3 + 32, " ____");
            mvprintw(height / 2 + 5, width / 3 + 32, " ____");
            break;

        case 4000:
            mvprintw(height / 2 + 3, width / 3 + 28, "____");
            mvprintw(height / 2 + 5, width / 3 + 28, "____");
            break;

        default:
            break;
        }

        break;

    default:
        break;
    }
}

void changeSong(int *song, int x, int mute)
{
    if (!x)
    {
        if (!mute)
        { // back
            StopMusic();
            --(*song);
            if (!(*song))
                *song = 3;
            x = *song;
            initMusic(x);
        }
    }
    else if (!mute)
    { // forword
        StopMusic();
        ++(*song);
        if (*song == 4)
            *song = 1;
        x = *song;
        initMusic(x);
    }
}

// User input
int commands(int **mat, int *score, int dlc)
{
    initMusic(1);

    char c;
    int i, result, song = 1, mute = 0;
    int height, width;
    getmaxyx(stdscr, height, width);

    // WIN/LOSE
    int x = 0;

    // Initialize curses
    initscr();
    // Hide the cursor
    curs_set(0);
    // Enable keypad input
    keypad(stdscr, TRUE);

    char keys[] = "WASDQ";
    int nextMove = verif(mat);

    // Set non-blocking input
    timeout(0);

    // Auto-move variables
    clock_t begin, end;
    begin = clock();
    end = clock();

    while (nextMove)
    {
        move(0, 0);
        displayCurrentTime();
        // Moves the cursor to the top left corner8
        mvprintw(height / 2 - 12, width / 2 - 4, "SCORE");
        mvprintw(height / 2 - 11, width / 2 - 4, "%d \n", *score);
        printw("\n");
        prtMat(mat, keys);
        refresh();
        displayCurrentTime();

        c = getch();

        // AUTO-MOVE
        if (c == -1)
        {
            end = clock();
            unsigned long millis = (end - begin) * 1000 / CLOCKS_PER_SEC;
            if (millis >= 12000)
            { // 1000 = 1s

                c = keys[nextMove - 1];
                begin = clock();

                // deletet arrows
                if (nextMove == 1 || nextMove == 3)
                {
                    for (i = 7; i >= -10; i--)
                        mvprintw(height / 2 + i, width / 4 + 17,
                                 "                 ");
                }
                else
                    for (i = 2; i <= 7; i++)
                    {
                        mvprintw(height / 2 + i, width / 4 + 20,
                                 "                                         ");
                        mvprintw(height / 2 + i, width / 4 + 29,
                                 "                                         ");
                    }
            }
            else
            {
                arrows(nextMove, millis);
            }
        }
        else
        {
            if (nextMove == 1 || nextMove == 3)
            {
                for (i = 7; i >= -10; i--)
                    mvprintw(height / 2 + i, width / 4 + 17,
                             "                 ");
            }
            else
                for (i = 2; i <= 7; i++)
                {
                    mvprintw(height / 2 + i, width / 4 + 20,
                             "                                         ");
                    mvprintw(height / 2 + i, width / 4 + 29,
                             "                                         ");
                }
        }
        // MOVE EXECUTION
        result = 0;

        // char switch
        switch (toupper(c))
        {
        case 'W':
            result = input(0, 1, mat, 0, score);
            begin = clock();
            break;

        case 'A':
            result = input(1, 2, mat, 0, score);
            begin = clock();
            break;

        case 'S':
            result = input(2, 3, mat, 0, score);
            begin = clock();
            break;

        case 'D':
            result = input(3, 4, mat, 0, score);
            begin = clock();
            break;

        case 'Q':
            // to stop the auto-move
            StopMusic();
            int option = Menu(0);
            if (!option)
            {
                *score = 0;
                reset(mat);
                // to start the auto-move
                initMusic(1);
            }
            else if (option == 1)
            {

                initMusic(1);
            }
            else if (option == 2)
            {
                clear();
                return 0;
            }

            break;
        case 'M':
            if (mute)
                mute--,
                    initMusic(song);
            else
                mute++,
                    StopMusic();
            break;

        case 'O':
            changeSong(&song, 0, mute);
            break;

        case 'P':
            changeSong(&song, 1, mute);
            break;

        default:
            break;
        }

        // WIN SCREEN
        if (eMoves(mat, 1) == 2)
        {
            x = 1;
            break;
        }

        nextMove = verif(mat);
    }
    i = height / 2;
    result = width / 4 - 10;
    if (!x)
    {
        clear();
        // GAME OVER screen
        StopMusic();
        initMusic(4);
        refresh();
        c = 1;

        mvprintw(i - 5, result + 5, "  ________   ________   _____ ______    _______           ________   ___      ___  _______    ________     ");
        mvprintw(i - 4, result + 5, " |\\   ____\\ |\\   __  \\ |\\   _ \\  _   \\ |\\  ___ \\         |\\   __  \\ |\\  \\    /  /||\\  ___ \\  |\\   __  \\    ");
        mvprintw(i - 3, result + 5, " \\ \\  \\___| \\ \\  \\|\\  \\\\ \\  \\\\\\__\\ \\  \\\\ \\   __/|        \\ \\  \\|\\  \\\\ \\  \\  /  / /\\ \\   __/| \\ \\  \\|\\  \\   ");
        mvprintw(i - 2, result + 5, "  \\ \\  \\  ___\\ \\   __  \\\\ \\  \\\\|__| \\  \\\\ \\  \\_|/__       \\ \\  \\\\\\  \\\\ \\  \\/  / /  \\ \\  \\_|/__\\ \\   _  _\\  ");
        mvprintw(i - 1, result + 5, "   \\ \\  \\|\\  \\\\ \\  \\ \\  \\\\ \\  \\    \\ \\  \\\\ \\  \\_|\\ \\       \\ \\  \\\\\\  \\\\ \\    / /    \\ \\  \\_|\\ \\ \\  \\ \\  \\ ");
        mvprintw(i, result + 5, "    \\ \\_______\\\\ \\__\\ \\__\\\\ \\__\\    \\ \\__\\\\ \\_______\\       \\ \\_______\\\\ \\__/ /      \\ \\_______\\ \\__\\ \\__\\");
        mvprintw(i + 1, result + 5, "     \\|_______| \\|__|\\|__| \\|__|     \\|__| \\|_______|        \\|_______| \\|__|/        \\|_______|\\|__|\\|__|");

        refresh();
        // 10sec
        usleep(10000000);
    }
    else
    {

        c = 1;
        clear();
        // GAME OVER scree
        StopMusic();
        initMusic(5);
        refresh();

        mvprintw(i - 5, result + 25, "                            _   _     _   _   U _____ u   ____     ");
        mvprintw(i - 4, result + 25, " __        __      ___     | \\ | |   | \\ | |  \\| ___ |/U |  _ \\ u  ");
        mvprintw(i - 3, result + 25, " \\ \\      / /     |_ _|   <|  \\| |> <|  \\| |>  |  _|    \\| |_) |/   ");
        mvprintw(i - 2, result + 25, " /\\ \\ /\\ / /\\      | |    U| |\\  |u U| |\\  |u  | |___    |  _ <    ");
        mvprintw(i - 1, result + 25, "U  \\ V  V /  U   U/| |\\u   |_| \\_|   |_| \\_|   |_____|   |_| \\_\\   ");
        mvprintw(i, result + 25, ".-,_\\ /\\ /_,-..-,_|___|_,-.||   \\,-. ||   \\,-. <<   >>   //   \\_  ");
        mvprintw(i + 1, result + 25, " \\_)-'  '-(_/  \\_)-' '-(_/ (_ )  (_/ (_ )  (_/(__) (__) (__)  (__) ");

        refresh();
        // 10sec
        usleep(10000000);

        return 1;
    }
    StopMusic();
    return 0;
}

int main()
{
    int **mat, i, menu, score = 0;

    // Initialize curses
    initscr();
    // Hide the cursor
    curs_set(0);
    // Enable keypad input
    keypad(stdscr, TRUE);
    // Don't display input characters
    noecho();
    // Set non-blocking input
    timeout(0);

    // Initialize SDL Mixer and defensive programing
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        fprintf(stderr, " SDL_mixer Error: %s\n", Mix_GetError());
        return EXIT_FAILURE;
    }

    // Initialize colors
    initColors();

    mat = (int **)calloc(4, sizeof(int *));
    for (i = 0; i < 4; i++)
        mat[i] = (int *)calloc(4, sizeof(int));

    srand(time(NULL));

    for (i = 0; i < 3; i++)
        poz(mat);

    displayCurrentTime();

    printControls();
    // START MENU
    menu = Menu(1);
    // Game music

    if (!menu)
        // START GAME
        commands(mat, &score, 0);
    else if (menu == 1)
        menu = Menu(1);
    else if (menu == 2)
    {
        clear();
    }
    else if (menu == 3)
        commands(mat, &score, 1);

    getch();

    // Clean up SDL Mixer
    Mix_CloseAudio();

    for (i = 0; i < 4; i++)
        free(mat[i]);

    free(mat);

    // Clean up curses
    endwin();

    return 0;
}