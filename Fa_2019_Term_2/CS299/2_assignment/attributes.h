/* 	This is the header file for the attributes list (with priorities).
	The priority list is structured as a linked list in which each node 
	includes an integer (priority) and a string (the favorable attribute)

	Written by Austen Hsiao for CS299 assignment2
*/

struct node
{
	int priority;
	char *message;
	node *next;
};

class attributes
{
	public:
		attributes(void);
		~attributes(void);
		int insert(int priority, char message[]);
		int remove(int priority);
		int display(void);
 
	private:
		node *head;
		//available queue;
};
