#include <iostream>
#include <string>
using namespace std;
class Data
{
  int year;
  int month;
  int day;
  int index_time;
  int index_temperature;
public:
  Data(); //по умолчанию
  Data(int _year, int _month, int _day); //конструктор инициализации
  Data(const Data &object); //конструктор копирования
  Data& operator=(const Data &object); // оператор присваивания
  bool check_data(Data &object); //проверка на наличие даты
  int time_index(const Data &object); // показывает, где курсор времени
  int temperature_index(const Data &object); // показывает, где курсор температуры
  friend ostream& operator<< (ostream &out, const Data &object); // вывод
  friend istream& operator>> (std::istream &in, Data &object); // ввод
  ~Data() // деструктор
  {}
};
Data::Data()
{
  year = 2000;
  month = 12;
  day = 23;
  index_time = 0;
  index_temperature = 0;
}
Data::Data(int _year, int _month, int _day)
{
  year = _year;
  month = _month;
  day = _day;
  index_time = 0;
  index_temperature = 0;
}
Data::Data(const Data &object)
{
  year = object.year;
  month = object.month;
  day = object.day;
  index_time = object.index_time;
  index_temperature = object.index_temperature;
}
Data& Data::operator=(const Data &object)
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
bool Data::check_data( Data &object)
{
  int const N = 256;
  int index = 0;
  int index_string = 0;
  string data;
  int  size_array;
  ifstream fin("Thermometer.txt");
  char ArrayWord[N] = { "" };
  if ((object.day / 10) != 0)
    data += ((object.day / 10) + '0');
  data += ((object.day % 10) + '0');
  if ((object.month / 10) != 0)
    data += ((object.month / 10) + '0');
  data += ((object.month % 10) + '0');
  data += ((object.year / 1000) + '0');
  data += ((object.year % 1000) / 100 + '0');
  data += ((object.year % 100) / 10 + '0');
  data += ((object.year % 10) + '0');
  while (!fin.eof())
  {
    fin.getline(ArrayWord, N);
    size_array = strlen(ArrayWord);
    index_string += size_array + 2;
    if (ArrayWord[6] == data[0])
    {
        for (int j = 6, i = 0; j < size_array; j++, i++)
        {
          if (ArrayWord[j] == '.')
            j++;
          if (ArrayWord[j] == data[i])
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
int Data::time_index(const Data &object)
{
  return object.index_time;
}
int Data::temperature_index(const Data &object)
{
  return object.index_temperature;
}
ostream& operator<< (ostream &out, const Data &object)
{
  out << "Data: " << object.day << "." << object.month << "." << object.year << endl;
  return out;
}
istream& operator>> (std::istream &in, Data &object)
{
  in >> object.year;
  in >> object.month;
  in >> object.day;
  return in;
}