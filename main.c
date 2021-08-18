/********************************
 * Minesweeper 2019             *
 *                              *
 * Author: Sergio Tallo Torres  *
 *                              *
 * Version 0.9 (9.1.2020)       *
 ********************************/

#include <stdlib.h>
#include "include/struct_declaration.h"
#include "include/command_line.h" //Functions: controlargc, dimensions, number of mines
#include "include/saved_games.h" //Functions: nametheplayer, opensavedgame
#include "include/board_defining.h" //Function: minefielddefine
#include "include/game_round.h" //Functions: game, endofthegame
#include "include/memory_allocation.h" //Function: freeboardmemory

/**\file main.c
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief main source file of the Minesweeper program
 */

/**
 *\brief Program's main Function
 *
 * The main Program Functions that control the game are here
 *
 *\param argc Number of Arguments
 *\param argv Strings of the different Arguments
 *\return EXIT_SUCCESS if the Program ends correctly
 */
int main (int argc, char **argv){

    struct game board; //Declaration of the game board.

    /****************************************************************************************************
    *   This three functions are to check if the command line arguments are written properly and if so, *
    *   store them as a variable (width, height and mines) in the struct.                               *
    *****************************************************************************************************/

    controlargc(&argc); //How many total arguments should be (3 in our case).
    dimensions(&argv[1], &board); //dimensions; The dimensions of the board.
    numberofmines(&argv[2], &board); //numberofmines; The number of mines in the board.

    /********************************************************************************
    *   The user have to write a player's name and the program will search if       *
    *   the player has played before and if so load his statistics and saved games  *
    *********************************************************************************/

    nametheplayer(&board);
    opensavedgame(&board);

    /************************************************************************************************************
     *  If there is no unfinished saved games or the user doesn't want to continue the saved game, the program  *
     *  generate a new gameboard with the dimensions and mines from the command line arguments.                 *
     ************************************************************************************************************/

    if (board.finishedflag == 1) {
        minefielddefine(&board); //Define the gameboard (dimensions and where are the mines).
    }

    game(&board); //Manage what happened during the game itself
    endofthegame(&board); //Manage what happened when the game finished.
    freeboardmemory(&board); //The dynamic allocated memory is freed before the end of the program.

    return EXIT_SUCCESS;
}
