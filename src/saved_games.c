/************************************************
*   Created by Sergio Tallo Torres on 8.1.20.   *
*************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/files_handling.h" //Functions: openfileread, readplayerfile, closefile, readboardfile, openfilewrite, writeplayerfile, writeboardfile
#include "../include/saved_games.h" //Function: userinput
#include "../include/print_functions.h" //Function: printplayerstatistic
#include "../include/board_defining.h" //Function: newstatistics

/**\file saved_games.c
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Functions that manage save the game and open saved games
 */

/**
 * \brief Ask the player for a Player's name
 *
 * /param board The struct where all variables of the game are
 */
void nametheplayer(struct game *board){

    printf("\n -------------");
    printf("\n| MINESWEEPER |\n");
    printf(" -------------\n");

    char *input; //Variable for the user input in std input
    input = malloc (MAX_INPUT_LENGTH * sizeof(char));

    do {
        printf ("\nPlayer's name: ");
        userinput(input);
        if (strlen(input) > MAX_NAME_LENGTH) {
            printf("Player name too long!\n");
        }
    } while (strlen(input) > MAX_NAME_LENGTH);

    strcpy(board->playername, input);

    printf("Hi %s!\n", board->playername);

    free (input);

}

/**
 * \brief Check if the user has played before.
 *
 * Load his/her statistics and if there is a saved game ask to load it before loading the content.
 *
 * /param board The struct where all variables of the game are
 */
void opensavedgame(struct game *board) {

    /************************************************************************************************************
     *  Read the playername (saved in the struct) and try to open a file .log with the playername as filename   *
     ************************************************************************************************************/

    FILE *playerdata;
    char filename[MAX_NAME_LENGTH + 4];
    strcpy(filename, board->playername);
    strcat(filename,".log");
    openfileread(&playerdata, filename);

    /********************************************************************************************************
     *  If there is a file with the players name, read the statistics and write them in the struct, if not  *
     *  create a new player and set every statistics to zero                                                *
     ********************************************************************************************************/

    if (playerdata != NULL) {

        readplayerfile(&playerdata, board);
        closefile(&playerdata);

    } else {
        newstatistics(board);
    }

    printplayerstatistics (board); //Print the actual players statistics in the stdout


    /************************************************************************************************
     *  If the player has left a saved unfinished game, will be asked to open the last game, if so, *
     *  the last boardgame will be loaded to continue playing where the player has left.            *
     ************************************************************************************************/

    if (board->finishedflag == 0) {

        char *input;
        input = malloc (MAX_INPUT_LENGTH * sizeof(char));
        char aux;

        do {
            do {
                printf("You have a saved game. Do you want to continue? (allowed input (y/n)) ");

                userinput(input);

                if (strlen(input) > 2) {
                    printf("Incorrect input\n\n");
                }
            } while (strlen(input) > 2);

            aux = input[0];

        } while (aux != 'y' && aux != 'Y' && aux != 'n' && aux != 'N');

        if (aux == 'n' || aux == 'N'){
            board->finishedflag = 1;
        }

        if (aux == 'y' || aux == 'Y'){

            FILE *gameboard;
            char filename2[MAX_NAME_LENGTH + 4];
            strcpy(filename2, board->playername);
            strcat(filename2,".dat");

            openfileread(&playerdata, filename);
            openfileread(&gameboard, filename2);
            readboardfile(&playerdata, &gameboard, board);
            closefile(&gameboard);
            closefile(&playerdata);
        }

        free (input);

    } else {
        printf("You have no saved games.\n");
    }
}

/**
 * \brief Manage every user input in the std input
 *
 * \param input char variable für user input in the stdin
 */
void userinput (char *input){
    //User input buffer, big enough to avoid wrong user inputs
    fgets(input, MAX_INPUT_LENGTH, stdin);
    fflush(stdin);
    input[strlen(input) - 1] = '\0';
    printf("\n");
}

/**
 * \brief Save the gameboard and player status in a .dat and a.log file
 *
 * \param board The struct where all variables of the game are
 */
void savegame(struct game board) {

    //First write the player statistics in a .log file with the name of the player
    FILE *playerdata;
    char filename[MAX_NAME_LENGTH + 4];
    strcpy(filename, board.playername);
    strcat(filename,".log");
    openfilewrite(&playerdata, filename);
    writeplayerfile(&playerdata, board);
    closefile(&playerdata);


    //Then write the gameboard in a .dat file with the name of the player
    FILE *gameboard;
    char filename2[MAX_NAME_LENGTH + 4];
    strcpy(filename2, board.playername);
    strcat(filename2,".dat");
    openfilewrite(&gameboard, filename2);
    writeboardfile(&gameboard, board);
    closefile(&gameboard);

}
