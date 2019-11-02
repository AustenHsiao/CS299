#include <iostream>
#include <cctype>
#include <cstring>
#include "reject.h"

using namespace std;

reject::reject(void)
{
	/*Constructor*/
	head = NULL;
	add_index = 0;
}

reject::~reject(void)
{
	/*Destructor: we iterate through the nodes deleting everything in the 
	dynamically allocated array that != NULL, then we delete the array, then we 
	delete the node*/
	reject_node *temp = head;
	while(temp)
	{
		for(int i = 0; i < ARRAY_MAX; ++i)
		{
			if(temp->store_names[i] != NULL)
			{
				delete temp->store_names[i];
			}
		}
		delete []temp->store_names;
		temp = temp->next;
		delete head;
		head = temp;
	}

}

int reject::push(char store_name[])
{
	/*If the user decides that a certain store does not meet their needs, 
	the store name will be used as an argument to push it onto the reject 
	stack*/
	if(!head)
	{
		/*If the head doesn't exist, we make it, then make the double pointer,
		then set all of the pointers within the pointer array to NULL. Then 
		the first index is populated. add_index is incremented by 1 so we know
		where the next element is going*/
		head = new reject_node;
		head->store_names = new char*[ARRAY_MAX];
		for(int i = 0; i < ARRAY_MAX; ++i)
		{
			head->store_names[i] = NULL;
		}	
		head->store_names[add_index] = new char[strlen(store_name) + 1];
		strcpy(head->store_names[add_index], store_name);
		head->next = NULL;
		++add_index;
		return 1;
	}
	else
	{
		/*If the head already exists and the add_index is 0-4, we just update the index and 
		increment. If head already exists and the add_index == 5, then we make a new node at 
		the front, along with the array, then populate index 0.*/
		if(add_index < ARRAY_MAX) //if the add_index is 0-4. Technically, add_index should only ever stay = 0 when we call the constructor, since =0 means we fall back 1 node, =5 makes a new one.
		{
			head->store_names[add_index] = new char[strlen(store_name) + 1];
			strcpy(head->store_names[add_index], store_name);
			++add_index;
		}
		else if(add_index == ARRAY_MAX)
		{
			reject_node *current = new reject_node;
			current->store_names = new char*[ARRAY_MAX];
			for(int i = 0; i < ARRAY_MAX; ++i)
			{
				current->store_names[i] = NULL;
			}	
			add_index = 0;
			current->store_names[add_index] = new char[strlen(store_name) + 1];
			strcpy(current->store_names[add_index], store_name);
			current->next = head;
			head = current;
			++add_index;					 
		}
		return 1;
	}
	return 0;
}

int reject::pop(void)
{
	/*Pop will remove the last added element. If the head is NULL, return 0. If the head exists and the 
	add_index is greater than 0, we get rid of the element at [add_index - 1]*/
	if(!head)
	{
		return 0;
	}
	else
	{
		/*If add_index is greater than 0, this means that we have something occupying index 0. 
		So we don't need to destroy any nodes. Otherwise, if add_index==0, we need to get rid of the 
		node*/
		if(add_index > 0)
		{
			delete []head->store_names[add_index - 1];
			head->store_names[add_index - 1] = NULL;
			--add_index;
			if(add_index == 0)
			{
				pop();	
			}
			return 1;
		}
		else if(add_index == 0)
		{
			if(head->next == NULL)
			{
				delete head->store_names;
				delete head;
				head = NULL;
			}
			else
			{
				reject_node *current = head->next;
				delete []head->store_names;
				delete head;
				add_index = ARRAY_MAX - 1;
				head = current;
				delete head->store_names[add_index];
				head->store_names[add_index] = NULL;
			}
			return 1;
				
		}
		return 0;
	}
}

int reject::peek(void)
{
	/*If the head doesnt exist, return 0. Otherwise if head exists, we want to print out
	the most recent element, which is found at index [add_index - 1]. The way the other functions
	are implemented, we dont't have to worry about add_index being 0 or 5*/
	if(!head)
	{
		return 0;
	}
	else
	{
		cout << "\nRecent rejection: " << head->store_names[add_index - 1] << '\n';
		return 1;
	}

}

int reject::display(void)
{
	/*Display function prints out all of the rejected stores. The order in which they get printed
	is a bit wonky because it iterates through each array for each node, but since we don't care
	about order, I left it as is. What I mean is that if we consecutively push 1-9 onto the stack, 
	my print function will return: 6 7 8 9 1 2 3 4 5*/
	int count = 1;
	if(!head)
	{
		return 0;
	}
	else
	{
		reject_node *temp = head;	
		cout << "\n________Rejected Stores________\n";
		while(temp)
		{
			for(int i = 0; i < ARRAY_MAX; ++i)
			{
				if(temp->store_names[i] != NULL)
				{
					cout << count << ". " << temp->store_names[i] << '\n';
					++count; 
				}
			}
			temp = temp->next;
		}
		return 1;
	}
	return 0;
}
