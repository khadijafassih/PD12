#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

const int BOARD_row = 40;
const int BOARD_col = 70;

char board[BOARD_row][BOARD_col] =
    {".-=~=-.                                                     .-=~=-.",
     "(__  _)-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-(__  _)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)@@@@@@                                               ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                            @@@@@@@@@( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                             ++++++++( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)@@@@@@@@@@@                                          ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                                     ( _ __)",
     "( _ __)                                                     ( _ __)",
     "(__  _)-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-(__  _)",
     "`-._.-'                                                     `-._.-'"};

/*char player[50][50] = {
    " ______.........--=T=--.........______",
    "   .             |:|",
    ":-. //           /""'''""-.",
    "': '-._____..--""(""'''""()`---.__",
    " /:   _..__   ''  ""'''""'[] |""`\\",
    "': :'     `-.     _:._     ''''"" :",
    "::          '--=:____:.___....-''"};*/

 
int pX = 10, pY = 10;
int eX = 30, eY = 18;
int eX2 = 9, eY2 = 18;
int eX3 = 25, eY3 = 2;
int eX4 = 35, eY4 = 6;
int score = 0;
int lives = 2;
int fX = -1, fY = -1;

int printscore()
{
    gotoxy(BOARD_col + 2, 2);
    cout << "score: " << score;
    return 0;
}
int printlives()
{
    gotoxy(BOARD_col + 2, 4);
    cout << "lives: " << lives;

    if (board[pX - 1][pY] == '@' || board[pX - 1][pY] == '+' || board[pX + 1][pY] == '@' || board[pX + 1][pY] == '+')
    {
        return lives - 1;
    }

    return lives;
}
bool isValidMove(int x, int y)
{
    if (x < 0 || x >= BOARD_col || y < 0 || y >= BOARD_row)
        return false;

    char destinationChar = board[y][x];
    if (destinationChar == '=' || destinationChar == '-' || destinationChar == '.' || destinationChar == '_' || destinationChar == '(' || destinationChar == ')' || destinationChar == '+' || destinationChar == '@')
        return false;

    return true;
}
void moveEnemy(int enemyIndex, int &ex, int &ey)
{
    int randomMove = rand() % 4; // Random number between 0 and 3

    switch (randomMove)
    {
    case 0: // Move left
        if (isValidMove(ex - 1, ey))
        {
            board[ey][ex] = ' ';
            ex--;
            board[ey][ex] = 'E';
        }
        break;
    case 1: // Move right
        if (isValidMove(ex + 1, ey))
        {
            board[ey][ex] = ' ';
            ex++;
            board[ey][ex] = 'E';
        }
        break;
    case 2: // Move up
        if (isValidMove(ex, ey - 1))
        {
            board[ey][ex] = ' ';
            ey--;
            board[ey][ex] = 'E';
        }
        break;
    case 3: // Move down
        if (isValidMove(ex, ey + 1))
        {
            board[ey][ex] = ' ';
            ey++;
            board[ey][ex] = 'E';
        }
        break;
    }
}

void printBoard();
void initializeBoard();
void movePlayerLeft();
void movePlayerRight();
void movePlayerDown();
void movePlayerUp();
void fire();
void moveFire(int timeStep);

int main()
{
    system("cls");
    printBoard();
    while (true)
    {
        system("cls");
        printBoard();
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayerLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayerRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePlayerUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePlayerDown();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            fire();
        }
        moveEnemy(1, eX, eY);
        moveEnemy(2, eX2, eY2);
        moveEnemy(3, eX3, eY3);
        moveEnemy(4, eX4, eY4);
        moveFire(1);
        lives = printlives();
        printscore();
        if (lives == 0)
        {
            system("cls");
            cout << "Game Over!" << endl;
            break; 
        }
        Sleep(80);
    }
    return 0;
}
void initializeBoard()
{
    for (int i = 0; i < BOARD_row; ++i)
    {
        for (int j = 0; j < BOARD_col; ++j)
        {
            board[i][j];
        }
    }
}

void printBoard()
{
    for (int i = 0; i < BOARD_row; ++i)
    {
        for (int j = 0; j < BOARD_col; ++j)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void movePlayerLeft()
{
    if (pX > 0 && board[pX][pY - 1] != ')')
    {
        board[pX][pY] = ' ';
        pY--;
        board[pX][pY] = 'P';
    }
}

void movePlayerRight()
{
    if (pX < BOARD_col - 1 && board[pX][pY + 1] != '(')
    {
        board[pX][pY] = ' ';
        pY++;
        board[pX][pY] = 'P';
    }
}

void movePlayerUp()
{
    if (pX > 0 && board[pX - 1][pY] != '=' && board[pX - 1][pY] != '-' && board[pX - 1][pY] != '.' && board[pX - 1][pY] != '_')
    {
        board[pX][pY] = ' ';
        pX--;
        board[pX][pY] = 'P';
    }
}

void movePlayerDown()
{
    if (pX < BOARD_row - 1 && board[pX + 1][pY] != '=' && board[pX + 1][pY] != '-' && board[pX + 1][pY] != '.' && board[pX + 1][pY] != '_')
    {
        board[pX][pY] = ' ';
        pX++;
        board[pX][pY] = 'P';
    }
}

void fire()
{
    if (fY == -1)
    {
        fX = pY;
        fY = pX - 1;
    }
    board[fY][fX] = '|';
}

void moveFire(int timeStep)
{
    if (fY >= 0 && fY < BOARD_row && fX >= 0 && fX < BOARD_col)
    {
        board[fY][fX] = ' ';

        fY -= timeStep;

        if (fY >= 0 && fY < BOARD_row && fX >= 0 && fX < BOARD_col)
        {
            if (board[fY][fX] == 'E')
            {
                score++;
                fX = -1;
                fY = -1;
            }
            else if (fY >= 0 && fY < BOARD_row && fX + 1 >= 0 && fX + 1 < BOARD_col && board[fY][fX + 1] != '=' && board[fY][fX + 1] != '-' && board[fY][fX + 1] != '.' && board[fY][fX + 1] != '_')
            {
                board[fY][fX] = '|';
            }
            else
            {
                // Resetting fire coordinates
                fX = -1;
                fY = -1;
            }
        }
    }
    else if (fY == 0 && board[fY - 1][fX] != ' ')
    {
        // Resetting fire coordinates
        fX = -1;
        fY = -1;
    }
}
