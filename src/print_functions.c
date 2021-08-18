/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#include <stdio.h>
#include "../include/struct_declaration.h"

/**\file print_functions.c
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Functions that printf something in the stdout
 */

/**
 * \brief Print the player statistics in the stdout
 *
 * \param board Struct where all the game variables are
 */
void printplayerstatistics (struct game *board) {

    printf("\nYour statistics are:\n");
    printf("Games played: %d\n", board->gamesplayed);
    printf("Games won: %d\n", board->gameswon);
    printf("Games lost: %d\n", board->gameslost);
    printf("Cells opened: %d\n\n", board->openedcells);

}

/**
 * \brief Print the actual status of the game content in the stdout
 *
 * \param board Struct where all the game variables are
 */
void printgameboard (struct game *board){

    printf("\nDimensions: %lux%lu\n", board->height, board->width);
    printf("Number of mines: %lu\n", board->mines);
    printf("Mines to find: %d", (int) board->mines - board->minecounting);
    if((int) board->mines - board->minecounting < 0){
        printf(" (at least %d founded mines are not in the right position)", -1 * ((int) board->mines - board->minecounting));
    }
    printf("\n\n");

    //Algorithm to print the gameboard's coordinate names on the upper and left side of the content

    int widthint = (int) board->width;

    printf ("\t");

    for (int i = 0; i < widthint; i++) {
        if (i < 26) {
            printf("%c ", 65 + i);
        } else {
            printf("%c ", 71 + i);
        }
    }

    printf("\n");

    /****************************************************************************************************
     *  Every board cell will be printed. A # if its not opened, it's content if it's already opened,   *
     *  or a ? if it's marked                                                                           *
     ****************************************************************************************************/

    for (unsigned long i = 1; i < board->height + 1; i++) {
        printf("%lu\t", i);
        for (unsigned long j = 1; j < board->width + 1; j++) {
            if (board->minefield[i][j].openflag == 1) {
                if (board->minefield[i][j].content == '0') {
                    printf("  ");
                } else {
                    printf("%c ", board->minefield[i][j].content);
                }
            } else if (board->minefield[i][j].minemark == 1) {
                printf("%c ", '?');
            } else {
                printf("%c ", 35);
            }
        }
        printf("\n");
    }
}
