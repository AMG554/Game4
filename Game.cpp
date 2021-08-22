#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING // Needed with c++17
#include <iostream>
#include <string>
#include "textpixels.h"
#include "textpixels_enums.h"
#include <Windows.h>

using namespace textpixels;
using namespace std;


char space[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
int row;
int column;
char token = 'X';
bool tie = false;
string n1 = " ";
string n2 = " ";
int digit;

const int LEVEL_WIDTH = 35;
const int LEVEL_HEIGHT = 15;
const int GUI_HEIGHT = 10;
const int WALL_LEFT = 0;                                     // constant 'variables'
const int WALL_RIGHT = LEVEL_WIDTH - 1;
const int WALL_TOP = 0;
const int WALL_BOTTOM = LEVEL_HEIGHT - 1;

enum Screen
{
	MENU = 1,
	PLAY,
	SCORE,
	PAUSE,
	GAMEOVER,
	EXIT,
	NONE
};


int displayMenuScreen()
{
	// 60fps is plenty fast for a menu.
	textpixels::setFps(60);
	int choice = Screen::NONE;
	do                            // Keeps looping, waiting for input
	{
		textpixels::startFrame();   // Needed always at start of game loop
		fillWindow(FG_DARK_BLUE);
		fillRect(1, 1, LEVEL_WIDTH - 2, LEVEL_HEIGHT + 8, FG_BLACK);
		drawString(5, 5, "(P) PLAY Snake!", layerColours(FG_WHITE, BG_DARK_MAGENTA));
		drawString(5, 8, "(X) exit", layerColours(FG_BLACK, BG_WHITE));
		drawString(5, 10, "(S) Scoreboard", layerColours(FG_BLACK, BG_WHITE));


		if (keyIsDown('P'))
		{
			choice = Screen::PLAY;
		}
		else if (keyIsDown('X'))
		{
			choice = Screen::EXIT;
		}
		else if (keyIsDown('S'))
		{
			choice = Screen::SCORE;
		}
		textpixels::endFrame();     // Needed always at end of game loop.
	} while (choice == Screen::NONE);     // Only stop when playerHasQuit  
	return(choice);
}
void functionOne()
{
	system("cls");
	cout << "   |   |   " << endl;
	cout << " " << space[0][0] << " " << "|" << " " << space[0][1] << " " << "|" << " " << space[0][2] << " " << endl;
	cout << "___|___|___" << endl;
	cout << "   |   |   " << endl;
	cout << " " << space[1][0] << " " << "|" << " " << space[1][1] << " " << "|" << " " << space[1][2] << " " << endl;
	cout << "___|___|___" << endl;
	cout << "   |   |   " << endl;
	cout << " " << space[2][0] << " " << "|" << " " << space[2][1] << " " << "|" << " " << space[2][2] << " " << endl;
	cout << "   |   |   " << endl;
}

void functionTwo()
{

	if (token == 'X')
	{
		cout << n1 << " Enter";
		cin >> digit;
	}
	if (token == 'O')
	{
		cout << n2 << " Enter";
		cin >> digit;
	}

	if (digit == 1)
	{
		row = 0;
		column = 0;
	}
	if (digit == 2)
	{
		row = 0;
		column = 1;
	}
	if (digit == 3)
	{
		row = 0;
		column = 2;
	}
	if (digit == 4)
	{
		row = 1;
		column = 0;
	}
	if (digit == 5)
	{
		row = 1;
		column = 1;
	}
	if (digit == 6)
	{
		row = 1;
		column = 2;
	}
	if (digit == 7)
	{
		row = 2;
		column = 0;
	}
	if (digit == 8)
	{
		row = 2;
		column = 1;
	}
	if (digit == 9)
	{
		row = 2;
		column = 2;
	}
	else if (digit < 1 && digit >9)
	{
		cout << "Invalid !! " << endl;
	}

	if (token == 'X' && space[row][column] != 'x' && space[row][column] != 'O')
	{
		space[row][column] = 'X';
		token = 'O';
	}
	else if (token == 'O' && space[row][column] != 'X' && space[row][column] != 'O')
	{
		space[row][column] = 'O';
		token = 'X';
	}
	else
	{
		cout << "There is no empty space!" << endl;
		functionTwo();
	}

	functionOne();

}

bool functionThree(bool tie)
{
	tie = true;
	for (int i = 0; i < 3; i++)
	{
		if (space[i][0] == space[i][1] && space[i][0] == space[i][2] || space[0][i] == space[1][i] && space[0][i] == space[i][2])
			return true;
	}
	if (space[0][0] == space[1][1] && space[1][1] == space[2][2] || space[0][2] == space[1][1] && space[1][1] == space[2][0])
	{
		return true;
	}

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (space[i][j] != 'X' && space[i][j] != 'O')
			{
				return false;
			}
		}
	}
}
int main(bool tie)
{
	// textpixels creates our 30x30 console window
	textpixels::setupConsole(LEVEL_WIDTH, LEVEL_HEIGHT + GUI_HEIGHT, 15, 15);
	// 'screen' as a term for the Menu screen
	int screen = Screen::MENU;    // Start the game at the menu.
	int scoreX = 0;
	int scoreO = 0;

	while (screen != Screen::EXIT)   // Outermost loop of the whole program
	{
		if (screen == Screen::MENU)
		{
			screen = displayMenuScreen();
		}
		else if (screen == Screen::SCORE)
		{
			system("cls");
			cout << "X won " << scoreX << " times" << endl;
			cout << "O won " << scoreO << " times" << endl;
		}
		else if (screen == Screen::PLAY)
		{
			system("cls");
			cout << " Enter name. Player 1 : " << endl;
			cin >> n1;
			cout << " Enter name. Player 2 : " << endl;
			cin >> n2;
			cout << n1 << " make the first play. " << endl;
			cout << n2 << " make the second play. " << endl;
			Sleep(1000);
			while (!functionThree(tie))
			{
				functionOne();
				functionTwo();
				functionThree(tie);
			}
			if (token == 'X' && tie == false)
			{
				cout << n2 << "Wins!!" << endl;
				scoreX += 1;
				break;
			}
			else if (token == 'O' && tie == false)
			{
				cout << n1 << "Wins!!" << endl;
				scoreO += 1;
				break;
			}
			else
			{
				cout << "It's a draw" << endl;
				break;
			}
		}
	}
}

