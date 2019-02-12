#include "linked_list.h"

int main(){
	list * lista = new_list();
	push_start(lista,10);
	push_end(lista,20);
	push_start(lista,5);

	print_linked(lista);
	kill_elem(lista,20);
	print_linked(lista);

	replace(lista,10,7);
	print_linked(lista);
	kill_list(lista);
}