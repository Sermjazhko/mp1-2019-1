#include <iostream>
using namespace std;
class Thermometer //Ќј„јЋ№Ќјя ƒј“ј ЌјЅЋёƒ≈Ќ»я (!)
{
  int year;
  int month;
  int day;
  int time;
  char temperature[24];
public:
  Thermometer(); //конструктор по умолчанию
  Thermometer(int _year, int _month, int _day, int _time, int _temperature); //конструктор инициализации
  Thermometer(const Thermometer &observation); //конструктор копировани€
  Thermometer& operator=(const Thermometer &observation); // оператор присваивани€
 // void set_observation(); // задать наблюдение
  void get_observation(); // узнать наблюдение
  int get_temperature(int _year, int _month, int _day, int _time); //узнать температуру в выбранном наблюдении
  int get_average_temperature(int _year, int _month, int _day); //узнать среднюю температуру в выбранном наблюдении
  int get_av_temp_d_or_n(int _year, int _month, int index); //узнать среднюю дневную или ночную температуру в наблюдении
  void observation_file(); //сохранить историю наблюдений в файл
  void print_observation(); //считать историю наблюдений из файла
  ~Thermometer() //деструктор
  {}
};
Thermometer::Thermometer()
{
  year = 2000;
  month = 01;
  day = 01;
  time = 0;
  for (int i = 0; i < 24; i++)
    temperature[i] = '-';
}
Thermometer::Thermometer(int _year, int _month, int _day, int _time, int _temperature)
{
  year = _year;
  month = _month;
  day = _day;
  time = _time;
  temperature[_time] = _temperature;
  for (int i = 0; i < 24; i++)
    if (i!=_time)
      temperature[i] = '-';
}
Thermometer::Thermometer(const Thermometer &observation)
{
  year = observation.year;
  month = observation.month;
  day = observation.day;
  time = observation.time;
  temperature[time] = observation.temperature[time];
  for (int i = 0; i < 24; i++)
  {
    temperature[i] = observation.temperature[i];
  }
}
Thermometer& Thermometer::operator=(const Thermometer &observation)
{
  if (this == &observation)
    return *this;
  year = observation.year;
  month = observation.month;
  day = observation.day;
  time = observation.time;
  for (int i = 0; i < 24; i++)
  {
    temperature[i] = observation.temperature[i];
  }
  return *this;

}
//void Thermometer::set_observation(){}
void Thermometer::get_observation()
{
  cout << year << endl << month << endl << day << endl << time << endl << temperature[time] << endl;
  cout << "All temperature:" << endl;
  for (int i = 0; i < 24; i++)
  {
    cout << temperature[i] << endl;
  }
}
int Thermometer::get_temperature(int _year, int _month, int _day, int _time)
{
  return 0;
}
int Thermometer::get_average_temperature(int _year, int _month, int _day)
{
  return 0;
}
int Thermometer::get_av_temp_d_or_n(int _year, int _month, int index)
{
  return 0;
}
void Thermometer::observation_file()
{

}
void Thermometer::print_observation()
{

}
int main()
{
  int l;
  Thermometer a(2000, 9, 1, 12, 35);
  a.get_observation();

  cout << endl << "END PROGRAMM";
  cin >> l;
}