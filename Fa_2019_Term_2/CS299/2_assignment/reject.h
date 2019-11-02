/*Header file for the reject pile.
Written for CS299 assignment 2 by Austen Hsiao
Implemented as a linear linked list of arrays
*/

const int ARRAY_MAX = 5;

struct reject_node
{
	char **store_names;
	reject_node *next;
};

class reject
{
	public:
		reject(void);
		~reject(void);
		int push(char store_name[]);
		int pop(void);
		int peek(void);
		int display(void);
	private:
		reject_node *head;
		int add_index; //This is a counter that tells us the lowest index that's open	
};
