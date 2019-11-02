/*The structure of each method for the ADT is divided into 3 parts, one for each of the categories (registering, materials, homework). 
If I were to improve this code, I would've made the user input 1, 2, or 3 for the categories instead of having them input a case sentitive string.
This would be an improvement because each section could be condensed into 3 function calls (assuming I wrote a separate function that uses 1, 2, or 3 as an argument). 
Written by Austen Hsiao for CS299*/

#include "assignment1.h"
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

int menu_option(void)
{
	int n;

	cout << "\nSelect menu option (1-3). Enter '9' to quit:\n";
        cin >> n;
        while(cin.fail())
        {
	        cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid input. Select menu option (1-3). Enter '9' to quit:\n";
                cin >> n;
        }
	cin.ignore(100, '\n');
        return n;
}

college_life::college_life()
{
	head_registering = NULL;
	head_materials = NULL;
	head_homework = NULL;
}

void display_menu(void)
{
	cout << "\n________Main Menu________\n";
	cout << "1. Enter hint\n2. Like a hint\n3. Display hints\n";
}

college_life::~college_life()
{
	node *temp_head;
	node *nextone;
	//for registering
	if(head_registering)
	{
		temp_head = head_registering;
		nextone = temp_head->next;
		while(temp_head)
		{
			delete [] temp_head->hint;
			delete temp_head;
			temp_head = nextone;
			if(temp_head)
			{
				nextone = temp_head->next;
			}
		}
	}
	//for materials
	if(head_materials)
	{
		temp_head = head_materials;
		nextone = temp_head->next;
		while(temp_head)
		{
			delete [] temp_head->hint;
			delete temp_head;
			temp_head = nextone;
			if(temp_head)
			{
				nextone = temp_head->next;
			}
		}
	}
	//for homework
	if(head_homework)
	{
		temp_head = head_homework;
		nextone = temp_head->next;
		while(temp_head)
		{
			delete [] temp_head->hint;
			delete temp_head;
			temp_head = nextone;
			if(temp_head)
			{
				nextone = temp_head->next;
			}
		}
	}
}

void college_life::add_hint(char category[], char hint[])
{
	node *temp;
	node *newhint;

	if(strcmp(category, "Registering") == 0)	
	{	
		if(!head_registering)
		{
			head_registering = new node;
			head_registering->hint = new char[strlen(hint) + 1];
			strcpy(head_registering->hint, hint);
			head_registering->likes = 0;
			head_registering->next = NULL;
		}
		//If the linked list is not empty, append to the end:
		else
		{
			temp = head_registering;
			
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			newhint = new node;
			newhint->hint = new char[strlen(hint) + 1];
			strcpy(newhint->hint, hint);
			newhint->likes = 0;
			newhint->next = NULL;
			temp->next = newhint;
		}

	
	}
	else if(strcmp(category, "Materials") == 0)
	{
		if(!head_materials)
		{
			head_materials = new node;
			head_materials->hint = new char[strlen(hint) + 1];
			strcpy(head_materials->hint, hint);
			head_materials->likes = 0;
			head_materials->next = NULL;
		}	
		else
		{
			temp = head_materials;
			
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			newhint = new node;
			newhint->hint = new char[strlen(hint) + 1];
			strcpy(newhint->hint, hint);
			newhint->likes = 0;
			newhint->next = NULL;
			temp->next = newhint;
		}
	}
	else if(strcmp(category, "Homework") == 0)
	{
		if(!head_homework)
		{
			head_homework = new node;
			head_homework->hint = new char[strlen(hint) + 1];
			strcpy(head_homework->hint, hint);
			head_homework->likes = 0;
			head_homework->next = NULL;
		}	
		else
		{
			temp = head_homework;
			
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			newhint = new node;
			newhint->hint = new char[strlen(hint) + 1];
			strcpy(newhint->hint, hint);
			newhint->likes = 0;
			newhint->next = NULL;
			temp->next = newhint;
		}
	}
	else
	{
		cout << "\nCategory not recognized. Hint not added\n";
	}
}

int college_life::display(char category[])
{
	node *temp;
	int counter = 1;

	if(strcmp(category, "Registering") == 0)
	{
		if(!head_registering)
		{
			cout << "\nNo " << "Registering" << " hints to show\n";
			return 0;
		}
		else if(head_registering->next == NULL)
		{
			cout << "\n" << counter << ".\nHINT: " << head_registering->hint << "\nLIKES: " << head_registering->likes << '\n';	
			return 1;
		}
		else
		{
			temp = head_registering;
			while(temp)
			{
				cout << "\n" << counter << ".\nHINT: "<< temp->hint << "\nLIKES: " << temp->likes << '\n';
				temp = temp->next;
				counter += 1;
			}
		}		
	}
	else if(strcmp(category, "Materials") == 0)
	{
		if(!head_materials)
		{
			cout << "\nNo "<< "Material" << " hints to show\n";
			return 0;
		}
		else if(head_materials->next == NULL)
		{
			cout << "\n" << counter << ".\nHINT: " << head_materials->hint << "\nLIKES: " << head_materials->likes << '\n';	
			return 1;
		}
		else
		{
			temp = head_materials;
			while(temp)
			{
				cout << "\n" << counter << ".\nHINT: "<< temp->hint << "\nLIKES: " << temp->likes << '\n';
				temp = temp->next;
				counter += 1;
			}
		}		
	}
	else if(strcmp(category, "Homework") == 0)
	{
		if(!head_homework)
		{
			cout << "\nNo " << "Homework" << " hints to show\n";
			return 0;
		}
		else if(head_homework->next == NULL)
		{
			cout << "\n" << counter << ".\nHINT: " << head_homework->hint << "\nLIKES: " << head_homework->likes << '\n';	
			return 1;
		}
		else
		{
			temp = head_homework;
			while(temp)
			{
				cout << "\n" << counter << ".\nHINT: "<< temp->hint << "\nLIKES: " << temp->likes << '\n';
				temp = temp->next;
				counter += 1;
			}
		}		
	}
	else
	{
		cout << "\nCategory not recognized. No data to show\n";
		return 0;
	}
	return counter;
}

int college_life::like(char category[], int hint_index)
{
	int counter = 1;
	node *temp;
	node *previous;
	node *place;

	if(strcmp(category, "Registering") == 0)
	{
		if(hint_index == 1)
		{
			//the first node should be the most liked. So we don't need to sort the LLL
			head_registering->likes += 1;
		}
		//if we are not liking the first node (head), this else clause will 'like' the appropriate node.
		else
		{
			//temp is going to be the node we want to like. Previous is the node directly in front of temp
			temp = head_registering;
			previous = head_registering;
			place = head_registering;

			//Moves over the number of times specified and calls this node, "temp"
			while(counter < hint_index)
			{
				temp = temp->next;
				counter += 1;
			}
			temp->likes += 1;

			//Moves over until we see temp. This is before temp, so we call it, "previous"
			while(previous->next != temp)
			{
				previous = previous->next;
			}
			//previous->next becomes temp->next because temp will always move up if incremented (theres no way to decrement)
			previous->next = temp->next;
			
			//Here's where we start sorting stuff. If the number of likes on the node we just changed is greater than or equal to the hlikes on the head, it must be placed in the front. In other words, it becomes the new head
			if(temp->likes >= head_registering->likes)
			{
				temp->next = head_registering;
				head_registering = temp;
			}
			else
			{
				while(temp->likes < place->next->likes)
				{
					place = place->next;
				}
				temp->next = place->next;
				place->next = temp;				
			}	
		}					
	}
	else if(strcmp(category, "Materials") == 0)
	{
		if(hint_index == 1)
		{
			head_materials->likes += 1;
		}
		else
		{
			temp = head_materials;
			previous = head_materials;
			place = head_materials;

			while(counter < hint_index)
			{
				temp = temp->next;
				counter += 1;
			}
			temp->likes += 1;

			while(previous->next != temp)
			{
				previous = previous->next;
			}
			previous->next = temp->next;
			
			if(temp->likes >= head_materials->likes)
			{
				temp->next = head_materials;
				head_materials = temp;
			}
			else
			{
				while(temp->likes < place->next->likes)
				{
					place = place->next;
				}
				temp->next = place->next;
				place->next = temp;				
			}	
		}					

	}
	else if(strcmp(category, "Homework") == 0)
	{
		if(hint_index == 1)
		{
			head_homework->likes += 1;
		}
		else
		{
			temp = head_homework;
			previous = head_homework;
			place = head_homework;

			while(counter < hint_index)
			{
				temp = temp->next;
				counter += 1;
			}
			temp->likes += 1;

			while(previous->next != temp)
			{
				previous = previous->next;
			}
			previous->next = temp->next;
			
			if(temp->likes >= head_homework->likes)
			{
				temp->next = head_homework;
				head_homework = temp;
			}
			else
			{
				while(temp->likes < place->next->likes)
				{
					place = place->next;
				}
				temp->next = place->next;
				place->next = temp;				
			}	
		}					

	}
	return 0;
}

