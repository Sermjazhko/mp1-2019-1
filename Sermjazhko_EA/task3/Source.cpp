#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include <vector>
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
  void get_observation(vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp); // вывести начальную дату
  void Get_temperature(Date observation, vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i); //узнать температуру в выбранном наблюдении
  double get_average_temperature(Date observation, int index_dat, int check_month, vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i); //узнать среднюю температуру в выбранном наблюдении
  double get_av_temp_d_or_n(Date observation, int index, int check_month, vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i); //узнать среднюю дневную или ночную температуру в наблюдении
  void observation_file(vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i); //сохранить историю наблюдений в файл
  void print_observation(vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i); //считать историю наблюдений из файла
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
void Thermometer::get_observation(vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp)
{
  cout << "Дата:" << endl;
  for (int i = date[0].size() - 1; i >= 0; i--)
    cout << date[0].at(i) << ".";
  cout << endl << "Время: " << time[0].at(0) << endl;
  cout << "Темп.: " << temp[0].at(0) << endl;
}
void Thermometer::Get_temperature(Date observation, vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i)
{
  int check = 0;
  for (int k = 0; k <= i; k++)
  {
    if (date[k].at(0) == observation.get_year(observation))
      if (date[k].at(1) == observation.get_month(observation))
        if (date[k].at(2) == observation.get_day(observation))
          check = 1;
    if (check == 1)
    {
      cout << "Темп.: ";
      for (int j = 0; j < temp[k].size(); j++)
        cout << temp[k].at(j) << " ";
      cout << endl;
      return;
    }
  }
  if (check == 0)
    cout << "Дата не найдена";
}
double Thermometer::get_average_temperature(Date observation, int index_date, int check_month, vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i)
{
  if (index_date == 0) //для даты
  {
    int check = 0;
    double agg = 0;

    for (int k = 0; k <= i; k++)
    {
      if (date[k].at(0) == observation.get_year(observation))
        if (date[k].at(1) == observation.get_month(observation))
          if (date[k].at(2) == observation.get_day(observation))
            check = 1;
      if (check == 1)
      {
        for (int j = 0; j < temp[k].size(); j++)
          agg += temp[k].at(j);
        return agg / (temp[k].size());
      }
    }
    if (check == 0)
      return -500;
  }
  if (index_date == 1) //для месяца
  {
    int check = 0;
    double agg = 0;
    int p = 0;
    for (int k = 0; k <= i; k++)
    {
      if (date[k].at(1) == check_month)
        check = 1;
      if (check == 1)
      {
        for (int j = 0; j < temp[k].size(); j++)
        {
          agg += temp[k].at(j);
          p++;
        }
        check = 0;
      }
    }
    if (p == 0)
      return -200;
    return agg / p;
  }
  if (index_date == 2) //для всего времени
  {
    int check = 0;
    double agg = 0;
    int p = 0;
    for (int k = 0; k <= i; k++)
    {
      for (int j = 0; j < temp[k].size(); j++)
      {
        agg += temp[k].at(j);
        p++;
      }
      check = 0;
    }
    if (p == 0)
      return -200;
    return agg / p;
  }
}
double Thermometer::get_av_temp_d_or_n(Date observation, int index_, int check_month, vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i)
{
  if (index_ == 1) //дневное
  {
    int check = 0;
    double agg = 0;
    int p = 0;
    for (int k = 0; k <= i; k++)
    {
      if (date[k].at(1) == check_month)
        check = 1;
      if (check == 1)
      {
        for (int j = 0; j < temp[k].size(); j++)
          if ((time[k].at(j) >= 6) && (time[k].at(j) <= 17))
          {
            agg += temp[k].at(j);
            p++;
          }
        check = 0;
      }
    }
    if (p == 0)
      return -200;
    return agg / p;
  }
  if (index_ == 2) //ночное
  {
    int check = 0;
    double agg = 0;
    int p = 0;
    for (int k = 0; k <= i; k++)
    {
      if (date[k].at(1) == check_month)
        check = 1;
      if (check == 1)
      {
        for (int j = 0; j < temp[k].size(); j++)
        {
          if ((time[k].at(j) < 6) || ((time[k].at(j) > 17)))
          {
            agg += temp[k].at(j);
            p++;
          }
        }
        check = 0;
      }
    }
    if (p == 0)
      return -200;
    return agg / p;
  }
}
void Thermometer::observation_file(vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i)
{
  ofstream out("Thermometer.txt", ios_base::app); // запись в конец файла 
  int index_space = 0;
  for (int q = 0; q <= i; q++)
  {
    out << "Date: ";
    for (int r = 2; r >= 0; r--)
      out << date[q][r] << ".";
    out << endl;
    out << "Time:        ";
    for (int l = 0; l < time[q].size(); l++)
    {
      if (time[q][l] >= 0)
        if (time[q][l] >= 10)
        {
          out << time[q][l] << "  ";
          index_space = index_space + 2;
        }
        else
        {
          out << time[q][l] << "   ";
          index_space = index_space + 3;
        }
    }
    for (int id = 0; id < (100 - index_space); id++)
      out << " ";
    index_space = 0;
    out << endl << "Temperature: ";
    for (int o = 0; o < temp[q].size(); o++)
    {
      if (temp[q][o] >= 0)
        if (temp[q][o] >= 10)
        {
          out << temp[q][o] << "  ";
          index_space = index_space + 2;
        }
        else
        {
          out << temp[q][o] << "   ";
          index_space = index_space + 3;
        }
      else
        if (temp[q][o] < 0)
          if ((temp[q][o] > -10))
          {
            out << temp[q][o] << "  ";
            index_space = index_space + 2;
          }
          else
          {
            out << temp[q][o] << " ";
            index_space = index_space + 2;
          }
    }
    for (int id = 0; id < (100 - index_space); id++)
      out << " ";
    out << endl;
  }
  out.close(); // закрывает файл для записи 
}
void Thermometer::print_observation(vector <vector <int>> date, vector <vector <int>> time, vector <vector <int>> temp, int i)
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
  int i = 1;
  vector <vector <int>> date_v = { {1, 1, 1}, {}, {}, {}, {}, {}, {}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{} };
  vector <vector <int>> time_v = { {}, {}, {}, {}, {}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {} };
  vector <vector <int>> temperature_v = { {}, {}, {}, {}, {}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {} };
  Date check_date;
  Thermometer check_thermometer;

  char *array = { "" };
  do
  {
    cout << "0 - Завершить работу" << endl << "1 - Уставить начальное наблюдение" << endl << "2 - Узнать начальное наблюдение" << endl << "3 - Задать наблюдение" << endl << "4 - Получить температуру в заданном наблюдении" << endl << "5 - Здать серию наблюдений" << endl << "6 - Получить среднюю температуру за день/месяц/всё время" << endl << "7 - Получить среднюю дневную или ночную температуру за месяц" << endl << "8 - Сохранить наблюдение" << endl << "9 - Считать историю наблюдений из файла" << endl;
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
      date_v = { {}, {}, {}, {}, {}, {}, {}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{}, {},{} };
      date_v[0].emplace_back(check_date.get_year(check_date));
      date_v[0].emplace_back(check_date.get_month(check_date));
      date_v[0].emplace_back(check_date.get_day(check_date));
      cout << "Время в часах: ";
      cin >> _time[0];
      time_v[0].emplace_back(_time[0]);
      cout << "Температура: ";
      cin >> _temperature[0];
      temperature_v[0].emplace_back(_temperature[0]);
      check_thermometer.series_observation(check_date, 1, _time, _temperature);
    }
    break;
    case 2:
      check_thermometer.get_observation(date_v, time_v, temperature_v);
      break;
    case 3:
    {
      Thermometer check;
      int point = 0;
      int time_check = -1;
      cout << "Год/месяц/день:" << endl;
      cin >> check_date;
      for (int k = 0; k < i; k++)
      {
        if (date_v[k].at(0) == check_date.get_year(check_date))
          if (date_v[k].at(1) == check_date.get_month(check_date))
            if (date_v[k].at(2) == check_date.get_day(check_date))
            {
              point = 1;
              cout << "Время в часах: ";
              cin >> _time[0];
              for (int s = 0; s < time_v[k].size(); s++)
              {
                if (time_v[k][s] == _time[0])
                {
                  time_check = s;
                  break;
                }
              }
              if (time_check == -1)
                time_v[k].emplace_back(_time[0]);

              cout << "Температура: ";
              cin >> _temperature[0];
              if (time_check == -1)
                temperature_v[k].emplace_back(_temperature[0]);
              if (time_check != -1)
                temperature_v[k][time_check] = _temperature[0];
              check.series_observation(check_date, 1, _time, _temperature);
              check_thermometer = check;
              k = i + 1;
            }
      }
      if (point == 0)
      {
        date_v[i].emplace_back(check_date.get_year(check_date));
        date_v[i].emplace_back(check_date.get_month(check_date));
        date_v[i].emplace_back(check_date.get_day(check_date));
        cout << "Время в часах: ";
        cin >> _time[0];
        time_v[i].emplace_back(_time[0]);
        cout << "Температура: ";
        cin >> _temperature[0];
        temperature_v[i].emplace_back(_temperature[0]);
        check.series_observation(check_date, 1, _time, _temperature);
        check_thermometer = check;
        i++;
      }
    }
    break;
    case 4:
    {
      Date temperature;
      cout << "Введите год, месяц, день наблюдения:" << endl;
      cin >> temperature;
      Thermometer temperature_check;
      temperature_check.Get_temperature(temperature, date_v, time_v, temperature_v, i - 1);
    }
    break;
    case 5:
    {
      Thermometer check1;
      int check = 0;
      int point = 0;
      int l;
      int time_check = -1;
      delet_array(_time, _temperature);
      cout << "Год/месяц/день:" << endl;
      cin >> check_date;
      for (int k = 0; k < i; k++)
      {
        if (date_v[k].at(0) == check_date.get_year(check_date))
          if (date_v[k].at(1) == check_date.get_month(check_date))
            if (date_v[k].at(2) == check_date.get_day(check_date))
            {
              cout << "Количество наблюдений, которые хотите задать:" << endl;
              cin >> temp;
              for (int t = 0; t < temp; t++)
              {

                time_check = -1;
                point = 1;
                cout << "Время в часах: ";
                cin >> _time[t];
                for (int s = 0; s < time_v[k].size(); s++)
                {
                  if (time_v[k][s] == _time[t])
                  {
                    time_check = s;
                    break;
                  }
                }
                if (time_check == -1)
                  time_v[k].emplace_back(_time[t]);

                cout << "Температура: ";
                cin >> _temperature[t];
                if (time_check == -1)
                  temperature_v[k].emplace_back(_temperature[t]);
                if (time_check != -1)
                {
                  temperature_v[k][time_check] = _temperature[t];
                }
              }
              check1.series_observation(check_date, temp, _time, _temperature);
              check_thermometer = check1;
              k = i + 1;
            }
      }
      if (point == 0)
      {
        date_v[i].emplace_back(check_date.get_year(check_date));
        date_v[i].emplace_back(check_date.get_month(check_date));
        date_v[i].emplace_back(check_date.get_day(check_date));
        cout << "Количество наблюдений, которые хотите задать:" << endl;
        cin >> temp;
        for (int k = 0; k < temp; k++)
        {
          cout << "Время в часах: ";
          cin >> _time[k];
          time_v[i].emplace_back(_time[k]);
          for (l = 0; l < k; l++)
          {
            if (_time[l] == _time[k])
            {
              check = 1;
              time_v[i].pop_back();
              break;
            }
          }
          cout << "Температура: ";
          cin >> _temperature[k];
          temperature_v[i].emplace_back(_temperature[k]);
          if (check == 1)
          {
            temperature_v[i][l] = _temperature[k];
            temperature_v[i].pop_back();
          }
        }
        check1.series_observation(check_date, temp, _time, _temperature);
        check_thermometer = check1;
        i++;
      }
    }
    break;
    case 6:
    {
      Date temperature;
      int s = 0;
      int j = 0;
      Thermometer temperature_check;
      cout << "0 - За день" << endl << "1 - За месяц" << endl << "2 - Всё время" << endl;
      cin >> s;
      if (s == 0)
      {
        cout << "Год/месяц/день:" << endl;
        cin >> temperature;
        cout << "Средняя температура за день: " << temperature_check.get_average_temperature(temperature, s, j, date_v, time_v, temperature_v, i - 1) << endl;
      }
      if (s == 1)
      {
        cout << "Месяц:" << endl;
        cin >> j;
        cout << "Средняя температура за месяц: " << temperature_check.get_average_temperature(temperature, s, j, date_v, time_v, temperature_v, i - 1) << endl;
      }
      if (s == 2)
        cout << "Средняя температура за всё время: " << temperature_check.get_average_temperature(temperature, s, j, date_v, time_v, temperature_v, i - 1) << endl;
    }
    break;
    case 7:
    {
      Date temperature;
      int t = 0;
      int j = 0;
      Thermometer temperature_check;
      cout << "Месяц:" << endl;
      cin >> j;
      cout << "1 - Дневная" << endl << "2 - Ночная" << endl;
      cin >> t;
      cout << "Средняя температура: " << temperature_check.get_av_temp_d_or_n(temperature, t, j, date_v, time_v, temperature_v, i - 1) << endl;
    }
    break;
    case 8:
      check_thermometer.observation_file(date_v, time_v, temperature_v, i - 1);
      array = "";
      break;
    case 9:
      check_thermometer.print_observation(date_v, time_v, temperature_v, i - 1);
      break;
    default:
      cout << "Error!" << endl;
      break;
    }
  } while (index != 0);
  cout << endl << "END PROGRAMM";
}
