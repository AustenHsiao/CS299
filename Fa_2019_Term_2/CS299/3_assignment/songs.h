/*This is the header file for assignment 3 
 written by Austen Hsiao for CS299*/

struct node
{
	int position;
	char *title;
	char *lower_title;	
	char *artist;
	char *album_name;
	char *length; 
	int number_of_retrievals;
	node *left;
	node *right;
	~node {
	
}	
};
/*
struct tree_node 
{
	song data;
	tree_node * left;
	tree_node * right; 
};

tree_node * root;

copy_song(
int copy_song(song & copy_from, song & copy_to);
  */

class songs
{
	public:
		songs(void);
		int insert(char title[], char artist[], char album_name[], char length[]);
		int find_song(char title[]);	
		int display(void);
		int remove_all(void);
		int find_and_remove(char name[]);
	private:
		node *root;
		int position(char name[]);
		int placement(node *new_entry, node *&root);
		int find(node *&root, char name[]);
		int change_to_lowercase(char name[]);
		int display(node *&root);
		int remove(node *&root);
		int number_of_children(node *root);
		node *successor(node *& root); 
		int single_delete(char *name, node *& root);
		int remove_in_order(node *& root);
};
