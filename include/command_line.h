/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#ifndef MINESWEEPER_BIC_COMMAND_LINE_H
#define MINESWEEPER_BIC_COMMAND_LINE_H

#include "struct_declaration.h"

/**\file command_line.h
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Every function that work with the command line
 */

/**
 * \brief Control the number of command line arguments
 *
 * In this case, the number should be 2, (one for the board dimensions and one for the number of mines)
 * If it's different than 2 the program will exit with an error.
 *
 * \param argc The number of command line arguments
 */
void controlargc(const int *argc);

/**
 * \brief Control the Argument used for the board dimensions.
 *
 * Control if it has the right format and if so write it in the right struct variable
 *
 * \param argv The first command line argument
 * \param board The struct where all variables of the game are
 */
void dimensions(char **argv, struct game *board);

/**
 * \brief Control the Argument used for the dimensions.
 *
 * Control if it has the right format and if so write it in the right struct variable
 *
 * \param argv The second command line argument
 * \param board The struct where all variables of the game are
 */
void numberofmines(char **argv, struct game *board);

#endif //MINESWEEPER_BIC_COMMAND_LINE_H
