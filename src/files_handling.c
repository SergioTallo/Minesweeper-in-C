/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/struct_declaration.h"
#include "../include/memory_allocation.h" //Functions: memoryallocationboard, memoryallocationcell
#include "../include/saved_games.h" //Function: userinput

/**\file files_handling.c
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Every function that has something to do with files: Open, write, read...
 *
 */

/**
 * \brief Close a file.
 * Error message if the file is not closed succesfully
 *
 * \param pFile File pointer to the file you want to close
 */
void closefile (FILE **pFile){

    if (fclose(*pFile) != 0) {
        fprintf(stderr, "fclose not successful!\n");
        exit(1);
    }
}

/**
 * \brief Open a file with reading privileges.
 *
 * \param pFile File pointer to the file you want to open
 * \param filename File name of the file you want to open
 */
void openfileread (FILE **pFile, char *filename){

    *pFile = fopen(filename,"rb");

    /************************************************************************************************
     *  If there is no file with this filename tell the user there is no player with this name,     *
     *  and asked if it should create a new one.                                                    *
     ************************************************************************************************/

    if (*pFile == NULL){
        char input[50];
        char aux;
        do{
            do{
                printf("\nThere is no saved player named %s, do you want to create a new one?", filename);
                userinput(input);
                if (strlen(input)>2){
                    printf("Input incorrect (allowed input (y/n)\n");
                }
            }while (strlen(input)>2);
            aux = input[0];
            if (aux != 'y' && aux != 'Y' && aux != 'n' && aux != 'N'){
                printf("Input incorrect (allowed input (y/n)\n");
            }
        }while (aux != 'y' && aux != 'Y' && aux != 'n' && aux != 'N');

        if ((aux == 'n' || aux == 'N') && *pFile == NULL){
            fprintf(stderr, "\nError opening file\n");
            exit(1);
        }
    }
}

/**
 * \brief Open a file with writing privileges
 * Error message if the File could not be opened properly
 *
 * \param pFile File pointer to the file you want to open
 * \param filename File pointer to the file you want to open
 */
void openfilewrite (FILE **pFile, char *filename){

    *pFile = fopen(filename,"wb");

    if (*pFile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
}

/**
 * \brief Write the actual board status in a file.
 *
 * \param pFile File pointer to the file in which you want to save the board status
 * \param board The struct where all variables of the game are
 */
void writeboardfile (FILE **pFile, struct game board) {

    ///Write every board game's row individually with a for loop.
    for(unsigned long i = 0; i < board.height +2; i++){
        for(unsigned long j = 0; j < board.width +2; j++){
            size_t ret2 = fwrite(&board.minefield[i][j], 1, sizeof(struct cell), *pFile);

            if (ret2 != sizeof(struct cell)) {
                fprintf(stderr, "FILE NOT WRITTEN");
            }
        }
    }
}

/**
 * \brief Write the statistics of the player in a file
 * (also the height and width of the last game)
 *
 * \param pFile File pointer to the file in which you want to save the player stats
 * \param board The struct where all variables of the game are
 */
void writeplayerfile (FILE **pFile, struct game board) {
    size_t ret = fwrite(&board, 1, sizeof(struct game), *pFile);

    if (ret != sizeof(struct game)) {
        fprintf(stderr, "FILE NOT WRITTEN");
    }
}

/**
 * \brief Read the player's statistics from a file.
 *
 * \param pFile File pointer to the file from where you want to read the player stats
 * \param board The struct where all variables of the game are
 */
void readplayerfile (FILE **pFile, struct game *board){

    struct game buffer2;

    fread(&buffer2, sizeof(struct game), 1, *pFile);

    board->gameslost = buffer2.gameslost;
    board->gameswon = buffer2.gameswon;
    board->gamesplayed = buffer2.gamesplayed;
    board->openedcells = buffer2.openedcells;
    board->finishedflag = buffer2.finishedflag;
    board->mines = buffer2.mines;
    board->mineflag = 0;
    board->winflag = 0;
}

/**
 * \brief Read the board status of the last saved game
 *
 * \param pFile File pointer to the file from where you want to read the player stats
 * \param pFile1 File pointer to the file from where you want to read the board stats
 * \param board The struct where all variables of the game are
 */
void readboardfile (FILE **pFile, FILE **pFile1, struct game *board){

    /*******************************************************************************************************************
    * First read the height and width of the last board from the player file, than read the last status of the board   *
    * from the board file. Every row individually with a for loop.                                                     *
    ********************************************************************************************************************/

    struct game buffer;

    fread(&buffer, sizeof(struct game), 1, *pFile);

    board->width = buffer.width;
    board->height = buffer.height;

    memoryallocationboard(board);

    struct cell bufferboard;

    memoryallocationcell(board);

    for(unsigned long i = 0; i < board->height+2; i++){
        for(unsigned long j = 0; j < board->width+2; j++){
            fread(&bufferboard, sizeof(struct cell), 1, *pFile1);
            board->minefield[i][j] = bufferboard;
        }
    }
}
