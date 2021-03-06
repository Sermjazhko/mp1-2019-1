using namespace std;
class computer
{
  vector <int> x_ship;
  vector <int> y_ship;
public:
  static vector <vector<int>> ship_field;
  computer();
  computer(vector <int> x, vector <int> y);
  computer(const computer &object);
  computer& operator=(const computer &object);
  void print_field();
  bool check(vector <int> x, vector <int> y);
  void creation_ship();
  int get_ship_field(int x, int y);
  ~computer()
  {}
};
vector <vector <int>> computer::ship_field;
computer::computer()
{
  ship_field.resize(10);
  for (int i = 0; i < 10; i++)
  {
    ship_field[i].resize(10);
    for (int j = 0; j < 10; j++)
      ship_field[i][j] = 0;
  }
}
computer::computer(vector <int> x, vector <int> y)
{
  for (int i = 0; i < x.size(); i++)
    ship_field[x[i]][y[i]] = 1;
}
computer::computer(const computer &object)
{
  x_ship = object.x_ship;
  y_ship = object.y_ship;
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      ship_field[i][j] = object.ship_field[i][j];
    }
  }
}
computer& computer::operator=(const computer &object)
{
  if (this == &object)
    return *this;

  x_ship = object.x_ship;
  y_ship = object.y_ship;
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      ship_field[i][j] = object.ship_field[i][j];
    }
  }
  return *this;
}
void computer::print_field()
{
  cout << "#   0 1 2 3 4 5 6 7 8 9 " << endl;
  cout << "  ______________________" << endl;

  for (int i = 0; i < 10; i++)
  {
    cout << i << " |";
    for (int j = 0; j < 10; j++)
    {
      cout << setfill(' ') << setw(2) << ship_field[i][j];
    }
    cout << "|" << endl;
  }
  cout << "  ----------------------" << endl;
}
bool computer::check(vector <int> x, vector <int> y)
{
  for (int j = 0; j < x.size(); j++)
  {
    for (int q = -1; q <= 1; q++)
    {
      if ((y[j] + q >= 0) && (y[j] + q < 10) && (ship_field[x[j]][y[j] + q] == 1))
        return false;
      if ((x[j] + q >= 0) && (x[j] + q < 10) && (ship_field[x[j] + q][y[j]] == 1))
        return false;
      if ((x[j] + q >= 0) && (y[j] + q >= 0) && (x[j] + q < 10) && (y[j] + q < 10) && (ship_field[x[j] + q][y[j] + q] == 1))
        return false;
      if ((x[j] + q >= 0) && (y[j] - q >= 0) && (x[j] + q < 10) && (y[j] - q < 10) && (ship_field[x[j] + q][y[j] - q] == 1))
        return false;
    }
  }
  return true;
}
void computer::creation_ship()
{
  vector <vector <int>> field;
  srand(time(NULL));
  int number_ship = 10;
  int size_ship;
  size_ship = 4;
  vector <int> array_ship = { 0, 0 , 0, 0 };
  while (number_ship != 0)
  {
    int identifier;
    vector <int> c_x;
    vector <int> c_y;
    computer check = { c_x, c_y };
    switch (size_ship)
    {
    case 1:
    {
      if (array_ship[0] == 4)
        number_ship = 0;
      else
      {
        c_x.push_back(rand() % 10);
        c_y.push_back(rand() % 10);
        if (check.check(c_x, c_y))
        {
          check = { c_x, c_y };
          array_ship[0]++;
        }
      }
    }
    break;
    case 2:
    {
      if (array_ship[1] == 3)
        size_ship = 1;
      else
      {
        identifier = rand() % 2 + 1;
        if (identifier == 1) // фиксируем x
        {
          c_x.push_back(rand() % 9);
          c_y.push_back(rand() % 9);
          for (int r = 0; r < 1; r++)
          {
            c_x.push_back(c_x[r]);
            c_y.push_back(c_y[r] + 1);
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
            array_ship[1]++;
          }
        }
        if (identifier == 2) // фиксируем y
        {
          c_x.push_back(rand() % 9);
          c_y.push_back(rand() % 9);
          for (int r = 0; r < 1; r++)
          {
            c_x.push_back(c_x[r] + 1);
            c_y.push_back(c_y[r]);
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
            array_ship[1]++;
          }
        }
      }
    }
    break;
    case 3:
    {
      if (array_ship[2] == 2)
        size_ship = 2;
      else
      {
        identifier = rand() % 2 + 1;
        if (identifier == 1) // фиксируем x
        {
          c_x.push_back(rand() % 8);
          c_y.push_back(rand() % 8);
          for (int r = 0; r < 2; r++)
          {
            c_x.push_back(c_x[r]);
            c_y.push_back(c_y[r] + 1);
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
            array_ship[2]++;
          }
        }
        if (identifier == 2) // фиксируем y
        {
          c_x.push_back(rand() % 8);
          c_y.push_back(rand() % 8);
          for (int r = 0; r < 2; r++)
          {
            c_x.push_back(c_x[r] + 1);
            c_y.push_back(c_y[r]);
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
            array_ship[2]++;
          }
        }
      }
    }
    break;
    case 4:
    {
      if (array_ship[3] == 1)
        size_ship = 3;
      else
      {
        identifier = rand() % 2 + 1;
        if (identifier == 1) // фиксируем x
        {
          c_x.push_back(rand() % 7);
          c_y.push_back(rand() % 7);
          for (int r = 0; r < 3; r++)
          {
            c_x.push_back(c_x[r]);
            c_y.push_back(c_y[r] + 1);
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
            array_ship[3]++;
          }
        }
        if (identifier == 2) // фиксируем y
        {
          c_x.push_back(rand() % 6);
          c_y.push_back(rand() % 6);
          for (int r = 0; r < 3; r++)
          {
            c_x.push_back(c_x[r] + 1);
            c_y.push_back(c_y[r]);
          }
          if (check.check(c_x, c_y))
          {
            check = { c_x, c_y };
            array_ship[3]++;
          }
        }
      }
    }
    break;
    }
  }
}
int computer::get_ship_field(int x, int y)
{
  if (x >= 0 && x < 10 && y >= 0 && y < 10)
    return ship_field[x][y];
  return -1;
}
