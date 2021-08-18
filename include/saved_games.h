/************************************************
*   Created by Sergio Tallo Torres on 8.1.20.   *
*************************************************/

#ifndef MINESWEEPER_BIC_SAVED_GAMES_H
#define MINESWEEPER_BIC_SAVED_GAMES_H

#include "struct_declaration.h"

/**\file saved_games.h
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Functions that manage save the game and open saved games
 */

/**
 * \brief Ask the player for a Player's name
 *
 * /param board The struct where all variables of the game are
 */
void nametheplayer(struct game *board);

/**
 * \brief Check if the user has played before.
 *
 * Load his/her statistics and if there is a saved game ask to load it before loading the content.
 *
 * /param board The struct where all variables of the game are
 */
void opensavedgame(struct game *board);

/**
 * \brief Manage every user input in the std input
 *
 * \param input char variable für user input in the stdin
 */
void userinput (char *input);

/**
 * \brief Save the gameboard and player status in a .dat and a.log file
 *
 * \param board The struct where all variables of the game are
 */
void savegame(struct game board);
#endif //MINESWEEPER_BIC_SAVED_GAMES_H
