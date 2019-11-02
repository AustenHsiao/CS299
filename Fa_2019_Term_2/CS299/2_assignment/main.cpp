#include <iostream>
#include <cstring>
#include <cctype>
#include "attributes.h"
#include "available.h"
#include "reject.h"

using namespace std;

const int SIZE = 100;

int main(void)
{
	/*Variables Section; I need 4 static char arrays because of my enqueue function for available products.
	Readme.txt refers to this function as the largest pitfall in the program. I should've written it differently*/
	attributes attribute_list;
	available dealer;
	reject reject_list;
	char YN;
	char buffer[SIZE];
	char attribute1[SIZE];
	char attribute2[SIZE];
	char attribute3[SIZE];
	int priority;
	int menu = 0;
	
	/*Menu*/
	while(menu != 9)
	{
		cout << "\n________MENU________\n\n" << "1. Add feature\n" << "2. Remove feature\n" << "3. Display entered features\n" << "4. Add store\n" << "5. Evaluate product(s)\n" << "6. Display all rejected stores\n" << "7. Display most recent rejected store\n" << "(Enter 9 to exit) Enter menu option: ";
		cin >> menu;
		while(cin.fail() || menu < 1 || menu > 9)
		{
			cin.clear();
			cin.ignore(SIZE, '\n');
			cout << "Invalid option, enter menu option: ";
			cin >> menu;
		}
		cin.ignore(SIZE, '\n');
		cout << "\n\n";
		switch(menu)
		{
			case 1: cout << "Enter feature: ";
				cin.get(buffer, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				cout << "\nEnter priority: ";
				cin >> priority;
				while(cin.fail() || priority < 1)
				{
					cin.clear();
					cin.ignore(SIZE, '\n');
					cout << "Invalid option, enter priority: ";
					cin >> priority;
				}
				cin.ignore(SIZE, '\n');
				
				attribute_list.insert(priority, buffer);
				break;

			case 2: if(attribute_list.display() == 0)
				{
					cout << "No features to remove\n";
					break;
				}
				cout << "Enter the priority level of the feature you want to remove: ";
				cin >> priority;
				while(cin.fail() || priority < 1)
				{
					cin.clear();
					cin.ignore(SIZE, '\n');
					cout << "Invalid option, enter menu option: ";
					cin >> priority;
				}
				cin.ignore(SIZE, '\n');
				attribute_list.remove(priority);
				break;
			
			case 3: if(attribute_list.display() == 0)
				{
					cout << "No features to display\n";
				}	
				break;
	
			case 4: cout << "Enter store name: ";
				cin.get(buffer, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				
				cout << "Enter product's 1st attribute: ";
				cin.get(attribute1, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				
				cout << "Enter product's 2nd attribute: ";
				cin.get(attribute2, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				
				cout << "Enter product's 3rd attribute: ";
				cin.get(attribute3, SIZE, '\n');
				cin.ignore(SIZE, '\n');
			
				dealer.enqueue(buffer, attribute1, attribute2, attribute3);
				break;	

			case 5: if(attribute_list.display() == 0)
				{
					cout << "No features to compare\n";
					break;
				}
			
				while(dealer.peek() == 1)
				{
					cout << "\nDo you want to remove this store (Y/N): ";
					cin >> YN;
					while((YN != 'Y' && YN != 'y' && YN != 'N' && YN != 'n') || cin.fail())
					{
						cin.clear();
						cin.ignore(SIZE, '\n');
						cout << "\nInvalid response. Do you want to remove this store (Y/N): ";
						cin >> YN;
					}			
					cin.ignore(SIZE, '\n');
					if(YN == 'n' || YN == 'N')
					{
						dealer.dequeue(); //I'm removing it from the queue, so I guess I should've made an 'accept' ADT, but I have a headache now so no
					}	
					else
					{
						cout << "\nEnter the name of the store for confirmation: "; //This is my way of not integrating the ADTs with each other. It's difficult for me to access the data stored in the node of a different ADT, so I'm not going to bother
						cin.get(buffer, SIZE, '\n');
						cin.ignore(SIZE, '\n');
						reject_list.push(buffer);
						dealer.dequeue();
					}
				}
				break;
			case 6: if(reject_list.display() == 0)
				{ 
					cout << "\nNo rejected stores to display\n";
				}
				break;
			case 7: if(reject_list.peek() == 0)
				{
					cout << "\nNo rejected stores to display\n";
				}
		}
	}
return 0;
}

