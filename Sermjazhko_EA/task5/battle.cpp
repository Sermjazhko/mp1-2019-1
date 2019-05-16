#include <iostream>
#include <vector>
#include <iomanip>
#include <clocale>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "player.h"
#include "computer.h"
using namespace std;
int ship_player = 0;
int ship_computer = 0;

class battle
{
	player player_1;
	computer player_2;
public:
	static vector <vector<int>> battlefield;
	static vector <vector<int>> color_computer;
	static vector <vector<int>> color_player;
	battle();
	battle(player _player_1, computer _player_2);
	bool attack_player(int x, int y);
	bool attack_computer();
	void print_field_();
	~battle()
	{}
};
vector <vector <int>> battle::battlefield;
vector <vector <int>> battle::color_computer;
vector <vector <int>> battle::color_player;
battle::battle()
{
	battlefield.resize(10);
	color_computer.resize(11);
	color_player.resize(11);
	for (int i = 0; i < 10; i++)
	{
		battlefield[i].resize(10);
		color_computer[i].resize(11);
		color_player[i].resize(11);
		for (int
			j = 0; j < 10; j++)
		{
			battlefield[i][j] = 0;
			color_computer[i][j] = 0;
			color_player[i][j] = 0;
		}
	}
}
battle::battle(player _player_1, computer _player_2)
{
	ship_computer = 0;
	ship_player = 0;
	battlefield.resize(10);
	color_computer.resize(11);
	color_player.resize(11);
	for (int i = 0; i < 10; i++)
	{
		battlefield[i].resize(10);
		color_computer[i].resize(11);
		color_player[i].resize(11);
		for (int
			j = 0; j < 10; j++)
		{
			battlefield[i][j] = 0;
			color_computer[i][j] = 0;
			color_player[i][j] = 0;
		}
	}
	player_1 = _player_1;
	player_2 = _player_2;
}
bool battle::attack_player(int x, int y)
{
	if (player_2.get_ship_field(x, y) == 1)
	{
		if (color_player[x][y] == 2 || color_player[x][y] == 1)
		{
			cout << "Вы уже называли эти координаты!" << endl;
			return true;
		}
		cout << "Попал" << endl;
		battlefield[x][y] = 1;
		color_player[x][y] = 2;
		if ((player_2.get_ship_field(x + 1, y) == 1) || (x - 1 >= 0 && player_2.get_ship_field(x - 1, y) == 1) || (y - 1 >= 0 && player_2.get_ship_field(x, y - 1) == 1) || (y + 1 < 10 && player_2.get_ship_field(x, y + 1) == 1))
		{
			int i = 1, j = -1;
			int indet = 0, check = 0;
			while (player_2.get_ship_field(x + i, y) == 1)
			{
				if (color_player[x + i][y] == 2)
					check++;
				indet++;
				i++;
			}
			while (player_2.get_ship_field(x + j, y) == 1)
			{
				if (color_player[x + j][y] == 2)
					check++;
				indet++;
				j--;
			}
			if (check == indet && check != 0)
			{
				if (x + i >= 0 && x + i < 10)
					color_player[x + i][y] = 1;
				if (x + j >= 0 && x + j < 10)
				{
					color_player[x + j][y] = 1;
				}
				for (; j <= i; j++)
				{
					if (x + j >= 0 && x + j < 10)
					{
						if (y + 1 >= 0 && y + 1 < 10)
							color_player[x + j][y + 1] = 1;
						if (y - 1 >= 0 && y - 1 < 10)
							color_player[x + j][y - 1] = 1;
					}
				}
			}
			i = 1;
			j = -1;
			indet = 0;
			check = 0;
			while (player_2.get_ship_field(x, y + i) == 1)
			{
				if (color_player[x][y + i] == 2)
					check++;
				indet++;
				i++;
			}
			while (player_2.get_ship_field(x, y + j) == 1)
			{
				if (color_player[x][y + j] == 2)
					check++;
				indet++;
				j--;
			}
			if (check == indet && check != 0)
			{
				if (y + i >= 0 && y + i < 10)
					color_player[x][y + i] = 1;
				if (y + j >= 0 && y + j < 10)
				{
					color_player[x][y + j] = 1;
				}
				for (; j <= i; j++)
				{
					if (y + j >= 0 && y + j < 10)
					{
						if (x + 1 >= 0 && x + 1 < 10)
							color_player[x + 1][y + j] = 1;
						if (x - 1 >= 0 && x - 1 < 10)
							color_player[x - 1][y + j] = 1;
					}
				}
			}
		}
		else
		{
			for (int q = -1; q <= 1; q++)
			{
				if ((y + q >= 0) && (y + q < 10))
					color_player[x][y + q] = 1;
				if ((x + q >= 0) && (x + q < 10))
					color_player[x + q][y] = 1;
				if ((x + q >= 0) && (y + q >= 0) && (x + q < 10) && (y + q < 10))
					color_player[x + q][y + q] = 1;
				if ((x + q >= 0) && (y - q >= 0) && (x + q < 10) && (y - q < 10))
					color_player[x + q][y - q] = 1;
			}
			color_player[x][y] = 2;
		}
		ship_computer++;
		return true;
	}
	else
	{
		cout << "Промах" << endl;
		color_player[x][y] = 1;
		return false;
	}
}
bool battle::attack_computer()
{
	int x = rand() % 10;
	int y = rand() % 10;
	while (color_computer[x][y] == 2 || color_computer[x][y] == 1)
	{
		x = rand() % 10;
		y = rand() % 10;
	}
	if (player_1.get_player_field(x, y) == 1)
	{
		cout << " Комп попал" << endl;
		color_computer[x][y] = 2;
		if ((player_1.get_player_field(x + 1, y) == 1) || (x - 1 >= 0 && player_1.get_player_field(x - 1, y) == 1) || (y - 1 >= 0 && player_1.get_player_field(x, y - 1) == 1) || (y + 1 < 10 && player_1.get_player_field(x, y + 1) == 1))
		{
			int i = 1, j = -1;
			int indet = 0, check = 0;
			while (player_1.get_player_field(x + i, y) == 1)
			{
				if (color_computer[x + i][y] == 2)
					check++;
				indet++;
				i++;
			}
			while (player_1.get_player_field(x + j, y) == 1)
			{
				if (color_computer[x + j][y] == 2)
					check++;
				indet++;
				j--;
			}
			if (check == indet && check != 0)
			{
				if (x + i >= 0 && x + i < 10)
					color_computer[x + i][y] = 1;
				if (x + j >= 0 && x + j < 10)
				{
					color_computer[x + j][y] = 1;
				}
				for (; j <= i; j++)
				{
					if (x + j >= 0 && x + j < 10)
					{
						if (y + 1 < 10 && y + 1 >= 0)
							color_computer[x + j][y + 1] = 1;
						if (y + 1 < 10 && y - 1 >= 0)
							color_computer[x + j][y - 1] = 1;
					}
				}
			}
			i = 1;
			j = -1;
			indet = 0;
			check = 0;
			while (player_1.get_player_field(x, y + i) == 1)
			{
				if (color_computer[x][y + i] == 2)
					check++;
				indet++;
				i++;
			}
			while (player_1.get_player_field(x, y + j) == 1)
			{
				if (color_computer[x][y + j] == 2)
					check++;
				indet++;
				j--;
			}
			if (check == indet && check != 0)
			{
				if (y + i >= 0 && y + i < 10)
					color_computer[x][y + i] = 1;
				if (y + j >= 0 && y + j < 10)
				{
					color_computer[x][y + j] = 1;
				}
				for (; j <= i; j++)
				{
					if (y + j >= 0 && y + j < 10)
					{
						if (x + 1 >= 0 && x + 1 < 10)
							color_computer[x + 1][y + j] = 1;
						if (x - 1 >= 0 && x - 1 < 10)
							color_computer[x - 1][y + j] = 1;
					}
				}

			}
		}
		else
		{
			for (int q = -1; q <= 1; q++)
			{
				if ((y + q >= 0) && (y + q < 10))
					color_computer[x][y + q] = 1;
				if ((x + q >= 0) && (x + q < 10))
					color_computer[x + q][y] = 1;
				if ((x + q >= 0) && (y + q >= 0) && (x + q < 10) && (y + q < 10))
					color_computer[x + q][y + q] = 1;
				if ((x + q >= 0) && (y - q >= 0) && (x + q < 10) && (y - q < 10))
					color_computer[x + q][y - q] = 1;
			}
			color_computer[x][y] = 2;
		}
		ship_player++;
		return true;
	}
	else
	{
		cout << " Комп промазал" << endl;
		color_computer[x][y] = 1;
		return false;
	}
}
void battle::print_field_()
{
	cout << "#   0 1 2 3 4 5 6 7 8 9     #   0 1 2 3 4 5 6 7 8 9 " << endl;
	cout << "  ______________________      ______________________" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << " |";
		for (int j = 0; j < 10; j++)
		{
			HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
			if (color_computer[i][j] == 2)
			{
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << setfill(' ') << setw(2) << player_1.player_field[i][j];
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			if (color_computer[i][j] == 1)
			{
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << setfill(' ') << setw(2) << player_1.player_field[i][j];
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			if (color_computer[i][j] == 0)
				cout << setfill(' ') << setw(2) << player_1.player_field[i][j];
		}
		cout << "|    ";
		cout << i << " |";
		for (int j = 0; j < 10; j++)
		{
			HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
			if (color_player[i][j] == 2)
			{
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << setfill(' ') << setw(2) << battlefield[i][j];
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			if (color_player[i][j] == 1)
			{
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << setfill(' ') << setw(2) << battlefield[i][j];
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			if (color_player[i][j] == 0)
				cout << setfill(' ') << setw(2) << battlefield[i][j];
		}
		cout << "|" << endl;
	}
	cout << "  ----------------------      ----------------------" << endl;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	computer play_2;
	player play_1;
	battle PLAY = { play_1, play_2 };;
	play_2.creation_ship();
	play_1.creation_ship();
	while (ship_computer != 20 && ship_player != 20)
	{
		if (ship_computer == 20)
		{
			cout << "Вы победили!" << endl;
			break;
		}
		if (ship_player == 20)
			cout << "Вы проиграли, лол!" << endl;
		int x, y;
		do {
			PLAY.print_field_();
			do {
				cout << "Введите координаты для атаки: " << endl;
				cin >> x >> y;
			} while ((x > 9 || x < 0 || y < 0 || y>10));
			clrscr();
		} while (PLAY.attack_player(x, y));
		do {
		} while (PLAY.attack_computer());
	}
	int stop_pr;
	cin >> stop_pr;
}
