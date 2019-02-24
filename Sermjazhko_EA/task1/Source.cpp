#include <iostream>
#include <clocale> 
using namespace std;
class DynamicArray
{
  int *m_array;
  int array_size;
  int *subarray;
public:
  DynamicArray()              // конструктор по умолчанию
  {
    array_size = 0;
    m_array = new int[0];
    subarray = new int[0];
  }
  DynamicArray(int size)// конструктор 
  {
    int i;
    m_array = new int[size];
    for (i = 0; i < size; i++)
      m_array[i] = i;
    array_size = size;
  }
  DynamicArray(const DynamicArray &object)// конструктор копирования
  {
    int i;
    m_array = new int[object.array_size];
    array_size = object.array_size;
    for (i = 0; i < object.array_size; i++)
      m_array[i] = object.m_array[i];
  }
  DynamicArray& operator=(const DynamicArray &object)//  оператор присваивания
  {
    int i;
    m_array = new int[object.array_size];
    for (i = 0; i < object.array_size; i++)
      m_array[i] = object.m_array[i];
    array_size = object.array_size;
    return *this;
  }
  void setArray(int size) //задание массива вручную
  {
    int i = 0, l;
    for (i; i < size; i++)
    {
      cout << "Элемент " << i << ": ";
      cin >> l;
      m_array[i] = l;
    }
  }
  void setElement(int index, int number)// вывод/изменение элемента
  {
    if (index == -1)
      cout << m_array[number];
    else
      m_array[number] = index;
  }
  void printArray(int size) //вывод массива
  {
    int i;
    for (i = 0; i < size; i++)
      cout << " " << i << " элемент " << m_array[i] << "\n";
  }
  void minElement()//минимальный элемент массива
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
    cout << "Индекс:" << n << " элемент: " << min;
  }
  void orderArray() // проверка массива на упорядоченность по возрастанию
  {
    int i, n = 0;
    for (i = 0; i < (array_size - 1); i++)
      if (m_array[i] <= m_array[i + 1])
        n++;
    if (n == array_size - 1)
      cout << "Массив упорядочен\n";
    else
      cout << "Массив неупорядочен\n";
  }
  void printSubarray(int size, int arraysize) //вывод подмассива с нечетными элементами
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
    cout << "Подмассив:\n";
    for (i = 0; i < size; i++)
      cout << subarray[i] << "\n";
  }
  ~DynamicArray() //деструктор
  {
    delete[] m_array;
    delete[] subarray;
  }
};
int check(int left, int right, int &value)
{
  do
  {
    if ((value < left) || (value > right))
    {
      cout << "Данные введены неверно, попробуйте ещё раз:\n";
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
  cout << "Введите размер массива:\n";
  cin >> size;
  do
  {
    if (size < 0)
    {
      cout << "Данные введены неверно, попробуйте ещё раз:\n";
      cin >> size;
    }
  } while (size < 0);
  DynamicArray object(size);
  DynamicArray subarray;
  cout << "Вы хотите сами заполнить массив?\n 0 - Нет\n 1 - Да\n";
  cin >> index;
  check(0, 1, index);
  if (index == 0)
  {
    cout << "\nСтандартный массив:\n";
    object.printArray(size);
  }
  else
  {
    object.setArray(size);
    cout << "\nВведенный массив:\n";
    object.printArray(size);
  }
  do
  {
    cout << "\nВы хотите задать элемент массива по его индексу?\n 0 - Нет\n 1 - Да\n";
    cin >> index;
    check(0, 1, index);
    if (index == 1)
    {
      cout << "Введите индекс элемента, который хотите изменить:\n";
      cin >> number;
      check(0, size - 1, number);
      cout << "\nВведите новый элемент:\n" << number << " элемент: ";
      cin >> element;
      object.setElement(element, number);
    }
  } while (index != 0);
  cout << "\nВы хотите узнать элемент по его индексу?:\n 0 - Нет\n 1 - Да\n";
  cin >> index;
  check(0, 1, index);
  if (index == 1)
  {
    cout << "\nВведите индекс:\n";
    cin >> number;
    check(0, size - 1, number);
    cout << "\nЭлемент под номером " << number << ": ";
    object.setElement(-1, number);
  }
  cout << "\n\nВы хотите вывести новый массив?\n 0 - Нет\n 1 - Да\n";
  cin >> index;
  check(0, 1, index);
  if (index == 1)
  {
    cout << "Новый массив:\n";
    object.printArray(size);
  }
  cout << "\nВы хотите узнать индекс минимального элемента?\n 0 - Нет\n 1 - Да\n";
  cin >> index;
  check(0, 1, index);
  if (index == 1)
    object.minElement();
  cout << "\n\nХотите проверить, является ли массив упорядоченным по возрастанию?\n 0 - Нет\n 1 - Да\n";
  cin >> index;
  check(0, 1, index);
  if (index == 1)
    object.orderArray();
  subarray = object;
  cout << "\nХотите выделить подмассив с элементами нечетных индексов?\n 0 - Нет\n 1 - Да\n";
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
