/*This is the header file for assignment 3 written by Austen Hsiao for CS299.
Songs are contained by the song struct, nodes within the BST are contained as 
tree_node, and the overarching functions governing the tree are in the class, 
'song_list'*/

struct song
{
	int value;
	char *title;
	char *lower_title;	
	char *artist;
	char *album_name;
	char *length; 
	int number_of_retrievals;	
};

struct tree_node 
{
	song data;
	tree_node * left;
	tree_node * right; 
};

class song_list
{
	public:
		song_list(void);
		~song_list(void);
		int insert(song &to_insert); 
		int search(char name[]);
		int display_all(void);
		int remove_all(void);
		int single_remove(char name[]);		
	private:
		tree_node *root;
		int insert_private(song &to_insert, tree_node *& root); 
		int search_private(int key, tree_node *& root);
		int print_info(tree_node * root);
		int int_value(char name[]);
		int display_all_private(tree_node *& root);
		int remove_all_private(tree_node *& root);
		int remove_node(tree_node *&root);
		int number_of_children(tree_node * root);
		int single_remove_private(int key, tree_node *& root);
		tree_node *successor_info(tree_node *& root);
		tree_node *successor_r(tree_node *& root);
		int copy_song(song &from, song &destination);
};
