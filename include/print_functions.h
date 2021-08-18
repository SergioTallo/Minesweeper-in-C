/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#ifndef MINESWEEPER_BIC_PRINT_FUNCTIONS_H
#define MINESWEEPER_BIC_PRINT_FUNCTIONS_H

#include "struct_declaration.h"

/**\file print_functions.h
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Functions that print in the stdout
 */

/**
 * \brief Print the player statistics in the stdout
 *
 * \param board Struct where all the game variables are
 */
void printplayerstatistics (struct game *board);

/**
 * \brief Print the actual status of the game content in the stdout
 *
 * \param board Struct where all the game variables are
 */
void printgameboard (struct game *board);

#endif //MINESWEEPER_BIC_PRINT_FUNCTIONS_H
