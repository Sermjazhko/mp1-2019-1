#include <iostream>
#include <string>
using namespace std;
class Date
{
  int year;
  int month;
  int day;
  int index_time;
  int index_temperature;
public:
  Date(int _year, int _month, int _day); //конструктор инициализации
  Date(const Date &object); //конструктор копирования
  Date& operator=(const Date &object); // оператор присваивания
  int get_year(const Date &object);
  int get_month(const Date &object);
  int get_day(const Date &object);
  friend ostream& operator<< (ostream &out, const Date &object); // вывод
  friend istream& operator>> (std::istream &in, Date &object); // ввод
  ~Date() // деструктор
  {}
};
Date::Date(int _year = 2000, int _month = 1, int _day = 1)
{
  year = _year;
  month = _month;
  day = _day;
  index_time = 0;
  index_temperature = 0;
}
Date::Date(const Date &object)
{
  year = object.year;
  month = object.month;
  day = object.day;
  index_time = object.index_time;
  index_temperature = object.index_temperature;
}
Date& Date::operator=(const Date &object)
{
  if (this == &object)
    return *this;
  year = object.year;
  month = object.month;
  day = object.day;
  index_time = object.index_time;
  index_temperature = object.index_temperature;
  return *this;
}
int Date::get_year(const Date &object)
{
  return object.year;
}
int Date::get_month(const Date &object)
{
  return object.month;
}
int Date::get_day(const Date &object)
{
  return object.day;
}
ostream& operator<< (ostream &out, const Date &object)
{
  out << "Date: " << object.day << "." << object.month << "." << object.year << endl;
  return out;
}
istream& operator>> (std::istream &in, Date &object)
{
  in >> object.year;
  in >> object.month;
  in >> object.day;
  return in;
}
