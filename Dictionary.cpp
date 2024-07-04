#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

Node::Node()
{
	for (int i = 0; i < 26; i++)
	{
		next[i] = NULL;
	}
}

Tree::Tree()
{
	root = new Node;
}

bool Tree::checkstring(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			return true;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			return true;
		}
		else if (str[i] >= 32 && str[i] <= 47)
		{
			return true;
		}
	}
	return false;
}

void Tree::insert(string str, string meaning)
{
	Node* tmp = root;
	int size = str.size();
	bool found = 0;
	int j;

	if (checkstring(str))
	{
		cout << "Invalid word" << endl;
		return;
	}
	else if (checkstring(meaning))
	{
		cout << "Invalid meaning" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			found = 0;
			j = 0;
			for (; j < 26 && tmp->next[j] != NULL; j++)
			{
				if (str[i] == tmp->next[j]->data)
				{
					found = 1;
					tmp = tmp->next[j];
				}
			}
			if (found == 0)
			{
				tmp->next[j] = new Node;
				tmp->next[j]->data = str[i];
				tmp = tmp->next[j];

			}
		}
		tmp->meaning = meaning;
	}
}


void Tree::Load()
{
	string str, str1;
	ifstream in;
	in.open("Dictionary.txt");
	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> str >> str1;
			if (!in.eof())
			{
				insert(str, str1);
			}
		}
	}
	else
	{
		cout << "File NOt found" << endl;
		exit(0);
	}
}

bool Tree::search(string str)
{
	bool found = true;
	Node* ptr = root;
	for (int i = 0; i < str.size(); i++)
	{
		found = false;
		for (int j = 0; j < 26; j++)
		{
			if (ptr->next[j] != NULL && str[i] == ptr->next[j]->data)
			{
				found = true;
				ptr = ptr->next[j];
				break;
			}
		}
		if (!found)
			break;
	}
	if (found == true)
	{
		cout <<"\t\t\t\t" << str << "       " << ptr->meaning << endl;
		return true;
	}
	else
	{
		return false;
	}
}

void Tree::finder(string str, string strArr[10])
{
	for (int k = 0; k < 10; k++)
	{
		Node* ptr = root;
		for (int i = 0; i < str.size(); i++)
		{
			for (int j = 0; j < 26; j++)
			{
				if (ptr->next[j] != NULL && str[i] == ptr->next[j]->data)
				{
					strArr[k] += ptr->next[j]->data;
					ptr = ptr->next[j];
					break;
				}
			}
		}
		suggest(ptr, strArr[k]);
	}
	callokNull();
}

void Tree::callokNull()
{
	okNull(root);
}

void Tree::okNull(Node* tmp)
{
	if (tmp != NULL)
	{
		tmp->ok = 0;
		for (int i = 0; i < 26; i++)
		{
			okNull(tmp->next[i]);
		}
	}
	return;
}

void Tree::suggest(Node* rr, string& newStr)
{
	int count = 0;
	Node* tmp = rr;
	bool flag = 0;
	while (tmp != NULL)
	{
		int j = 0;
		flag = 1;
		for (; j < 26; j++)
		{
			if (tmp->next[j] != NULL && tmp->next[j]->ok == 0)
			{
				flag = 0;
				tmp->ok = 1;
				tmp = tmp->next[j];
				break;
			}
		}
		if (flag == 1)
		{
			tmp = tmp->next[0];
		}

		if (tmp != NULL)
		{
			newStr += tmp->data;
		}
	}

}

void Tree::del(string str)
{
	bool found = false;
	Node* ptr = root;
	for (int i = 0; i < str.size(); i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (ptr->next[j] != NULL && str[i] == ptr->next[j]->data)
			{
				found = true;
				if (i == str.size() - 1)
					ptr->next[j] = NULL;
				else
					ptr = ptr->next[j];
				break;
			}
		}
	}
}


void Tree::update()
{
	string str, str1, option;
	cout << "Entre word to be updated: ";
	cin >> str;
	system("cls");
	cout << "Are you sure you want to update word?" << endl;
	cout << "YES      ||      NO" << endl;
	cin >> option;
	if (option >= "0" && option <= "9")
	{
		cout << "Invalid input" << endl;
	}
	else
	{
		if (option == "yes")
		{
			if (search(str))
			{
				del(str);
				cout << "Entre updated word : ";
				cin >> str;
				cout << "Entre updated word meaning : ";
				cin >> str1;
				insert(str, str1);
			}
			else
			{
				cout << "Word not found" << endl;
			}
		}

		else if (option == "no")
		{
			cout << "Word not updated" << endl;
		}
	}
}

void Tree::unloader()
{
	ofstream out;
	out.open("Dictionary.txt");
	out.close();
	unload(root, "");
}

void Tree::unload(Node* ptr, string str) {
	bool flag = 0;
	for (int i = 0; i < 26; i++) {
		if (ptr->next[i] != NULL) {
			unload(ptr->next[i], str + ptr->next[i]->data);
			flag = 1;
		}
	}
	if (!flag)
	{
		ofstream out;
		out.open("Dictionary.txt", ios::app);
		out << str << "\t" << ptr->meaning << endl;
		out.close();
	}
}