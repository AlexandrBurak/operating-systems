/*...*/
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>   
#include <windows.h>
using namespace std;


struct DataForPolynom {
	int deg;
	vector<double> odds;
	double x;
	double res;
};


DWORD WINAPI polynom(LPVOID par)
{

	DataForPolynom* data = (DataForPolynom*)par;

	double res = 0;
	for (int i = 0; i < data->deg; i++)
	{
		res += data->odds[i] * pow(data->x, data->deg - i);
		Sleep(15);
	}
	res += data->odds[data->deg];
	Sleep(15);
	cout << "p(" << data->x << ") = " << res << endl;
	data->res = res;
	return 0;
}


void get_data_for_th(DataForPolynom& dt) {
	cout << "Vvedite stepen' polynoma: ";
	cin >> dt.deg;
	for (int i = 0; i < dt.deg + 1; i++) {
		double var;
		cout << "Koeficient: ";
		cin >> var;
		dt.odds.push_back(var);
	}
	cout << endl;
	
}

int main() {
	DataForPolynom num, denum;
	get_data_for_th(num);
	get_data_for_th(denum);
	double x;
	cout << "Vvedite znachenie x: ";
	cin >> x;
	cout << endl;
	num.x = x;
	denum.x = x;

	int polynom_count = 2;

	HANDLE* PolynomThreadHandls = new HANDLE[polynom_count];
	DWORD* PolynomThreadID = new DWORD[polynom_count];
	PolynomThreadHandls[0] = CreateThread(NULL, 0, polynom, (void*)&num, 0, &PolynomThreadID[0]);
	PolynomThreadHandls[1] = CreateThread(NULL, 0, polynom, (void*)&denum, 0, &PolynomThreadID[1]);
	WaitForMultipleObjects(polynom_count, PolynomThreadHandls, TRUE, INFINITE);

	cout << "f(" << x << ") = " << num.res / denum.res;

	return 0;
}