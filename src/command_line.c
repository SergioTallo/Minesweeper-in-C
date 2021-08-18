/************************************************
*   Created by Sergio Tallo Torres on 18.12.19. *
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/struct_declaration.h"

/**\file command_line.c
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
void controlargc(const int *argc) {

    if (*argc != 3) {
        if (*argc < 3) {
            fprintf(stderr, "Error command line: Too few arguments!");
            exit(1);
        } else if (*argc > 3) {
            fprintf(stderr, "Error command line: Too many arguments!");
            exit(1);
        }
    }
}

/**
 * \brief Control the Argument used for the board dimensions.
 *
 * Control if it has the right format and if so write it in the right struct variable
 *
 * \param argv The first command line argument
 * \param board The struct where all variables of the game are
 */
void dimensions(char **argv, struct game *board) {

    if (strlen(*argv) > 5 || strlen(*argv) < 3){
        fprintf(stderr, "Error Argument 1: Format is not correct (ddXdd)\n");
        exit(1);
    }

    char *token;
    const char delim[2] = "x";
    token = strtok(*argv, delim);
    board->width = strtoul(token, NULL, 10);
    token = strtok(NULL, delim);
    board->height = strtoul(token, NULL, 10);

    if (board->width > MAX_WIDTH) {
        fprintf(stderr, "Error Argument 1: Board too wide (max 52 rows)\n");
        exit(1);
    }
    if (board->height > MAX_HEIGTH) {
        fprintf(stderr, "Error Argument 1: Board too high (max 99 lines)\n");
        exit(1);
    }

    if (board->width < MIN_HEIGTH) {
        fprintf(stderr, "Error Argument 1: Board too narrow (min 2 rows)\n");
        exit(1);
    }
    if (board->height < MIN_WIDTH) {
        fprintf(stderr, "Error Argument 1: Board too short (min 2 lines)\n");
        exit(1);
    }
}

/**
 * \brief Control the Argument used for the dimensions.
 *
 * Control if it has the right format and if so write it in the right struct variable
 *
 * \param argv The second command line argument
 * \param board The struct where all variables of the game are
 */
void numberofmines(char **argv, struct game *board) {

    board->mines = strtoul(*argv, NULL, 10);

    if (isdigit(board->mines == 0) || board->mines == 0) {
        fprintf(stderr, "Error second argument: Wrong argument. Should be a int != 0");
        exit(1);
    }

    if (board->mines >= board->height * board->width) {
        fprintf(stderr, "Error second argument: Too many mines. It should be less than %lu.",
                board->height * board->width);
        exit(1);
    }

}
