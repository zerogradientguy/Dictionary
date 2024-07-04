#ifndef DICTIONARY_H
#define DICTIONARY_H

using namespace std;
class Node
{
public:
	bool ok = 0;
	char data;
	Node* next[26];
	string meaning;
	Node();
};

class Tree
{
public:
	Node* root;
	void insert(string str, string meaning);
	Tree();
	bool checkstring(string str);
	bool search(string str);
	void Load();
	void callokNull();
	void okNull(Node* tmp);
	void suggest(Node* rr, std::string&);
	void finder(string str, string strArr[10]);
	void del(string str);
	void update();
	void unload(Node* ptr, string str);
	void unloader();
};

#endif // !DICTIONARY_H