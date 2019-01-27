#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/*Test from Ubuntu*/

using namespace std;

/*Caesar cipher with a key*/
/*File on input*/

//Alphabet include english language
const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const size_t alph_size = alphabet.size();

//Read fron file
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

//Write into file
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

//Outputting text from a file
void print_text(vector<string> text)
{
	for (size_t i = 0; i < text.size(); i++) {
		cout << text[i] << endl;
	}
}

//Encryption
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

//Decryption
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

int main()
{
	size_t key = 0; bool num = true; int count = 0; string path = "";
	vector<string> text;  //text read from file
	while(num)
	{
		system("cls");
		showmenu();
		cin >> count;
		switch (count)
		{
			case 1:   //Open file
			{
				//Format: *.txt if the file is in the same directory as the program
				//Full path if not (*:\...\*.txt)
				cout << "Write a file name" << endl; 
				path = "";
				cin >> path;
				text = read_file(path);
				system("pause");
				break;
			};
			//Format: *.txt if the file is in the same directory as the program
			//Full path if not (*:\...\*.txt)
			case 2:   //Output text from a file
			{
				if (text.size() == 0) cout << "Text is empty!" << endl;
				else print_text(text);
				system("pause");
				break;
			};
			case 3:   //Encrypt file
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
			//To decrypt file you need to open it
			case 4:   //Decrypt file
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
			case 0:   //Exit the program
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
