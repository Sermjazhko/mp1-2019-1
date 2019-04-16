#include <iostream>
#include <vector>
#include <string>
using namespace std;
class ProcessingCenter
{
  string full_name;
  int salary;
  string deposit;
  int deposit_status;
  string password;
public:
  static vector <string> full_name_;//база данных клиентов
  static vector <int> salary_;
  static vector <int> deposit_; // время
  static vector <int> deposit_status_; //сумма
  static vector <int> deposit_status_end;
  static vector <string> password_;
  ProcessingCenter(); //конструктор по умолчанию
  ProcessingCenter(string _name, int _salary, int _deposit, int _deposit_status, string _password); //конструктор инициализации
  ProcessingCenter(const ProcessingCenter &object); //конструктор копирования
  bool authorization_check(int number, string &_password); //проверка авторизации
  int get_salary(int number);// получить информацию о счете
  int get_deposit(int number);// получить информацию о депозите
  void operations(int amount, int number, int time);//изменение депозита/счета
  void set_deposit_status(int time, int number);// состояние депозита через некоторое время
  int get_deposit_status(int number); // состояние депозита
  int get_deposit_status_end(int number); // состояние депозита
  void withdraw_interest(int number);// снять проценты
  void close(int number);//перевести всё на зарплатный счет
  ~ProcessingCenter() //деструктор
  {}
};
ProcessingCenter::ProcessingCenter()
{
  full_name = "";
  salary = 0;
  deposit = "";
  deposit_status = 0;
  password = "";
}
ProcessingCenter::ProcessingCenter(string _name, int _salary, int _deposit, int _deposit_status, string _password)
{
  full_name = _name;
  salary = _salary;
  deposit = _deposit;
  deposit_status = _deposit_status;
  password = _password;
  full_name_.push_back(_name);// начало
  salary_.push_back(_salary);
  deposit_.push_back(_deposit);
  deposit_status_.push_back(_deposit_status);
  deposit_status_end.push_back(_deposit_status);
  password_.push_back(_password);
}
ProcessingCenter::ProcessingCenter(const ProcessingCenter &object)
{
  full_name = object.full_name;
  salary = object.salary;
  password = object.password;
}
vector <string> ProcessingCenter::full_name_;
vector <int> ProcessingCenter::salary_;
vector <int> ProcessingCenter::deposit_;
vector <int> ProcessingCenter::deposit_status_;
vector <int> ProcessingCenter::deposit_status_end;
vector <string> ProcessingCenter::password_;
bool ProcessingCenter::authorization_check(int number, string &_password)
{
  string check;
  if (number > full_name_.size())
    return false;
  check = password_[number - 1];
  if (check.length() != _password.length())
    return false;
  for (int i = 0; i < _password.length(); i++)
    if (check[i] != _password[i])
      return false;
  _password = full_name_[number - 1];
  return true;
}
int ProcessingCenter::get_salary(int number)
{
  return salary_[number - 1];
}
int ProcessingCenter::get_deposit(int number)
{
  return deposit_[number - 1];
}
void ProcessingCenter::operations(int amount, int number, int time)
{
  if (salary_[number - 1] < amount)
  {
    cout << "Недостаточно средств!" << endl;
    return;
  }
  deposit_[number - 1] = time;
  deposit_status_[number - 1] = amount;
  deposit_status_end[number - 1] = amount;
  salary_[number - 1] = salary_[number - 1] - amount;
}
void ProcessingCenter::set_deposit_status(int time, int number)
{
  double i = 0;
  double percent = 0;
  if (deposit_status_[number - 1] > 1000000)
  {
    if (deposit_[number - 1] == 3)
      i = 0.08;
    if (deposit_[number - 1] == 6)
      i = 0.1;
    if (deposit_[number - 1] == 12)
      i = 0.11;
    if (deposit_[number - 1] == 24)
      i = 0.12;
    if (deposit_[number - 1] == 36)
      i = 0.14;
  }
  else
    if (deposit_status_[number - 1] > 500000)
    {
      if (deposit_[number - 1] == 3)
        i = 0.07;
      if (deposit_[number - 1] == 6)
        i = 0.08;
      if (deposit_[number - 1] == 12)
        i = 0.09;
      if (deposit_[number - 1] == 24)
        i = 0.1;
      if (deposit_[number - 1] == 36)
        i = 0.11;
    }
    else
      if (deposit_status_[number - 1] > 100000)
      {
        if (deposit_[number - 1] == 3)
          i = 0.06;
        if (deposit_[number - 1] == 6)
          i = 0.066;
        if (deposit_[number - 1] == 12)
          i = 0.07;
        if (deposit_[number - 1] == 24)
          i = 0.08;
        if (deposit_[number - 1] == 36)
          i = 0.09;
      }
      else
      {
        if (deposit_[number - 1] == 3)
          i = 0.05;
        if (deposit_[number - 1] == 6)
          i = 0.055;
        if (deposit_[number - 1] == 12)
          i = 0.06;
        if (deposit_[number - 1] == 24)
          i = 0.07;
        if (deposit_[number - 1] == 36)
          i = 0.075;
      }
  percent = deposit_status_[number - 1] * i;
  deposit_status_end[number - 1] = deposit_status_end[number - 1] + percent * time;
}
int ProcessingCenter::get_deposit_status(int number)
{
  return deposit_status_[number - 1];
}
int ProcessingCenter::get_deposit_status_end(int number)
{
  return deposit_status_end[number - 1];
}
void ProcessingCenter::withdraw_interest(int number)
{
  salary_[number - 1] += (deposit_status_end[number - 1] - deposit_status_[number - 1]);
  deposit_status_end[number - 1] = deposit_status_[number - 1];
}
void ProcessingCenter::close(int number)
{
  salary_[number - 1] += deposit_status_end[number - 1];
  deposit_status_end[number - 1] = 0;
  deposit_status_[number - 1] = 0;
  deposit_[number - 1] = -1;
}
