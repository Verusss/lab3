/*Program pozwala na wygenerowanie losowych Słowian (tylu, ile poda użytkownik przy starcie programu), 
każdemu z nich przypisuje imię z dołączonego pliku oraz numer.*/
#include <vector>	
#include <set>		
#include <map>		

#include <queue>	
#include <stack>	

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Slav.h"

using namespace std; 

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
void sexRecognition(Slav *, int);

/*Funkcja wywołuje generowanie Słowian, a także wywołujekolejne funkcje oraz zawiera obsługę błędów. */
int main(int argc, char const *argv[])
{
	if (argc!=2)
	{
		cout << "Incorrect number of arguments." << endl;
		return 0;
	}
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	sexRecognition(slavs, n);

	delete [] slavs;
}

/*W funkcji wkładamy Słowian do różnego rodzaju kontenerów.*/
void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("\n# Containers\n");
	REPORT_CONTAINERS;
	printf("\n## vector\n");

	//Słowianie umieszczani są w losowej kolejności w wektorze. 
	srand(time(NULL));
	for(int i=0; i<n; i++)
		if(rand()%2) 
			vectorOfSlavs.push_back(&slavs[i]);
		else 
			vectorOfSlavs.insert(vectorOfSlavs.begin(), &slavs[i]);


	//Wyświetlamy wszystkich Słowian w wektorze. 
	for (vector <Slav *>::iterator iter=vectorOfSlavs.begin(); iter!=vectorOfSlavs.end(); iter++)
		cout << (*iter)->description() << endl;


	REPORT_CONTAINERS;
	printf("\n## set\n");

	//Przenosimy Słowian z wektoru do zbioru. 
	for (vector <Slav *>::iterator iter=vectorOfSlavs.begin(); iter!=vectorOfSlavs.end(); iter++)
		setOfSlavs.insert (*iter);
	vectorOfSlavs.clear();
	
	REPORT_CONTAINERS;
	printf("\n## map\n");

	//Tworzymy słownik Słowian z zawartości zbioru, czyszcząc ten zbiór. 
	for (set <Slav *>::iterator iter=setOfSlavs.begin(); iter!=setOfSlavs.end(); iter++)
		mapOfSlavs[*iter]=*(++iter);
	setOfSlavs.clear();

	//Wyświetlamy pary Słowian.
	for (map <Slav *, Slav *>::iterator iter=mapOfSlavs.begin(); iter!=mapOfSlavs.end(); iter++)
		cout << iter->first->description() << "\t" << iter->second->description() << endl;
	
	REPORT_CONTAINERS;
}

/*W funkcji ustawiamy Słowian w kolejce oraz przenosimy ich na stos, a następnie z tego stosu zdejmujemy.*/
void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("\n# Adapters\n");
	REPORT_ADAPTERS;
	printf("\n## queue\n");

	//Umieszczenie Słowian w kolejce.
	for (int i=0; i<n; i++)
		queueOfSlavs.push(&slavs[i]);

	
	REPORT_ADAPTERS;

	printf("\n## stack\n");
	//Przenosimy Słowian z kolejki do stosu.
	for (int i=0; i<n; i++)
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	//Wyświetlamy Słowian zdejmowanych ze stosu. 
	for (int i=0; i<n; i++)
	{
		cout << stackOfSlavs.top()->description() << endl;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

/*Funkcja korzysta z rozpoznawania płci na podstawie tego, czy ostatni znak danego imienia jest literą
"a", a następnie wkłada Słowian do jednego wektora, Słowianki do drugiego. Tworzy słowniki z obu wektorów
oraz nazw danej płci i pozwala użytkownikowi na wyświetlenie wektora, zawierającego Słowianki (female) 
lub Słowian (male).*/
void sexRecognition(Slav * slavs, int n)
{
	vector <Slav *> vectorOfWomen;
	vector <Slav *> vectorOfMen;
	for(int i=0; i<n; i++)
	{
		if(slavs[i].sex()==Slav::male)
			vectorOfMen.push_back(&slavs[i]);
		else 
			vectorOfWomen.push_back(&slavs[i]);
	}
	map <vector <Slav *>, string> mapOfWomen;
	map <vector <Slav *>, string> mapOfMen;
	string female;
	mapOfWomen[vectorOfWomen]="female";
	mapOfMen[vectorOfMen]="male";
	cout << "Write in 'male' or 'female':" << endl;
	string sex;
	cin >> sex;
	if (sex=="female")
	{		
		if (vectorOfWomen.size()==0)
			cout << "Vector is empty." << endl;
		else 
		{
			if (vectorOfWomen.size()==1)
				cout << "There is 1 woman:" << endl;
			else 
			{
				cout << "There are " << vectorOfWomen.size() << " women:" << endl;
			}
			for (vector <Slav *>::iterator iter=vectorOfWomen.begin(); iter!=vectorOfWomen.end(); iter++)
				cout << (*iter)->description() << endl;
		}
	}
	else if (sex=="male")
	{
		if (vectorOfMen.size()==0)
			cout << "Vector is empty." << endl;
		else 
		{
			if (vectorOfMen.size()==1)
				cout << "There is 1 man:" << endl;
			else
			{
				cout << "There are " << vectorOfMen.size() << " men:" << endl;
			}
			for (vector <Slav *>::iterator iter=vectorOfMen.begin(); iter!=vectorOfMen.end(); iter++)
			cout << (*iter)->description() << endl;
		}
	}
	else 
		printf("Incorrect argument.\n");
}

/*Funkcja służy do wyświetlania wielkości poszczególnych kontenerów.*/
void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

/*Funkcja służy do wyświetlania wielkości poszczególnych adapterów.*/
void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());
}
