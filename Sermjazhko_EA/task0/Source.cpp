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
    cout << meters << " �.";
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

  cout << "������� ����� � ������:\n";
  while (a < 0)
    cin >> a;

  length len(a);

  len.printlen();

  cout << "�������� ������� ���������:\n0 - ���\n1 - ���\n2 - �����\n3 - ������\n4 - ����\n";
  while ((unit < 0) || (unit > 4))
    cin >> unit;

  switch (unit)
  {
  case 0:
    cout << a << " - " << len.ft() << " ����\n";
    break;
  case 1:
    cout << a << " - " << len.yard() << " ����\n";
    break;
  case 2:
    cout << a << " - " << len.arshin() << " ������\n";
    break;
  case 3:
    cout << a << " - " << len.sazhen() << " ������\n";
    break;
  case 4:
    cout << a << " - " << len.inch() << " �����\n";
    break;
  }
  cin >> a;
}