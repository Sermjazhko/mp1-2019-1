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
  length(const length &len)
  {
    meters = len.meters;
  }
  length& operator=(const length &len)
  {
    meters = len.meters;
    return *this;
  }
  void printlen()
  {
    cout << meters << " м. ";
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
  cout << "Введите длину в метрах:\n";
  do
  {
    cin >> a;
    if (a < 0)
      cout << "Неверные данные, попробуйте ещё раз:\n";
  } while (a < 0);
  length len(a);
  length check;

  check = len;
  cout << "Выберите единицу измерения:\n0 - Фут\n1 - Ярд\n2 - Аршин\n3 - Сажень\n4 - Дюйм\n";
  do
  {
    cin >> unit;
    if ((unit < 0) || (unit > 4))
      cout << "Неверные данные, попробуйте ещё раз:\n";
  } while ((unit < 0) || (unit > 4));
  switch (unit)
  {
  case 0:
    check.printlen();
    cout << "это " << len.ft() << " фута\n";
    break;
  case 1:
    check.printlen();
    cout << "это " << len.yard() << " ярда\n";
    break;
  case 2:
    check.printlen();
    cout << "это " << len.arshin() << " аршина\n";
    break;
  case 3:
    check.printlen();
    cout << "это " << len.sazhen() << " сажней\n";
    break;
  case 4:
    check.printlen();
    cout << "это " << len.inch() << " дюйма\n";
    break;
  }
  cin >> a;
}
