#include <iostream>
#include <cctype>
#include <cstring>
#include "assignment2.h"

using namespace std;
const int SIZE = 200;

int main(void)
{
	char buffer[SIZE];
	char *message;
	int priority;
	features test;
	
	
		cout << "\nEnter preferred feature: ";
		cin.get(buffer, 200, '\n');
		cin.ignore(200, '\n');

		message = new char[strlen(buffer) + 1];
		strcpy(message, buffer);
		
		cout << "\nEnter priority of this feature: ";
		cin >> priority;
		while(cin.fail())
		{
			cin.clear();
			cin.ignore(200, '\n');
			cout << " \nEnter priority of this feature: ";
			cin >> priority;
		}
		cin.ignore(200, '\n');
		
		test.insert(priority, message);
		test.display();
		delete [] message;		
	
}
