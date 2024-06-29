2048 Terminal Game
Welcome to the terminal-based version of the classic 2048 game!

Description
This is a console-based implementation of the popular 2048 game. The game's objective is to slide numbered tiles on a grid to combine them to create a tile with the number 2048. The game is written in C++ and runs in a terminal.

How to Play
Objective: Combine the tiles to reach the number 2048.
Controls:
Press W to slide tiles Upward
Press A to slide tiles Leftward
Press S to slide tiles Downward
Press D to slide tiles Rightward
Press P to pause the game
Press ESC to exit the game
Game End: The game ends when there are no more valid moves or the player reaches the tile 2048.
Scoring: Your score increases as you combine tiles. The highest score is saved and can be viewed from the main menu.

Game Menu
Upon starting the game, you will be presented with the following options:

Press 1 to play the game
Press 2 to view the high score
Press 3 to exit the game
High Score
The game keeps track of the highest score. If your score surpasses the previous high score, it will be saved automatically.

Code Overview
Functions
char key_press(): Captures and returns user key presses.
int options(): Displays the main menu and returns the selected option.
void change_highscore(int *score): Updates the high score if the current score is higher.
void display_all_time_best(): Displays the highest score.
bool check_score(string arr[][4]): Checks if any tile has reached the number 2048.
bool check_move(char arr[], char move): Validates if the move is allowed.
int randomi(): Generates a random index for the 4x4 grid.
void print(string arr[][4]): Prints the current state of the game board.
void add_2(string arr[][4]): Adds a '2' tile in a random empty position after each move.
bool game(string arr[][4], int *score): Handles the game logic, including capturing moves and updating the board.
Main Function
The main function initializes the game board, handles the game loop, and processes user inputs from the main menu.

