#include <iostream>
#include <cctype>
#include <cstring>
#include "attributes.h"

using namespace std;

attributes::attributes(void)
{
/*Constructor*/
	head = NULL;
}

attributes::~attributes(void)
{
/*Destructor*/
	while(head)
	{
		node *temp = head->next;
		delete head->message;
		delete head;
		head = temp;
	}
}


int attributes::insert(int priority, char message[])
{
/*	For the insert function, we're inserting nodes onto a linked list
	Nodes are ordered with respect to the priority
	insert takes 2 arguments, an integer, and a character array.
	The integer denotes the priority of the attribute we're adding and the 
	array describes the attribute we want
*/
	if(!head)
	{
		head = new node;
		head->priority = priority;
		head->message = new char[strlen(message) + 1];
		strcpy(head->message, message);
		head->next = NULL;
		return 1; //return 1 for success
	}
	else
	{
		node *temp;
		node *add;
		//If the new node has a priority less than the head, add it to the front
		if(head->priority > priority)
		{
			temp = new node;
			temp->priority = priority;
			temp->message = new char[strlen(message) + 1];
			strcpy(temp->message, message);
			//temp->message = message;
			temp->next = head;
			head = temp;
			return 1;		
		}

		/*otherwise...we iterate through the list until the next node is either greater than or equal to the priority we want to add.
		  If the current node is equal to the priority we want to add, this means that we've previously assigned this priority. We're
		  trying to mimick an absolute ordered list, so in this case, we will change the associated attribute. 
		  If the node's priority is not equal, we create a new node and add it behind. 
		*/
		else
		{
			temp = head;

			while(temp->next != NULL && temp->next->priority <= priority)
			{
				temp = temp->next;
			}
			
			if(temp->priority == priority)
			{
				cout << "\nAn attribute with this priority is already assigned. Previous attribute will be overwritten.\n";
				delete [] temp->message;
				temp->message = new char[strlen(message) + 1];
				strcpy(temp->message, message);
			}
			else
			{
				add = new node;
				add->priority = priority;
				add->message = new char[strlen(message) + 1];
				strcpy(add->message, message);
				add->next = temp->next;
				temp->next = add;
			}
		}	
		return 1;
	}
}

int attributes::remove(int priority)
{
/*	Remove function has 1 argument.
	The user will specify which attribute to remove 
	by the priority. Because I'm using a linked list, 
	it must iterate through the nodes in O(n), if we were
	using a true dynamically allocated (absolute ordered)
	array, this would be reduced to O(1)... but whatever
*/
	node *temp = head;
	node *current;
	if(!head)
	{
		return 0;
	}
	/*If the head is equal to the priority specified, we remove it*/
	else
	{
		if(head->priority == priority)
		{
			temp = head->next;
			delete []head->message;
			delete head;
			head = temp;
			return 1;
		}
		else
		{
			while(temp->next != NULL && temp->next->priority != priority)
			{
				temp = temp->next;
			}
		
			/*If we iterate through the LL and don't find the priority user
			  specified, that means temp->next == NULL and the priority is not
			  in the list.
			*/
			if(temp->next == NULL)
			{
				cout << "\nAn attribute associated with this priority level was not found\n";
			}
			else
			{
				//set 'current' to become the node we want to delete
				current = temp->next; 
				temp->next = current->next;
				
				delete []current->message;
				delete current;			
			}
			return 1;
		}
	}
	return 0; //return 0 if it didn't work
}

int attributes::display(void)
{
/*	Display function takes no arguments
	If the head == NULL, prints out a statement that the list is empty.
	otherwise, this function will iterate through the linked list and 
	print out each node's priority and attribute
*/
	if(!head)
	{
		return 0;
	}
	else
	{
		node *temp = head;
		cout << "\n________ALL ATTRIBUTES AND PRIORITY LEVELS________";
		while(temp)
		{
			cout << "\nPriority: " << temp->priority << "\tAttribute: " << temp->message;
			temp = temp->next;
		}
		cout << '\n';
		return 1;
	}
}


