//Вариант 7 Типографские правки

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

string file_choose()
{
	/*
	Функция, позволяет выбрать файл. 
	Пользователь вводит название, если файл с таким названием существует, то вовзвращает его в string.
	*/
	string name;
	bool ok = true;
	while (ok)
	{

		getline(cin, name);

		ifstream file;
		file.open("d:\\texts\\" + name + ".txt");

		if (file)
		{
			file.close();
			return name;
		}
		else cout << '\n' << "Error! Input correct name!" << endl;
	}

}


vector <char> file_reading(ifstream& ifile)
{
	/*
	Функция, читает содержимое файла и переносит его в вектор char пока не натыкается на EOF
	Аргументы:
		file: ifstream& - ссылка на поток ввода
	Выводит:
		data: vector <char> - вектор текста из файла
	*/
	vector < char > data;
	char symb;
	while ((symb = ifile.get()) != EOF)
		data.push_back(symb);
	ifile.close();

	return data;
}
char symbols[5] = { '!', '.', ',', '?', ')' };
vector <char> file_redaction(vector <char>& data)
{
	/*
	Функция, из полученного файла вводит элементы в выбранный. 
	Если i-ый элемент равен пробелу, то редактируем файл. 
	*/
	vector <char> redact;
	if (data.size() == 0) cout << '\n' << "Error! There are no symbols in file " << endl;
	else
	{
		
		cout << '\n' << '\n' << "Redacted file: " << endl;
		for (int i = 0; i < data.size() - 1; ++i)
		{
			char x = data[i], y = data[i + 1];
			if (x == ' ')
			{
				switch (y)
				{
				case '?':
				case '!':
				case '.':
				case ',':

				case ' ': 
					break;
				default:
					redact.push_back(x);
					break;
				}
			}

			else 
			{
				switch (x)
				{
				case '?':
				case '!':
				case '.':
				case ',':
				{
					if (y == ' ')
					{
						redact.push_back(x);
					}
					else
						redact.push_back(x);
						redact.push_back(' ');
					break;
				}
				default:
					redact.push_back(x);
					break;
				}

			}
		}
	}
	return redact;
}

void output(vector <char>& data) //выводим данные из файла
{
	cout << "Your text is: " << endl;
	for (int i = 0; i < data.size(); ++i) {
		cout << data[i];
	}
}

bool YN_function()
{
	/*
	Функция узнает, вводит пользователь Y или N.
	В зависимости от этого возвращает:
		'1', если введено 'Y'
		'0', если введено 'N'
	*/
	string button;
	bool end = true;
	cout << '\n' << "Do you want to continue? Input 'Y' or 'N' " << endl;
	while (end)
	{
		getline(cin, button);
		if (button[0] == 'Y' && button.length() == 1) return  true;
		if (button[0] == 'N' && button.length() == 1)  return false;
		else cout <<'\n' << "Write 'Y' or 'N'!" << endl;
	}
}

void ofile_change(vector <char>& redacted, ofstream& ofile)
{
	for (auto c : redacted)
		ofile << c;
	ofile.close();
}

int main()
{
	bool finish = true;
	while (finish)
	{
		cout << "Enter a file`s name: (input1, input2, input3)" << endl;
		string file_name = file_choose();

		ifstream ifile("d:\\texts\\" + file_name + ".txt");
		

		vector <char> data = file_reading(ifile);
		output(data);

		
		vector <char> redacted = file_redaction(data);

		ofstream ofile("d:\\texts\\" + file_name + ".txt");
		ofile_change(redacted, ofile);

		if (redacted.size()!=0) output(redacted);
		data.clear();
		finish = YN_function();
	}
}