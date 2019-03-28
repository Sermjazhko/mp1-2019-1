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
  bool check_date(Date &object); //проверка на наличие даты
  int time_index(const Date &object); // показывает, где курсор времени
  int temperature_index(const Date &object); // показывает, где курсор температуры
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
bool Date::check_date(Date &object)
{
  int const N = 256;
  int index = 0;
  int index_string = 0;
  string date;
  int  size_array;
  ifstream fin("Thermometer.txt");
  char ArrayWord[N] = { "" };
  if ((object.day / 10) != 0)
    date += ((object.day / 10) + '0');
  date += ((object.day % 10) + '0');
  if ((object.month / 10) != 0)
    date += ((object.month / 10) + '0');
  date += ((object.month % 10) + '0');
  date += ((object.year / 1000) + '0');
  date += ((object.year % 1000) / 100 + '0');
  date += ((object.year % 100) / 10 + '0');
  date += ((object.year % 10) + '0');
  while (!fin.eof())
  {
    fin.getline(ArrayWord, N);
    size_array = strlen(ArrayWord);
    index_string += size_array + 2;
    if (ArrayWord[6] == date[0])
    {
      for (int j = 6, i = 0; j < size_array; j++, i++)
      {
        if (ArrayWord[j] == '.')
          j++;
        if (ArrayWord[j] == date[i])
        {
          index++;
          if (index == (size_array - 8))
          {
            object.index_time = index_string;
            fin.getline(ArrayWord, N);
            object.index_temperature = index_string + strlen(ArrayWord) + 2;
            fin.close();
            return true;
          }
        }
        else
          index = 0;
      }
    }
  }
  index_string = 0;
  fin.close();
  return false;
}
int Date::time_index(const Date &object)
{
  return object.index_time;
}
int Date::temperature_index(const Date &object)
{
  return object.index_temperature;
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
