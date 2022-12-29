#include <cstdlib>
#include <iostream>
#include <cstring>
#include "List.h"

//initializing our STATIC class member:
int List::_total = 0;

const int max_chars = 100;
extern const int limit;

List::List(){
	
	_head = _current = _previous = _new_First = _other = _prior = _post = _middle = _replaced = _actual = _nextOne = _back = NULL;
}

List::~List(){

	//IMPORTANT: this takes us back to the very beginning of the list:
	_current = _head;
		
	while(_total > 0){
		
		_previous = _current;
		
		_current = _current->next;
			
		if(_total > 1)
			std::cout << "\nCurrently " << _total << " nodes in the list.\n";
		else
			std::cout << "\nCurrently " << _total << " single node in the list.\n";
		
		_previous->next = NULL;	
		
		delete _previous;
			
		//current = current->next;
			
		_total -= 1;
			
		if(_total > 1)
			std::cout << "AFTER DELETION: " << _total << " nodes left.\n\n";
		else
			std::cout << "AFTER DELETION: " << _total << " single node left.\n\n";				
	}				
		
	std::cout << "\nEnd of destructor.\n";	

}




//copy constructor:
List::List(List& obj){
	
	int temp_total=0;
	
	obj._current = obj._previous = obj._head;
	
	while(temp_total < _total){
		
		_current = new node;
		
		_current = obj._current;
		
		_previous->next = _current;
		obj._previous->next = obj._current;
			
		strcpy(_current->brand, obj._current->brand);
		_current->price = obj._current->price;
		_current->next = NULL;
			
		_previous = _current;
		obj._previous = obj._current;
		
		temp_total += 1;
			
	}
	
	 repositioning_ptrs(obj);		
}
		
void List::AddNode(char* name, double p){

	_current = new node;
	
	if(_head == NULL)
		_head = _current;
			
	else
		_previous->next = _current;
		
	strcpy(_current->brand, name);
	_current->price = p;
	_current->next = NULL;
		
	_previous = _current;
	
	_total += 1;		
	
	return;
}
		
void List::DeleteNode(int choice){
	
	if(_total == 0)
		std::cout << "\nSorry: it is currently impossible to remove nodes, since there are none in the list.\n\n";
		
	else{
	
		int index = 1;
		int sub = choice - 1;
		
		if(choice > _total || choice == 0){
			
			std::cout << "Sorry, this is an invalid number. Total number of nodes is: " << _total << "\n\n";
		}
	
		else{
			
/************************************************************************************************************************************************
*																																			    *
*																																			    *		
*					OPTION 1: if user chooses node no.1 from the list (ie: the node pointed to by HEAD pointer):								    *
*																																			    *
*																																			    *
************************************************************************************************************************************************/
			
			if(choice == 1){
					
				//this takes us back to the very beginning of the list (NOTE: both HEAD and CURRENT now point to the first object of the list):
				_current = _head;
					
				//accessing following node via address contained in object's NEXT member + making this object HEAD/FIRST object of the list:
				_head = _head->next;
					
				//deleting the chosen object (which used to be FIRST, but is now left aside, being only pointed to by TEMP pointer):
				_current->next = NULL;		
				delete _current;
					
				_total -= 1;
					
				std::cout << "\nNode no." << choice << " (HEAD node) now deleted and replaced with second (now FIRST/HEAD) object.\n";
					
				repositioning_ptrs();
			}
					
/************************************************************************************************************************************************
*																																			    *
*																																			    *		
*												OPTION 2: if user chooses the LAST node (pointed to by CURRENT pointer:				    		*
*																																			    *
*																																			    *
************************************************************************************************************************************************/

			/*
				REMEMBER: at this stage, the user would most likely have added a new node to the list.
				
				Therefore: both CURRENT ***and*** PREVIOUS pointers points to the LAST object created.
											|
											---> this cannot be undone or changed, since making both pointers point to the same last object is
													part of the object-adding function.
													
												It is why we must therefore go back again to the very beginning of the list, in order to assign
												the address of the PENULTIMATE object to PREVIOUS pointer!
			*/
			
			else if(choice == _total){
				
				int index = 1;
				int sub = choice-1;
					
				//IMPORTANT: this takes us back to the very beginning of the list:
				_current = _head;
					
				while(index < choice){
						
					if(index == sub)
						_previous = _current;
						
					_current = _current->next;
											
					index += 1;
				}
				
				//now: CURRENT points to the LAST object and PREVIOUS points to the PENULTIMATE object.
				//ALSO: remember that NEXT member of the last object of the list, pointed to by CURRENT, has already been set to NULL.
				
				delete _current;
				_previous->next = NULL;
				
				_total -= 1;
				
				std::cout << "\nNode no." << choice << " (LAST node) now deleted and replaced with second-from-last object.\n";
					
				repositioning_ptrs();				
				
			}
			
/************************************************************************************************************************************************
*																																			    *
*																																			    *		
*					OPTION 3: if user chooses node that is NOT the first node of the list nor the LAST (pointed to by HEAD):				    *
*																																			    *
*																																			    *
************************************************************************************************************************************************/
				
			else{
					
/************************************************************************************************************************************************
	STEPS 1 + 2: FINDING OBJECT + ASSIGN ITS ADDRESS TO 'temp' POINTER + FINDING PREVIOUS OBJECT & ASSIGN ITS ADDRESS TO 'previous' POINTER
************************************************************************************************************************************************/

				int index = 1;
				int sub = choice-1;
					
				//IMPORTANT: this takes us back to the very beginning of the list:
				_current = _head;
					
				while(index < choice){
						
					if(index == sub)
						_previous = _current;
						
					_current = _current->next;
											
					index += 1;
				}
							
/************************************************************************************************************************************************ 
	STEP 3: ASSIGNING ADDRESS OF OBJECT THAT FOLLOWS SOON-TO-BE-DELETED OBJECT TO 'next' MEMBER OF 'previous' POINTER 			
************************************************************************************************************************************************/
					
				/*
				now: using CURRENT pointer (remember: this points to the current object searched for by the user) to assign the address of its
				NEXT member to address of NEXT member of previous object pointed to by PREVIOUS:			
				*/
				_previous->next = _current->next;
					
				//deleting the object which is pointed by CURRENT:
				_current->next = NULL;		
				delete _current; 
					
				_total -= 1;
					
				std::cout << "\nNode no." << choice << " now deleted and replaced by node no." << choice+1 << ".\n";
				std::cout << "(which means that node no." << choice+1 << " effectively becomes node no." << choice << ")\n\n";
					
				//re-establishing what is now the current object at position CHOICE:
				_current = _previous->next;
					
/************************************************************************************************************************************************ 
	STEP 4: ENSURING THAT BOTH 'current' AND 'previous' POINTERS POINT TO THE SAME OBJECT: THE LAST OBJECT OF THE LIST:
			(this is to make sure the pointers are up to date in order to enable the user to add more nodes to the list)		
************************************************************************************************************************************************/
		
				repositioning_ptrs();
		
			}
		}			
	}
	
	return;
}


int List::getTotal(){
	
	return _total;
}


void List::insert_node(char* n, double p, int position){
	
	if(_total < 2){
		
		std::cout << "\nThere must be a minimum of 2 nodes in the linked list to insert a new node.\nChoose OPTION 1 to add more nodes.\n";
		return;
	}	
		
	else{
		
		if(position == 1){
			
			//starting from the beginning:
			_current = _head;
			
			//*************************** STEP 1: CREATING DYNAMIC OBJECT + ASSIGNING ITS ADDRES TO 'current' POINTER *******************************
			
			_current = new node;
			
			
			//*************************** STEP 2: ASSIGNING DATA TO MEMBERS OF OBJECT VIA 'current' POINTER **************************************
				
			strcpy(_current->brand, n);	
			_current->price = p;
			

			//*************************** STEP 4: ASSIGNING ADDRESSES TO 'next' MEMBER IN 'current'  *********************************************
			
			_current->next = _head;
			
			_head = _current;
			
			_total += 1;
			
			//*************************** STEP 5: ENSURING 'previous' POINTER POINTS TO CURRENT OBJECT ********************************************			
			
			repositioning_ptrs();
					
		}

		else{
			
			//*************************** STEP 1: FINDING POSITION FOR 'current' AND 'previous' POINTERS *****************************************
			
			//starting from the beginning:
			_current = _head;
					
			int index = 1;
			int sub = position-1;
			
			while(index < position){
				
				if(index == sub)
					_previous = _current;
						
				_current = _current->next;
				index += 1;
			}
			
			//*************************** STEP 2: CREATING DYNAMIC OBJECT + ASSIGNING ITS ADDRES TO 'current' POINTER ****************************
			
			_current = new node;
			
			
			//*************************** STEP 3: ASSIGNING DATA TO MEMBERS OF OBJECT VIA 'current' POINTER ***************************************
				
			strcpy(_current->brand, n);	
			_current->price = p;
			
			//*************************** STEP 4: ASSIGNING ADDRESSES TO 'next' MEMBERS IN 'current' + 'previous' POINTERS ************************
			
			_current->next = _previous->next;
			
			_previous->next = _current;
			
			_total += 1;
			
			//*************************** STEP 5: ENSURING 'previous' POINTER POINTS TO CURRENT OBJECT *******************************************			
			
			repositioning_ptrs();	
						
		}	
	}
		
	return;
}

	
	
//**********************************************************************************************************************************************
/*

void List::DeleteNode(int delData){
	
	nodePtr delPtr = NULL;
	
	//resetting all our NODE-type pointers to NULL, effectively taking us back to the beginning of the list:
	_previous = _current = _head;
	
	
	//traversing the list, while BOTH conditions remain true:
	while(_current != NULL && _current->data != delData){
			
		_previous = _current;
		
		_current = _current->next;
	}
	
	// if we reach this stage, it means that (a) we have effectively reached the very end of the list (_CURRENT=NULL), or (b) that the value 
	// searched for has been found: 
	
	if(_current == NULL){
		
		std::cout << "\nSorry: " << delData << " is not in the list.\n\n";
		delete delPtr;
	}
	
	else{ //if _CURRENT->DATA == DELDATA:
		
		delPtr = _current;
		_current = _current->next;
		_previous->next = _current;
		
		if(delPtr == _head){
			
			_head = _head->next;
			_previous = NULL;
		}
		
		delete delPtr;
		
		std::cout << "\nThe value: " << delData << " has been found and deleted.\n\n";
	}
	
	_total -= 1;
	

	
	return;
}
*/


void List::repositioning_ptrs(List& obj){
	
/************************************************************************************************************************************************ 
	THIS IS TO ENSURE THAT BOTH 'current' AND 'previous' POINTERS POINT TO THE SAME OBJECT: THE LAST OBJECT OF THE LIST:
	(and subsequently to make sure the pointers are up to date in order to enable the user to add more nodes to the list)		
************************************************************************************************************************************************/
	
	//starting from the beginning:
	obj._current = obj._head;
	
	while(obj._current->next != NULL)			
		obj._current = obj._current->next;
			
	obj._previous = obj._current;
	
	obj._new_First = obj._other = obj._head;
		
}


void List::repositioning_ptrs(){
	
/************************************************************************************************************************************************ 
	THIS IS TO ENSURE THAT BOTH 'current' AND 'previous' POINTERS POINT TO THE SAME OBJECT: THE LAST OBJECT OF THE LIST:
	(and subsequently to make sure the pointers are up to date in order to enable the user to add more nodes to the list)		
************************************************************************************************************************************************/
	
	//starting from the beginning:
	_current = _head;
	
	while(_current->next != NULL)			
		_current = _current->next;
			
	_previous = _current;
	
	_new_First = _other = _head;
		
}

void List::rearrangeNodes(int numNode, int newPosition){ //---> most complex of all functions!

		
	if(numNode > _total || numNode == 0){
		
		std::cout << "Sorry: invalid value.\n";
		return;
	}
				
	else if(newPosition > _total || newPosition == 0){
			
		std::cout << "Sorry: invalid value.\n";
		return;						
	}
		
/***********************************************************************************************************************************************
*																																			   *
*											(1) if user wants to replace ***first*** object in the list:									   *
*																																			   *
***********************************************************************************************************************************************/
		
		else if(numNode == 1){
			
			/*
			NOTE HERE: there 3 cases for when NUMNODE is == 1:
			
					(1) when the chosen position to place node 1 is 2 (all we need is a swap between node 1 and node 2)					
					(2) when the chosen position to place node 1 is at the very end of the list (this node 1 needs to have its NEXT == NULL)					
					(3) when the chosen position to place node 1 is anywhere else in the list
			*/
			
			//case (1):	
			if(newPosition == 2)
				swapFirst(); //---> good
			
			//case (2):					
			else if(newPosition == _total)
				placeAtEnd(); //---> good
			
			//case (3):	
			else
				firstAnywhere(newPosition);	//---> good				
		}
		
/***********************************************************************************************************************************************
*																																			   *
*											(2) if user wants to replace ***last*** object in the list:										   *
*																																			   *
***********************************************************************************************************************************************/	
		
		else if(numNode == _total){
			
			/*
			NOTE HERE: as in above, there 3 cases for when NUMNODE is == total:
			
					(1) when the chosen position to place last node is PENULTIMATE is 2 (all we need is a swap between last and second-to-last nodes)					
					(2) when the chosen position to place last node is at very start of the list				
					(3) when the chosen position to place last node is anywhere else in the list
			*/
			
			//case (1):
			
			if(newPosition == _total-1)
				swapLast(newPosition); //---> good
			
			//case (2):					
			else if(newPosition == 1)
				 placeAtBeginning(newPosition); //---> good
			
			//case (3):	
			else
				lastAnywhere(newPosition);				
			
		}
			
						
			
		
/***********************************************************************************************************************************************
*																																			   *
*											(3) if user has chosen any other object in the list:										       *
*																																			   *
***********************************************************************************************************************************************/
		
		else{

			if(newPosition == 1) 
				moveToBeginning(numNode, newPosition);
				
			else if(newPosition == _total)	
				moveToEnd(numNode, newPosition);
					
			else if(newPosition == numNode-1)
				swapBefore(numNode, newPosition);
				
			else if(newPosition == numNode+1)
				swapAfter(numNode, newPosition);

			else
				moveAnywhere(numNode, newPosition);
		}
		
	repositioning_ptrs();

	return;
}


void List::placeAtEnd(){
	
	_current = new node;
	
	_previous->next = _current;
	
	strcpy(_current->brand, _head->brand);
	_current->price = _head->price;
	_current->next = NULL;
	
	nodePtr temp = new node;
	
	strcpy(temp->brand, _head->brand);
	temp->price = _head->price;
	temp->next = _head->next;
	
	_head = _head->next;
	
	temp->next = NULL;
	delete temp;
	
	repositioning_ptrs();	
	
	return;	
}


void List::firstAnywhere(int newPosition){ //---> this is for REARRANGE() function only (for CASE 2)

	//starting from top of list:
	_current = _head;

	//we make another pointer that points to first node in list and which is pointed to by HEAD:
	nodePtr badHead = _head;
	
	//next step: locating node positions (CURRENT + PREVIOUS):					
	int index = 1;
	int post_Pos = newPosition+1; 
	/*
	---> NOTE: the reason why we add 1 is because we must already foresee the new order of objects:
	
				obj1	obj2 	obj3	obj4	obj5
				
				we want obj1 to be third in the list? --> therefore: 
				
						obj2	obj3	obj1	obj4	obj5
										|
										---> 3rd in the list, as requested!
						
				...which subsequently becomes:
				
						obj1	obj2	obj3	obj4	obj5
						
				...and so: if we type in '3' for the new place of the node, the system must understand this as '3 + 1' !
	*/
				
	while(index < post_Pos){
		
		if(index == newPosition)
			_previous = _current;
			
		_current = _current->next;
		index += 1;		
	}
	
	//once we have located the node to be replaced (as well as its PREVIOUS node), we make a new object, in which we copy the data from former HEAD:
	nodePtr replacementNode = new node;
							
	strcpy(replacementNode->brand, _head->brand);
	replacementNode->price = _head->price;
	replacementNode->next = _current; //---> this creates a link with the FOLLOWING node:
	
	//this creates a link with the PREVIOUS node:
	_previous->next = replacementNode;
	
	//penulitmate step: redefining the ***new*** HEAD object:
	_head = _head->next;
								
	//last step: removing/deleting the former HEAD object:
	badHead->next = NULL;
	delete badHead;
				
	//*************************** ENSURING 'previous' POINTER POINTS TO CURRENT OBJECT *******************************************			
				
	repositioning_ptrs(); 
	
	//---> NOTE: in this function, TOTAL (in the end) remains the same.		
	
	return;
}


void List::placeAtBeginning(int newPosition){ //---> this is for REARRANGE() function only

	//newPosition == 1
	
	//starting from top of list:
	_previous = _current = _head;
	
	int index = 1;
	int subPos = _total-1;
	
	//moving to last node (and defining previous(ie: FIRST) object along the way):
	while(index < _total){
		
		if(index == subPos)
			_previous = _current;
			
		_current = _current->next;
		
		index += 1;
	}
	
	//here: using pointer already available from structure declaration in H file to create new object:
	_new_First = new node;
	
	//transferring all data from last node to new_First pointer:
	strcpy(_new_First->brand, _current->brand);
	_new_First->price = _current->price;
	
	//*******************************************************************************************************
	
	_new_First->next = _head;
	
	_previous->next = NULL;
	
	_head = _new_First;
	
	//deleting the former LAST object pointed to by CURRENT:
	delete _current;
	//...with, effectively, PREVIOUS pointer now pointing to last node, and TEMP 
	
	//here: resetting positions of CURRENT and PREVIOUS pointers:
	repositioning_ptrs();

	return;
}


void List::lastAnywhere(int newPosition){ //---> this is for REARRANGE() function only

	/*
	IMPORTANT NOTE:
	
	for this function, we require TWO more pointers: one which points to the object BEFORE the new position, and another which points
	to the object that FOLLOWS the new position.
	
	We shall call these pointers: BEFORE and AFTER. 
	*/
	
	//starting from top of list (with all FIVE pointers starting from the same first object in the list):
	_previous = _current = _head;
	nodePtr before = NULL;
	nodePtr after = NULL;
	
	int index = 1;
	int subPos = _total-1;
	int prior = newPosition-1;
	
	//moving to last node (and defining previous(ie: FIRST) object along the way):
	while(index < _total){
		
		if(index == prior)
			before = _current;
			
		if(index == newPosition)
			after = _current;
		
		if(index == subPos)
			_previous = _current;
			
		_current = _current->next;
		
		index += 1;
	}
	
	//here: using pointer already available from structure declaration in H file to create new object:
	_other = new node;
	
	//transferring all data from last node to new_First pointer:
	strcpy(_other->brand, _current->brand);
	_other->price = _current->price;
	
	//*******************************************************************************************************
		
	//here: assigning NEXT member of the object PRIOR to the new position with address of newly created object pointed to by OTHER:
	before->next = _other;
	
	//here: assigning NEXT member of newly created object pointed to by OTHER with address of object that FOLLOWS this new object:
	_other->next = after;
	
	//here: setting the penultimate object as LAST object:
	_previous->next = NULL;
	
	//now: deleting what used to be LAST object, pointed to by CURRENT:
	delete _current;
	
	//here: resetting positions of CURRENT and PREVIOUS pointers:
	repositioning_ptrs();
		
	return;
}


void List::moveToBeginning(int numNode, int newPosition){
	
	_other = _current = _head;
	
	int index = 1;
	int before = numNode - 1;
	int after = numNode + 1;
	
	while(index <= _total){
		
		if(index == before)
			_prior = _current;
		
		if(index == numNode)
			_middle = _current;
			
		if(index == after)
			_post = _current;
		
		if(index < _total)
			_current = _current->next;
			
		index += 1;
	
	}
	
	_prior->next = _post;
	
	_middle->next = _head;
	
	_head = _middle;
	
	//here: resetting positions of CURRENT and PREVIOUS pointers:
	repositioning_ptrs();	
	
	return;
}


void List::moveToEnd(int numNode, int newPosition){
	
	//HERE: bear in mind: PREVIOUS and CURRENT already point to the last object of the list
	_current = new node;
	
	_current->next = NULL; //HERE: not forgetting to initialize NEXT member to NULL
	
	_total += 1;
	
	_previous->next = _current;
	
	//going back to beginning of list:
	_other = _current = _head;
	
	//here: locating BEFORE and AFTER objects (ie: before and after NUMNODE object):
	
	int index = 1;
	int before = numNode - 1;
	int after = numNode + 1;
	
	while(index < _total){
		
		if(index == before)
			_prior = _current;
		
		if(index == numNode)
			_middle = _current; //---> we are using MIDDLE as the NUMNODE object
			
		if(index == after)
			_post = _current;
			
		_current = _current->next; //---> NOTE: in last loop, CURRENT points to the last (newly created) object of the list
		
		index += 1;
	}
	
	_prior->next = _post;
	
	strcpy(_current->brand, _middle->brand);
	_current->price = _middle->price;
	_current->next = NULL;
	
	_middle->next = NULL;
	delete _middle;
	
	//_total -= 1;
	
	//here: resetting positions of CURRENT and PREVIOUS pointers:
	repositioning_ptrs();	
	
	return;
}


void List::swapBefore(int numNode, int newPosition){
	
	_previous = _current = _head;
	
	int index = 1;
	
	while(index < _total){
		
		if(index == newPosition)
			_previous = _current;
			
		if(index == numNode)
			_other = _current;
			
		_current = _current->next;
		
		index += 1;
	}
	
	nodePtr temp = new node;
	
	//swapping:
	strcpy(temp->brand, _other->brand);
	temp->price = _other->price;
	
	strcpy(_other->brand, _previous->brand);
	_other->price = _previous->price;
	
	strcpy(_previous->brand, temp->brand);
	_previous->price = temp->price;
		
	delete temp;
	
	//here: resetting positions of CURRENT and PREVIOUS pointers:
	repositioning_ptrs();
	
	return;
}


void List::swapAfter(int numNode, int newPosition){
	
	_previous = _current = _head;
	
	int index = 1;
	
	while(index < _total){
		
		if(index == numNode)
			_previous = _current;
		
		if(index == newPosition)	
			_other = _current;
			
		_current = _current->next;
		
		index += 1;
	}
	
	nodePtr temp = new node;
	
	//swapping:
	strcpy(temp->brand, _other->brand);
	temp->price = _other->price;
	
	strcpy(_other->brand, _previous->brand);
	_other->price = _previous->price;
	
	strcpy(_previous->brand, temp->brand);
	_previous->price = temp->price;
		
	delete temp;
	
	//here: resetting positions of CURRENT and PREVIOUS pointers:
	repositioning_ptrs();
		
	return;	
}



void List::moveAnywhere(int numNode, int newPosition){
	
	_prior = _actual = _post = _replaced = _nextOne = _previous = _current = _head;
	
	if(numNode < newPosition){
		
		//example: numNode == 2, newPosition == 4
		int index = 1;
		int before = numNode-1; // == 1
		int after = numNode+1; // == 3
		int following = newPosition+1; // == 5
		
		while(index <= _total){
			
			if(index == before) //if (index == 1) == before (before == numNode - 1 == 2 - 1 == 1)
				_prior = _current;
				
			if(index == numNode) //if (index == 2) == actual (actual == numNode == 2)
				_actual = _current;
				
			if(index == after) //if (index == 3) == after (after == numNode + 1 == 2 + 1 == 3)
				_post = _current;
				
			if(index == newPosition) //if (index == 4) == newPosition (newPosition == 4)
				_replaced = _current;
				
			if(index == following) //if (index == 5) == following (following == newPosition + 1= 4 + 1 == 5)
				_nextOne = _current;
			
			if(index < _total)
				_current = _current->next;
				
			index += 1;			
		}
		
		nodePtr temp = new node;
		
		_total += 1;
		
		//copying data:
		strcpy(temp->brand, _actual->brand);
		temp->price = _actual->price;
		
		temp->next = _nextOne;		
		
		_replaced->next = temp;
		
		_prior->next = _post;
				
		_actual->next = NULL;
		delete _actual;
		
	}
	
	else{
		
		//example: numNode == 5, newPosition == 3
		
		int index = 1;
		int past = newPosition-1; // past == 2
		int before = numNode-1; // prior == 4
		int after = numNode+1; // post == 6

		while(index <= _total){
			
			if(index == past)
				_back = _current; // == 2
				
			if(index == newPosition)
				_replaced = _current; // == 3
			
			if(index == before)
				_prior = _current; // == 4
				
			if(index == numNode)
				_actual = _current; // == 5
				
			if(index == after)
				_post = _current; // == 6
			
			if(index < _total)	
				_current = _current->next;
			
			index += 1;
		}
	
		nodePtr temp = new node;
		
		_total += 1;
		
		//copying data:
		strcpy(temp->brand, _actual->brand);
		temp->price = _actual->price;		
		//temp->next = actual->next;
		
		_prior->next = _post;
		
		temp->next = _replaced;
		
		_back->next = temp;
			
		_actual->next = NULL;
		delete _actual;		
	}
	
	//here: resetting positions of CURRENT and PREVIOUS pointers:
	repositioning_ptrs();
 	
	return;
}


void List::swapNodes(int n1, int n2){

	int penultimate = _total-1;
	
	if(n1 == 1 && n2 == 2){
		
		swapFirst();
		repositioning_ptrs();
	}

/**********************************************************************************************************************************************
*																																			  *
*											CASE (1): IF N1 == 1															              	  *
*																																			  *
**********************************************************************************************************************************************/
		
	else if(n1 == 1 && n2 == _total){
		
		//starting from top of list:
		_previous = _current = _head;
		
		int index=1;
		//moving to last node:
		while(index < _total){
			
			_current = _current->next;
			
			index += 1;
		}
				
		nodePtr temp = new node;
		
		//saving data of first node:
		strcpy(temp->brand, _head->brand);
		temp->price = _head->price;
		
		//swapping data between first and last nodes:
		strcpy(_head->brand, _current->brand);
		_head->price = _current->price;
		
		strcpy(_current->brand, temp->brand);
		_current->price = temp->price;
		
		//deleting temp object:
		temp->next = NULL;
		delete temp;
		
		//here: resetting positions of CURRENT and PREVIOUS pointers:
		repositioning_ptrs();
	}
	
	else if(n1 == 1 && (n2 != 2 && n2 != _total)){
		
		//starting from top of list:
		_previous = _current = _head;
		
		int index=1;
		//moving to requested node:
		while(index < n2){

			_current = _current->next;			
			index += 1;
		}
				
		nodePtr temp = new node;
		
		//saving data of first node:
		strcpy(temp->brand, _head->brand);
		temp->price = _head->price;
		
		//swapping data between first and last nodes:
		strcpy(_head->brand, _current->brand);
		_head->price = _current->price;
		
		strcpy(_current->brand, temp->brand);
		_current->price = temp->price;
		
		//deleting temp object:
		temp->next = NULL;
		delete temp;
		
		//here: resetting positions of CURRENT and PREVIOUS pointers:
		repositioning_ptrs();				
	}
	
/**********************************************************************************************************************************************
*																																			  *
*											CASE (2): IF N1 == TOTAL															              *
*																																			  *
**********************************************************************************************************************************************/
		
	else if(n1 == _total && n2 == penultimate)
		swapLast(n2);
	
	else if(n1 == _total && n2 == 1){
		
		//starting from top of list:
		_previous = _current = _head;
		
		int index = 1;
		
		//moving to last node:
		while(index < _total){
				
			_current = _current->next;			
			index += 1;
		}
		
		nodePtr temp = new node;
		
		//saving data from last node:
		strcpy(temp->brand, _current->brand);
		temp->price = _current->price;
		
		//swapping data between first and last nodes:
		strcpy(_current->brand, _head->brand);
		_current->price = _head->price;
		
		strcpy(_head->brand, temp->brand);
		_head->price = temp->price;
		
		delete temp;
		
		//here: resetting positions of CURRENT and PREVIOUS pointers (in case the user wishes to add or remove an object):
		repositioning_ptrs();		
		
	}
	
	else if(n1 == _total && (n2 != penultimate && n2 != 1)){
		
		//starting from top of list:
		_previous = _current = _head;
		
		int index = 1;
		
		//moving to last node (+ finding the chosen node -pointed to by OTHER- to replace contents with along the way):
		while(index < _total){
			
			if(index == n2)
				_other = _current; //--> here: to avoid any confusion, we are using the OTHER pointer (not PREVIOUS)
				
			_current = _current->next;			
			index += 1;
		}
		
		nodePtr temp = new node;
		
		//saving data from last node:
		strcpy(temp->brand, _current->brand);
		temp->price = _current->price;
		
		//swapping data between first and last nodes:
		strcpy(_current->brand, _other->brand);
		_current->price = _other->price;
		
		strcpy(_other->brand, temp->brand);
		_other->price = temp->price;
		
		delete temp;
		
		//here: resetting positions of CURRENT and PREVIOUS pointers:
		repositioning_ptrs();		
	}
	
/**********************************************************************************************************************************************
*																																			  *
*											CASE (3): IF N1 != 1 && N1 != TOTAL													              *
*																																			  *
**********************************************************************************************************************************************/
	
	else{
		
		if(n1 > n2){
			
			//starting from top of list:
			_previous = _current = _head;
			
			int index = 1;
			
			//moving to node 1 (+ finding node 2 to replace contents with along the way):
			while(index < n1){
				
				if(index == n2)
					_other = _current; //--> here: to avoid any confusion, we are using the OTHER pointer (not PREVIOUS)
					
				_current = _current->next;			
				index += 1;
			}
			
			nodePtr temp = new node;
			
			//saving data from last node:
			strcpy(temp->brand, _current->brand);
			temp->price = _current->price;
			
			//swapping data between first and last nodes:
			strcpy(_current->brand, _other->brand);
			_current->price = _other->price;
			
			strcpy(_other->brand, temp->brand);
			_other->price = temp->price;
			
			delete temp;
			
			//here: resetting positions of CURRENT and PREVIOUS pointers:
			repositioning_ptrs();			
		}
		
		else{
			
			//the technique here is to swap the valuues of n1 and n2, and follow the same procedure as above:
			
			int t;
			
			t = n1;
			n1 = n2;
			n2 = t;
			
			//starting from top of list:
			_previous = _current = _head;
			
			int index = 1;
			
			//moving to node 1 (+ finding node 2 to replace contents with along the way):
			while(index < n1){
				
				if(index == n2)
					_other = _current; //--> here: to avoid any confusion, we are using the OTHER pointer (not PREVIOUS)
					
				_current = _current->next;			
				index += 1;
			}
			
			nodePtr temp = new node;
			
			//saving data from last node:
			strcpy(temp->brand, _current->brand);
			temp->price = _current->price;
			
			//swapping data between first and last nodes:
			strcpy(_current->brand, _other->brand);
			_current->price = _other->price;
			
			strcpy(_other->brand, temp->brand);
			_other->price = temp->price;
			
			delete temp;
			
			//here: resetting positions of CURRENT and PREVIOUS pointers:
			repositioning_ptrs();			
		}		
	}
	
	return;		
}

void List::swapFirst(){ //---> this is for REARRANGE() function only (for CASE 1)
	
	//starting from top of list:
	_previous = _current = _head;
	
	//moving to next node:
	_current = _current->next;
	
	nodePtr temp = new node;
	
	//saving data from node 1:
	temp->next = _previous->next;
	strcpy(temp->brand, _previous->brand);
	temp->price = _previous->price;
	
	//swapping data between node 1 and node 2:
	strcpy(_previous->brand, _current->brand);
	_previous->price = _current->price;
	
	strcpy(_current->brand, temp->brand);
	_current->price = temp->price;
	
	temp->next = NULL;
	delete temp;
	
	//here: resetting positions of CURRENT and PREVIOUS pointers:
	repositioning_ptrs();	
	
	return;
}

void List::swapLast(int newPosition){
	
	//starting from top of list:
	_previous = _current = _head;
	
	int index = 1;
	
	//moving to last node (and defining previous object along the way):
	while(index < _total){
		
		if(index == newPosition)
			_previous = _current;
			
		_current = _current->next;
		
		index += 1;
	}
	
	nodePtr temp = new node;
	
	//saving data from last node:
	strcpy(temp->brand, _current->brand);
	temp->price = _current->price;
	
	//swapping data from penulitmate to last node:
	strcpy(_current->brand, _previous->brand);
	_current->price = _previous->price; 
	
	//swapping data from temp to penultimate node:
	strcpy(_previous->brand, temp->brand);
	_previous->price = temp->price;
	
	delete temp;
	
	//here: resetting positions of CURRENT and PREVIOUS pointers:
	repositioning_ptrs();	
		
	return;
}


void List::display_head_node(){
	
	if(_total == 0)
		printf("Sorry but... There are 0 nodes in the list.\n\n");
		
	else{
		
		printf("\nData for HEAD node:\n\n");
	
		//going back to beginning of list:
		_current = _head;
				
		std::cout << "\t" << _current->brand << "\n\t" << _current->price << "$\n\n";
	
/************************************************************************************************************************************************ 
	NOW: ENSURING THAT BOTH 'current' AND 'previous' POINTERS POINT TO THE SAME OBJECT: THE LAST OBJECT OF THE LIST:
	(this is to make sure the pointers are up to date in order to enable the user to add more nodes to the list)		
************************************************************************************************************************************************/

		repositioning_ptrs();
	}
		
	return;	
}


void List::number_nodes(){

	std::cout << "Total number of nodes in the linked list so far: " << _total << "\n\n";
	
	return;
}


void List::error_message(){
	
	std::cout << "Sorry: you have entered an invalid number.\n\n";
	
	return;
}



void List::queue_mode(char* brand, double price){
			
	int num=0;
		
	//going to last object of the list:
	repositioning_ptrs();
		
	if(_total > limit){
			
		std::cout << "\nSorry: the number of nodes in the list exceeds the limit of the queue.\n";
			
		while(_total > limit){
					
			int index = 1;
			int sub = _total-1;
						
			//IMPORTANT: this takes us back to the very beginning of the list:
			_current = _head;
						
			while(index < _total){
							
				if(index == sub)
					_previous = _current;
							
					_current = _current->next;
												
					index += 1;
			}
					
			//now: CURRENT points to the LAST object and PREVIOUS points to the PENULTIMATE object.
			//ALSO: remember that NEXT member of the last object of the list, pointed to by CURRENT, has already been set to NULL.
					
			delete _current;
				
			_previous->next = NULL;
					
			_total -= 1;
			num += 1;
						
			repositioning_ptrs();				
		}
			
		std::cout << "\n\nWe have therefore had to delete the last " << num << " nodes:\n\n";
			
		PrintList();
			
		std::cout << "\n\nQueue is now ready to be used.\n\n";	
	}
		
	else{ //if(*total < limit)
			
		int difference = limit - _total;
			
		if(difference == 1)
			std::cout << "\nIn order to have a QUEUE, you must add another node to the list:\n\n";	
				
		else
			std::cout << "\nIn order to have a QUEUE, you must add another " << difference << " nodes to the list:\n\n";
			
		int index = 0;
			
		while(index < difference){
				
			AddNode(brand, price);
			std::cout << "\n";
				
			index += 1;
				
			if(index == 1)
				std::cout << "\n1 node added to list.\n";
			else
				std::cout << "\n" << index << " nodes added to list.\n";				
		}
						
		std::cout << "\nYour list now full:\n\n";
			
		PrintList();
			
		std::cout << "\nQueue is now ready to be used. Add a new node:\n";			
	}
		
	//here: we are calling the ADD_NODE_FROM_REAR() function which adds a new node at the rear/end of the list:		
	AddNode(brand, price);		
		
	//here: we are getting rid of the first node, whereby the following node now becomes the HEAD node:
	//this takes us back to the very beginning of the list (NOTE: both HEAD and CURRENT now point to the first object of the list):
	_current = _head;
					
	//accessing following node via address contained in object's NEXT member + making this object HEAD/FIRST object of the list:
	_head = _head->next;
					
	//deleting the chosen object (which used to be FIRST, but is now left aside, being only pointed to by TEMP pointer):
	_current->next = NULL;		
	delete _current;
					
	_total -= 1;
					
	repositioning_ptrs();		
			
	std::cout << "\nHere is your queue of nodes, MINUS the former first node which has been popped out of the queue!\n\n";
		
	PrintList();
		
	return;
}


void List::sortAlphabetic(){
		
	int outer_cycle;
	int inner_cycle;
	
	do{	
	
		_previous = _current = _head;
		outer_cycle = 0;
		inner_cycle = 1;
		
		while(inner_cycle < _total){
			
			_current = _current->next;

			int result = strcmp(_previous->brand, _current->brand); //*********
			
			if(result > 0){

				char temp[max_chars];
				strcpy(temp, _current->brand);
				strcpy(_current->brand, _previous->brand);
				strcpy(_previous->brand, temp);
				
				double t;
				t = _current->price;
				_current->price = _previous->price;
				_previous->price = t;

				_previous = _current;	

				outer_cycle += 1;
				inner_cycle += 1;				
			}
			
			else{
				inner_cycle += 1;
				_previous = _current;
			}			
		}
			
	}while(outer_cycle > 0);
	
	std::cout << "\n\nYour linked list sorted alphabetically:\n\n";
	
	PrintList();
	
	return;
}


void List::sortNumeric(int choice){

	if(choice == 1){
		
		int outer_cycle;
		int inner_cycle;
		
		do{	
		
			_previous = _current = _head;
			outer_cycle = 0;
			inner_cycle = 1;
			
			while(inner_cycle < _total){
				
				_current = _current->next;
				
				if(_previous->price > _current->price){
	
					char temp[max_chars];
					strcpy(temp, _current->brand);
					strcpy(_current->brand, _previous->brand);
					strcpy(_previous->brand, temp);
					
					double t;
					t = _current->price;
					_current->price = _previous->price;
					_previous->price = t;
	
					_previous = _current;	
	
					outer_cycle += 1;
					inner_cycle += 1;				
				}
				
				else{
					inner_cycle += 1;
					_previous = _current;
				}			
			}
				
		}while(outer_cycle > 0);
		
		std::cout << "\n\nYour linked list sorted numerically by price (in INCREASING order):\n\n";
		
		PrintList();
	}
	
	else{
		
		int outer_cycle;
		int inner_cycle;
		
		do{	
		
			_previous = _current = _head;
			outer_cycle = 0;
			inner_cycle = 1;
			
			while(inner_cycle < _total){
				
				_current = _current->next;
				
				if(_previous->price < _current->price){
	
					char temp[max_chars];
					strcpy(temp, _current->brand);
					strcpy(_current->brand, _previous->brand);
					strcpy(_previous->brand, temp);
					
					double t;
					t = _current->price;
					_current->price = _previous->price;
					_previous->price = t;
	
					_previous = _current;	
	
					outer_cycle += 1;
					inner_cycle += 1;				
				}
				
				else{
					inner_cycle += 1;
					_previous = _current;
				}			
			}
				
		}while(outer_cycle > 0);
		
		std::cout << "\n\nYour linked list sorted numerically by price (in DECREASING order):\n\n";
		
		PrintList();
	}
			
	return;
}	

		
void List::PrintList(){
	
	_current = _head;
	
	while(_current != NULL){
		
		//printing:
		std::cout << "\nBrand of car: " << _current->brand << "\nPrice of car: " << _current->price << "$.\n" << std::endl;
		
		//advancing one notch:
		_current = _current->next;
	}
	
	return;
}





