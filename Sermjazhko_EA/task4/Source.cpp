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
    cout << "Выход - 0" << endl << "Регистрация клиента - 1" << endl << "Авторизация - 2" << endl;
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
      cout << "Введите номер счета:" << endl;
      cin >> number;
      cout << "Введите пароль:" << endl;
      cin >> password;
      check1 = { number };
      while (!check1.authorization(number, password))
      {
        cout << "Неверно введены данные:" << endl;
        cout << "Введите номер счета:" << endl;
        cin >> number;
        cout << "Введите пароль:" << endl;
        cin >> password;
        check1 = { number };
      }
      cout << "Клиент: " << password << endl;
      do
      {
        cout << "0 - Выход" << endl << "1 - Доступные депозиты" << endl << "2 - Проверить на наличие открытого депозита" << endl << "3 - Открыть депозит" << endl << "4 - Показать состояние депозита" << endl << "5 - Снять проценты" << endl << "6 - Закрыть депозит" << endl << "7 - Перемотать время" << endl;
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
            cout << "Открыт депозит на: " << check.get_deposit(number) << " месяцев, внесено средств - " << check.get_deposit_status(number) << endl;
          }
          else
            cout << "Открытого депозита нет." << endl;
        }
        break;
        case 3:
        {
          int salary;
          cout << "Введите количество месяцев, на которое хотите взять депозит (1 год - 12 месяцев, 2 года - 24, 3 года - 36)" << endl;
          cin >> month_deposit;
          while ((month_deposit != 3) && (month_deposit != 6) && (month_deposit != 12) && (month_deposit != 24) && (month_deposit != 36))
          {
            cout << "Неверно введены данные" << endl;
            cin >> month_deposit;
          }
          cout << "Сколько средств перевести?" << endl;
          cin >> salary;
          check1.open_deposit(month_deposit, salary);
        }
        break;
        case 4:
        {
          cout << "Состояние депозита: " << check1.deposit_() << endl;
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
            cout << "Депозит можно закрыть только по истечении срока!" << endl;
        }
        break;
        case 7:
        {
          int index = time_check;
          cout << "Сколько месяцев прошло?" << endl;
          cin >> time;
          time_check += time;
          if (time_check > month_deposit)
          {
            time = month_deposit - index;
            cout << "Срок депозита подошел к концу!" << endl;
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
