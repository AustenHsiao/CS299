/*This file describes all functions depicted in songs.h. Written by Austen Hsiao for CS299 assignment3
The public functions include: adding a song, total deletion, single deletion, and retrieval.*/

#include "songs.h"
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

song_list::song_list(void)
{
	/*Any new tree will be NULL*/
	root = NULL;
}

song_list::~song_list(void)
{
	/*As part of this assignment, we had to make a delete_all function, so I call it here instead of rewriting it*/
	remove_all();	
}

int song_list::insert(song &to_insert)
{
	/*This is just a wrapper so the user does not directly interact with the tree*/
	return insert_private(to_insert, root);
}

int song_list::insert_private(song &to_insert, tree_node *& root)
{
	/*Insert function, if the root is NULL, this means we have a place to put stuff.
	otherwise we move either left or right depending on the value, which is stored inside the song*/
	if(!root)
	{
		root = new tree_node;
		root->data = to_insert;
		root->left = NULL;
		root->right = NULL;
		return 0;
	}
	else if(to_insert.value > root->data.value)
	{
		return insert_private(to_insert, root->right);
	}
	return insert_private(to_insert, root->left);
}

int song_list::search(char name[])
{
	/*Wrapper for search function*/
	return search_private(int_value(name), root);
}

int song_list::search_private(int key, tree_node *& root)
{
	/*Searches the BST for a given value (calculated from the name inputted into the search function)*/
	if(!root)
	{
		return 0;
	}
	else if(root->data.value == key)
	{	/*This is the case in which we found the right node, we increment the number of retreivals, then print the info*/
		++root->data.number_of_retrievals;
		return print_info(root);
	}
	else if(key > root->data.value)
	{
		return search_private(key, root->right);
	}
	return search_private(key, root->left);
}

int song_list::print_info(tree_node *root)
{
	/*Prints song info from a given tree node*/
	if(root != NULL)
	{
		cout << "\nSong name: " << root->data.title;
		cout << "\nSong artist: " << root->data.artist;
		cout << "\nAlbum name: " << root->data.album_name;
		cout << "\nDuration: " << root->data.length;
		cout << "\nRetrieved: " << root->data.number_of_retrievals << '\n';
		return 1;
	}
	return 0;
}

int song_list::int_value(char name[])
{
	/*This is copy and pasted from main, 
	but I wanted this here as well so we 
	can search within the BST*/

        int length = strlen(name);
        int position = 0;
        char *lower_name = new char[strlen(name) + 1];
        strcpy(lower_name, name);

        for(int i = 0; i < length; ++i)
        {
                lower_name[i] = tolower(name[i]);
                position += int( int(lower_name[i]) / (i+1) );
        }
        delete []lower_name;
        return position;
}

int song_list::display_all(void)
{	
	return display_all_private(root);
}

int song_list::display_all_private(tree_node *& root)
{
	if(!root)
	{
		return 0;
	}
	else
	{	/*The return 1 + func() is there so we return a non 0 
		value if there are nodes*/
		display_all_private(root->left);
		if(root)
		{
			print_info(root);
		}
		return 1 + display_all_private(root->right);
	}
}

int song_list::remove_all(void)
{
	return remove_all_private(root);
}

int song_list::remove_node(tree_node *&root)
{	/*Single deletion of whatever node we pass into this*/
	if(!root)
	{
		return 0;
	}
	else
	{
		delete []root->data.title;
		delete []root->data.lower_title;
		delete []root->data.artist;
		delete []root->data.album_name;
		delete []root->data.length;
		delete root;
		root = NULL;
		return 1;
	}
}

int song_list::remove_all_private(tree_node *& root)
{
	/*This remove_all function uses post_order traversal
	so that we delete the leaf nodes prior to anything else.
	Using pre- or in-order traversal will likely nullify a node
	with children, so that it will become impossible to access
	the child node(s), causing memory leaks*/
	if(!root)
	{
		return 0;
	}
	else
	{
		remove_all_private(root->left);
		remove_all_private(root->right);		
		return 1 + remove_node(root);
	}
}		

int song_list::single_remove(char name[])
{
	/*This is the wrapper function for a single deletion,
	the user passes in a string, then the value is returned 
	from int_value. This value is then passed into the 
	single remove function*/
	int key = int_value(name);
	if(!root)
	{
		return 0;
	}
	return single_remove_private(key, root);
}


int song_list::single_remove_private(int key, tree_node *& root)
{
	if(!root)
	{
		return 0;
	}
	else if(key > root->data.value)
	{
		return single_remove_private(key, root->right);
	}
	else if(key < root->data.value)
	{
		return single_remove_private(key, root->left);
	}
	/*Above is for traversal*/
	else if(key == root->data.value)
	{
		int children = number_of_children(root);
		/*If the key is equal to the node we're on, we need to delete it. Either it has 1, 2 or 3 children*/
		if(children == 0)
		{
			//Delete the node, no changes afterward
			return remove_node(root);
		}
		else if(children == 1)
		{
			//Replace current node with the only child
			tree_node *to_delete = root; //Hold onto root (we want to delete this)
			if(root->left == NULL)
			{
				//This means that the right has a node
				root = root->right; //Replace root
			}
			else
			{
				//This means that the left has a node
				root = root->left; //Replace root
			}
			return remove_node(to_delete); //Delete the original root
		}
		else if(children == 2)
		{
			//If 2 children, replace the current node with the in-order successor,
			tree_node *hold = successor_info(root); 
			copy_song(hold->data, root->data); 
			return single_remove_private(hold->data.value, root->right); //Then we want to delete the in-order successor	
		}
		return 5; //Return 5 because why not. All possible cases are contained above, but it helped me to reason through them to leave it as 'else if' statements
	}
	return 1; //Again, I only used else if, this is here so the compiler doesn't complain
}
		
int song_list::copy_song(song &from, song &destination)
{
	//This copies data from one song to another, overwriting what was in the destination to begin with*/
	delete []destination.title;
	delete []destination.lower_title;
	delete []destination.artist;
	delete []destination.album_name;
	delete []destination.length;

	destination.value = from.value;
	destination.number_of_retrievals = from.number_of_retrievals;

	destination.title = new char[strlen(from.title) + 1];
	strcpy(destination.title, from.title);
	
	destination.lower_title = new char[strlen(from.title) + 1];
	strcpy(destination.title, from.title);
	
	destination.artist = new char[strlen(from.artist) + 1];
	strcpy(destination.artist, from.artist);

	destination.album_name = new char[strlen(from.album_name) + 1];
	strcpy(destination.album_name, from.album_name);

	destination.length = new char[strlen(from.length) + 1];
	strcpy(destination.length, from.length);

	return 1;
}

int song_list::number_of_children(tree_node *root)
{
	//Returns the number of children for any given tree_node
	if(root->right == NULL && root->left == NULL)
	{
		return 0;
	}
	else if((root->right != NULL && root->left == NULL) || (root->right == NULL && root->left != NULL) )
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

tree_node* song_list::successor_info(tree_node *& root)
{
	/*Returns the tree node of the in order successor. This is a
	wrapper function because we need to go right once, then as far
	left as possible*/
	return successor_r(root->right);
}

tree_node* song_list::successor_r(tree_node *& root)
{
	/*Here is where we go as far left as possible*/
	if(root->left == NULL)
	{
		return root;
	}	
	return successor_r(root->left);
}
