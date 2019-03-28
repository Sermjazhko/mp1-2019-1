#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include "Date.h"
using namespace std;
class Thermometer
{
  Date observation_date;
  int time[24];
  int temperature[24];
public:
  Thermometer(); //конструктор по умолчанию
  Thermometer(Date observation, int _time, int _temperature); //конструктор инициализации
  Thermometer(const Thermometer &observation); //конструктор копирования
  Thermometer& operator=(const Thermometer &observation); // оператор присваивания
  void series_observation(Date observation, int number, int *_time, int *_temperature); // задать наблюдение или серию 
  void get_observation(); // вывести начальную дату
  string Get_temperature(Date observation); //узнать температуру в выбранном наблюдении
  double get_average_temperature(Date observation, int index_dat, int check_month); //узнать среднюю температуру в выбранном наблюдении
  double get_av_temp_d_or_n(Date observation, int index, int check_month); //узнать среднюю дневную или ночную температуру в наблюдении
  void observation_file(const Thermometer &observation); //сохранить историю наблюдений в файл
  void print_observation(); //считать историю наблюдений из файла
  ~Thermometer() //деструктор
  {}
};
Thermometer::Thermometer()
{
  observation_date = { 2000, 1, 1 };
  for (int i = 0; i < 24; i++)
    time[i] = -1;
  for (int i = 0; i < 24; i++)
    temperature[i] = -289;
}
Thermometer::Thermometer(Date observation, int _time, int _temperature)
{
  observation_date = observation;
  time[_time] = _time;
  temperature[_time] = _temperature;
}
Thermometer::Thermometer(const Thermometer &observation)
{
  observation_date = observation.observation_date;
  for (int i = 0; i < 24; i++)
  {
    time[i] = observation.time[i];
    temperature[time[i]] = observation.temperature[time[i]];
  }
}
Thermometer& Thermometer::operator=(const Thermometer &observation)
{
  if (this == &observation)
    return *this;
  observation_date = observation.observation_date;
  for (int i = 0; i < 24; i++)
  {
    time[i] = observation.time[i];
    temperature[i] = observation.temperature[i];
  }
  return *this;
}
void Thermometer::series_observation(Date observation, int number, int *_time, int *_temperature)
{
  observation_date = observation;
  for (int i = 0; i < number; i++)
  {
    time[_time[i]] = _time[i];
    temperature[_time[i]] = _temperature[i];
  }
}
void Thermometer::get_observation()
{
  int index = 0;
  int const N = 256;
  ifstream fin("Thermometer.txt");
  char ArrayWord[N] = { "" };
  cout << "Start data:" << endl;
  while (index != 3)
  {
    fin.getline(ArrayWord, N);
    cout << ArrayWord << endl; //Вывод строки
    index++;
  }
  fin.close();
}
string Thermometer::Get_temperature(Date observation)
{
  int const N = 256;
  int index = 0;
  int number = 0;
  string str = "False";
  int size_array;
  ifstream fin("Thermometer.txt");
  char ArrayWord[N] = { "" };
  if (observation.check_date(observation))
  {
    while (!fin.eof())
    {
      fin.getline(ArrayWord, N); //Построчное считывание информации в массив
      size_array = strlen(ArrayWord);
      number += size_array + 2;
      if (number == observation.temperature_index(observation))
      {
        fin.getline(ArrayWord, N);
        fin.close();
        return ArrayWord;
      }
    }
  }
  else
  {
    fin.close();
    return str;
  }
  return str;
}
double Thermometer::get_average_temperature(Date observation, int index_date, int check_month)
{
  int const N = 256;
  int CHECK = 0;
  int I = -1;
  double L = 0;
  int point = 0;
  double avarage_index = 1;
  int index = 0;
  int number = 0;
  int size_array;
  ifstream fin("Thermometer.txt");
  char ArrayWord[N] = { "" };
  if (index_date == 0)
  {
    if (observation.check_date(observation))
    {
      while (!fin.eof())
      {
        fin.getline(ArrayWord, N); //Построчное считывание информации в массив
        size_array = strlen(ArrayWord);
        number += size_array + 2;
        if (number == observation.temperature_index(observation))
        {
          fin.getline(ArrayWord, N);
          for (int l = 0; l <= size_array; l++)
          {
            L += atoi(ArrayWord + 13 + point);
            avarage_index++;
            if (ArrayWord[13 + point] == ' ')
              return L / (avarage_index - 2);
            point = point + 4;
          }
        }
      }
    }
    return 0;
  }
  if (index_date == 1)
  {
    while (!fin.eof())
    {
      fin.getline(ArrayWord, N); //Построчное считывание информации в массив
      size_array = strlen(ArrayWord);
      number += size_array + 2;
      if (ArrayWord[7] == '.' || ArrayWord[8] == '.')
      {
        if (ArrayWord[7] == '.')
          I = atoi(ArrayWord + 8);
        if (ArrayWord[8] == '.')
          I = atoi(ArrayWord + 9);
      }
      else
        I = 0;
      if (I == check_month)
      {
        fin.getline(ArrayWord, N);
        fin.getline(ArrayWord, N);
        for (int l = 0; l <= size_array; l++)
        {
          L += atoi(ArrayWord + 13 + point);
          if (ArrayWord[13 + point] == ' ')
            break;
          point = point + 4;
          avarage_index++;
        }
      }
      point = 0;
    }
    return L / (avarage_index - 1);
  }
  if (index_date == 2)
  {
    while (!fin.eof())
    {
      fin.getline(ArrayWord, N); //Построчное считывание информации в массив
      size_array = strlen(ArrayWord);
      number += size_array + 2;
      fin.getline(ArrayWord, N);
      fin.getline(ArrayWord, N);
      for (int l = 0; l <= size_array; l++)
      {
        CHECK = atoi(ArrayWord + 13 + point);
        L += atoi(ArrayWord + 13 + point);
        if (ArrayWord[13 + point] == ' ')
          break;
        point = point + 4;
        avarage_index++;
      }
      point = 0;
    }
    return (L - CHECK) / (avarage_index - 2);
  }
  return NULL;
}
double Thermometer::get_av_temp_d_or_n(Date observation, int index_, int check_month)
{
  int const N = 256;
  int I = -1;
  double D = 0, Noth = 0, O = 0;
  int point_d = 0, point_n = 0;
  int point = 0;
  double avarage_index_d = 1, avarage_index_n = 1;
  int size_array;
  ifstream fin("Thermometer.txt");
  char ArrayWord[N] = { "" };
  if (index_ == 1) // дневное
  {
    while (!fin.eof())
    {
      fin.getline(ArrayWord, N); //Построчное считывание информации в массив
      size_array = strlen(ArrayWord);
      if (ArrayWord[7] == '.' || ArrayWord[8] == '.')
      {
        if (ArrayWord[7] == '.')
          I = atoi(ArrayWord + 8);
        if (ArrayWord[8] == '.')
          I = atoi(ArrayWord + 9);
      }
      else
        I = 0;
      if (I == check_month)
      {
        fin.getline(ArrayWord, N);
        for (int l = 0; l <= size_array; l++)
        {
          if (((O = atoi(ArrayWord + 13 + point)) >= 6) && ((O = atoi(ArrayWord + 13 + point)) <= 21))
            point_d++;
          if (((O = atoi(ArrayWord + 13 + point)) < 6) && ((O = atoi(ArrayWord + 13 + point)) > 21))
            point_n++;
          if (ArrayWord[13 + point] == ' ')
            break;
          point = point + 4;
        }
        point = 0;
        fin.getline(ArrayWord, N);
        for (int l = 0; l <= size_array; l++)
        {
          while (point_d != 0)
          {
            D += atoi(ArrayWord + 13 + point);
            point_d--;
            avarage_index_d++;
            point = point + 4;
          }
          while (point_n != 0)
          {
            point = 0;
            Noth += atoi(ArrayWord + 13 + point);
            point_d--;
            avarage_index_n++;
            point = point + 4;
          }
        }
      }
      point = 0;
    }
    if (avarage_index_d == 1)
      return 0;
    return D / (avarage_index_d - 1);
  }
  if (index_ == 2) //ночное
  {
    while (!fin.eof())
    {
      fin.getline(ArrayWord, N); //Построчное считывание информации в массив
      size_array = strlen(ArrayWord);
      if (ArrayWord[7] == '.' || ArrayWord[8] == '.')
      {
        if (ArrayWord[7] == '.')
          I = atoi(ArrayWord + 8);
        if (ArrayWord[8] == '.')
          I = atoi(ArrayWord + 9);
      }
      else
        I = 0;
      if (I == check_month)
      {
        fin.getline(ArrayWord, N);
        for (int l = 0; l <= size_array; l++)
        {
          if (((O = atoi(ArrayWord + 13 + point)) < 6) && ((O = atoi(ArrayWord + 13 + point)) > 0))
            point_n++;
          if (((O = atoi(ArrayWord + 13 + point)) > 21) && ((O = atoi(ArrayWord + 13 + point)) < 24))
            point_n++;
          if (ArrayWord[13 + point] == ' ')
            break;
          point = point + 4;
        }
        point = 0;
        fin.getline(ArrayWord, N);
        for (int l = 0; l <= size_array; l++)
        {
          while (point_n != 0)
          {
            point = 0;
            Noth += atoi(ArrayWord + 13 + point);
            point_n--;
            avarage_index_n++;
            point = point + 4;
          }
        }
      }
      point = 0;
    }
    if (avarage_index_n == 1)
      return 0;
    return Noth / (avarage_index_n - 1);
  }
  return NULL;
}
void Thermometer::observation_file(const Thermometer &observation)
{
  ofstream out("Thermometer.txt", ios_base::app); // запись в конец файла 
  int i, j;
  int index_space = 0;
  if (observation_date.check_date(observation_date))
  {
    i = observation_date.time_index(observation_date);
    ofstream f("Thermometer.txt", ofstream::binary | ofstream::out | ofstream::in); // для замены, если дата уже есть
    f.seekp(i);
    f << "Time:        ";
    for (int i = 0; i < 24; i++)
    {
      if (i == time[i])
        if (time[i] >= 10)
        {
          f << time[i] << "  ";
          index_space = index_space + 2;
        }
        else
        {
          f << time[i] << "   ";
          index_space = index_space + 3;
        }
    }
    for (int id = 0; id < (96 - index_space); id++)
      f << " ";
    j = observation_date.temperature_index(observation_date);
    f.seekp(j);
    index_space = 0;
    f << "Temperature: ";
    for (int i = 0; i < 24; i++)
    {
      if (i == time[i])
        if (temperature[i] >= 10 || temperature[i] < 0)
        {
          if (temperature[i] < -9)
          {
            f << temperature[i] << " ";
            index_space++;
          }
          f << temperature[i] << "  ";
          index_space = index_space + 2;
        }
        else
        {
          f << temperature[i] << "   ";
          index_space = index_space + 3;
        }
    }
    for (int id = 0; id < (96 - index_space); id++)
      f << " ";
    f.close();
    return;
  }
  index_space = 0;
  out << observation_date << "Time:        ";
  for (int i = 0; i < 24; i++)
  {
    if (i == time[i])
      if (time[i] >= 0)
        if (time[i] >= 10)
        {
          out << time[i] << "  ";
          index_space = index_space + 2;
        }
        else
        {
          out << time[i] << "   ";
          index_space = index_space + 3;
        }
  }
  for (int id = 0; id < (100 - index_space); id++)
    out << " ";
  index_space = 0;
  out << endl << "Temperature: ";
  for (int i = 0; i < 24; i++)
  {
    if (i == time[i])
      if (temperature[i] >= 0)
        if (temperature[i] >= 10)
        {
          out << temperature[i] << "  ";
          index_space = index_space + 2;
        }
        else
        {
          out << temperature[i] << "   ";
          index_space = index_space + 3;
        }
      else
        if (temperature[i] < 0)
          if ((temperature[i] > -10))
          {
            out << temperature[i] << "  ";
            index_space = index_space + 2;
          }
          else
          {
            out << temperature[i] << " ";
            index_space = index_space + 2;
          }
  }
  for (int id = 0; id < (100 - index_space); id++)
    out << " ";
  out << endl;
  out.close(); // закрывает файл для записи 
}
void Thermometer::print_observation()
{
  int const N = 256;
  ifstream fin("Thermometer.txt");
  char ArrayWord[N] = { "" };
  cout << "History observation:" << endl;
  while (!fin.eof())
  {
    fin.getline(ArrayWord, N);
    cout << ArrayWord << endl; //Вывод строки
  }
  fin.close();
}
void delet_array(int *time, int *temperature)
{
  for (int i = 0; i < 24; i++)
    time[i] = -1;
  for (int i = 0; i < 24; i++)
    temperature[i] = -289;
}
int main()
{
  setlocale(LC_ALL, "Rus");
  int temp;
  int _time[24], _temperature[24];
  int index;
  Date check_date;
  Thermometer check_thermometer;
  char *array = { "" };
  do
  {
    cout << "0 - Завершить работу" << endl << "1 - Уставить начальное наблюдение" << endl << "2 - Узнать начальное наблюдение" << endl << "3 - Задать наблюдение" << endl << "4 - Получить температуру в заданном наблюдении" << endl << "5 - Здать серию наблюдений" << endl << "6 - Получить среднюю температуру за день/месяц/всё время" << endl << "7 - Получить среднюю дневную или ночную температуру за месяц" << endl << "8 - Сохранить наблюдение" << endl << "9 - Считать историю ннаблюдений из файла" << endl;
    cin >> index;
    switch (index)
    {
    case 0:
      break;
    case 1:
    {
      ofstream out("Thermometer.txt");
      out << "";
      out.close();
      cout << "Год/месяц/день:" << endl;
      cin >> check_date;
      cout << "Время в часах: ";
      cin >> _time[0];
      cout << "Температура: ";
      cin >> _temperature[0];
      check_thermometer.series_observation(check_date, 1, _time, _temperature);
      check_thermometer.observation_file(check_thermometer);
    }
    break;
    case 2:
      check_thermometer.get_observation();
      break;
    case 3:
    {
      Thermometer check;
      cout << "Год/месяц/день:" << endl;
      cin >> check_date;
      cout << "Время в часах: ";
      cin >> _time[0];
      cout << "Температура: ";
      cin >> _temperature[0];
      check_date.check_date(check_date);
      check.series_observation(check_date, 1, _time, _temperature);
      check_thermometer = check;
    }
    break;
    case 4:
    {
      Date temperature;
      cout << "Введите год, месяц, день наблюдения:" << endl;
      cin >> temperature;
      Thermometer temperature_check;
      cout << temperature_check.Get_temperature(temperature) << endl;
    }
    break;
    case 5:
    {
      Thermometer check1;
      delet_array(_time, _temperature);
      cout << "Год/месяц/день:" << endl;
      cin >> check_date;
      cout << "Количество наблюдений, которые хотите задать:" << endl;
      cin >> temp;
      for (int i = 0; i < temp; i++)
      {
        cout << "Время в часах: ";
        cin >> _time[i];
        cout << "Температура: ";
        cin >> _temperature[i];
      }
      check_date.check_date(check_date);
      check1.series_observation(check_date, temp, _time, _temperature);
      check_thermometer = check1;
    }
    break;
    case 6:
    {
      Date temperature;
      int i = 0;
      int j = 0;
      Thermometer temperature_check;
      cout << "0 - За день" << endl << "1 - За месяц" << endl << "2 - Всё время" << endl;
      cin >> i;
      if (i == 0)
      {
        cout << "Год/месяц/день:" << endl;
        cin >> temperature;
        cout << "Средняя температура за день: " << temperature_check.get_average_temperature(temperature, i, j) << endl;
      }
      if (i == 1)
      {
        cout << "Месяц:" << endl;
        cin >> j;
        cout << "Средняя температура за месяц: " << temperature_check.get_average_temperature(temperature, i, j) << endl;
      }
      if (i == 2)
        cout << "Средняя температура за всё время: " << temperature_check.get_average_temperature(temperature, i, j) << endl;
    }
    break;
    case 7:
    {
      Date temperature;
      int i = 0;
      int j = 0;
      Thermometer temperature_check;
      cout << "Месяц:" << endl;
      cin >> j;
      cout << "1 - Дневная" << endl << "2 - Ночная" << endl;
      cin >> i;
      cout << "Средняя температура: " << temperature_check.get_av_temp_d_or_n(temperature, i, j) << endl;
    }
    break;
    case 8:
      check_thermometer.observation_file(check_thermometer);
      array = "";
      break;
    case 9:
      check_thermometer.print_observation();
      break;
    default:
      cout << "Error!" << endl;
      break;
    }
  } while (index != 0);
  cout << endl << "END PROGRAMM";
}
