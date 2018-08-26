#include <cstdlib>
#include <iostream>
#include <string>
#include <locale>
#include <fstream>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

/*Реализовать в программе шифрование и дешифрацию содержимого файла по методу Цезаря с ключом.*/
/*P.S. без учета пробела*/

//В работе использован свой алфавит, состоящий из английских букв
const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const size_t alph_size = alphabet.size();

//Чтение файла
vector<string> read_file(string file_name)
{
	vector<string> text;
	string temp;
	ifstream ist(file_name, ios::in | ios::binary);
	if (!ist) {
		cout << "Can't open the file with this name!" << endl;
	}
	else {
		while (!ist.eof()) {
			getline(ist, temp);
			text.push_back(temp);
		}
		cout << "File has been successfully read!" << endl;
	}
	ist.close(); 
	return text;
}

//Запись в файл
void write_file(string file_name, vector<string> text)
{
	string temp;
	ofstream ost(file_name);
	if (!ost) {
		cout << "Сan't open the file with this name!" << endl;
	}
	else {
		for (size_t i = 0; i < text.size(); i++) {
			ost << text[i] << endl;
		}
		cout << "File has been successfully writed!" << endl;
	}
	ost.close(); 
}

//Вывод текста из файла
void print_text(vector<string> text)
{
	for (size_t i = 0; i < text.size(); i++) {
		cout << text[i] << endl;
	}
}

//Шифрование
/*vector<string> encrypt(vector<string> text, size_t k)
{
	k %= alph_size;
	string txt;
	for (size_t i = 0; i < text.size(); ++i) {
		txt = text[i];
		for (size_t j = 0; j < txt.length(); ++j) 
		{
			if (isprint((unsigned char)txt[j])) 
			{
				txt[j] = alphabet[(alphabet.find(txt[j]) + k) % alph_size];
			}
		}
		text[i] = txt;
	}
	return text;
}*/
vector<string> encrypt(vector<string> text, size_t k)
{
	k %= alph_size;
	string txt;
	for (size_t i = 0; i < text.size(); ++i) {
		txt = text[i];
		for (size_t j = 0; j < txt.length(); ++j)
		{
			if (txt[j] == ' ') continue;
			else if (isprint((unsigned char)txt[j]))
			{
				txt[j] = alphabet[(alphabet.find(txt[j]) + k) % alph_size];
			}
		}
		text[i] = txt;
	}
	return text;
}
//Дешифровка
vector<string> decrypt(vector<string> text, size_t k)
{
	k %= alph_size;
	string txt;
	for (size_t i = 0; i < text.size(); ++i) {
		txt = text[i];
		for (size_t j = 0; j < txt.length(); ++j)
		{
			if (txt[j] == ' ') continue;
			else if (isprint((unsigned char)txt[j]))
			{
				txt[j] = alphabet[(alphabet.find(txt[j]) - k + alph_size) % alph_size];
			}
		}
		text[i] = txt;
	}
	return text;
}

void showmenu()
{
	cout << "Menu : " << endl;
	cout << "1 - Open file\n";
	cout << "2 - Write text from file\n";
	cout << "3 - Crypt file\n";
	cout << "4 - Decrypt file\n";
	cout << "0 - Exit\n";
	cout << endl;
}
//реализация
int main()
{
	size_t key = 0; bool num = true; int count = 0; string path = "";
	vector<string> text;  //текст считанный из файла
	while(num)
	{
		system("cls");
		showmenu();
		cin >> count;
		switch (count)
		{
			case 1:   //Открыть файл
			{
				cout << "Write a file name" << endl;
				path = "";
				cin >> path;
				text = read_file(path);
				system("pause");
				break;
			};
			case 2:   //Выписать строку из файла
			{
				if (text.size() == 0) cout << "Text is empty!" << endl;
				else print_text(text);
				system("pause");
				break;
			};
			case 3:   //Зашифровать файл
			{
				if (text.size() == 0) cout << "Text is empty!" << endl;
				else 
				{
					cout << "Write key:" << endl;
					cin >> key;
					string file_name = path + "_crypt.txt";
					write_file(file_name, encrypt(text, key));
					cout << ("Text crypted, path: " + file_name) << endl;
				}
				system("pause");
				break;
			};
			case 4:   //Расшифровать файл
			{
				if (text.size() == 0) { cout << "Text is empty!" << endl; }
				else {
					cout << "write key:" << endl;
					cin >> key;
					string file_name = path + "_decrypt.txt";
					write_file(file_name, decrypt(text, key));
					cout << ("text decrypted, path: " + file_name) << endl;
				}
				system("pause");
				break;
			};
			case 0:   //Выйти из программы
			{
				num = false;
				exit(0);
			}
			default:
			{
				cout << "Wrong input!" << endl;
				system("pause");
				break;
			}
			
		}
	}
	return 0;
}