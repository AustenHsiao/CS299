#include <iostream>
#include <cctype>
#include <cstring>
#include "available.h"

using namespace std;

available::available(void)
{
	head = NULL;
}

available::~available(void)
{
	if(!head)
	{}
	else
	{
		/*I think we were told not to structure the destructor this way,
		but it makes sense to me :\ */
		item_node *temp = head->next;
		while(temp != head)
		{
			delete []temp->name;
			delete []temp->attribute1;
			delete []temp->attribute2;
			delete []temp->attribute3;
			delete temp;
			temp = temp->next;	
		}
		delete []head->name;
		delete []head->attribute1;
		delete []head->attribute2;
		delete []head->attribute3;
		delete head;
	}
}	

int available::enqueue(char name[], char a1[], char a2[], char a3[])
{
	if(!head)
	{
		/*If no head node exists, we make one. Then we populate
		the three fields for each of the attributes. Each item 
		holds a maximum of 3 attributes*/
		head = new item_node;
		head->name = new char[strlen(name) + 1];
		strcpy(head->name, name);
		head->attribute1 = new char[strlen(a1) + 1];
		strcpy(head->attribute1, a1);
		head->attribute2 = new char[strlen(a2) + 1];
		strcpy(head->attribute2, a2);
		head->attribute3 = new char[strlen(a3) + 1];
		strcpy(head->attribute3, a3);
		head->next = head;
		return 1;
	}
	else
	{
		/*If the head already exists, we make a new node called 'add', 
		populate the fields, then link them in a way that makes a 
		circular linked list*/
		item_node *add = new item_node;	
		add->name = new char[strlen(name) + 1];
		strcpy(add->name, name);
		add->attribute1 = new char[strlen(a1) + 1];
		strcpy(add->attribute1, a1);
		add->attribute2 = new char[strlen(a2) + 1];
		strcpy(add->attribute2, a2);
		add->attribute3 = new char[strlen(a3) + 1];
		strcpy(add->attribute3, a3);
		add->next = head->next;
		head->next = add;
		return 1;
	}
	return 0; //0 if it's broken
}

int available::dequeue(void)
{
	/*Removes the last element of our list, which is 'head'. 
	Traversal is required to reset head, so we're dealing with
	time-complexity O(n)*/
	if(!head)
	{
		return 0;
	}
	else if(head->next == head)
	{
		delete []head->name;
		delete []head->attribute1;
		delete []head->attribute2;
		delete []head->attribute3;
		delete head;
		head = NULL;
		return 1;
	}
	else
	{
		item_node *to_delete = head;
		head = head->next;
		while(head->next != to_delete)
		{
			head = head->next;
		}
		head->next = to_delete->next;
		to_delete->next = NULL;
		delete []to_delete->name;
		delete []to_delete->attribute1;
		delete []to_delete->attribute2;
		delete []to_delete->attribute3;
		delete to_delete;
		to_delete = NULL;
		return 1;
	}
}

int available::peek(void)
{
	if(!head)
	{
		return 0;
	}
	else
	{
//		item_node *temp = head->next;
//		if(temp != head)
//		{
//			cout << "\nItem Name: " << temp->name << "; Attributes: " << temp->attribute1 << ", " << temp->attribute2 << ", " << temp->attribute3 << '\n';   
//			temp = temp->next;
//		}
		cout << "\nStore Name: " << head->name << "\t|| Product Attributes: " << head->attribute1 << ", " << head->attribute2 << ", " << head->attribute3 << '\n';   
		return 1;
	}
}

int available::display(void)
{
	/*Display function displays all of the items and their attributes.
	If the head doesnt exist, we return 0. If the head does exist, this function will 
	iterate through the list (from head->next to head) and print out the items + 
	attributes*/
	if(!head)
	{
		return 0;
	}
	else
	{
		item_node *temp = head->next;
		while(temp != head)
		{
			cout << "\nStore Name: " << temp->name << "; Product Attributes: " << temp->attribute1 << ", " << temp->attribute2 << ", " << temp->attribute3 << '\n';   
			temp = temp->next;
		}
		cout << "\nStore Name: " << temp->name << "; Product Attributes: " << temp->attribute1 << ", " << temp->attribute2 << ", " << temp->attribute3 << '\n';   
		return 1;
	}
}

