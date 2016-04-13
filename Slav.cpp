#include "Slav.h"
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iterator>
#include <string>

using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size()); 
	/*Jest to leniwa inicjalizacja. Najpierw wywołuje się funkcja init(), 
	dzięki czemu names.size() przyjmuje wartość powstałą w wyniku działania funkcji init() zamiast 0.*/
	_name = names[rand() % amountOfNames];
	_id = _counter++;
}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id) + "]";
}

Slav::enum_sex Slav::sex()
{
	if (_name.back()=='a')
		return female;
	else
		return male;
}
