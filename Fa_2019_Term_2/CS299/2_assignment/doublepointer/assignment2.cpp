#include <iostream>
#include <cctype>
#include <cstring>
#include "assignment2.h"

using namespace std;

/*char preferred_attribute(void)
{
	char buffer[SIZE];
	char *message;

	cout << "\nEnter preferred feature: ";
	cin.get(buffer, 100, '\n');
	cin.ignore(100, '\n');
	
	message = new char[strlen(buffer) + 1];
	strcpy(message, buffer);
	return message;
}*/

features::features(void)
{
	preferred = NULL;
	length = 0;
}

features::~features(void)
{
	for(int i = 0; i <= length; ++i)
	{
		if(preferred[i] != NULL)
		{
			delete [] preferred[i];
			preferred[i] = NULL;
		}
	}		
	delete [] preferred;
}

void features::insert(int priority, char *attribute)
{
	//If there's nothing in the array, we make a new array
	if(preferred == NULL)
	{
		//The maximum length is the priority because we're using indices to keep track of priority level
		preferred = new char*[priority]; 
		
		//for every value, assign the pointer to NULL, so we don't get random values from pre-existing memory
		for(int i = 0; i <= priority; ++i)
		{
			preferred[i] = NULL;
		}
		//Set the value at 'priority' level to the favorable attribute
		preferred[priority] = attribute;
		//we keep track of the array length so we can decide whether or not we need to extend it
		length = priority;	
	}

	//If the array already exists and the priority is > than the current length, we need to make a longer array
	else if(preferred != NULL && priority > length)
	{
		//Copy the entire array over to a new one
		char **copy = new char*[length];
		for(int i = 0; i <= length; ++i)
		{
			if(preferred[i] != NULL)
			{
				copy[i] = preferred[i];
			}
			else
			{
				copy[i] = NULL;
			}
		}

		delete [] preferred; //I don't want to delete the pointers captured within the array, but we need to delete it so we can make another one

		preferred = new char*[priority]; //make a new array of the right size
		for(int i = 0; i <= length; ++i)
		{
			if(copy[i] != NULL)
			{
				preferred[i] = copy[i];
			}
			else
			{
				preferred[i] = NULL;
			}
		}
		//For the rest of the array that we haven't copied over, set it all to NULL
		for(int i = length + 1; i <= priority; ++i)
		{
			preferred[i] = NULL;
		}
		//Add in the string (character array) and update the size counter
		preferred[priority] = attribute;
		length = priority;
		delete [] copy;
	}
	//The last case is if we have an array but the length is less than or equal to the current length
	else
	{	
		//we're going to overwrite anything in any position
		preferred[priority] = attribute;
		//length stays the same
	}	
}

void features::display(void)
{
	cout << '\n' << "_____Priority: Feature_____" << '\n';
	for(int i = 1; i <= length; ++i)
	{
		if(preferred[i])
		{
			cout << '\n' << i << ": " << preferred[i] << '\n';
		} 
		/*else
		{
			cout << "\n" << i << " is NULL\n";
		}*/
	} 
}


