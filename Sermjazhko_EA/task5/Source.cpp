#include <iostream>
#include <fstream>
#include <string>

int main(void)
{

  setlocale(LC_ALL, "Russian_Russia.1251"); //��� ��������� win ���������� ������ �������� ����� � �������

  std::ifstream file_in;

  file_in.open("text.txt");

  if (!file_in)
  {
    std::cerr << "������, ���������� ������� ���� : text.txt" << std::endl;
    return (EXIT_FAILURE);
  }

  std::cout << "������� ����� ������ ��� �������� :" << std::endl;
  int i_number_line_delete = 0; //��� �������� ������ ������ ������� ����� �������
  std::cin >> i_number_line_delete;

  int i_number_line_now = 0; //������� �����
  std::string line; //��� �������� ������
  std::string line_file_text; //��� �������� ������ �����

  while (getline(file_in, line))
  {
    i_number_line_now++;

    if (!(i_number_line_now == i_number_line_delete))
    {
      line_file_text.insert(line_file_text.size(), line); /*�������� ������*/
      /*�������� ������� �� ��������� ������*/
      line_file_text.insert(line_file_text.size(), "\r\n");

    }
  }

  file_in.close();

  //������ � line_file_text ����� ����������� ���������� ����� �����, ������ ����� ������������ ����

  std::ofstream file_out;

  file_out.open("text.txt", std::ios::trunc | std::ios::binary); //������� � ��������

  //��������

  file_out.write(line_file_text.c_str(), line_file_text.size());
  file_out.clear();

  return (EXIT_SUCCESS);
}