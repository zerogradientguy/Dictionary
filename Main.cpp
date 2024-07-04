#include<iostream>
#include<string>
#include<windows.h>
#include"Dictionary.h"
#include<fstream>

using namespace std;

void nullstr(string str[10]) {
	for (int i = 0; i < 10; i++)
	{
		str[i] = "\0";
	}
}

int main()
{
	Tree obj;
	string option;
	string strArr[10];
	obj.Load();
	char choice;
	string cho = " ";

	string word, meaning, searchWord, prefix, delword, suggestions[10];
	while (true)
	{
		if (cho != "")
		{
			system("PAUSE");
			system("CLS");
			cout << "\n\n\n\n\n\n\n\n";
			cout << "\t\t\t\t**********************************************\n";
			cout << "\t\t\t\t*                                            *\n";
			cout << "\t\t\t\t*                                            *\n";
			cout << "\t\t\t\t*        Enter To Select the Option          *\n";
			cout << "\t\t\t\t*        1. Insert word                      *\n";
			cout << "\t\t\t\t*        2. Search word                      *\n";
			cout << "\t\t\t\t*        3. Suggest word                     *\n";
			cout << "\t\t\t\t*        4. Delete word                      *\n";
			cout << "\t\t\t\t*        5. Update word                      *\n";
			cout << "\t\t\t\t*        6. EXIT                             *\n";
			cout << "\t\t\t\t*                                            *\n";
			cout << "\t\t\t\t*                                            *\n";
			cout << "\t\t\t\t**********************************************\n";
			cout << "\t\t\t\t*************ENTER CHOICE (1-4)    :     ";
		}
		getline(cin, cho);
		if (cho.length() == 1)
		{
			choice = cho[0];
			cho = "\n";

			switch (choice)
			{
			case '1':
				cout << "\t\t\t\tEnter word to insert: ";
				cin >> word;
				cout << "\t\t\t\tEnter meaning of word: ";
				cin >> meaning;
				obj.insert(word, meaning);
				break;
			case '2':
				cout << "\t\t\t\tEnter word to search: ";
				cin >> searchWord;
				
				if (obj.search(searchWord))
				{
					cout << "\t\t\t\tWORD FOUND!!" << endl;
				}
				else
				{
					cout << "\n\t\t\t\tWORD NOT FOUND!!!" << endl;
				}
				break;
			case '3':
				cout << "\t\t\t\tEnter prefix for word suggestions: ";
				cin >> prefix;
				obj.finder(prefix, suggestions);
				system("cls");
				cout << "\t\t\t\tWord suggestions:\n";
				for (int i = 0; i < 10; ++i)
				{
					string suggestion = suggestions[i];
					cout << "- " << suggestion << endl;
				}
				nullstr(suggestions);
				break;
			case '4':
				cout << "\t\t\t\tEnter word to be deleted: ";
				cin >> delword;
				system("cls");
				cout << "\t\t\t\tAre you sure you want to delete word?" << endl;
				cout << "YES or NO" << endl;
				cin >> option;
				if (option >= "0" && option <= "9")
				{
					cout << "\t\t\t\tINVALID INPUT!!! " << endl;
				}
				else
				{
					if (option == "yes")
					{
						obj.del(delword);
						cout << "\t\t\t\tWORD DELETED !!!\n";
					}
					else if (option == "no")
					{
						cout << "\t\t\t\tWORD NOT DELETED" << endl;
					}
				}
				break;
			case '5':
				obj.update();
				break;
			case '6':
				cout << "\n\n\t\t\t\tUpdating File.........\n";
				obj.unloader();
				cout << "\n\n\t\t\t\tExiting Program.\n";
				return 0;
			default:
				choice = ' ';
				cout << "\t\t\t\tINVALID INPUT, INPUT AGAIN!!\n";
			}

		}
	}
	return 0;
}