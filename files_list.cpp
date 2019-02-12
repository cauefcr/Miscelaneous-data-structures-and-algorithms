#include "linked_list.h"
#include <stdio.h>

void linked_to_file(list* lst, FILE* arc, no* tmp){ //writes a linked list as a csv file
	if(tmp != nullptr){
		fprintf(arc, "%i,", tmp->val);
		return linked_to_file(lst,arc,tmp->next);
	}
	fprintf(arc, "\n");
}

list* file_to_linked(FILE* arc, list* lst = new_list()){
	if (fscanf(arc,"%i,",&tmp) == 1){
		push_end(lst,tmp);
		return file_to_linked(arc,lst);
	}
	return lst;
}

void salvar(list* lista, FILE* arquivo){
	linked_to_file(lista,arquivo,lista->head);
}

void carregar(list* lista, FILE* arquivo){
	lista = file_to_linked(arquivo);
}

int main(){
	FILE* out_file;

	list* test_list = new_list();
	for(int i = 0; i < 10; i++){
		push_end(test_list,i);
	}
//	print_linked(test_list);

	out_file = fopen("out.txt","w");
	salvar(test_list,out_file);
	fclose(out_file);

	FILE* in_file;
	in_file = fopen("out.txt","r");
	list* test_list2 = file_to_linked(in_file);
	fclose(in_file);
	print_linked(test_list2);
}