/*	This is the header file for availabile items.
	Available items are stored in a circular linked list 
	queue. 
	
	Written for CS299 assignment 2 by Austen Hsiao
*/

struct item_node
{
	char *name;
	char *attribute1;
	char *attribute2;
	char *attribute3;
	item_node *next;
};

class available
{
	public:
		available();
		~available();
		int enqueue(char name[], char a1[], char a2[], char a3[]);
		int dequeue(void);
		int peek(void);
		int display(void);

	private:
		item_node *head;
};
