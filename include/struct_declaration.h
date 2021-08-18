/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#ifndef MINESWEEPER_BIC_STRUCT_DECLARATION_H
#define MINESWEEPER_BIC_STRUCT_DECLARATION_H

#include <stdbool.h>
#define MAX_NAME_LENGTH 11
#define MAX_INPUT_LENGTH 50
#define MAX_WIDTH 52
#define MAX_HEIGTH 99
#define MIN_HEIGTH 2
#define MIN_WIDTH 2

/**
 * \file struct_declaration.h
 * \brief In this file will be declared the structs necesary to the game
 */

///Every cell of the board and its content
struct cell {
    ///What is behind every cell
    char content;
    ///If the cell is open (1) or closed (0)
    bool openflag;
    ///If its marked as a mine by the player (1) if not (0)
    bool minemark;
};

///The board game with all its variables
struct game {
    ///Player's name that also define the name of the files involved in the game
    char playername[MAX_NAME_LENGTH];
    ///Board game Width (in number of cells)
    unsigned long width;
    ///Board game Height (in number of cells)
    unsigned long height;
    ///Number of mines hidden in the board game
    unsigned long mines;
    ///This is the actual gameboard (every cell). Dynamic generated 2D struct array.
    struct cell **minefield;
    ///Flag to show if the game is finished
    bool finishedflag;
    ///Flag to show if the player explode a mine
    bool mineflag;
    ///Flag to show if the player won the game
    bool winflag;
    ///Number of games played by the player
    int gamesplayed;
    ///Number of games won by the player
    int gameswon;
    ///Number of games lost by the player
    int gameslost;
    ///Number of cells opened by the player
    int openedcells;
    ///Number of mines still to found in the actual game
    int minecounting;
};


#endif //MINESWEEPER_BIC_STRUCT_DECLARATION_H
