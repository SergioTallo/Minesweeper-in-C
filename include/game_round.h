/************************************************
*   Created by Sergio Tallo Torres on 7.1.20.   *
*************************************************/

#ifndef MINESWEEPER_BIC_GAME_ROUND_H
#define MINESWEEPER_BIC_GAME_ROUND_H

#include <stdbool.h>
#include "struct_declaration.h"

/** \file game_round.h
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Here are the functions useful for the actual game round
 */

/**
 * \brief Define, control and execute how a round in the game works.
 *
 * \param board Struct where all the game variables are
 */
void game(struct game *board) ;

/**
 * \brief Function involved in open a board game cell
 *
 * \param board Struct where all the game variables are
 */
void opencell (struct game *board);

/**
 * \brief Check at the end of every round if the player has won the game.
 *
 * \param board Struct where all the game variables are
 * \return 1 If the player won the game, 0 if not.
 */
bool wincheck(struct game *board);

/**
 * \brief hat happened after the player win or loose the game.
 *
 * \param board Struct where all the game variables are
 */
void endofthegame(struct game *board) ;

#endif //MINESWEEPER_BIC_GAME_ROUND_H
