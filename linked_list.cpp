#include <iostream>
#include <new>

using namespace std;

typedef struct no{
	int val;
	no * next;
}no;

typedef struct{
	no * head;
	no * tail;
} list;

//CRUD
//create*, retrieve*, update*, delete*
//done?
list * new_list(){
	list * lst = new list;
	lst->head = nullptr;
	lst->tail = nullptr;
	return lst;
}

no * new_node(int value){
	no * node = new no();
	node->val = value;
	/*C 
	no * node = (no *) malloc (sizeof(no));
	node->next = NULL;
	*/
	return node;
}

void add_next_to(no * node, int value){ //make it bool?
	no * tmp = new no(); //constructs it empty
	no * aux = node->next;
	tmp->val = value;
	node->next = tmp;
	tmp->next = aux;
}

void print_linked(list * lst){
	no * tmp = lst->head;
	cout<< "tail: "<< (lst->tail)->val << " head: " << (lst->head)->val << endl;

	while(true){
		cout << tmp->val << ", ";
		if(tmp->next == nullptr){
			break;
		}
		else{
			tmp = tmp->next;
		}
	}
	cout << endl;
}

void push_end(list * lst, int value){
	no * prev_tail = lst->tail;
	no * new_tail = new_node(value);
	if (lst->head == nullptr){
		lst->head = new_tail;
	}
	prev_tail->next = new_tail;
	lst->tail = new_tail;
}

void push_start(list * lst, int value){
	no * prev_head = lst->head;
	no * new_head = new_node(value);
	if (lst->tail == nullptr){
		lst->tail = new_head;
	}
	lst->head = new_head;
	new_head->next = prev_head;
}

void kill_elem(list * lst, int value){
	no * curr = lst->head;
	no * prev;
	if (curr->val == value){ //for the head
		curr = curr->next;
		delete(lst->head);
		lst->head = curr;
		return;
	}

	do { //everything in the middle
		prev = curr;
		curr = curr->next;
	} while ( (curr != lst->tail) || (curr->val != value) );

	if (curr == lst->tail){ //for the tail
		lst->tail = prev;
	}
	curr = curr->next;
	delete(prev->next);
	prev->next = curr;
	return;
}
no * find(list * lst, int value){
	//find node with a certain value and return it's adress, returns nullptr if it can't find the value
	no * curr = lst->head;
	while(true){
		if(curr->val == value){
			return curr;
		}
		if(curr == lst->tail){
			return nullptr;
		}
		curr = curr->next;
	}
}
bool replace(list * lst, int old_value,int new_value){
	no * node = new_node(0);
	if((node = find(lst,old_value)) != nullptr){
		node->val = new_value;
		return true;
	}
	else{
		return false;
	}
}

int main(){
	list * lista = new_list();
	push_start(lista,10);
	push_end(lista,20);
	push_start(lista,5);

	print_linked(lista);
/*	kill_elem(lista,20);
	print_linked(lista);
*/
	replace(lista,10,7);
	print_linked(lista);
//	kill_list(head);
}