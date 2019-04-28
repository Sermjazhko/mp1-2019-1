#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "ProcessingCenter.h"
using namespace std;
int index = 1;
class Deposit
{
  int account_number;
public:
  Deposit(int number = -1);
  Deposit(const Deposit &object);
  void registration(); //заполнение базы данных
  bool authorization(int number, string &_password);//авторизация клиента
  void deposit_information();// информация о депозите
  bool check_open();//проверить на открытие депозита 
  void open_deposit(int time, int salary);//открыть депозит
  int deposit_(); // показать состояние 
  void withdraw();//снять проценты
  void close_deposit();//закрыть депозит
  ~Deposit()
  {}
};
Deposit::Deposit(int number)
{
  account_number = number;
}
Deposit::Deposit(const Deposit &object)
{
  account_number = object.account_number;
}
void Deposit::registration()
{
  string  surname, name, patronymic;
  string full_name_;
  int add, i = 0;
  string pass;
  ProcessingCenter check_name;
  cout << "ФИО: " << endl;
  cin >> surname;
  cin >> name;
  cin >> patronymic;
  cout << "Количество средств на счету:" << endl; //фиксированное?
  cin >> add;
  while (i == 0)
  {
    cout << "Пароль (от 3 симовол без пробелов):" << endl;
    cin >> pass;
    i++;
    if (pass.length() < 3)
      i = 0;
  }
  full_name_ = surname;
  full_name_ += " ";
  full_name_ += name;
  full_name_ += " ";
  full_name_ += patronymic;
  check_name = { full_name_, add, -1, 0, pass };
  cout << "Ваш номер счета: " << setfill('0') << setw(4) << index << endl;
  index++;
}
bool Deposit::authorization(int number, string &_password)
{
  ProcessingCenter check;
  if (check.authorization_check(number, _password))
    return true;
  else
    return false;
}
void Deposit::deposit_information()
{
  ProcessingCenter check;
  cout << "Доступные депозиты: " << endl;
  cout << "Сумма депозита          " << "Срок:      " << "Процентные ставки:  " << endl;
  if (check.get_salary(account_number) > 1000000)
  {
    cout << "1 млн.                  " << "3 месяца   " << "8%" << endl;
    cout << "                        " << "6 месяца   " << "10%" << endl;
    cout << "                        " << "1 год      " << "11%" << endl;
    cout << "                        " << "2 года     " << "12%" << endl;
    cout << "                        " << "3 года     " << "14%" << endl;
  }
  if (check.get_salary(account_number) > 500000)
  {
    cout << "от 500 тыс. до 1 млн.   " << "3 месяца   " << "7%" << endl;
    cout << "                        " << "6 месяца   " << "8%" << endl;
    cout << "                        " << "1 год      " << "9%" << endl;
    cout << "                        " << "2 года     " << "10%" << endl;
    cout << "                        " << "3 года     " << "11%" << endl;
  }
  if (check.get_salary(account_number) > 100000)
  {
    cout << "от 100 тыс. до 500 тыс. " << "3 месяца   " << "6%" << endl;
    cout << "                        " << "6 месяца   " << "6,6%" << endl;
    cout << "                        " << "1 год      " << "7%" << endl;
    cout << "                        " << "2 года     " << "8%" << endl;
    cout << "                        " << "3 года     " << "9%" << endl;
  }
  cout << "до 100 тыс.             " << "3 месяца   " << "5%" << endl;
  cout << "                        " << "6 месяца   " << "5,5%" << endl;
  cout << "                        " << "1 год      " << "6%" << endl;
  cout << "                        " << "2 года     " << "7%" << endl;
  cout << "                        " << "3 года     " << "7,5%" << endl;
  cout << "Сумма на счёте: " << check.get_salary(account_number) << endl;
}
bool Deposit::check_open()
{
  ProcessingCenter check;
  if (check.get_deposit(account_number) == -1)
    return false;
  else
    return true;
}
void Deposit::open_deposit(int time, int salary)
{
  ProcessingCenter check;
  check.operations(salary, account_number, time);
}
int Deposit::deposit_()
{
  ProcessingCenter check;
  int _deposit_ = 0;
  _deposit_ = check.get_deposit_status_end(account_number);
  return _deposit_;
}
void Deposit::withdraw()
{
  ProcessingCenter check;
  check.withdraw_interest(account_number);
}
void Deposit::close_deposit()
{
  ProcessingCenter check;
  check.close(account_number);
}
