struct node
{
	char *hint;
	int likes;
	node *next;
};

class college_life
{
	public: 
		college_life();
		~college_life();
		void add_hint(char category[], char hint[]);
		int like(char category[], int hint_index);
		int display(char category[]);
	private:
		node *head_registering;
		node *head_materials;
		node *head_homework;
};

int menu_option(void);
void display_menu(void);
