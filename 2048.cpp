#include <iostream>
#include <time.h>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>
#define KEY_UP 72 // defining key codes.

#define KEY_DOWN 80

#define KEY_LEFT 75

#define KEY_RIGHT 77

using namespace std;

char key_press() // function used to take input
{
    char k;
    cin >> k;

    switch (k)
    {
        case 'w':
        case 'W':
            return 'U';

        case 'a':
        case 'A':
            return 'L';

        case 's':
        case 'S':
            return 'D';

        case 'd':
        case 'D':
            return 'R';

        case 27: // Escape key.
            return 'E';

        case 'p':
        case 'P':
            return 'P';

        default:
            return 'X';
    }
}

int options() // used to display options at the start of the game.
{ 

    cout << "Press 1 to play \nPress 2 for highscore\nPress 3 to exit game" << endl;
    int x;
    cin >> x;
    return x;
}
void change_highscore(int *score) // takes score as input and checks if score > highscore. if so changes high score in highscore file.
{
    fstream myfile;
    myfile.open("highscore.txt", ios ::in);
    int s;
    if (myfile.is_open())
    {
        myfile >> s;
    }
    else
    {
        cout << "Error displaying highscore..." << endl;
    }
    myfile.close();
    if (*score > s)
    {
        myfile.open("highscore.txt", ios ::out);
        myfile << *score;
    };
}
void display_all_time_best() //used to displlay highscore
{
    fstream myfile;
    myfile.open("highscore.txt", ios ::in); // ios in means taking input from file.
    int s;
    if (myfile.is_open())
    {
        myfile >> s;
    }
    else
    {
        cout << "Error displaying highscore..." << endl;
    }
    cout << "Your highscore is " << s << "!" << endl;
}
bool check_score(string arr[][4]) // used to check if score reaches 2048, in that case user wins.
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (arr[i][j] == "2048")
            {
                return true;
            }
        }
    }
    return false;
}
bool check_move(char arr[], char move)
{
    for (int i = 0; i < 4; i++)
    {
        if (arr[i] == move)
        {
            return true;
        }
    }
    return false;
}

int randomi()// return a random coordinate in the 4 by 4 matrix
{
    int r = rand() % 4;
    return r;
}

void print(string arr[][4]) // used to print the matrix.
{
    // system("CLS");
    int num;
    for (int rows = 0; rows < 4; rows++)
    {
        cout << "\t\t\t\t\t\t\t\t"; // used to add spaces before each row.
        
        for (int col = 0; col < 4; col++)
        // if statements ensure that the matrix is always symmetrical.
        {
            if (arr[rows][col] != " ")
            {
                num = stoi(arr[rows][col]);
            }

            if (arr[rows][col] == " ")
            {
                cout << "|    ";
            }
            else if ((num < 10))
            {
                cout << "| " << arr[rows][col] << "  ";
            }
            else if (num < 100)
            {
                cout << "| " << arr[rows][col] << " ";
            }
            else if (num < 1000)
            {
                cout << "| " << arr[rows][col];
            }
            else if (num < 10000)
            {
                cout << arr[rows][col];
            }
        }
        cout << "|" << endl;
    }
}
void add_2(string arr[][4]) // adds a 2 in random location after every move.
{
    int x = randomi();
    int y = randomi();
    while (arr[x][y] != " ") // ensures a 2 is always generated in a free block.
    {
        x = randomi();
        y = randomi();
    }
    arr[x][y] = "2";
}
bool game(string arr[][4], int *score)
{
    int k = 0;
    int move = 0;
    bool moved = false;
    char check_arr[4] = {' ', ' ', ' ', ' '};
    while (!moved && move < 4) //  !moved esures loops runs until a 'piece' is moved and move < 4 ensures a user can try all 4 options and if
    { // all 4 moves have been tried and moved is stll false the loop will break and function will return false ending the game.
        
        char input = key_press();
        cout << "Input: " << input << endl;
        if (!check_move(check_arr, input)) // ensures that for the case when a user input a direction which is not possible,  the user doesn't enter the same input again
        // in that iteration. 
        {
            if(input == 'U' || input == 'L' || input == 'R' || input == 'D'){
                check_arr[k] = input;
                k++;
            }
          
            
            if (input == 'U') // used to skew all the elements up and add same numbers if certain conditions are met
            {

                for (int c = 0; c < 4; c++)
                {
                    int space = 10; // used to indicate free spaces in the matrix.
                    for (int r = 0; r < 4; r++)
                    {
                        if (arr[r][c] == " " && r < space)
                        {
                            space = r;
                        }
                        if (arr[r][c] != " " && r != 0)
                        {
                            if (arr[space - 1][c] == arr[r][c] && (space <= 3 && space >= 0))
                            {
                                
                                int temp = 2 * stoi(arr[r][c]);
                                arr[space - 1][c] = to_string(temp);
                                arr[r][c] = " ";
                                *score += temp;
                                moved = true;
                                // space = 10;
                            }
                            else if (arr[r - 1][c] == arr[r][c])
                            {
                                int temp = 2 * stoi(arr[r][c]);
                                arr[r - 1][c] = to_string(temp);
                                arr[r][c] = " ";
                                *score += temp;
                                moved = true;
                                if (r - 1 == space)
                                    space = 10;
                            }
                            else if (arr[r - 1][c] == " ")
                            {
                               
                                arr[space][c] = arr[r][c];
                                arr[r][c] = " ";
                                moved = true;
                                space++;
                            }
                            if (arr[r][c] == " " && r < space)
                            {
                                space = r;
                            }
                        }
                    }
                }
                move++;
            }
            else if (input == 'D')
            {
                for (int c = 0; c < 4; c++)
                {
                    int space = -10;
                    for (int r = 3; r >= 0; r--)
                    {
                        if (arr[r][c] == " " && r > space)
                        {
                            space = r;
                        }
                        if (arr[r][c] != " " && r != 3)
                        {
                            if (arr[space + 1][c] == arr[r][c] && ((space) <= 3 && space >= 0))
                            {
                                int temp = 2 * stoi(arr[r][c]);
                                arr[space + 1][c] = to_string(temp);
                                arr[r][c] = " ";
                                *score += temp;
                                moved = true;
                                // space = -10;
                            }
                            else if (arr[r + 1][c] == arr[r][c])
                            {
                                
                                int temp = 2 * stoi(arr[r][c]);
                                arr[r + 1][c] = to_string(temp);
                                arr[r][c] = " ";
                                *score += temp;
                                moved = true;
                                if (r + 1 == space)
                                    space = -10;
                            }
                            else if (arr[r + 1][c] == " ")
                            {
                               
                                arr[space][c] = arr[r][c];
                                arr[r][c] = " ";
                                moved = true;
                                space--;
                            }
                            if (arr[r][c] == " " && r > space)
                            {
                                space = r;
                            }
                        }
                    }
                }

                move++;
            }
            else if (input == 'R')
            {
                for (int r = 0; r < 4; r++)
                {
                    int space = -10;
                    for (int c = 3; c >= 0; c--)
                    {

                        if (arr[r][c] == " " && c > space)
                        {
                            space = c;
                        }
                        if (arr[r][c] != " " && c != 3)
                        {
                            if (arr[r][space + 1] == arr[r][c] && ((space) <= 3 && space >= 0))
                            {

                                int temp = 2 * stoi(arr[r][c]);
                                arr[r][space + 1] = to_string(temp);
                                arr[r][c] = " ";
                                *score += temp;
                                moved = true;
                                // space = -10;
                            }
                            else if (arr[r][c + 1] == arr[r][c])
                            {
                                int temp = 2 * stoi(arr[r][c]);
                                arr[r][c + 1] = to_string(temp);
                                arr[r][c] = " ";
                                *score += temp;
                                moved = true;
                                if (c + 1 == space)
                                    space = -10;
                            }
                            else if (arr[r][c + 1] == " ")
                            {
                                arr[r][space] = arr[r][c];
                                arr[r][c] = " ";
                                moved = true;
                                space--;
                            }
                            if (arr[r][c] == " " && c > space)
                            {
                                space = c;
                            }
                        }
                    }
                }

                move++;
            }
            else if (input == 'L')
            {
                for (int r = 0; r < 4; r++)
                {
                    int space = 10;
                    for (int c = 0; c < 4; c++)
                    {

                        if (arr[r][c] == " " && c < space)
                        {
                            space = c;
                        }
                        if (arr[r][c] != " " && c != 0)
                        {
                            if (arr[r][space - 1] == arr[r][c] && ((space) <= 3 && space >= 0))
                            {
                                cout << "1st" << endl;
                                int temp = 2 * stoi(arr[r][c]);
                                arr[r][space - 1] = to_string(temp);
                                arr[r][c] = " ";
                                *score += temp;
                                moved = true;
                                // space = -10;
                            }
                            else if (arr[r][c - 1] == arr[r][c])
                            {
                                cout << "2nd" << endl;
                                int temp = 2 * stoi(arr[r][c]);
                                arr[r][c - 1] = to_string(temp);
                                arr[r][c] = " ";
                                *score += temp;
                                moved = true;
                                if (c - 1 == space)
                                    space = 10;
                            }
                            else if (arr[r][c - 1] == " ")
                            {
                                cout << "3rd" << endl;
                                arr[r][space] = arr[r][c];
                                arr[r][c] = " ";
                                moved = true;
                                space++;
                            }
                            if (arr[r][c] == " " && c < space)
                            {
                                space = c;
                            }
                        }
                    }
                }

                move++;
            }
            else if (input == 'E') // used to terminate the game.
            {
                return false;
            }
            else if (input == 'P') // used to pause the game.
            {
                // system("CLS");
                cout << setw(90) << "Game paused." << endl;
                cout << setw(90) << "Press P to unpause the game." << endl << endl;
                do{
                    input = key_press();
                }while(input != 'P');
                return true;
            }
            else if(input == 'X'){ // used for wrong input.
                cout << "Wrong input!" << endl;
                return true;
            }
        }
        else
        {
            cout << "You have already tried this direction. Try another direction!" << endl;
        }
    }
    add_2(arr);
    if (check_score(arr)) // used to check if score in any block is 2048.
    {
        cout << "You win!" << endl;
        return false;
    }
    return moved;
}
int main()
{
    // initialising the board.
    int op, score = 0;
    srand(time(0));
    int x1, y1, x2, y2;
    string board[4][4];
    for (int rows = 0; rows < 4; rows++)
    {
        for (int columns = 0; columns < 4; columns++)
        {
            board[rows][columns] = " ";
        }
    }
    x1 = randomi();
    y1 = randomi();
    x2 = randomi();
    y2 = randomi();
    while (x1 == x2)
    {
        x2 = randomi();
    }
    while (y1 == y2)
    {
        y2 = randomi();
    }
    board[x1][y1] = "2";
    board[x2][y2] = "2";
    cout << setw(90) << "WELCOME TO 2048" << endl;
    do
    {
        op = options();
        if (op == 1)
        {
            cout << "The game's objective is to slide numbered tiles on a grid to combine them to create a tile with the number 2048 \nPress 'W' to slide Upward \nPress 'A' to slide Leftward \nPress 'S' to slide Downward \nPress 'D' to slide Right" << endl << "Good luck!" << endl;
            do
            {
                cout << setw(90) << "Press esc to exit." << endl;
                cout << setw(90) << "Press P to pause." << endl;
                print(board);
                cout << "Score: " << score << endl;
            } while (game(board, &score));
            cout << "Game ended!" << endl;
            cout << "Total score: " << score << endl
                 << endl;
            change_highscore(&score);
        }
        else if (op == 2)
        {
            display_all_time_best();
            cout << endl;
        }
        else if (op == 3)
        {
            cout << "Exiting....";
        }
        else
        {
            cout << "Wrong input!" << endl;
        }
    } while (op != 3);
}