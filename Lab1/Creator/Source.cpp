#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

struct employee
{
	int num;
	char name[10];
	double hours;
};

int main(int argc, char* argv[])
{
	char* filename = argv[1];

	ofstream out(filename, ios::binary);

	cout << "How many emps you want write?\n";
	int num = atoi(argv[2]);


	for (int i = 0; i < num; i++)
	{
		system("cls");
		employee emp;
		cout << "Enter employee num:\n";
		cin >> emp.num;

		cout << "Enter employee name:\n";
		cin >> emp.name;

		cout << "Enter employee hours:\n";
		cin >> emp.hours;

		out.write((char*)&emp, sizeof(struct employee));
	}

	out.close();

	return 1;
}