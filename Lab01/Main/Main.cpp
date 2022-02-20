#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

#pragma warning(disable : 4996)

using namespace std;

struct employee
{
	int num;
	char name[10];
	double hours;
};

char* prepareDataForCreatorProcess(char*& fileEmplName, char*& num)
{

	char data[200] = "Creator ";
	strcat(data, fileEmplName);
	strcat(data, " ");
	strcat(data, num);
	char* str = new char[100];
	strcpy(str, data);

	return str;
}

void runCreatorProcess(char* dataForProcess)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	wchar_t wtext[100];
	mbstowcs(wtext, dataForProcess, strlen(dataForProcess) + 1);
	LPWSTR ptr = wtext;

	if (!CreateProcess(NULL, ptr, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "The new process is not created.\n";
		return;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void CheckBinFile(char* fileEmplName) {
	ifstream in(fileEmplName, ios::binary);

	cout << "Empls:\n";
	while (in.peek() != EOF)
	{
		employee empl;
		in.read((char*)&empl, sizeof(employee));
		cout << "Empl number: " << empl.num << " !! Empl name: " << empl.name << " !! Empl hours: " << empl.hours << endl;
	}

	in.close();

}

char* prepareDataForReporterProcess(char*& fileEmplName, char*& fileReportName, char*& hours)
{
	char data[200] = "Reporter ";

	strcat(data, fileEmplName);
	strcat(data, " ");
	strcat(data, fileReportName);
	strcat(data, " ");
	strcat(data, hours);

	char* str = new char[100];
	strcpy(str, data);

	return str;
}

void runReporterProcess(char* data)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	wchar_t wtext[100];
	mbstowcs(wtext, data, strlen(data) + 1);
	LPWSTR ptr = wtext;

	if (!CreateProcess(NULL, ptr, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "The new process is not created.\n";
		return;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void checkTextFile(char* fileName)
{
	ifstream fin(fileName);

	char line[200];
	while (!fin.eof())
	{
		fin.getline(line, 200);

		cout << line << endl;
	}

	fin.close();
}

int main()
{
	char* fileEmplName = new char[30];
	cout << "Enter file name: ";
	cin >> fileEmplName;
	cout << "\nEnter the count: ";
	char* num = new char[10];
	cin >> num;
	char* dataForCreator = prepareDataForCreatorProcess(fileEmplName, num);
	cout << dataForCreator << endl;
	runCreatorProcess(dataForCreator);
	CheckBinFile(fileEmplName);

	char* fileReportName = new char[30];
	cout << "\nEnter file report name: ";
	cin >> fileReportName;
	char* payment = new char[10];
	cout << "\nEnter payment: ";
	cin >> payment;
	cout << endl;
	char* data = prepareDataForReporterProcess(fileEmplName, fileReportName, payment);
	runReporterProcess(data);

	checkTextFile(fileReportName);

	return 0;
}