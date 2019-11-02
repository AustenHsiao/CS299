char preferred_attribute(void);

class features
{
	public:
		features(void);
		~features(void);
		void insert(int priority, char *attribute);
		void display(void);
	private:
		char **preferred;	
		int length;
};
