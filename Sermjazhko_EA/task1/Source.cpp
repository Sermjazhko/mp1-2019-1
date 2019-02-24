#include <iostream>
#include <clocale> 
using namespace std;
class DynamicArray
{
  int *m_array;
  int array_size;
  int *subarray;
public:
  DynamicArray()              // ����������� �� ���������
  {
    array_size = 0;
    m_array = new int[0];
    subarray = new int[0];
  }
  DynamicArray(int size)// ����������� 
  {
    int i;
    m_array = new int[size];
    for (i = 0; i < size; i++)
      m_array[i] = i;
    array_size = size;
  }
  DynamicArray(const DynamicArray &object)// ����������� �����������
  {
    int i;
    m_array = new int[object.array_size];
    array_size = object.array_size;
    for (i = 0; i < object.array_size; i++)
      m_array[i] = object.m_array[i];
  }
  DynamicArray& operator=(const DynamicArray &object)//  �������� ������������
  {
    int i;
    m_array = new int[object.array_size];
    for (i = 0; i < object.array_size; i++)
      m_array[i] = object.m_array[i];
    array_size = object.array_size;
    return *this;
  }
  void setArray(int size) //������� ������� �������
  {
    int i = 0, l;
    for (i; i < size; i++)
    {
      cout << "������� " << i << ": ";
      cin >> l;
      m_array[i] = l;
    }
  }
  void setElement(int index, int number)// �����/��������� ��������
  {
    if (index == -1)
      cout << m_array[number];
    else
      m_array[number] = index;
  }
  void printArray(int size) //����� �������
  {
    int i;
    for (i = 0; i < size; i++)
      cout << " " << i << " ������� " << m_array[i] << "\n";
  }
  void minElement()//����������� ������� �������
  {
    int i, n = 0;
    int min;
    min = m_array[0];
    for (i = 0; i < (array_size - 1); i++)
    {
      if (m_array[i + 1] < min)
      {
        min = m_array[i + 1];
        n = i + 1;
      }
    }
    cout << "������:" << n << " �������: " << min;
  }
  void orderArray() // �������� ������� �� ���������������
  {
    int i, n = 0;
    for (i = 0; i < (array_size - 1); i++)
      if (m_array[i] <= m_array[i + 1])
        n++;
    if (n == array_size - 1)
      cout << "������ ����������\n";
    else
      cout << "������ ������������\n";
  }
  void printSubarray(int size, int arraysize) //����� ���������� � ��������� ����������
  {
    int i, j = 0;
    subarray = new int[size];
    double n;
    for (i = 0; i < arraysize; i++)
    {
      n = i % 2;
      if (n != 0)
      {
        subarray[j] = m_array[i];
        j++;
      }
    }
    cout << "���������:\n";
    for (i = 0; i < size; i++)
      cout << subarray[i] << "\n";
  }
  ~DynamicArray() //����������
  {
    delete[] m_array;
  }
};
int check(int left, int right, int &value)
{
  do
  {
    if ((value < left) || (value > right))
    {
      cout << "������ ������� �������, ���������� ��� ���:\n";
      cin >> value;
    }
  } while ((value < left) || (value > right));
  return value;
}
int main()
{
  setlocale(LC_ALL, "Rus");
  int index;
  int number;
  int element;
  int size;
  double newsize;
  int min = 0;
  cout << "������� ������ �������:\n";
  cin >> size;
  do
  {
    if (size < 0)
    {
      cout << "������ ������� �������, ���������� ��� ���:\n";
      cin >> size;
    }
  } while (size < 0);
  DynamicArray object(size);
  DynamicArray subarray;
  cout << "�� ������ ���� ��������� ������?\n 0 - ���\n 1 - ��\n";
  cin >> index;
  check(0, 1, index);
  if (index == 0)
  {
    cout << "\n����������� ������:\n";
    object.printArray(size);
  }
  else
  {
    object.setArray(size);
    cout << "\n��������� ������:\n";
    object.printArray(size);
  }
  do
  {
    cout << "\n�� ������ ������ ������� ������� �� ��� �������?\n 0 - ���\n 1 - ��\n";
    cin >> index;
    check(0, 1, index);
    if (index == 1)
    {
      cout << "������� ������ ��������, ������� ������ ��������:\n";
      cin >> number;
      check(0, size - 1, number);
      cout << "\n������� ����� �������:\n" << number << " �������: ";
      cin >> element;
      object.setElement(element, number);
    }
  } while (index != 0);
  cout << "\n�� ������ ������ ������� �� ��� �������?:\n 0 - ���\n 1 - ��\n";
  cin >> index;
  check(0, 1, index);
  if (index == 1)
  {
    cout << "\n������� ������:\n";
    cin >> number;
    check(0, size - 1, number);
    cout << "\n������� ��� ������� " << number << ": ";
    object.setElement(-1, number);
  }
  cout << "\n\n�� ������ ������� ����� ������?\n 0 - ���\n 1 - ��\n";
  cin >> index;
  check(0, 1, index);
  if (index == 1)
  {
    cout << "����� ������:\n";
    object.printArray(size);
  }
  cout << "\n�� ������ ������ ������ ������������ ��������?\n 0 - ���\n 1 - ��\n";
  cin >> index;
  check(0, 1, index);
  if (index == 1)
    object.minElement();
  cout << "\n\n������ ���������, �������� �� ������ �������������?\n 0 - ���\n 1 - ��\n";
  cin >> index;
  check(0, 1, index);
  if (index == 1)
    object.orderArray();
  subarray = object;
  cout << "\n������ �������� ��������� � ���������� �������� ��������?\n 0 - ���\n 1 - ��\n";
  cin >> index;
  check(0, 1, index);
  if (index == 1)
  {
    newsize = size;
    newsize = floor(newsize / 2);
    subarray.printSubarray(newsize, size);
  }
  cin >> index;
}