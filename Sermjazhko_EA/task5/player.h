﻿using namespace std;
void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);
	WORD Attr;
	DWORD Count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

	int col = Attr;
	int width = buf.dwSize.X;
	int height = buf.dwSize.Y;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;
	SetConsoleCursorPosition(Console, zpos);

	FillConsoleOutputAttribute(Console, col, width * height, zpos, &Count);
	FillConsoleOutputCharacter(Console, ' ', width * height, zpos, &Count);
}
class player
{
  vector <int> x_ship;
  vector <int> y_ship;
public:
  static vector <vector<int>> player_field;
  player();
  player(vector <int> x, vector <int> y);
  player(const player &object);
  player& operator=(const player &object);
  void print_field();
  bool check(vector <int> x, vector <int> y);
  void creation_ship();//забивание поля
  int get_player_field(int x, int y);
  ~player()
  {}
};
vector <vector <int>> player::player_field;
player::player()
{
  player_field.resize(10);
  for (int i = 0; i < 10; i++)
  {
    player_field[i].resize(10);
    for (int j = 0; j < 10; j++)
      player_field[i][j] = 0;
  }
}
player::player(vector <int> x, vector <int> y)
{
  for (int i = 0; i < x.size(); i++)
    player_field[x[i]][y[i]] = 1;
}
player::player(const player &object)
{
  x_ship = object.x_ship;
  y_ship = object.y_ship;
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      player_field[i][j] = object.player_field[i][j];
    }
  }
}
player& player::operator=(const player &object)
{
  if (this == &object)
    return *this;
  x_ship = object.x_ship;
  y_ship = object.y_ship;
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
      player_field[i][j] = object.player_field[i][j];
  }
  return *this;
}
void player::print_field()
{
  cout << "#   0 1 2 3 4 5 6 7 8 9 " << endl;
  cout << "  ______________________" << endl;

  for (int i = 0; i < 10; i++)
  {
    cout << i << " |";
    for (int j = 0; j < 10; j++)
    {
      cout << setfill(' ') << setw(2) << player_field[i][j];
    }
    cout << "|" << endl;
  }
  cout << "  ----------------------" << endl;
}

bool player::check(vector <int> x, vector <int> y)
{
  for (int j = 0; j < x.size(); j++)
  {
    for (int q = -1; q <= 1; q++)
    {
      if ((y[j] + q >= 0) && (y[j] + q < 10) && (player_field[x[j]][y[j] + q] == 1))
        return false;
      if ((x[j] + q >= 0) && (x[j] + q < 10) && player_field[x[j] + q][y[j]] == 1)
        return false;
      if ((x[j] + q >= 0) && (y[j] + q >= 0) && (x[j] + q < 10) && (y[j] + q < 10) && player_field[x[j] + q][y[j] + q] == 1)
        return false;
      if ((x[j] + q >= 0) && (y[j] - q >= 0) && (x[j] + q < 10) && (y[j] - q < 10) && (player_field[x[j] + q][y[j] - q] == 1))
        return false;
    }
  }
  return true;
}
void player::creation_ship()
{
  vector <vector <int>> field;
  int number_ship = 10;
  vector <int> array_ship = { 0, 0 , 0, 0 };
  while (number_ship != 0)
  {
    int size_ship;
    int x, y;
    int identifier;
    vector <int> c_x;
    vector <int> c_y;
    player check = { c_x, c_y };
    cout << "Сколько палуб?  ";
    cin >> size_ship;
    switch (size_ship)
    {
    case 1:
    {
      if (array_ship[0] == 4)
        cout << "Израсходованы попытки" << endl;
      else
      {
        cout << "Введите координаты коробля (сначала строки): ";
        cin >> x >> y;
        c_x.push_back(x);
        c_y.push_back(y);
        if (check.check(c_x, c_y))
        {
          check = { c_x, c_y };
		  clrscr();
          check.print_field();
          array_ship[0]++;
          number_ship--;
        }
        else
          cout << "Нельзя пересекать корабли и ставить их рядом " << endl;
      }
    }
    break;
    case 2:
    {
      if (array_ship[1] == 3)
        cout << "Израсходованы попытки" << endl;
      else
      {
        cout << "По горизонтали - 1, по вертикали - 2: ";
        cin >> identifier;
        if (identifier == 1) // фиксируем x
        {
          cout << "Введите координаты коробля (сначала строки): ";
          cin >> x >> y;
          c_x.push_back(x);
          c_y.push_back(y);
          do
          {
            cout << "Введите координату след. столбца: ";
            cin >> y;
          } while (y == c_y[0] || y > c_y[0] + 1 || y < c_y[0] - 1);
          c_x.push_back(x);
          c_y.push_back(y);
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
			clrscr();
            check.print_field();
            array_ship[1]++;
            number_ship--;
          }
          else
            cout << "Нельзя пересекать корабли и ставить их рядом " << endl;
        }
        if (identifier == 2) // фиксируем y
        {
          cout << "Введите координаты коробля (сначала строки): ";
          cin >> x >> y;
          c_x.push_back(x);
          c_y.push_back(y);
          do
          {
            cout << "Введите координату след. строки: ";
            cin >> x;
          } while (x == c_x[0] || x > c_x[0] + 1 || x < c_x[0] - 1);
          c_x.push_back(x);
          c_y.push_back(y);
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
			clrscr();
            check.print_field();
            array_ship[1]++;
            number_ship--;
          }
          else
            cout << "Нельзя пересекать корабли и ставить их рядом " << endl;
        }
      }
    }
    break;
    case 3:
    {
      if (array_ship[2] == 2)
        cout << "Израсходованы попытки" << endl;
      else
      {
        cout << "По горизонтали - 1, по вертикали - 2: ";
        cin >> identifier;
        if (identifier == 1) // фиксируем x
        {
          int index = 0;
          cout << "Введите координаты коробля (сначала строки): ";
          cin >> x >> y;
          c_x.push_back(x);
          c_y.push_back(y);
          while (index != 2)
          {
            cout << "Введите координату след. столбца: ";
            cin >> y;
            if (y != c_y[0] && y <= c_y[0] + 1 && y >= c_y[0] - 1)
            {
              c_x.push_back(x);
              c_y.push_back(y);
              index++;
            }
            if (index == 1)
              if (y != c_y[1] && y <= c_y[1] + 1 && y >= c_y[1] - 1)
              {
                index++;
                c_x.push_back(x);
                c_y.push_back(y);
              }
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
			clrscr();
            check.print_field();
            array_ship[2]++;
            number_ship--;
          }
          else
            cout << "Нельзя пересекать корабли и ставить их рядом " << endl;
        }
        if (identifier == 2) // фиксируем y
        {
          int index = 0;
          cout << "Введите координаты коробля (сначала строки): ";
          cin >> x >> y;
          c_x.push_back(x);
          c_y.push_back(y);
          while (index != 2)
          {
            cout << "Введите координату след. строки: ";
            cin >> x;
            if (x != c_x[0] && x <= c_x[0] + 1 && x >= c_x[0] - 1)
            {
              c_x.push_back(x);
              c_y.push_back(y);
              index++;
            }
            if (index == 1)
              if (x != c_x[1] && x <= c_x[1] + 1 && x >= c_x[1] - 1)
              {
                index++;
                c_x.push_back(x);
                c_y.push_back(y);
              }
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
			clrscr();
            check.print_field();
            array_ship[2]++;
            number_ship--;
          }
          else
            cout << "Нельзя пересекать корабли и ставить их рядом " << endl;
        }
      }
    }
    break;
    case 4:
    {
      if (array_ship[3] == 1)
        cout << "Израсходованы попытки" << endl;
      else
      {
        cout << "По горизонтали - 1, по вертикали - 2: ";
        cin >> identifier;
        if (identifier == 1) // фиксируем x
        {
          int index = 0;
          cout << "Введите координаты коробля (сначала строки): ";
          cin >> x >> y;
          c_x.push_back(x);
          c_y.push_back(y);
          while (index != 3)
          {
            cout << "Введите координату след. столбца: ";
            cin >> y;
            if (y != c_y[0] && y <= c_y[0] + 1 && y >= c_y[0] - 1)
            {
              c_x.push_back(x);
              c_y.push_back(y);
              index++;
            }

            if (index >= 1)
              if (y != c_y[1] && y <= c_y[1] + 1 && y >= c_y[1] - 1)
              {
                index++;
                c_x.push_back(x);
                c_y.push_back(y);
              }
            if (index == 2)
              if (y != c_y[2] && y <= c_y[2] + 1 && y >= c_y[2] - 1)
              {
                index++;
                c_x.push_back(x);
                c_y.push_back(y);
              }
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
			clrscr();
            check.print_field();
            array_ship[3]++;
            number_ship--;
          }
          else
            cout << "Нельзя пересекать корабли и ставить их рядом " << endl;
        }
        if (identifier == 2) // фиксируем y
        {
          int index = 0;
          cout << "Введите координаты коробля (сначала строки): ";
          cin >> x >> y;
          c_x.push_back(x);
          c_y.push_back(y);
          while (index != 3)
          {
            cout << "Введите координату след. строки: ";
            cin >> x;
            if (x != c_x[0] && x <= c_x[0] + 1 && x >= c_x[0] - 1)
            {
              c_x.push_back(x);
              c_y.push_back(y);
              index++;
            }
            if (index >= 1)
              if (x != c_x[1] && x <= c_x[1] + 1 && x >= c_x[1] - 1)
              {
                index++;
                c_x.push_back(x);
                c_y.push_back(y);
              }
            if (index == 2)
              if (x != c_x[2] && x <= c_x[2] + 1 && x >= c_x[2] - 1)
              {
                index++;
                c_x.push_back(x);
                c_y.push_back(y);
              }
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
			clrscr();
            check.print_field();
            array_ship[3]++;
            number_ship--;
          }
          else
            cout << "Нельзя пересекать корабли и ставить их рядом " << endl;
        }
      }
    }
    break;
    default:
    {
      cout << "Нет такого корабля" << endl;
    }
    break;
    }
  }
}
int player::get_player_field(int x, int y)
{
  if (x >= 0 && x < 10 && y >= 0 && y < 10)
    return player_field[x][y];
  return -1;
}
