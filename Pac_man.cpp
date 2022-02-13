#include <iostream>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cmath>
using namespace std;
//****************************loading maze from file****************************************************
char header[6][42];
void load();
char mazeA[24][70];
void maze_show();
//*******************************************************************************************************************
//________________________calculate score_________________________________________________________
void calculate_score();
void printScore();
//___________________________________________________________________________________________________
//*************************to avoid flickering**************************************
void gotoxy(int x, int y);
//__________________________________________________________________________________________
//*****************************lives system*****************************
void lives_counter();
void lives_show();
///__________________________________________________________________________-_____
//*********************************energizer system***********************************
int energy = 1;
void energy_loss();
void energyzer();
void energizer_show();

//-------------------------------------------------------------------------------------
void movepack_man();
void movePacmanLeft();
void movePacmanRight();
void movePacmanUp();
void movePacmanDown();
//************************************ single ghost move up
void ghost1_moveup();
void ghost_move();

//*************
int ghostDirection();
bool ghostMovementRand();
// random motion
bool move_down = false;
bool move_up = true;
// lives*******

int pacmanX = 9;  // X Coordinate of Pacman
int pacmanY = 31; // Y Coordinate of Pacman
int score = 0;

int ghostX_2 = 1; // chase
int ghostY_2 = 23;

int ghostX = 19; // random movement
int ghostY = 25;
// vertical movement.............................
int ghostX_1 = 12; // move UpDown
int ghostY_1 = 2;
bool move_up_1();
bool move_down_1();
bool gostmovement_vertical();
char previousItem = ' ';
char previousItem_Vertical = ' ';
bool gameRunning_vertical = true;
bool temp = false;
//___________________________________________
//***********************************
// horizontol moovement
int ghostX_3 = 15; // horizontolly move
int ghostY_3 = 22;
char previousItem_horizontol = ' ';
int turn_horizontol = 0;
bool temp_horizontol = false;
bool gostmovement_horizontol();
bool move_left_3();
bool move_right_3();
bool gameRunning_horizontol = true;

//**********************************
//-----------chasing ghoast-------------------------
bool ghost_chase();
int distance(int p_x, int p_y, int g_x, int g_y);
float directionG[4] = {1, 1, 1, 1};
int small_idx();
char previousItem_chase = ' ';
bool gameRunning_chasing = true;
//-----------------------------------------------
bool gameRunning = true;
int lives = 3;
int turn = 0;

//******************loading header***************************************************************
void show_header()
{
    for (int i = 0; i < 6; i++)
    {
        cout << "\t\t";
        for (int j = 0; j < 42; j++)
        {

            cout << header[i][j];
        }
        cout << endl;
    }
}
void pac_header()
{
    string s;
    fstream f;
    f.open("header.txt", ios::in);
    for (int i = 0; i < 6; i++)
    {
        getline(f, s);
        for (int j = 0; j < 42; j++)
        {
            header[i][j] = s[j];
        }
    }
    f.close();
    show_header();
}
//*************************************************************************************
main()
{

    load();
    bool gameplay = true;
    system("CLS");
    system("Color 3");
    maze_show();
    pac_header();
    gotoxy(pacmanY, pacmanX);
    cout << "P";

    while (lives > 0 || energy > 0)
    {
        Sleep(100);

        gotoxy(pacmanY, pacmanX);

        printScore();

        lives_show();

        energizer_show();
        if (gameRunning == false || gameRunning_vertical == false || gameRunning_horizontol == false || gameRunning_chasing == false)
        {
            lives_counter();
            lives_show();
        }

        gameRunning_vertical = gostmovement_vertical();
        gameRunning_horizontol = gostmovement_horizontol();
        gameRunning_chasing = ghost_chase();
        gameRunning = ghostMovementRand();

        if (GetAsyncKeyState(VK_LEFT))
        {
            movePacmanLeft(); // Function call to move Pacman towards left
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePacmanRight(); // Function call to move Pacman towards right
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePacmanUp(); // Function call to move Pacman towards up
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePacmanDown(); // Function call to move Pacman towards down
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gameRunning = false; // Stop the game
        }
    }
}

//--------------------------------------------------------

void gotoxy(int x, int y) // Function Definition
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void load()
{
    fstream file;
    file.open("pac_data.txt", ios::in);
    string line;
    for (int i = 0; i < 24; i++)
    {
        getline(file, line);
        for (int j = 0; j < 71; j++)
        {
            mazeA[i][j] = line[j];
        }
    }
    file.close();
}

void printScore()
{
    gotoxy(75, 5);
    cout << "_______________________" << endl;

    gotoxy(74, 3);
    cout << " Total Score: " << score << endl
         << endl;
}
void maze_show()
{

    for (int i = 0; i < 24; i++)
    {

        for (int j = 0; j < 70; j++)
        {
            cout << mazeA[i][j];
        }
        cout << endl;
    }

    cout
        << endl;
}
void calculate_score()
{
    score++;
}
void lives_counter()
{
    if (energy < 1)
    {
        lives--;
    }
}
void lives_show()
{
    gotoxy(75, 4);
    cout << "Remaining lives:" << lives;
    if (lives == 0)
    {
        gotoxy(75, 5);
        cout << "Game Over!";
    }
}
void energyzer()
{
    // 30 iteration ghost cant kill
    energy = energy + 30;
}
void energy_loss()
{
    // ghost attack decrease energy 30 iteration does kill pacman

    energy--;
}
void energizer_show()
{
    gotoxy(75, 7);

    cout << "Energy level:" << energy;
}
void movePacmanLeft() // Function call to move Pacman towards lef
{
    if ((mazeA[pacmanX][pacmanY - 1] == ' ') || mazeA[pacmanX][pacmanY - 1] == '.' || mazeA[pacmanX][pacmanY - 1] == '@')
    {
        mazeA[pacmanX][pacmanY] = ' ';

        gotoxy(pacmanY, pacmanX);
        cout << " ";
        if (mazeA[pacmanX][pacmanY - 1] == '.')
        {
            calculate_score();
        }
        if (mazeA[pacmanX][pacmanY - 1] == '@')
        {
            energyzer();
        }
        mazeA[pacmanX][pacmanY - 1] = 'P';
        pacmanY = pacmanY - 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
void movePacmanRight()
{
    if ((mazeA[pacmanX][pacmanY + 1] == ' ') || mazeA[pacmanX][pacmanY + 1] == '.' || mazeA[pacmanX][pacmanY + 1] == '@')
    {
        mazeA[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        if (mazeA[pacmanX][pacmanY + 1] == '.')
        {
            calculate_score();
        }
        if (mazeA[pacmanX][pacmanY + 1] == '@')
        {
            energyzer();
        }
        mazeA[pacmanX][pacmanY + 1] = 'P';
        pacmanY = pacmanY + 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}

void movePacmanUp()
{
    if ((mazeA[pacmanX - 1][pacmanY] == ' ') || mazeA[pacmanX - 1][pacmanY] == '.' || mazeA[pacmanX - 1][pacmanY] == '@')
    {
        mazeA[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        if (mazeA[pacmanX - 1][pacmanY] == '.')
        {
            calculate_score();
        }
        if (mazeA[pacmanX - 1][pacmanY] == '@')
        {
            energyzer();
        }
        mazeA[pacmanX - 1][pacmanY] = 'P';
        pacmanX = pacmanX - 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}
void movePacmanDown()
{

    if ((mazeA[pacmanX + 1][pacmanY] == ' ') || mazeA[pacmanX + 1][pacmanY] == '.' || mazeA[pacmanX + 1][pacmanY] == '@')
    {
        mazeA[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";

        if (mazeA[pacmanX + 1][pacmanY] == '.')
        {
            calculate_score();
        }
        if (mazeA[pacmanX + 1][pacmanY] == '@')
        {
            energyzer();
        }
        mazeA[pacmanX + 1][pacmanY] = 'P';
        pacmanX = pacmanX + 1;
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}

//______________________________________packman movement end____________________________________________________________________________________________
//)**********************************Random movement of ghost"R"**************************************************
int ghostDirection()
{
    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}
bool ghostMovementRand()
{
    int value = ghostDirection();
    if (value == 1)
    {
        // move left in random movement
        if (mazeA[ghostX][ghostY - 1] == ' ' || mazeA[ghostX][ghostY - 1] == '.' || mazeA[ghostX][ghostY - 1] == 'P')
        {
            mazeA[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            cout << previousItem;
            ghostY = ghostY - 1;
            previousItem = mazeA[ghostX][ghostY];
            if (previousItem == 'P')
            {
                previousItem = ' ';
                energy_loss();
                return 0;
            }
            mazeA[ghostX][ghostY] = 'R';
            gotoxy(ghostY, ghostX);
            cout << "R";
        }
    }
    if (value == 2)
    {
        // move right in random movement
        if (mazeA[ghostX][ghostY + 1] == ' ' || mazeA[ghostX][ghostY + 1] == '.' || mazeA[ghostX][ghostY + 1] == 'P')
        {
            mazeA[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            cout << previousItem;
            ghostY = ghostY + 1;
            previousItem = mazeA[ghostX][ghostY];
            if (previousItem == 'P')
            {
                previousItem = ' ';
                energy_loss();
                return 0;
            }
            mazeA[ghostX][ghostY] = 'R';
            gotoxy(ghostY, ghostX);
            cout << "R";
        }
    }
    if (value == 3)
    {
        // move up in random movements
        if (mazeA[ghostX - 1][ghostY] == ' ' || mazeA[ghostX - 1][ghostY] == '.' || mazeA[ghostX - 1][ghostY] == 'P')
        {
            mazeA[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            cout << previousItem;
            ghostX = ghostX - 1;
            previousItem = mazeA[ghostX][ghostY];
            if (previousItem == 'P')
            {
                previousItem = ' ';
                energy_loss();
                return 0;
            }
            mazeA[ghostX][ghostY] = 'R';
            gotoxy(ghostY, ghostX);
            cout << "R";
        }
    }
    if (value == 4)
    {
        // move down in random movement
        if (mazeA[ghostX + 1][ghostY] == ' ' || mazeA[ghostX + 1][ghostY] == '.' || mazeA[ghostX + 1][ghostY] == '.')
        {
            mazeA[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            cout << previousItem;
            ghostX = ghostX + 1;
            previousItem = mazeA[ghostX][ghostY];
            if (previousItem == 'P')
            {
                previousItem = ' ';
                energy_loss();
                return 0;
            }
            mazeA[ghostX][ghostY] = 'R';
            gotoxy(ghostY, ghostX);
            cout << "R";
        }
    }
    return 1;
}
//
bool gostmovement_vertical()
{

    if (turn == 0)
    {
        temp = move_down_1();
        return temp;
    }
    if (turn == 1)
    {
        temp = move_up_1();
        return temp;
    }
}
bool move_up_1()
{
    if (mazeA[ghostX_1 - 1][ghostY_1] == ' ' || mazeA[ghostX_1 - 1][ghostY_1] == '.' || mazeA[ghostX_1 - 1][ghostY_1] == 'P')
    {

        mazeA[ghostX_1][ghostY_1] = previousItem_Vertical;
        gotoxy(ghostY_1, ghostX_1);
        cout << previousItem_Vertical;
        ghostX_1 = ghostX_1 - 1;
        previousItem_Vertical = mazeA[ghostX_1][ghostY_1];
        mazeA[ghostX_1][ghostY_1] = 'U';
        gotoxy(ghostY_1, ghostX_1);
        cout << "U";
    }
    if (ghostX_1 == 2)
    {
        previousItem_Vertical = ' ';
        turn = 0;
    }
    if (previousItem_Vertical != 'P')
    {

        return true;
    }
    previousItem_Vertical = ' ';
    energy_loss();
}
bool move_down_1()
{
    if (mazeA[ghostX_1 + 1][ghostY_1] == ' ' || mazeA[ghostX_1 + 1][ghostY_1] == '.' || mazeA[ghostX_1 + 1][ghostY_1] == 'P')
    {

        mazeA[ghostX_1][ghostY_1] = previousItem_Vertical;
        gotoxy(ghostY_1, ghostX_1);
        cout << previousItem_Vertical;
        ghostX_1 = ghostX_1 + 1;
        previousItem_Vertical = mazeA[ghostX_1][ghostY_1];
        mazeA[ghostX_1][ghostY_1] = 'U';
        gotoxy(ghostY_1, ghostX_1);
        cout << "U";
    }
    if (ghostX_1 == 22)
    {
        previousItem_Vertical = ' ';
        turn = 1;
    }
    if (previousItem_Vertical != 'P')
    {
        return true;
    }
    previousItem_Vertical = ' ';
    energy_loss();
}
//______________________________________end vertically____________________________________________________
//**************************************moving horizontol***************************************************************

bool gostmovement_horizontol()
{

    if (turn_horizontol == 0)
    {
        temp_horizontol = move_right_3();
        return temp_horizontol;
    }
    if (turn_horizontol == 1)
    {
        temp_horizontol = move_left_3();
        return temp_horizontol;
    }
}

bool move_right_3()
{
    if (mazeA[ghostX_3][ghostY_3 + 1] == ' ' || mazeA[ghostX_3][ghostY_3 + 1] == '.' || mazeA[ghostX_3][ghostY_3 + 1] == 'P')
    {

        mazeA[ghostX_3][ghostY_3] = previousItem_horizontol;
        gotoxy(ghostY_3, ghostX_3);
        cout << previousItem_horizontol;
        ghostY_3 = ghostY_3 + 1;
        previousItem_horizontol = mazeA[ghostX_3][ghostY_3];
        mazeA[ghostX_3][ghostY_3] = 'H';
        gotoxy(ghostY_3, ghostX_3);
        cout << "H";
    }
    if (mazeA[ghostX_3][ghostY_3 + 1] == '|')
    {
        previousItem_horizontol = ' ';
        turn_horizontol = 1;
    }
    if (previousItem_horizontol != 'P')
    {

        return true;
    }
    previousItem_horizontol = ' ';
    energy_loss();
}
bool move_left_3()
{
    // 3 is code word for hhorizontol movement of ghoas
    if (mazeA[ghostX_3][ghostY_3 - 1] == ' ' || mazeA[ghostX_3][ghostY_3 - 1] == '.' || mazeA[ghostX_3][ghostY_3 - 1] == 'P')
    {

        mazeA[ghostX_3][ghostY_3] = previousItem_horizontol;
        gotoxy(ghostY_3, ghostX_3);
        cout << previousItem_horizontol;
        ghostY_3 = ghostY_3 - 1;
        previousItem_horizontol = mazeA[ghostX_3][ghostY_3];
        mazeA[ghostX_3][ghostY_3] = 'H';
        gotoxy(ghostY_3, ghostX_3);
        cout << "H";
    }
    if (ghostY_3 == 2)
    {
        previousItem_horizontol = ' ';
        turn_horizontol = 0;
    }
    if (previousItem_horizontol != 'P')
    {

        return true;
    }
    previousItem_horizontol = ' ';
    energy_loss();
}
//***************************************************mvoing horizontol end****************************************
bool ghost_chase()

{

    directionG[0] = distance(pacmanX, pacmanY, ghostX_2, ghostY_2 + 1);
    directionG[1] = distance(pacmanX, pacmanY, ghostX_2, ghostY_2 - 1);
    directionG[2] = distance(pacmanX, pacmanY, ghostX_2 + 1, ghostY_2);
    directionG[3] = distance(pacmanX, pacmanY, ghostX_2 - 1, ghostY_2);
    int small_distance = small_idx();
    if (small_distance == 0)
    {
        // chase_moveRight

        if (mazeA[ghostX_2][ghostY_2 + 1] == ' ' || mazeA[ghostX_2][ghostY_2 + 1] == '.' || mazeA[ghostX_2][ghostY_2 + 1] == 'P')
        {
            mazeA[ghostX_2][ghostY_2] = previousItem_chase;
            gotoxy(ghostY_2, ghostX_2);
            cout << previousItem_chase;
            ghostY_2 = ghostY_2 + 1;
            previousItem_chase = mazeA[ghostX_2][ghostY_2];
            if (previousItem_chase == 'P')
            {
                previousItem_chase = ' ';
                energy_loss();
                return false;
            }
            mazeA[ghostX_2][ghostY_2] = 'G';
            gotoxy(ghostY_2, ghostX_2);
            cout << "G";
        }
        return true;
    }

    if (small_distance == 1)
    {
        // chase_moveLeft
        if (mazeA[ghostX_2][ghostY_2 - 1] == ' ' || mazeA[ghostX_2][ghostY_2 - 1] == '.' || mazeA[ghostX_2][ghostY_2 - 1] == 'P')
        {
            mazeA[ghostX_2][ghostY_2] = previousItem_chase;
            gotoxy(ghostY_2, ghostX_2);
            cout << previousItem_chase;
            ghostY_2 = ghostY_2 - 1;
            previousItem_chase = mazeA[ghostX_2][ghostY_2];
            if (previousItem_chase == 'P')
            {
                previousItem_chase = ' ';
                energy_loss();
                return false;
            }
            mazeA[ghostX_2][ghostY_2] = 'G';
            gotoxy(ghostY_2, ghostX_2);
            cout << "G";
        }
        return true;
    }
    if (small_distance == 2)
    {
        if (mazeA[ghostX_2 + 1][ghostY_2] == ' ' || mazeA[ghostX_2 + 1][ghostY_2] == '.' || mazeA[ghostX_2 + 1][ghostY_2] == 'P')
        {
            mazeA[ghostX_2][ghostY_2] = previousItem_chase;
            gotoxy(ghostY_2, ghostX_2);
            cout << previousItem_chase;
            ghostX_2 = ghostX_2 + 1;
            previousItem_chase = mazeA[ghostX_2][ghostY_2];
            if (previousItem_chase == 'P')
            {
                previousItem_chase = ' ';
                energy_loss();
                return false;
            }
            mazeA[ghostX_2][ghostY_2] = 'G';
            gotoxy(ghostY_2, ghostX_2);
            cout << "G";
        }
        return true;
    }
    if (small_distance == 3)
    {
        // chase_moveUp
        if (mazeA[ghostX_2 - 1][ghostY_2] == ' ' || mazeA[ghostX_2 - 1][ghostY_2] == '.' || mazeA[ghostX_2 - 1][ghostY_2] == 'P')
        {
            mazeA[ghostX_2][ghostY_2] = previousItem_chase;
            gotoxy(ghostY_2, ghostX_2);
            cout << previousItem_chase;
            ghostX_2 = ghostX_2 - 1;
            previousItem_chase = mazeA[ghostX_2][ghostY_2];
            if (previousItem_chase == 'P')
            {
                previousItem_chase = ' ';
                energy_loss();
                return false;
            }
            mazeA[ghostX_2][ghostY_2] = 'G';
            gotoxy(ghostY_2, ghostX_2);
            cout << "G";
        }
        return true;
    }
}
int distance(int p_x, int p_y, int g_x, int g_y)
{
    int d = sqrt(pow((g_x - p_x), 2) + (pow((g_y - p_y), 2)));
    return d;
}
int small_idx()
{
    int small = directionG[0];
    int s_idx = 0;
    for (int i = 1; i < 4; i++)
    {
        if (directionG[i] < small)
        {
            small = directionG[i];
            s_idx = i;
        }
    }

    return s_idx;
}
