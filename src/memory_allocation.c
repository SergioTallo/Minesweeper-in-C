/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "../include/struct_declaration.h"

/**\file memory_allocation.c
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Functions that handle the dynamic memory
 */

/**
 * \brief The memory for the minefield will be allocated
 *
 * \param board Struct where all the game variables are
 */
void memoryallocationboard(struct game *board){

    board->minefield = malloc(((board->height + 2) * (board->width + 2)) * sizeof(board->minefield));
    if (board->minefield == NULL) {
        fprintf(stderr, "MEMORY ERROR!");
        exit(1);
    }
}

/**
 * \brief With the help of a for loop, the memory for every cell will be allocated.
 *
 * \param board Struct where all the game variables are
 */
void memoryallocationcell(struct game *board){

    for (unsigned long i = 0; i < board->height + 2; i++) {
        board->minefield[i] = malloc((board->width + 2) * sizeof(struct cell));
        if (board->minefield[i] == NULL) {
            fprintf(stderr, "MEMORY ERROR!");
            exit(1);
        }
    }
}

/**
 * \brief Free the memory allocated memory used for the board. Using a for loop for freeing every row individually
 *
 * \param board Struct where all the game variables are
 */
void freeboardmemory(struct game *board){
    for(unsigned long i = 0; i < board->height+2; i++){
        free(board->minefield[i]);
    }
    free(board->minefield);
}
