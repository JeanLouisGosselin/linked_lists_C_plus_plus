
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "List.h"

const int max_chars = 100;

void menu(int*);
void enterBrand(char*);
void enterPrice(double*);
void enterNumber(int*);
void valuesForSwap(int*, int*);
void old_newPositions(int*, int*, int);
void queue_mode(char*); 
void increaseOrdecrease(int*);
void enterPosition(int*, int);

int main(int argc, char** argv) {
	
	//declaring our object:
	List obj1;

	int c, val, position, result;
	char brand[max_chars], answer;
	double price;
	int choice, n1, n2, numNode, newPosition;
	
	menu(&c);
	
	while(c > 0 && c < 12){
		
		switch(c){

			case 1:		
						enterBrand(brand);
						enterPrice(&price);
						obj1.AddNode(brand, price);
						break;
												
			case 2:
						enterNumber(&choice);
						obj1.DeleteNode(choice);
						break;
												
			case 3:
						enterBrand(brand);
						enterPrice(&price);
						result = obj1.getTotal();
						enterPosition(&position, result);
						obj1.insert_node(brand, price, position);
						break;
						
			case 4:
						result = obj1.getTotal();
						old_newPositions(&n1, &n2, result);
						obj1.rearrangeNodes(n1, n2);
						break;
						
			case 5:
						valuesForSwap(&n1, &n2);
						obj1.swapNodes(n1, n2);
						break;
						
			case 6:
						obj1.PrintList();
						break;
						
			case 7:
						obj1.number_nodes();
						break;
						
			case 8:
						obj1.display_head_node();
						break;
									
			case 9:		
						queue_mode(&answer);
						
						while(answer != 'n'){
							
							obj1.queue_mode(brand, price);
							queue_mode(&answer);
						}
						break;
						
			case 10:		
						obj1.sortAlphabetic();
						break;
						
			case 11:	
						increaseOrdecrease(&val);	
						obj1.sortNumeric(val);
						break;				
		}
		
		if(c == 12)
			break;
			
		else
			menu(&c);
	}
	
	std::cout << "\n\nHere: copying all the nodes from OBJ1 to OBJ2 (ie: invoking COPY CONSTRUCTOR):\n\n\tOBJ2 = OBJ1\n\n";
	
	List obj2;
	
	obj2 = obj1;
	
	std::cout << "Printing all nodes from OBJ1:\n\n";
	
	obj1.PrintList();
	
	std::cout << "\n\nNow: printing all nodes from OBJ2:\n\n";
	
	obj2.PrintList();
	
	printf("\n\nThe end.\n\n");

	return 0;
}


void menu(int* choice){
	
	printf("\nPlease choose one of the following choices:n\n");
	printf("(1) to add a new node (at rear of list only);\n");
	printf("(2) to remove a node;\n");
	printf("(3) to insert a new node anywhere in list;\n");
	printf("(4) to re-arrange order of one or several nodes;\n");
	printf("(5) to swap nodes;\n");
	printf("(6) to print all current data of nodes;\n");
	printf("(7) to print total number of nodes;\n");
	printf("(8) to display HEAD node;\n");
	printf("(9) to enter QUEUE mode;\n");
	printf("(10) to sort list alphabetically;\n");
	printf("(11) to sort list numerically;\n");
	printf("(12) to end program.\n\n");
	
	std::cin >> *choice;
	getchar();
		
	return;
}

void enterBrand(char* name){
	
	std::cout << "\nEnter brand of car: ";
	std::cin.getline(name, max_chars);
	
	return;
}

void enterPrice(double* p){
	
	std::cout << "\nEnter price of car: ";
	std::cin >> *p;
	getchar();
		
	return;
}

void enterNumber(int* n){

	std::cout << "Enter number of item you wish to remove from list (enter 1 to remove node 1, 2 to remove node 2 etc): ";
	std::cin >> *n;
	getchar();	
	
	return;
}

void valuesForSwap(int* n1, int* n2){
	
	std::cout << "Swap contents of node no.";
	std::cin >> *n1;
	printf("\n...with contents of node no.");
	std::cin >> *n2;
	getchar();	
	
}

void old_newPositions(int* numNode, int* newPosition, int tot){
	
	std::cout << "\nEnter number of node you wish to re-position in the list (between 1 and " << tot << "):";
	std::cin >> *numNode;
	
	while(*numNode < 1 || *numNode > tot){
		
		std::cout << "\nInvalid value.\n";
		std::cout << "\nEnter number of node you wish to re-position in the list (between 1 and " << tot << "):";
		std::cin >> *numNode;
	}
	
	std::cout << "\n...and you want this node at which position in the list? (between 1 and " << tot << "):";
	std::cin >> *newPosition;
	
	while(*newPosition < 1 || *numNode > tot){
		
		std::cout << "\nInvalid value.\n";
		std::cout << "\nEnter number of node you wish to re-position in the list (between 1 and " << tot << "):";
		std::cin >> *newPosition;
	}
	
	getchar();	
	
	return;
}


void queue_mode(char* c){
	
	std::cout << "\nContinue into QUEUE mode? (y/n) ";
	std::cin >> *c;
	getchar();
							
	return;
}

void increaseOrdecrease(int* val){
	
	printf("Choose one of the following:\n\n");
	
	printf("(1) to sort in INCREASING order;\n");
	printf("(2) to sort in DECREASING order.\n");
	std::cin >> *val;
	
	while(*val != 1 && *val != 2){
		
		printf("\nSorry: invalid choice. Start again.\n");
		printf("Choose one of the following:\n\n");
		
		printf("(1) to sort in INCREASING order;\n");
		printf("(2) to sort in DECREASING order.\n");
		std::cin >> *val;
	}	
	
	return;
}


void enterPosition(int* position, int tot){

	std::cout << "Enter position in list where you'd like to insert new node (anywhere between 1 and " << tot << "): ";
	std::cin >> *position;
	getchar();
	
	while(*position > tot){
		
		std::cout << "\nSorry: invalid value.\n";
		std::cout << "Enter position in list where you'd like to insert new node (anywhere between 1 and " << tot << "): ";
		std::cin >> *position;
		getchar();
	}	
	
	return;
}






