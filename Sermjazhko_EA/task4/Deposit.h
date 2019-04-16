#include <iostream>
#include <vector>
#include <string>
#include <clocale>
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
  void registration(); //���������� ���� ������
  bool authorization(int number, string &_password);//����������� �������
  void deposit_information();// ���������� � ��������
  bool check_open();//��������� �� �������� �������� 
  void open_deposit(int time, int salary);//������� �������
  int deposit_(); // �������� ��������� 
  void withdraw();//����� ��������
  void close_deposit();//������� �������
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
  cout << "���: " << endl;
  cin >> surname;
  cin >> name;
  cin >> patronymic;
  cout << "���������� ������� �� �����:" << endl; //�������������?
  cin >> add;
  while (i == 0)
  {
    cout << "������ (�� 3 ������� ��� ��������):" << endl;
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
  cout << "��� ����� �����: " << setfill('0') << setw(4) << index << endl;
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
  cout << "��������� ��������: " << endl;
  cout << "����� ��������          " << "����:      " << "���������� ������:  " << endl;
  if (check.get_salary(account_number) > 1000000)
  {
    cout << "1 ���.                  " << "3 ������   " << "8%" << endl;
    cout << "                        " << "6 ������   " << "10%" << endl;
    cout << "                        " << "1 ���      " << "11%" << endl;
    cout << "                        " << "2 ����     " << "12%" << endl;
    cout << "                        " << "3 ����     " << "14%" << endl;
  }
  if (check.get_salary(account_number) > 500000)
  {
    cout << "�� 500 ���. �� 1 ���.   " << "3 ������   " << "7%" << endl;
    cout << "                        " << "6 ������   " << "8%" << endl;
    cout << "                        " << "1 ���      " << "9%" << endl;
    cout << "                        " << "2 ����     " << "10%" << endl;
    cout << "                        " << "3 ����     " << "11%" << endl;
  }
  if (check.get_salary(account_number) > 100000)
  {
    cout << "�� 100 ���. �� 500 ���. " << "3 ������   " << "6%" << endl;
    cout << "                        " << "6 ������   " << "6,6%" << endl;
    cout << "                        " << "1 ���      " << "7%" << endl;
    cout << "                        " << "2 ����     " << "8%" << endl;
    cout << "                        " << "3 ����     " << "9%" << endl;
  }
  cout << "�� 100 ���.             " << "3 ������   " << "5%" << endl;
  cout << "                        " << "6 ������   " << "5,5%" << endl;
  cout << "                        " << "1 ���      " << "6%" << endl;
  cout << "                        " << "2 ����     " << "7%" << endl;
  cout << "                        " << "3 ����     " << "7,5%" << endl;
  cout << "����� �� �����: " << check.get_salary(account_number) << endl;
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
  if (check.get_deposit(account_number) != -1)
    cout << "������� ��� ������." << endl;
  else
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