/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#ifndef MINESWEEPER_BIC_FILES_HANDLING_H
#define MINESWEEPER_BIC_FILES_HANDLING_H

#include "struct_declaration.h"

/**\file files_handling.h
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Every function that has something to do with files
 * Open, write, read...
 */

/**
 * \brief Close a file.
 * Error message if the file is not closed succesfully
 *
 * \param pFile File pointer to the file you want to close
 */
void closefile(FILE **pFile);

/**
 * \brief Open a file with reading privileges.
 *
 * \param pFile File pointer to the file you want to open
 * \param filename File name of the file you want to open
 */
void openfileread(FILE **pFile, char *filename);

/**
 * \brief Open a file with writing privileges
 * Error message if the File could not be opened properly
 *
 * \param pFile File pointer to the file you want to open
 * \param filename File pointer to the file you want to open
 */
void openfilewrite (FILE **pFile, char *filename);

/**
 * \brief Write the actual board status in a file.
 *
 * \param pFile File pointer to the file in which you want to save the board status
 * \param board The struct where all variables of the game are
 */
void writeboardfile (FILE **pFile, struct game board);

/**
 * \brief Write the statistics of the player in a file
 * (also the height and width of the last game)
 *
 * \param pFile File pointer to the file in which you want to save the player stats
 * \param board The struct where all variables of the game are
 */
void writeplayerfile (FILE **pFile, struct game board);

/**
 * \brief Read the player's statistics from a file.
 *
 * \param pFile File pointer to the file from where you want to read the player stats
 * \param board The struct where all variables of the game are
 */
void readplayerfile (FILE **pFile, struct game *board);

/**
 * \brief Read the board status of the last saved game
 *
 * \param pFile File pointer to the file from where you want to read the player stats
 * \param pFile1 File pointer to the file from where you want to read the board stats
 * \param board The struct where all variables of the game are
 */
void readboardfile (FILE **pFile, FILE **pFile1, struct game *board);

#endif //MINESWEEPER_BIC_FILES_HANDLING_H
