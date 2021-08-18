/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#include <time.h>
#include <stdlib.h>
#include "../include/struct_declaration.h"
#include "../include/memory_allocation.h" //Functions: memoryallocationboard, memoryallocationcell

/**\file board_defining.c
 * \author Sergio Tallo Torres
 * \date 14.01.2020
 * \brief Hier will be implemented every function that is involved in the definition of the board game
 */

/**
 * \brief Create a new game board. Where is defined where the mines are, and how many adyacent mines has every cell
 *
 * \param board Struct where all the game variables are
 */
void minefielddefine(struct game *board) {

    memoryallocationboard(board); //The board itself is a dynamic generated struct (board.minefield)

    time_t t;
    srand((unsigned) time(&t));

    memoryallocationcell(board);

    //Every cell will be default defined as #
    for (unsigned long i = 1; i < board->height + 1; i++) {
        for (unsigned long j = 1; j < board->width + 1; j++) {
            board->minefield[i][j].content = 35;
        }
    }

    unsigned long k = 0;

    //Every mine position will be randomly selected
    while (k < board->mines) {
        unsigned long minespositiony = (rand() % board->width + 1);
        unsigned long minespositionx = (rand() % board->height + 1);

        if (board->minefield[minespositionx][minespositiony].content != 'M') {
            board->minefield[minespositionx][minespositiony].content = 'M';
            k++;
        }
    }

    //The number of adyacent mines of every cell will be calculated and written in every cell without mines
    for (unsigned long i = 1; i <= board->width; i++) {
        for (unsigned long j = 1; j <= board->height; j++) {
            int aux = 0;
            if (board->minefield[i][j].content != 'M') {
                if (board->minefield[i - 1][j - 1].content == 'M') {
                    aux++;
                }
                if (board->minefield[i][j - 1].content == 'M') {
                    aux++;
                }
                if (board->minefield[i + 1][j - 1].content == 'M') {
                    aux++;
                }
                if (board->minefield[i - 1][j].content == 'M') {
                    aux++;
                }
                if (board->minefield[i + 1][j].content == 'M') {
                    aux++;
                }
                if (board->minefield[i - 1][j + 1].content == 'M') {
                    aux++;
                }
                if (board->minefield[i][j + 1].content == 'M') {
                    aux++;
                }
                if (board->minefield[i + 1][j + 1].content == 'M') {
                    aux++;
                }
                board->minefield[i][j].content = (char) (aux + 48);
            }
        }
    }

    //Every cell will be default define as not opened
    for (unsigned long i = 1; i < board->height + 1; i++) {
        for (unsigned long j = 1; j < board->width + 1; j++) {
            board->minefield[i][j].openflag = 0;
        }
    }

    //Every cell will be default define as not marked
    for (unsigned long i = 1; i < board->height + 1; i++) {
        for (unsigned long j = 1; j < board->width + 1; j++) {
            board->minefield[i][j].minemark = 0;
        }
    }

    int aux = 0;

    //At the begginig one random mineless cell will be opened by the system
    while (aux == 0) {
        unsigned long minespositiony = (rand() % board->width + 1);
        unsigned long minespositionx = (rand() % board->height + 1);

        if (board->minefield[minespositionx][minespositiony].content == 'M' || board->minefield[minespositionx][minespositiony].content == '0') {
            aux = 0;
        } else {
            board->minefield[minespositionx][minespositiony].openflag = 1;
            aux = 1;
        }
    }

    //The games played counter will be up in one and the game will be set as not finished
    board->gamesplayed++;
    board->finishedflag = 0;
}

/**
 * \brief Search and eliminate unknown adyacent zeros in the game board.
 *
 * \param board Struct where all the game variables are
 * \param coordinatex User choice for coordinate X in the matrix
 * \param coordinatey User choice for coordinate Y in the matrix
 */
void eliminatezero(struct game *board, int coordinatex, int coordinatey) {

    board->minefield[coordinatey][coordinatex].openflag = 1;
    board->openedcells++;

    if (board->minefield[coordinatey - 1][coordinatex - 1].content == '0' && board->minefield[coordinatey - 1][coordinatex - 1].openflag == 0) {
        eliminatezero(board, coordinatex - 1, coordinatey - 1);
    } else {
        board->minefield[coordinatey - 1][coordinatex - 1].openflag = 1;
    }

    if (board->minefield[coordinatey - 1][coordinatex].content == '0' && board->minefield[coordinatey - 1][coordinatex].openflag == 0) {
        eliminatezero(board, coordinatex, coordinatey - 1);
    } else {
        board->minefield[coordinatey - 1][coordinatex].openflag = 1;
    }

    if (board->minefield[coordinatey - 1][coordinatex + 1].content == '0' && board->minefield[coordinatey - 1][coordinatex + 1].openflag == 0) {
        eliminatezero(board, coordinatex + 1, coordinatey - 1);
    } else {
        board->minefield[coordinatey - 1][coordinatex + 1].openflag = 1;
    }

    if (board->minefield[coordinatey][coordinatex - 1].content == '0' && board->minefield[coordinatey][coordinatex - 1].openflag == 0) {
        eliminatezero(board, coordinatex - 1, coordinatey);
    } else {
        board->minefield[coordinatey][coordinatex - 1].openflag = 1;
    }

    if (board->minefield[coordinatey][coordinatex + 1].content == '0' && board->minefield[coordinatey][coordinatex + 1].openflag == 0) {
        eliminatezero(board, coordinatex + 1, coordinatey);
    } else {
        board->minefield[coordinatey][coordinatex + 1].openflag = 1;
    }

    if (board->minefield[coordinatey + 1][coordinatex - 1].content == '0' && board->minefield[coordinatey + 1][coordinatex - 1].openflag == 0) {
        eliminatezero(board, coordinatex - 1, coordinatey + 1);
    } else {
        board->minefield[coordinatey + 1][coordinatex - 1].openflag = 1;
    }

    if (board->minefield[coordinatey + 1][coordinatex].content == '0' && board->minefield[coordinatey + 1][coordinatex].openflag == 0) {
        eliminatezero(board, coordinatex, coordinatey + 1);
    } else {
        board->minefield[coordinatey + 1][coordinatex].openflag = 1;
    }

    if (board->minefield[coordinatey + 1][coordinatex + 1].content == '0' && board->minefield[coordinatey + 1][coordinatex + 1].openflag == 0) {
        eliminatezero(board, coordinatex + 1, coordinatey + 1);
    } else {
        board->minefield[coordinatey + 1][coordinatex + 1].openflag = 1;
    }
}

/**
 * \brief Show the position of every mine in the content game.
 *
 * \param board Struct where all the game variables are
 */
void showmines(struct game *board) {

    for (unsigned long i = 1; i < board->height + 1; i++) {
        for (unsigned long j = 1; j < board->width + 1; j++) {
            if (board->minefield[i][j].content == 'M') {
                board->minefield[i][j].minemark = 0;
                board->minefield[i][j].openflag = 1;
            }
        }
    }
}

/**
 * \brief Count how many mines are yet to discover
 *
 * \param board Struct where all the game variables are
 */
void minecounting(struct game *board) {

    int aux = 0;

    for (unsigned long i = 1; i < board->height + 1; i++) {
        for (unsigned long j = 1; j < board->width + 1; j++) {
            if (board->minefield[i][j].minemark == 1) {
                aux++;
            }
        }
    }

    board->minecounting = aux;
}

/**
 * \brief When a new player is created, every statistic is put to zero
 *
 * \param board Struct where all the game variables are
 */
void newstatistics(struct game *board){

    board->gameslost = 0;
    board->gameswon = 0;
    board->gamesplayed = 0;
    board->openedcells = 0;
    board->finishedflag = 1;
    board->mineflag = 0;
    board->winflag = 0;
}
