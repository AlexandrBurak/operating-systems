/*...*/
#include <iostream>
#include <thread>
#include <chrono>
#include "DataForPolynom.cpp"

using std::cout;
using std::cin;
using std::endl;
using std::thread;

void polynom(DataForPolynom& data)
{

	double res = 0;
	for (int i = 0; i < data.deg; i++)
	{
		res += data.odds[i] * pow(data.x, data.deg - i);
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
	res += data.odds[data.deg];
	std::this_thread::sleep_for(std::chrono::milliseconds(15));
	cout << "p(" << data.x << ") = " << res << endl;
	data.res = res;
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

	thread num_th(polynom, std::ref(num));
	thread denum_th(polynom, std::ref(denum));
	num_th.join();
	denum_th.join();

	cout << "f(" << x << ") = " << num.res / denum.res;

	return 0;
}