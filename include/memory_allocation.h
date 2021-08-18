/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#ifndef MINESWEEPER_BIC_MEMORY_ALLOCATION_H
#define MINESWEEPER_BIC_MEMORY_ALLOCATION_H

#include "struct_declaration.h"

/**\file memory_allocation.h
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Functions that handle the dynamic memory
 */

/**
 * \brief The memory for the minefield will be allocated
 *
 * \param board Struct where all the game variables are
 */
void memoryallocationboard(struct game *board);

/**
 * \brief With the help of a for loop, the memory for every cell will be allocated.
 *
 * \param board Struct where all the game variables are
 */
void memoryallocationcell(struct game *board);

/**
 * \brief Free the memory allocated memory used for the board. Using a for loop for freeing every row individually
 *
 * \param board Struct where all the game variables are
 */
void freeboardmemory(struct game *board);

#endif //MINESWEEPER_BIC_MEMORY_ALLOCATION_H
