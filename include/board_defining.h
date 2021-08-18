/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#ifndef MINESWEEPER_BIC_BOARD_DEFINING_H
#define MINESWEEPER_BIC_BOARD_DEFINING_H

#include "struct_declaration.h"

/**\file board_defining.h
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Hier will be implemented every function that is involved in the definition of the board game
 */

/**
 * \brief Create a new game board. Where is defined where the mines are, and how many adyacent mines has every cell
 *
 * \param board Struct where all the game variables are
 */
void minefielddefine(struct game *board);

/**
 * \brief Search and eliminate unknown adyacent zeros in the game board.
 *
 * \param board Struct where all the game variables are
 * \param coordinatex User choice for coordinate X in the matrix
 * \param coordinatey User choice for coordinate Y in the matrix
 */
void eliminatezero(struct game *board, int coordinatex, int coordinatey);

/**
 * \brief Show the position of every mine in the content game.
 *
 * \param board Struct where all the game variables are
 */
void showmines(struct game *board);

/**
 * \brief Count how many mines are yet to discover
 *
 * \param board Struct where all the game variables are
 */
void minecounting (struct game *board);

/**
 * \brief When a new player is created, every statistic is put to zero
 *
 * \param board Struct where all the game variables are
 */
void newstatistics(struct game *board);

#endif //MINESWEEPER_BIC_BOARD_DEFINING_H
