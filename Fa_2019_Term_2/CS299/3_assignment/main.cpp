#include <iostream>
#include <cctype>
#include <cstring>
#include "songs.h"

using namespace std;
const int SIZE = 500;

int main(void)
{
	char name[SIZE];
	char artist[SIZE];
	char album_name[SIZE];
	char length[SIZE];
	char find[SIZE];
	songs test;
	
	int i = 0;
	while(i<4)
	{
	cout << "\nEnter song name: ";
	cin.get(name, SIZE, '\n');
	cin.ignore(SIZE, '\n');

	cout << "Enter artist name: ";
	cin.get(artist, SIZE, '\n');
	cin.ignore(SIZE, '\n');
	
	cout << "Enter album name: ";
	cin.get(album_name, SIZE, '\n');
	cin.ignore(SIZE, '\n');
	
	cout << "Enter song length: ";
	cin.get(length, SIZE, '\n');
	cin.ignore(SIZE, '\n');

	test.insert(name, artist, album_name, length);
	++i;
	}

	cout << "\nEnter song name to search for: ";
	cin.get(find, SIZE, '\n');
	cin.ignore(SIZE, '\n');	

	if(test.find_song(find) == 0)
	{
		cout << "\nSong not found";
	}

	cout << "\nEnter song name to search for: ";
	cin.get(find, SIZE, '\n');
	cin.ignore(SIZE, '\n');	

	if(test.find_song(find) == 0)
	{
		cout << "\nSong not found";
	}

	test.display();	
	cout << "\nEnter song name to delete: ";
	cin.get(find, SIZE, '\n');
	cin.ignore(SIZE, '\n');	

	test.find_and_remove(find);
	test.display();	
	return 0;
}
