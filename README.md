Compilation:

To compile the program execute in the terminal the script stored in the same folder named compileminesweeper.sh 
The user have to type ./compileminesweeper.sh
The content of the script is:
	gcc -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter -g main.c src/game_round.c src/files_handling.c src/print_functions.c src/memory_allocation.c src/command_line.c src/board_defining.c src/saved_games.c -o  minesweeper
With that the program will be compiled, with all the warnings include, in an executable file named minesweeper



Execution:

To execute the program correctly two extra command line arguments are needed. One of them is to determinate the dimensions of the board. The maximum height is 99 cells, and the maximum width is 52. The minimum value for height and with is 2. This argument should be typed with this format %%d%%. If height or width only have one digit the user doesn't have to write a 0 before it.
For the second argument the user have to type an integer that determine the number of mines that will be hidden in the game. The minimum number is 1 and the maximum is the multiplication between the width and the height of the board.
	Execution example: ./minesweeper 10x10 30

If some of the arguments are missing or there is an incorrect typing of them, the program will show an error line explaining why is incorrect and what the user should have typed instead.



Completed Tasks:

I completed the following tasks:

1.Main Task (30 points)
	The program dynamically generates the matrix.
	Then the 20 mines are randomly distributed within the matrix.
	Calculations of surrounding mines are done and value of nearby mines for each cell is stored in the matrix.
	If there are no mines a 0 should be stored.
	The matrix should furthermore have a flag for each cell if its already opened by the player or not.
	When a new game is started one random cell is shown but only if this cell contains a number unequal to zero and no mine.
	The player enters the coordinates of the field which should be opened:
		If the selected cell contains a mine, all other mines should be shown and the game is over.
		If the selected cell contains a number this cell is shown.
		The player wins the game when all cells without mines are opened.

2.Task (15 points)
	Extend the program to handle the case when a cell contains a zero in a different way:
		If a selected cell contains a zero then all neighbor cells are revealed as if they were opened by the player.
		If any of these contain another zero the neighbors of that cell have to be uncovered again as well.
		This process is repeated until all cells connected to each other containing zeros are opened.

3.Task (15 points)
	Extend the program to handle program arguments for a square Matrix size. (e.g., 5x5 or 15x15 etc)
	And amount of mines.

4.Task (15 points)
	Extend the program that a player can mark a mine with a prefix in front of the coordinates (e.g., ?)
	A marked mine will be shown to the player.
	Show amount of mines in the game minus the amount of marked mines.
	Also show if this sum is negative, meaning a cell was marked as mine which does not have a mine.
	The player wins the game when all cells with mines are marked or all cells are opened which are not a mine.

5.Task (15 points)
	Ask and save the names of the players.
	Generate a statistic for this player including:
		Played games
		Games won
		Games lost
		Opened cells
	This statistic has to be saved into a file named after the player.
	On start of a game when the player has entered his name, the statistic should be loaded if available.

6.Task (15 points)
	Save the result of the playing field including player name into a file.
	If a user wants to abort a game save the current playing field into a file and when this player starts a new game ask him if he wants to continue.
	Then load the playing field into the matrix and let the player continue the game.