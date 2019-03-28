#include <iostream>
#include <fstream>
#include <string>

int main(void)
{

  setlocale(LC_ALL, "Russian_Russia.1251"); //для платформы win разрешение вывода русского языка в консоль

  std::ifstream file_in;

  file_in.open("text.txt");

  if (!file_in)
  {
    std::cerr << "Ошибка, невозможно открыть файл : text.txt" << std::endl;
    return (EXIT_FAILURE);
  }

  std::cout << "Введите номер строки для удаления :" << std::endl;
  int i_number_line_delete = 0; //для хранения номера строки который нужно удалить
  std::cin >> i_number_line_delete;

  int i_number_line_now = 0; //счётчик строк
  std::string line; //для хранения строки
  std::string line_file_text; //для хранения текста файла

  while (getline(file_in, line))
  {
    i_number_line_now++;

    if (!(i_number_line_now == i_number_line_delete))
    {
      line_file_text.insert(line_file_text.size(), line); /*дабавить строку*/
      /*добавить перенос на слудующую строку*/
      line_file_text.insert(line_file_text.size(), "\r\n");

    }
  }

  file_in.close();

  //теперь в line_file_text будет содержаться измененный текст файла, теперь можно перезаписать файл

  std::ofstream file_out;

  file_out.open("text.txt", std::ios::trunc | std::ios::binary); //открыть и обрезать

  //записать

  file_out.write(line_file_text.c_str(), line_file_text.size());
  file_out.clear();

  return (EXIT_SUCCESS);
}