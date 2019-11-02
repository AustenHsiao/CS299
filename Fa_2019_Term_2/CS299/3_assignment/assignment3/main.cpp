#include "songs.h"
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

using namespace std;

/*Function prototypes*************************************************************************************/

	int int_value(char name[]);
	int change_to_lowercase(char name[]);
	int populate_song(song &new_song, char title[], char artist[], char album_name[], char length[]);
	int load_file(char name[]);
/*********************************************************************************************************/

const int SIZE = 500;

int main(void)
{
	song_list playlist;
	song buffer_song;
	char title[SIZE];
        char artist[SIZE];
        char album_name[SIZE];
        char length[SIZE];
	char throwaway[SIZE];
	int menu = 58008;

/*________________________________________________________________________________________*/
	//This bar separates functional code from variable declarations
/*________________________________________________________________________________________*/

	while(menu != 7)
	{
		cout << "\t________MENU________\n\t1. Load from file\n\t2. Insert song\n\t3. Find song\n\t4. Display all songs\n\t5. Remove all songs\n\t6. Remove single song\n\t7. Exit";
		cout << "\n\t\tEnter menu option: ";
		cin >> menu;
		while(cin.fail() || menu < 1 || menu > 7)	
		{
			cin.clear();
			cin.ignore(SIZE, '\n');
			cout << "\t\tInvalid input. Enter menu option: ";
			cin >> menu;
		}
		cin.ignore(SIZE, '\n');

		switch(menu)
		{
			case 1 :
			{	//LOAD FROM FILE
				cout << "Enter text file name (include filetype): ";
				cin.get(title, SIZE, '\n');

				ifstream file;
				file.open(title);

				if(!file)
				{
					cout << "\nFile not found\n";
				}
				else
				{
					while(!file.eof())
					{
						/*This loop continues until we get to the end of the file.
						This implementation is entirely reliant on the way the .txt
						file is structured.. there's definitely room for improvement*/

						file.getline(title, SIZE);
						file.getline(artist, SIZE);
						file.getline(album_name, SIZE);
						file.getline(length, SIZE);
						file.getline(throwaway, SIZE);
		
						populate_song(buffer_song, title, artist, album_name, length);
						playlist.insert(buffer_song);
						
					}
					cout << "\nFile loaded successfully\n\n";
					
				}
				file.close();
				break;
			}
			case 2 :
			{	//INSERT FUNCTION
				cout << "Enter song title: ";
				cin.get(title, SIZE, '\n');
				cin.ignore(SIZE, '\n');
			
				cout << "Enter song artist: ";
				cin.get(artist, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				
				cout << "Enter album name: ";
				cin.get(album_name, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				
				cout << "Enter song duration: ";
				cin.get(length, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				
				populate_song(buffer_song, title, artist, album_name, length);
				playlist.insert(buffer_song);
				cout << "\nSong added successfully\n\n";
				break;
			}
			case 3 :
			{	//RETRIEVE FUNCTION
				cout << "Search by song title: ";
				cin.get(title, SIZE, '\n');
				cin.ignore(SIZE, '\n');
			
				if(playlist.search(title) == 0)
				{
					cout << "Song not found\n\n";
				}
				break;
			}
			case 4 :
			{	//DISPLAY ALL FUNCTION
				cout << '\n';
				if(playlist.display_all() == 0)
				{
					cout << "No songs to display\n\n";
				}
				break;	
			}
			case 5 :
			{	//REMOVE ALL FUNCTION
				if(playlist.remove_all() == 0)
				{
					cout << "\nNo songs to remove\n\n";
				}
				else
				{
					cout << "\nRemoved all songs\n\n";
				}
				break;
			}
			case 6 :
			{	//REMOVE MATCH	
				if(playlist.display_all() == 0)
				{
					cout << "Playlist is empty, there's nothing to remove\n\n";
				} 
				else
				{
					cout << "\nRemove song by title: ";
					cin.get(title, SIZE, '\n');
					cin.ignore(SIZE, '\n');

					if(playlist.single_remove(title) == 0)
					{
						cout << "Song not found. No song removed\n\n";
					}
					else{cout << "\nRemoving song...\n\n";}
				}
				break;	
			}
		}
	}
	return 0;
}

/*Function definitions************************************************************************************/

int int_value(char name[])
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
        delete []lower_name;
        return position;
}

int change_to_lowercase(char name[])
{
        /*This function solely exists to change
        some character array into its lowercase
        equivalent, required for case insensitivity*/
        int length = strlen(name);
        for(int i = 0; i < length; ++i)
        {
                name[i] = tolower(name[i]);
        }
        return 1;
}

int populate_song(song &new_song, char title[], char artist[], char album_name[], char length[])
{
        int size_of_title = strlen(title);
        
	//Value is the integer used for the BST
        new_song.value = int_value(title);
        
        new_song.title = new char[strlen(title) + 1];
        strcpy(new_song.title, title);
        new_song.lower_title = new char[strlen(title) + 1];
        for(int i = 0; i < size_of_title; ++i)
        {
                new_song.lower_title[i] = tolower(title[i]);
        }

        //Enter song artist
        new_song.artist = new char[strlen(artist) + 1];
        strcpy(new_song.artist, artist);

        //Enter album name
        new_song.album_name = new char[strlen(album_name) + 1];
        strcpy(new_song.album_name, album_name);

        //Enter song length
        new_song.length = new char[strlen(length) + 1];
        strcpy(new_song.length, length);

        //Initialize the number of retrievals
        new_song.number_of_retrievals = 0;

        return new_song.value;
}

/******************************************************************************************************/






