#ifndef LIST_H

#define LIST_H

//const int max_chars = 100;
const int limit = 10;

class List{
	
	//data members:
	private:
		
		enum{max_chars = 100};
		
		//NOTE: this struct type is nested within the class itself:
		typedef struct node{
			
			char brand[max_chars];
			double price;
			node* next;
			
		}*nodePtr;
		
		nodePtr _head; //---> this is exactly the same as writing: node* head, except that we have replaced NODE* with NODEPTR	
		nodePtr _current;	
		nodePtr _previous;
		nodePtr _new_First;
		nodePtr _other;
		nodePtr _prior;
		nodePtr _post;
		nodePtr _middle;
		nodePtr _replaced;
		nodePtr _actual;
		nodePtr _nextOne;
		nodePtr _back;
		
		static int _total;
		

		
	//for functions:	
	public:
		
		//default constructor, which sets all three pointers above to NULL:
		List();
		
		~List();
		
		int getTotal();
		
		//copy constructor:
		List(List&);
		
		void AddNode(char*, double);
		//this method will delete the node whose value corresponds to the value we wish to delete (from the client server):
		void DeleteNode(int);	
		void PrintList();
		void insert_node(char*, double, int);
		void repositioning_ptrs(); //--> this function is used in order to have CURRENT and PREVIOUS pointers point to the last object of the list
		void repositioning_ptrs(List&);
		void swapNodes(int, int);
		void swapFirst();
		void swapLast(int);		
		//********************************* all functions below for REARRANGE() function only *****************************************************		
		void rearrangeNodes(int, int); //---> most complex of all functions!
		//if user has chosen first node to shift:	 
		void placeAtEnd();
		void firstAnywhere(int);
		//if user has chosen last node to shift:	
		void placeAtBeginning(int);
		void lastAnywhere(int);
		//if user has chosen any other node to shift:
		void moveToBeginning(int, int);
		void moveToEnd(int, int);
		void swapBefore(int, int);
		void swapAfter(int, int);
		void moveAnywhere(int, int);
		//*****************************************************************************************************************************************
		void display_head_node();		
		void number_nodes();		
		void error_message();
		void queue_mode(char*, double);
		void sortAlphabetic();
		void sortNumeric(int);
		
};

#endif
