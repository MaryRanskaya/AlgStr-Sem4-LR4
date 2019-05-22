#include <iostream>
#include "array.h"

using namespace std;

int main()
{
	Alg obj;
	obj.input();
	string departure, arrive;
	cout << "enter the city of the departure:";
	cin >> departure;
	cout << "enter the city of the arrival: ";
	cin >> arrive;
	obj.find_path(departure, arrive);

	system("pause");
	return 0;
}