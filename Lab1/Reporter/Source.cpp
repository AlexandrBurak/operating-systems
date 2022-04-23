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
	char* fileEmpName = argv[1];
	char* fileReportName = argv[2];
	int payment_for_hour = atoi(argv[3]);

	ifstream in(fileEmpName, ios::binary);
	employee* emp = new employee[100];
	int size = 0;
	while (in.peek() != EOF)
	{
		employee e;
		in.read((char*)&e, sizeof(employee));
		emp[size++] = e;
	}
	in.close();

	ofstream out(fileReportName);

	out << "Report about file \"" << fileEmpName << "\":\n";
	out << "EmpNum !! EmpName !! EmpHours !! EmpPayment" << "\n";

	if (size != 0)
	{
		for (int i = 0; i < size; i++)
		{
			out << emp[i].num << "  !!  " << emp[i].name << "  !!  " << emp[i].hours << "  !!  " << emp[i].hours * payment_for_hour << endl;
		}
	}
	else
	{
		out << "-empty-\n";
	}

	out.close();

	return 1;
}