#include <iostream>
#include "assignment1.h"
#include <cstring>
#include <cctype>

using namespace std;

int main(void)
{
	college_life portland;
	char *category; 
	char *input;
	char buffer[500];
	int n;
	int choices;
	int choice;

	display_menu();
	n = menu_option();
	while(n != 9)
	{
		switch(n)
		{
			case 1: cout << "\nEnter category ('Registering', 'Materials', 'Homework': CaSe SeNsItIvE):\n";
				cin.get(buffer, 500, '\n');
				cin.ignore(500, '\n');
				category = new char[strlen(buffer) + 1];
				strcpy(category, buffer);
				
				cout << "\nEnter hint:\n";
				cin.get(buffer, 500, '\n');
				cin.ignore(500, '\n');
				input = new char[strlen(buffer) + 1];
				strcpy(input, buffer);

				portland.add_hint(category, input); 	
				delete []category;
				delete []input;
				break;

			case 2: cout << "\nEnter the category of the hint you want to like ('Registering', 'Materials', 'Homework': CaSe SeNsItIvE):\n";
				cin.get(buffer, 500, '\n');
				cin.ignore(500, '\n');
				category = new char[strlen(buffer) + 1];
				strcpy(category, buffer);
				choices = portland.display(category);	
				if(choices == 0)
				{
					cout << "\nNo hints to like!\n";
					break;
				}

				cout << "\nEnter the number associated with the hint you want to like:\n";
				cin >> choice;
				while(cin.fail() || choice > choices || choice < 1)
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Invalid input. Enter index number of the hint you want to like:\n";
					cin >> choice;
				}
				cin.ignore(100, '\n');
			
				portland.like(category, choice);
				delete []category;
				
				break;

			case 3: cout << "\nEnter category to display ('Registering', 'Materials', 'Homework': CaSe SeNsItIvE):\n";
				cin.get(buffer, 500, '\n');
				cin.ignore(500, '\n');
				category = new char[strlen(buffer) + 1];
				strcpy(category, buffer);
				
				portland.display(category); 	
				delete []category;
				break;
		}
		display_menu();
		n = menu_option();
	}
}
