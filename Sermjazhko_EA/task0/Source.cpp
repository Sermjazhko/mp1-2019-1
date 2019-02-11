#include <iostream>
#include <clocale> 
using namespace std;

class length
{
  float meters;

public:

  length()
  {
    meters = 0;
  }
  length(float n)
  {
    meters = n;
  }
  void printlen()
  {
    cout << meters << " м.";
  }
  float ft()
  {
    return meters * 3.2808398950131;
  }
  float yard()
  {
    return meters * 1.0936132983;
  }
  float arshin()
  {
    return meters * 1.4060742407199;
  }
  float sazhen()
  {
    return meters * 0.46869141357;
  }
  float inch()
  {
    return meters * 39.37007874016;
  }
};

int main(void)
{
  setlocale(LC_ALL, "Rus");

  float a = -1;
  int unit = -1;

  cout << "¬ведите длину в метрах:\n";
  while (a < 0)
    cin >> a;

  length len(a);

  len.printlen();

  cout << "¬ыберите единицу измерени€:\n0 - ‘ут\n1 - ярд\n2 - јршин\n3 - —ажень\n4 - ƒюйм\n";
  while ((unit < 0) || (unit > 4))
    cin >> unit;

  switch (unit)
  {
  case 0:
    cout << a << " - " << len.ft() << " фута\n";
    break;
  case 1:
    cout << a << " - " << len.yard() << " €рда\n";
    break;
  case 2:
    cout << a << " - " << len.arshin() << " аршина\n";
    break;
  case 3:
    cout << a << " - " << len.sazhen() << " сажней\n";
    break;
  case 4:
    cout << a << " - " << len.inch() << " дюйма\n";
    break;
  }
  cin >> a;
}