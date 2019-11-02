#include <iostream>
#include <cctype>
#include <cstring>
#include "songs.h"

using namespace std;

songs::songs()
{
	//Constructor
	root = NULL;
}

/*
songs::~songs()
{
	//Destructor. NEED TO IMPLEMENT
}*/
	
int songs::position(char name[])
{
	int length = strlen(name);
	int position = 0;
	char *lower_name = new char[strlen(name) + 1];
	strcpy(lower_name, name);

	for(int i = 0; i < length; ++i)
	{
		/*This loop converts the alphas in the song name to lower case
		then, "position" is calculated. "Position" is used as the integer
		value for the binary search tree. "Position" is calculated as the 
		sum of: (each character's ASCII value) \ (character's index). This 
		makes it harder for two different song names to have the same 
		"position" value.
		Eg. position(int('a') + int('b')) != position(int('b') + int('a'))*/
		lower_name[i] = tolower(name[i]);
		position += int( int(lower_name[i]) / (i+1) ); 
	}
	delete []lower_name; //I don't need this pointer after position is calculated.
	return position;
}

int songs::insert(char title[], char artist[], char album_name[], char length[])
{
	int size_of_title = strlen(title);
	//Make the node and calculate position
	node *new_entry = new node;
	new_entry->position = position(title);
	
	//Enter song title. There are two entires for this-- one is the lowercase name
	new_entry->title = new char[strlen(title) + 1];
	strcpy(new_entry->title, title);
	new_entry->lower_title = new char[strlen(title) + 1];
	for(int i = 0; i < size_of_title; ++i)
	{
		new_entry->lower_title[i] = tolower(title[i]);
	}
	
	//Enter song artist
	new_entry->artist = new char[strlen(artist) + 1];
	strcpy(new_entry->artist, artist);
	
	//Enter album name
	new_entry->album_name = new char[strlen(album_name) + 1];
	strcpy(new_entry->album_name, album_name);

	//Enter song length
	new_entry->length = new char[strlen(length) + 1];
	strcpy(new_entry->length, length);

	//Initialize the number of retrievals
	new_entry->number_of_retrievals = 0;
	
	//Return the value associated with the 'placement' function
	return placement(new_entry, root);	
}

int songs::placement(node *new_entry, node *&root)
{
	if(!root)
	{
		root = new_entry;
		return 1; 
	//Return 1 because it worked
	}
	else if(new_entry->position > root->position && root->right == NULL)
	{
	/*If we have a situation where the new node has an int value
	greater than the current node AND the right node is empty, put
	the new node in the right position*/
		root->right = new_entry;
		return 1;
	}
	else if(new_entry->position < root->position && root->left == NULL)
	{
	/*If we have a situation where the new node has an int value
	less than the current node AND the left node is empty, put
	the new node in the left position*/
		root->left = new_entry;
		return 1;
	}
	else if(new_entry->position == root->position)
	{
	/*If the int of the new node is equal to the root, 
	we have a collision. Dunno what to do, so return 2.
	This means that if we enter the same thing twice, 
	it will only keep the first entry*/
		return 2;
	}
	else if(new_entry->position > root->position)
	{
	/*If the previous cases don't apply and the new node's int
	is greater than the root, then we traverse to the right.
	Because we check if the right node is NULL in one of the 
	base cases, this only gets triggered if the right node is
	not NULL*/
		return placement(new_entry, root->right);
	}
	else if(new_entry->position < root->position)
	{
	/*Literally same thing as the previous 'else if' clause but 
	this one only triggers if the new entry has an int less than
	the current node*/
		return placement(new_entry, root->left);
	}	
	return 0;	
}

int songs::find_song(char name[])
{
	/*I change the name array into all lowercase before
	passing it into the find function*/
	change_to_lowercase(name);
	return find(root, name);
}

int songs::change_to_lowercase(char name[])
{
	/*This function solely exists to change
	some character array into its lowercase
	equivalent*/
	int length = strlen(name);
	for(int i = 0; i < length; ++i)
	{
		name[i] = tolower(name[i]);
	}
	return 1; //I dont use this value because it can't be anything else
}

int songs::find(node *&root, char name[])
{
	//If nothing exists in the root, we've either hit the end, or the tree didn't exist to begin with
	if(!root)
	{
		return 0;
	}
	else if(root->position == position(name))
	{
	/*This is the case we want, where we find the right node. Print out all fields*/
		cout << '\n' << "Song Title: " << root->title;
		cout << '\n' << "Artist: " << root->artist;
		cout << '\n' << "Album Name: " << root->album_name;
		cout << '\n' << "Length: " << root->length;
		++root->number_of_retrievals; //We're retrieving it, so increment this counter
		cout << '\n' << "Retrieved: " << root->number_of_retrievals << " times\n";
		return 1;
	}
	/*This is the conditional recursive call, if the position of the current is less than the position of the name*/
	else if(root->position < position(name))
	{
		return find(root->right, name);
	}
	else if(root->position > position(name))
	{
	/*If the position of the current is greater than the position of the name*/
		return find(root->left, name);
	}
	return 0;
}

int songs::display(void)
{
	return display(root);
}

int songs::display(node *&root)
{
	if(!root)
	{
		//If no tree, return 0
		return 0;
	}
	else
	{
		display(root->left);
		if(root != NULL)
		{
			cout << '\n' << "Song Title: " << root->title;
			cout << '\n' << "Artist: " << root->artist;
			cout << '\n' << "Album Name: " << root->album_name;
			cout << '\n' << "Length: " << root->length;
			cout << '\n' << "Retrieved: " << root->number_of_retrievals << " times\n";
		}
			display(root->right);
		return 1; //1, it worked
	}
	return 0;
}

int songs::remove_all(void)
{
	return remove(root);
}

int songs::remove(node *&root)
{
	if(!root)
	{
		return 0;
	}
	else
	{
		node *right = root->right;
		remove(root->left);
		delete []root->title;
		delete []root->lower_title;
		delete []root->artist;
		delete []root->album_name;
		delete []root->length;
		delete root;
		root = NULL;
		remove(right);
		return 1; //it worked
	}
}

int songs::find_and_remove(char name[])
{
	char *find = new char[strlen(name) + 1];
	change_to_lowercase(name);
	strcpy(find, name);
	return single_delete(find, root);
}

int songs::single_delete(char *name, node *& root)
{
	if(!root)
	{
		return 0;
	}
	else if(strcmp(root->lower_title, name) != 0)
	{
		//If the current song title and name are NOT a match,//
		single_delete(name, root->left);
		return single_delete(name, root->right);
	}
	else if(strcmp(root->lower_title, name) == 0)
	{
		if(number_of_children(root) == 0)
		{
			delete []root->title;
			delete []root->lower_title;
			delete []root->artist;
			delete []root->album_name;
			delete []root->length;
			delete root;
			root = NULL;
		}
		if(number_of_children(root) == 1)
		{
			//If we have one child, replace with the child that exists
			if(root->left == NULL)
			{
				//Left side is empty, so we replace with the right
				node *to_delete = root;
				root = root->right;

				delete []to_delete->title;
				delete []to_delete->lower_title;
				delete []to_delete->artist;
				delete []to_delete->album_name;
				delete []to_delete->length;
				delete to_delete;
			}
			else
			{
				//Right side is empty, so we replace with the left
				node *to_delete = root;
				root = root->left;

				delete []to_delete->title;
				delete []to_delete->lower_title;
				delete []to_delete->artist;
				delete []to_delete->album_name;
				delete []to_delete->length;
				delete to_delete;
			}
		}

		if(number_of_children(root) == 2)
		{
		/* In the case of 2 children, we delete the information inside the node to be deleted,
		then repopulate with the in-order successor, which is found by calling successor(root->right)*/
			node *replace = successor(root->right);
			delete []root->title;
			delete []root->lower_title;
			delete []root->artist;
			delete []root->album_name;
			delete []root->length;
	
			root->title = new char[strlen(replace->title) + 1];
			strcpy(root->title, replace->title);
	
			root->lower_title = new char[strlen(replace->lower_title) + 1];
			strcpy(root->lower_title, replace->lower_title);
	
			root->artist = new char[strlen(replace->artist) + 1];
			strcpy(root->artist, replace->artist);
	
			root->album_name = new char[strlen(replace->album_name) + 1];
			strcpy(root->album_name, replace->album_name);
	
			root->length = new char[strlen(replace->length) + 1];
			strcpy(root->length, replace->length);
		
			root->position = replace->position;
			root->number_of_retrievals = replace->number_of_retrievals;
		
//			delete []replace->title;
//			delete []replace->lower_title;
//			delete []replace->artist;
//			delete []replace->album_name;
//			delete []replace->length;
			replace->number_of_retrievals = 900;
			
			//replace = NULL;
			remove_in_order(root);
		}
		return 1;
	}
	single_delete(name, root->left);
	return single_delete(name, root->right);
}
	
node *songs::successor(node *& root)
{
	/*I only need this function when there are two child nodes. This means that
	I will only ever call this function if there are 2 nodes below it, so I don't
	need to have the !root if-clause. This function returns the node that is the
	in order successor by going down to the left-most node*/
	if(root->left == NULL)
	{
		return root;
	}
	else 
	{
		return successor(root->left);
	}
}

int songs::number_of_children(node * root)
{
	/*We pass in any node to this function to return the number of children it has*/
	if(root->left == NULL && root->right == NULL)
	{
		return 0;
	}
	if(root->left != NULL && root->right == NULL) //I could've written this and the next clause in one line, but this was easier to think about
	{
		return 1;
	}
	if(root->left == NULL && root->right != NULL)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int songs::remove_in_order(node *& root)
{
	if(root->left == NULL)
	{
		/*delete []root->title;
		delete []root->lower_title;
		delete []root->artist;
		delete []root->album_name;
		delete []root->length;*/
		delete root;
		root = NULL;
		return 1;
	}
	else 
	{
		return remove_in_order(root->left);
	}
}

