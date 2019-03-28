#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Data.h"
using namespace std;
class Thermometer //НАЧАЛЬНАЯ ДАТА НАБЛЮДЕНИЯ (!)
{
  Data observation_data;
  int time[24];
  int temperature[24];
public:
  Thermometer(); //конструктор по умолчанию
  Thermometer(Data observation, int _time, int _temperature); //конструктор инициализации
  Thermometer(const Thermometer &observation); //конструктор копирования
  Thermometer& operator=(const Thermometer &observation); // оператор присваивания
  void series_observation(Data observation, int number, int *_time, int *_temperature); // задать наблюдение
  void get_observation(); // вывести начальную дату
  string Get_temperature(Data observation); //узнать температуру в выбранном наблюдении
  int get_average_temperature(Data observation); //узнать среднюю температуру в выбранном наблюдении
  int get_av_temp_d_or_n(Data observation, int index); //узнать среднюю дневную или ночную температуру в наблюдении
  void observation_file(const Thermometer &observation); //сохранить историю наблюдений в файл
  void print_observation(); //считать историю наблюдений из файла
  ~Thermometer() //деструктор
  {}
};
Thermometer::Thermometer()
{
  observation_data = { 2000, 1, 1 };
  for (int i = 0; i < 24; i++)
    time[i] = -1;
  for (int i = 0; i < 24; i++)
    temperature[i] = -289;
}
Thermometer::Thermometer(Data observation, int _time, int _temperature)
{
  observation_data = observation;
  time[_time] = _time;
  temperature[_time] = _temperature;
  // for (int i = 0; i < 24; i++)
  //   if (i!=_time)
  //     temperature[i] = 0;
}
Thermometer::Thermometer(const Thermometer &observation)
{
  observation_data = observation.observation_data;
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
  observation_data = observation.observation_data;
  for (int i = 0; i < 24; i++)
  {
    time[i] = observation.time[i];
    temperature[i] = observation.temperature[i];
  }
  return *this;
}
void Thermometer::series_observation(Data observation, int number, int *_time, int *_temperature)
{
  observation_data = observation;
  for (int i = 0; i < number; i++)
  {
    time[_time[i]] = _time[i];
    temperature[_time[i]] = _temperature[i];
  }
}
//void Thermometer::set_observation(){}
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
string Thermometer::Get_temperature(Data observation)
{
  int const N = 256;
  int index = 0;
  int number = 0;
  string str;
  int size_str, size_array;
  ifstream fin("Thermometer.txt");
  char ArrayWord[N] = { "" };
  if (observation.check_data(observation))
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
    str = "False";
    return str;
  }
}
int Thermometer::get_average_temperature(Data observation)
{
  return 0;
}
int Thermometer::get_av_temp_d_or_n(Data observation, int index)
{
  return 0;
}
void Thermometer::observation_file(const Thermometer &observation) // Попробовать считывать не индексы, а строки 
{
  ofstream out("Thermometer.txt", ios_base::app); // запись в конец файла 
  int i, j;
  if (observation_data.check_data(observation_data))
  {
    i = observation_data.time_index(observation_data);
    ofstream f("Thermometer.txt", ofstream::binary | ofstream::out | ofstream::in);
    f.seekp(i);
    f << "Time: " << setw(8);;
    for (int i = 0; i < 24; i++)
    {
      if (i == time[i])
        if (time[i] >= 10)
          f << time[i] << "  ";
        else
          f << time[i] << "   ";
    }
    f << "                                    ";
    f << endl;
    observation_data.check_data(observation_data);
    j = observation_data.temperature_index(observation_data);
    f.seekp(j);
    f << endl;
    f << "Temperature: ";
    for (int i = 0; i < 24; i++)
    {
      if (i == time[i])
        if (temperature[i] >= 10 || temperature[i] < 0)
          f << temperature[i] << "  ";
        else
          f << temperature[i] << "   ";
    }
    f << "                                    ";
    f.close();
    return;
  }
  out << observation_data << "Time: " << setw(8);
  for (int i = 0; i < 24; i++)
  {
    if (i == time[i])
      if (time[i] >= 10)
        out << time[i] << "  ";
      else
        out << time[i] << "   ";
  }
  out << "                                    ";
  out << endl << "Temperature: ";
  for (int i = 0; i < 24; i++)
  {
    if (i == time[i])
      if (temperature[i] >= 10 || temperature[i] < 0)
        out << temperature[i] << "  ";
      else
        out << temperature[i] << "   ";
  }
  out << "                                    ";
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
  int temp;
  int _time[24], _temperature[24];
  int index;
  Data check_data;
  Thermometer check_thermometer;
  char *array = { "" };
  do
  {
    cout << "0 - End programm" << endl << "1 - Start data and time" << endl << "2 - Get start data and time" << endl << "3 - Set observation" << endl << "4 - Get temperature on observation" << endl << "5 - Series observation" << endl << "6 - Get average temperature on data, month, all history" << endl << "7 - Get average day or noght time temperature" << endl << "8 - Preservation history" << endl << "9 - Get history observation" << endl;
    cin >> index;
    switch (index)
    {
    case 0:
      break;
    case 1:
    {
      cout << "Year, month, day:" << endl;
      cin >> check_data;
      cout << "Time: ";
      cin >> _time[0];
      cout << "Temperature: ";
      cin >> _temperature[0];
      check_thermometer.series_observation(check_data, 1, _time, _temperature);
      check_thermometer.observation_file(check_thermometer);
    }
    break;
    case 2:
      check_thermometer.get_observation();
      break;
    case 3:
    {
      Thermometer check;
      cout << "Year, month, day:" << endl;
      cin >> check_data;
      cout << "Time: ";
      cin >> _time[0];
      cout << "Temperature: ";
      cin >> _temperature[0];
      check_data.check_data(check_data);
      check.series_observation(check_data, 1, _time, _temperature);
      check_thermometer = check;
    }
    break;
    case 4:
    {
      Data temperature;
      cout << "Write time" << endl;
      cin >> temperature;
      Thermometer temperature_check;
      cout << temperature_check.Get_temperature(temperature) << endl;
    }
    break;
    case 5:
    {
      Thermometer check1;
      delet_array(_time, _temperature);
      cout << "Year, month, day:" << endl;
      cin >> check_data;
      cout << "Number series:" << endl;
      cin >> temp;
      for (int i = 0; i < temp; i++)
      {
        cout << "Time: ";
        cin >> _time[i];
        cout << "Temperature: ";
        cin >> _temperature[i];
      }
      check_data.check_data(check_data);
      check1.series_observation(check_data, temp, _time, _temperature);
      check_thermometer = check1;
    }
    break;
    case 6: //ЗАМЕНА ТЕКСТА
    {
      Data get_temperature;
      int i, j;
      cout << "Write time" << endl;
      cin >> get_temperature;
      if (get_temperature.check_data(get_temperature))
      {
        i = get_temperature.time_index(get_temperature);
        j = get_temperature.temperature_index(get_temperature);
        ofstream f("Thermometer.txt", ofstream::binary | ofstream::out | ofstream::in);
        f.seekp(i);
        f << "Time_NEW";
        f.seekp(j);
        f << "Temperature_NEW";
        f.close();
      }
      else
        cout << "False" << endl;
    }
    break;
    case 7:
    {

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


  // Data check; 
 //  cout << "Series, number time:" << endl;
  // cin >> temp;
  // for (int i = 0; i < temp; i++)
  // {
  //   cout << "Time: ";
  //   cin >> _time[i];
  //   cout << "Temperature: ";
  //   cin >> _temperature[i];
  // }
  // cout << "Year, month, day:" << endl;
  // cin >> check; 

  // Thermometer a;
  // a.series_observation(check, temp, _time, _temperature);
  // a.get_observation();
 //  a.observation_file(a);
 //  a.print_observation();
  cout << endl << "END PROGRAMM";
}