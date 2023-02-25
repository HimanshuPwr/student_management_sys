#include <bits/stdc++.h>
using namespace std;

struct date
{
	int day, month, year;
};

struct student
{
	int roll_no;
	int standard;
	char section;
	date *dob;
};

struct TrieNode
{

	unordered_map<char, TrieNode *> child;

	bool isLast;
	student *info;

	TrieNode()
	{

		for (char i = 'a'; i <= 'z'; i++)
			child[i] = NULL;

		isLast = false;
		info = NULL;
	}
};

TrieNode *root = NULL;

void insert(string s)
{
	int len = s.length();

	TrieNode *itr = root;
	for (int i = 0; i < len; i++)
	{

		TrieNode *nextNode = itr->child[s[i]];
		if (nextNode == NULL)
		{

			nextNode = new TrieNode();

			itr->child[s[i]] = nextNode;
		}

		itr = nextNode;

		if (i == len - 1)
		{
			itr->isLast = true;
			cout << "\nEnter student details please\n";
			itr->info = new student();
			cout << "Enter roll number\n";
			cin >> itr->info->roll_no;
			cout << "\nEnter standard\n";
			cin >> itr->info->standard;
			cout << "\nEnter section\n";
			cin >> itr->info->section;
			cout << "\nEnter dob\nday: ";
			itr->info->dob = new date();
			cin >> itr->info->dob->day;
			cout << "\nEnter month: ";
			cin >> itr->info->dob->month;
			cout << "\nEnter year: ";
			cin >> itr->info->dob->year;
			cout << "\n";
		}
	}
}

void displayContactsUtil(TrieNode *curNode, string prefix)
{

	if (curNode->isLast)
	{
		cout << prefix << endl;
		cout << curNode->info->roll_no << endl;
		cout << curNode->info->standard << "-" << curNode->info->section << endl;
		cout << curNode->info->dob->day << "/" << curNode->info->dob->month << "/" << curNode->info->dob->year << "/" << endl
			 << endl;
	}

	for (char i = 'a'; i <= 'z'; i++)
	{
		TrieNode *nextNode = curNode->child[i];
		if (nextNode != NULL)
			displayContactsUtil(nextNode, prefix + (char)i);
	}
}

void displayContacts(string str)
{
	TrieNode *prevNode = root;

	string prefix = "";
	int len = str.length();

	int i;
	for (i = 0; i < len; i++)
	{
		prefix += (char)str[i];

		char lastChar = prefix[i];

		TrieNode *curNode = prevNode->child[lastChar];

		if (curNode == NULL)
		{
			cout << "nNo Results Found for :" << prefix
				 << " n";
			i++;
			break;
		}

		cout << "nSuggestions based on :" << prefix
			 << " are n";
		displayContactsUtil(curNode, prefix);

		prevNode = curNode;
	}

	for (; i < len; i++)
	{
		prefix += (char)str[i];
		cout << "nNo Results Found for : " << prefix
			 << " n";
	}
}

void insertIntoTrie(int n)
{

	root = new TrieNode();
	string name;

	for (int i = 0; i < n; i++)
	{
		cout << "Please enter name of Student\n";
		cin >> name;
		insert(name);
	}
}

int main()
{

	int n;
	cout << "Please enter number of students\n";
	cin >> n;

	insertIntoTrie(n);

	string query;
	cout << "Please enter your query\n";
	cin >> query;

	displayContacts(query);

	return 0;
}
