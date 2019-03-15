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
  TranslatorDictionary(); //�� ���������
  TranslatorDictionary(string _english_word, string _russian_word); //����������� �������������
  TranslatorDictionary(const TranslatorDictionary &str); // ����������� ����������� 
  TranslatorDictionary& operator=(const TranslatorDictionary &str);// �������� ������������
  void addWord(TranslatorDictionary str); //�������� � ������� ����� � ��� �������
  void setWord(TranslatorDictionary str, int _index); //�������� �������
  string getWord(string str); //������ �������
  string checkWord(string str); //��������� ������� �����
  void printDictionary(); //������� ������� � ����������� ����
  ~TranslatorDictionary()//����������
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
void TranslatorDictionary::addWord(TranslatorDictionary str)
{
  setlocale(LC_ALL, "Rus");
  int line1, line2;
  ofstream out("dictionary.txt", ios_base::app); // ������ � ����� �����
  line1 = str.english_word.size();
  if (line1 < 20) // ������������ � �����
  {
    for (int i = 0; i < (20 - line1); i++)
      str.english_word += " ";
  }
  line2 = str.russian_word.size(); // ���������� �������� � ������
  if (line2 < 20) // ������������ � �����
  {
    for (int i = 0; i < (20 - line2); i++)
      str.russian_word += " ";
  }
  out << str.english_word << "� " << str.russian_word << endl;
  out.close(); // ��������� ���� ��� ������
}
void TranslatorDictionary::setWord(TranslatorDictionary str, int _index)
{
  ofstream f("dictionary.txt", ofstream::binary | ofstream::out | ofstream::in); //��� ������ ������
  int const N = 256;
  int index = 0;
  int size_str, size_array, Mysize = 0;
  ifstream fin("dictionary.txt");
  char ArrayWord[N] = { "" };
  while (!fin.eof())
  {
    fin.getline(ArrayWord, N); //���������� ���������� ���������� � ������ 
    size_array = strlen(ArrayWord);
    for (int j = 0, i = 0; j < size_array; j++) // ����� �����
    {
      if (str.english_word[i] == ArrayWord[j])
      {
        index++;
        i++;
        size_str = str.english_word.size();
        if (index == size_str && ((ArrayWord[j + 1] == ' ') || (ArrayWord[j + 1] == '�'))) // �������� ������� �����, �.�. ����� str � string  �� ��������� �� ���� �����
        {
          if (_index == 1) // ������ ��������
          {
            while (ArrayWord[j + 1] != '�')
              j++;
            j = j + 3;
            f.seekp(Mysize + j);
            f << str.russian_word;
            while (ArrayWord[j + 1] == ' ')
            {
              f << " ";
              j++;
            }
            f.close();
          }
          if (_index == 2) // ������ ������ �����
          {
            while (ArrayWord[j + 1] != '�')
              j++;
            j = j + 3;
            f.seekp(Mysize);
            f << str.russian_word;
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
  cout << "����� �� �������";
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
    fin.getline(ArrayWord, N); //���������� ���������� ���������� � ������
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
  str = "��� ����������";
  return str;
}
string TranslatorDictionary::checkWord(string str)
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
        if (index == size_str && ((ArrayWord[j + 1] == ' ') || (ArrayWord[j + 1] == '�')))
        {
          fin.close();
          str = "����� ���� � �������";
          return str;
        }
      }
      else
        index = 0;
    }
  }
  fin.close();
  str = "��� ����������";
  return str;
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
    cout << ArrayWord << endl; //����� ������
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
  while (a != 5)
  {
    cout << endl << "�������:" << endl << "0 - �������� ����� � �������" << endl << "1 - �������� �������" << endl << "2 - ������ ������� �����" << endl << "3 - ��������� �������" << endl << "4 - ������� �������" << endl << "5 - ��������� ������" << endl;
    cin >> a;
    switch (a)
    {
    case 0:
    {
      cout << "������� �����:" << endl;
      getline(cin, l);
      getline(cin, l);
      cout << "������� �������:" << endl;
      getline(cin, n);
      TranslatorDictionary check(l, n);
      check.addWord(check);
    }
    break;
    case 1:
    {
      cout << endl << "������� �����, ������� ������ ��������:" << endl;
      getline(cin, l);
      getline(cin, l);
      cout << endl << "1 - �������� �������" << endl << "2 - �������� ���� �����" << endl;
      cin >> index;
      cout << endl << "�� ��� ������ ��������:" << endl;
      getline(cin, n);
      getline(cin, n);
      TranslatorDictionary temp(l, n);
      temp.setWord(temp, index);
    }
    break;
    case 2:
    {
      cout << "������� �����, � �������� ������ ������ �������:" << endl;
      getline(cin, l);
      getline(cin, l);
      cout << all.getWord(l);
    }
    break;
    case 3:
    {
      cout << "������� �����, ������� ������ �����:" << endl;
      getline(cin, l);
      getline(cin, l);
      cout << all.checkWord(l);
    }
    break;
    case 4:
    {
      cout << "Dictionary:" << endl;
      all.printDictionary();
    }
    break;
    case 5:
      break;
      {
    default:
      cout << "����� ������� ���" << endl;
      break;
      }
    }
  }
  cout << endl << "End programm!" << endl;
  cin >> a;
}