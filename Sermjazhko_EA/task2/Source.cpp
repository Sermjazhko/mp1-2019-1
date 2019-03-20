#include <iostream>
#include <clocale>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;
class TranslatorDictionary
{
  string english_word;
  string russian_word;
public:
  TranslatorDictionary(); //по умолчанию
  TranslatorDictionary(string _english_word, string _russian_word); //конструктор инициализации
  TranslatorDictionary(const TranslatorDictionary &str); // конструктор копирования 
  TranslatorDictionary& operator=(const TranslatorDictionary &str);// оператор присваивания
  string addWord(string _english_word, string _russian_word, string _words); //добавить в словарь слово и его перевод
  void setWord(string _english_word, string _russian_word, int _index); //изменить перевод
  string getWord(string str); //узнать перевод
  bool checkWord(string str); //проверить наличие слова
  void file_printDictionary(string _words); // сохранить словарь в файл
  void printDictionary(); //считать словарь (с количеством слов) из файла
  ~TranslatorDictionary()//деструктор
  {}
};
TranslatorDictionary::TranslatorDictionary()
{
  english_word = "";
  russian_word = "";
}
TranslatorDictionary::TranslatorDictionary(string _english_word, string _russian_word)
{
  english_word = _english_word;
  russian_word = _russian_word;
}
TranslatorDictionary::TranslatorDictionary(const TranslatorDictionary &str)
{
  english_word = str.english_word;
  russian_word = str.russian_word;
}
TranslatorDictionary& TranslatorDictionary::operator=(const TranslatorDictionary &str)
{
  if (this == &str)
    return *this;
  english_word = str.english_word;
  russian_word = str.russian_word;
}
string TranslatorDictionary::addWord(string _english_word, string _russian_word, string _words)
{
  int line1, line2;
  line1 = _english_word.size();
  if (line1 < 20) // выравнивание в файле
  {
    for (int i = 0; i < (20 - line1); i++)
      _english_word += " ";
  }
  line2 = _russian_word.size(); // количество символов в строке
  if (line2 < 20) // выравнивание в файле
  {
    for (int i = 0; i < (20 - line2); i++)
      _russian_word += " ";
  }
  _words += _english_word;
  _words += _russian_word;
  _words += '_';
  return _words;
}
void TranslatorDictionary::setWord(string _english_word, string _russian_word, int _index)
{
  ofstream f("dictionary.txt", ofstream::binary | ofstream::out | ofstream::in); //для замены текста
  int const N = 256;
  int index = 0;
  int size_str, size_array, Mysize = 0;
  ifstream fin("dictionary.txt");
  char ArrayWord[N] = { "" };
  while (!fin.eof())
  {
    fin.getline(ArrayWord, N); //Построчное считывание информации в массив 
    size_array = strlen(ArrayWord);
    for (int j = 0, i = 0; j < size_array; j++) // поиск слова
    {
      if (_english_word[i] == ArrayWord[j])
      {
        index++;
        i++;
        size_str = _english_word.size();
        if (index == size_str && ((ArrayWord[j + 1] == ' ') || (ArrayWord[j + 1] == '—'))) // проверка полноты слова, т.е. чтобы str и string  не считались за одно слово
        {
          if (_index == 1) // замена перевода
          {
            while (ArrayWord[j + 1] != '—')
              j++;
            j = j + 3;
            f.seekp(Mysize + j);
            f << _russian_word;
            while (ArrayWord[j + 1] == ' ')
            {
              f << " ";
              j++;
            }
            f.close();
          }
          if (_index == 2) // замена самого слова
          {
            while (ArrayWord[j + 1] != '—')
              j++;
            j = j + 3;
            f.seekp(Mysize);
            f << _russian_word;
            while (ArrayWord[j + 1] == ' ')
            {
              f << " ";
              j++;
            }
            f.close();
          }
          fin.close();
          return;
        }
      }
      else
        index = 0;
    }
    Mysize = Mysize + size_array + 2;
  }
  cout << "Слово не найдено";
  fin.close();
  f.close();
}
string TranslatorDictionary::getWord(string str)
{
  int const N = 256;
  int index = 0;
  int size_str, size_array;
  ifstream fin("dictionary.txt");
  char ArrayWord[N] = { "" };
  while (!fin.eof())
  {
    fin.getline(ArrayWord, N); //Построчное считывание информации в массив
    size_array = strlen(ArrayWord);
    size_str = str.size();
    for (int j = 0, i = 0; j < size_array; j++)
    {
      if (str[i] == ArrayWord[j])
      {
        index++;
        i++;
        if (index == size_str)
        {
          fin.close();
          return ArrayWord;
        }
      }
      else
        index = 0;
    }
  }
  fin.close();
  str = "Нет совпадений";
  return str;
}
bool TranslatorDictionary::checkWord(string str)
{
  int const N = 256;
  int index = 0;
  int size_str, size_array, size_check = 0;
  ifstream fin("dictionary.txt");
  char ArrayWord[N] = { "" };
  while (!fin.eof())
  {
    fin.getline(ArrayWord, N);
    size_array = strlen(ArrayWord);
    size_str = str.size();
    for (int j = 0, i = 0; j < size_array; j++)
    {
      if (str[i] == ArrayWord[j])
      {
        index++;
        i++;
        if (index == size_str && ((ArrayWord[j + 1] == ' ') || (ArrayWord[j + 1] == '—')))
        {
          fin.close();
          return true;
        }
      }
      else
        index = 0;
    }
  }
  fin.close();
  return false;
}
void TranslatorDictionary::file_printDictionary(string _words)
{
  ofstream out("dictionary.txt", ios_base::app); // запись в конец файла
  for (int i = 0; i <= _words.size(); i++)
  {
    if (_words[i] == '_')
    {
      out << endl;
      i++;
    }
    out << _words[i];
  }
  out.close(); // закрывает файл для записи
}
void TranslatorDictionary::printDictionary()
{
  int const N = 256;
  int index = 0;
  ifstream fin("dictionary.txt");
  char ArrayWord[N] = { "" };
  while (!fin.eof())
  {
    fin.getline(ArrayWord, N);
    cout << ArrayWord << endl; //Вывод строки
    index++;
  }
  fin.close();
  cout << "Number or words:" << index - 1 << endl;
}
int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  setlocale(LC_ALL, "Rus");
  int a = 0;
  int index;
  TranslatorDictionary all;
  string l, n;
  string array;
  while (a != 6)
  {
    cout << endl << "Введите:" << endl << "0 - добавить слово в словарь" << endl << "1 - изменить перевод" << endl << "2 - узнать перевод слова" << endl << "3 - проверить наличие" << endl << "4 - вывести словарь из файла" << endl << "5 - сохранить в файл" << endl << "6 - завершить работу" << endl;
    cin >> a;
    switch (a)
    {
    case 0:
    {
      cout << "Введите слово:" << endl;
      getline(cin, l);
      getline(cin, l);
      cout << "Введите перевод:" << endl;
      getline(cin, n);
      TranslatorDictionary check(l, n);
      array = check.addWord(l, n, array);
    }
    break;
    case 1:
    {
      cout << endl << "Введите слово, которое хотите изменить:" << endl;
      getline(cin, l);
      getline(cin, l);
      cout << endl << "1 - изменить перевод" << endl << "2 - изменить само слово" << endl;
      cin >> index;
      cout << endl << "На что хотите изменить:" << endl;
      getline(cin, n);
      getline(cin, n);
      TranslatorDictionary temp(l, n);
      temp.setWord(l, n, index);
    }
    break;
    case 2:
    {
      cout << "Введите слово, у которого хотете узнать перевод:" << endl;
      getline(cin, l);
      getline(cin, l);
      cout << all.getWord(l);
    }
    break;
    case 3:
    {
      cout << "Введите слово, которое хотите найти:" << endl;
      getline(cin, l);
      getline(cin, l);
      if (all.checkWord(l))
        cout << "Слово найдено" << endl;
      else
        cout << "Слово не найдено" << endl;
    }
    break;
    case 4:
    {
      cout << "Dictionary:" << endl;
      all.printDictionary();
    }
    break;
    case 5:
    {
      all.file_printDictionary(array);
      array = "";
    }
    break;
    case 6:
      break;
      {
    default:
      cout << "Такой функции нет" << endl;
      break;
      }
    }
  }
  cout << endl << "End programm!" << endl;
}
