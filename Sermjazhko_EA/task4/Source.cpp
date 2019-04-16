#include <iostream>
#include <vector>
#include <string>
#include <clocale>
#include "Deposit.h"
using namespace std;
int main()
{
  setlocale(LC_ALL, "Rus");
  int point = -1;
  do
  {
    cout << "����� - 0" << endl << "����������� ������� - 1" << endl << "����������� - 2" << endl;
    cin >> point;
    if (point == 1)
    {
      Deposit check;
      check.registration();
    }
    if (point == 2)
    {
      Deposit check1;
      int number;
      int check_point = 0;
      int month_deposit = 0;
      int time_check = 0;
      int time = 0;
      string password;
      cout << "������� ����� �����:" << endl;
      cin >> number;
      cout << "������� ������:" << endl;
      cin >> password;
      check1 = { number };
      while (!check1.authorization(number, password))
      {
        cout << "������� ������� ������:" << endl;
        cout << "������� ����� �����:" << endl;
        cin >> number;
        cout << "������� ������:" << endl;
        cin >> password;
        check1 = { number };
      }
      cout << "������: " << password << endl;
      do
      {
        cout << "0 - �����" << endl << "1 - ��������� ��������" << endl << "2 - ��������� �� ������� ��������� ��������" << endl << "3 - ������� �������" << endl << "4 - �������� ��������� ��������" << endl << "5 - ����� ��������" << endl << "6 - ������� �������" << endl << "7 - ���������� �����" << endl;
        cin >> check_point;
        switch (check_point)
        {
        case 0:
          break;
        case 1:
        {
          check1.deposit_information();
        }
        break;
        case 2:
        {
          if (check1.check_open())
          {
            ProcessingCenter check;
            cout << "������ ������� ��: " << check.get_deposit(number) << " �������, ������� ������� - " << check.get_deposit_status(number) << endl;
          }
          else
            cout << "��������� �������� ���." << endl;
        }
        break;
        case 3:
        {
          int salary;
          cout << "������� ���������� �������, �� ������� ������ ����� ������� (1 ��� - 12 �������, 2 ���� - 24, 3 ���� - 36)" << endl;
          cin >> month_deposit;
          while ((month_deposit != 3) && (month_deposit != 6) && (month_deposit != 12) && (month_deposit != 24) && (month_deposit != 36))
          {
            cout << "������� ������� ������" << endl;
            cin >> month_deposit;
          }
          cout << "������� ������� ���������?" << endl;
          cin >> salary;
          check1.open_deposit(month_deposit, salary);
        }
        break;
        case 4:
        {
          cout << "��������� ��������: " << check1.deposit_() << endl;
        }
        break;
        case 5:
        {
          check1.withdraw();
        }
        break;
        case 6:
        {
          ProcessingCenter check;
          if (time_check >= check.get_deposit(number))
            check1.close_deposit();
          else
            cout << "������� ����� ������� ������ �� ��������� �����!" << endl;
        }
        break;
        case 7:
        {
          int index = time_check;
          cout << "������� ������� ������?" << endl;
          cin >> time;
          time_check += time;
          if (time_check > month_deposit)
          {
            time = month_deposit - index;
            cout << "���� �������� ������� � �����!" << endl;
            if (time < 0)
              time = 0;
          }
          ProcessingCenter check;
          check.set_deposit_status(time, number);
        }
        break;
        default:
          break;
        }
      } while (check_point != 0);
    }
  } while (point != 0);
}