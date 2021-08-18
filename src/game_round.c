/************************************************
*   Created by Sergio Tallo Torres on 7.1.20.   *
*************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/struct_declaration.h"
#include "../include/game_round.h" //Functions: opencell, wincheck
#include "../include/memory_allocation.h" //Functions: freeboardmemory
#include "../include/print_functions.h" //Functions: printgameboard, printplayerstatistics
#include "../include/board_defining.h" //Funtions: minecounting, showmines, eliminatezero
#include "../include/saved_games.h" //Functions: userinput, savegame

/** \file game_round.c
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Here are the functions useful for the actual game round
 */

/**
 * \brief Define, control and execute how a round in the game works.
 *
 * \param board Struct where all the game variables are
 */
void game(struct game *board) {

    /************************************************************************************************************
     *  This four functions manage every game round. And they will repeat till the conditions to win are true   *
     *  In that case, the winflag (win) or the mineflag (lost) will change to true (1)                          *
     ************************************************************************************************************/

    while (board->mineflag == 0 && board->winflag == 0) {
        minecounting(board); //Count how many mines are marked by the user as founded
        printgameboard(board); //Print the actual boardgame state
        opencell(board); //Manage the user's actions in every round
        board->winflag = wincheck(board); //Check if the conditions to win are true
    }
}

/**
 * \brief Function involved in open a board game cell
 *
 * \param board Struct where all the game variables are
 */
void opencell (struct game *board) {

    char *input; //User Input.
    input = malloc(MAX_INPUT_LENGTH * sizeof(char));

    bool rightinput = 1; //Check if the user input is right
    bool minemarker = 0; //To use the function mine marking
    int coordinatey = 0; //Coordinate X to open a cell
    int coordinatex = 0; //Coordinate Y to open a cell

    do {
        rightinput = 1; //The right input is 1 (true) by default and changes to 0 (false) if the input is not right

        do {
            printf("\n");
            printf("Witch cell do you wanna open? (int for game instructions) ");

            userinput(input);

            if (strlen(input) > 4) {
                rightinput = 0; //If the user write an input bigger than 4 characters the input is not right.
                printf("Input incorrect\n");
            }

        } while ((strlen(input) > 4));

        //If the user type int the program will show the game instructions
        if (strcmp(input, "int") == 0 || strcmp(input, "INT") == 0) {
            printf ("To open a cell: Type first the row's number followed with the column's letter (example: 1A)\n");
            printf ("To mark a cell as a founded mine: Type first the row's number followed with the column's letter"
                    " and followed with ? (example: 1A?)\n");
            printf ("Type save to save the game\n");
            printf ("Type stat to show the player's statistics\n");
            printf ("Type exit to end the game (actual game will be saved)\n");
            rightinput = 0;
            continue;
        }

        //If the user type save the player's statistics and the actual gameboard status will be written in files
        if (strcmp(input, "save") == 0 || strcmp(input, "SAVE") == 0) {
            savegame(*board);
            printf ("Game saved!\n");
            rightinput = 0;
            continue;
        }

        //If the user type stat the program will show the player's statistics
        if (strcmp(input, "stat") == 0) {
            printplayerstatistics(board);
            rightinput = 0;
            continue;
        }

        //If the user type exit, the game stops and the program ends.
        if (strcmp(input, "exit") == 0 || strcmp(input, "EXIT") == 0) {
            printf("Thank you for playing\n");
            savegame(*board); //Save the player's statistics and the actual gameboard status
            freeboardmemory(board); //Free the dynamic allocaed memory
            free (input);
            exit(EXIT_SUCCESS); //Ends the program
        }

        /****************************************************************************************
        *   This loop checks if the first inputs are numbers (for the coordinate y) and if so   *
        *   write them as an int in the right variable (coordinatey)                            *
        *****************************************************************************************/

        coordinatey = 0;
        int digits = 0;

        for (int i = 0; i < 5; i++) {
            if (input[i] < '0' || input[i] > '9') {
                if (digits == 0) {
                    digits++;
                }
                break;
            }
            coordinatey *= 10;
            coordinatey += (int) input[i] - '0';
            digits++;
        }
        if (coordinatey < 1 || coordinatey > (int) board->height) {
            printf("\nIncorrect input! First input should be a number between 1 and %d\n", (int) board->height);
            rightinput = 0; //If the user doesn't write a number between 1 and the content height the input is not right
        }

        /****************************************************************************************************
        *   This loop checks if the second input is a letter (for the coordinate x) and if so write them    *
        *   as an int in the right variable (coordinatey).                                                  *
        *****************************************************************************************************/

        char coordinatexchar = input[digits];
        coordinatex = coordinatexchar - 64;

        if (coordinatex < 1 || coordinatex > (int) board->width) {
            printf("\nIncorrect input! Second input should be a letter between A and %c "
                   "(no spaces between first and second input. Case sensitive!)\n", (int) board->width + 64);
            rightinput = 0;
        }


        //If the cell is already open, the inpt is not right
        if (rightinput == 1 && board->minefield[coordinatey][coordinatex].openflag == 1) {
            printf("\nCell already open!\n");
            rightinput = 0;
        }

        //Check if the user start the minemark function (writting ? after the cell coordinates)
        digits++;
        if (input[digits] == '?'){
            minemarker = 1;
        }

    } while (rightinput == 0);

    free (input);

    /******************************************************************************************************************
    *   The program check what kind of cell is the one under the coordinates given by the user, and act consequently  *
    *******************************************************************************************************************/

    if (minemarker == 1) { //If the minemarker is activated the program writes a ? in the given cell
        board->minefield[coordinatey][coordinatex].minemark = 1;

    } else { //If the minemarker is not activated
        board->minefield[coordinatey][coordinatex].openflag = 1; //The cell behind the coordinates
        board->openedcells++;                                    //will be opened (change the openflag to true)

        if (board->minefield[coordinatey][coordinatex].content == 'M') { //If there is a mine behind this coordinates
            board->mineflag = 1;                                         //the board's mineflag variable changes to true
        }                                                                //and the player lost the game

        if (board->minefield[coordinatey][coordinatex].content == '0') { //If there is a zero this cell will be erased
            eliminatezero(board, coordinatex, coordinatey);              //from the board with the other adyacent zeros
        }
    }
}

/**
 * \brief Check at the end of every round if the player has won the game.
 *
 * \param board Struct where all the game variables are
 * \return 1 If the player won the game, 0 if not.
 */
bool wincheck(struct game *board) {

    //Loop to check if every cell without a mine is open
    for (unsigned long i = 1; i < board->height + 1; i++) {
        for (unsigned long j = 1; j < board->width + 1; j++) {
            if (board->minefield[i][j].content != 'M' && board->minefield[i][j].openflag == 0) {
                return 0; //If any cell without a mine is closed the funcion return false (not win)
            }
        }
    }

    //Loop to check if every cell with a mine is marked
    for (unsigned long i = 1; i < board->height + 1; i++) {
        for (unsigned long j = 1; j < board->width + 1; j++) {
            if (board->minefield[i][j].minemark == 1 && board->minefield[i][j].content != 'M') {
                return 0; //If any cell with a mine is not marked the funcion return false (not win)
            }
        }
    }

    return 1;
}

/**
 * \brief hat happened after the player win or loose the game.
 *
 * \param board Struct where all the game variables are
 */
void endofthegame(struct game *board) {

    ///If the player loose the game
    if (board->mineflag == 1 && board->winflag == 0) {
        showmines(board);
        printgameboard(board);
        board->finishedflag = 1;
        printf("\nGame Over!");
        board->gameslost++;
    }

    ///If the player won the game
    if (board->winflag == 1 && board->mineflag == 0) {
        showmines(board);
        printgameboard(board);
        board->finishedflag = 1;
        printf("\nYou won the game!");
        board->gameswon++;
    }

    savegame(*board);
}
