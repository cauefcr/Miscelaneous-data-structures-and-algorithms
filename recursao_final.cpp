#include "linked_list.h"

void reverse(list* lst, no* prev = nullptr, no* atual = nullptr) {
	if (prev == nullptr && atual == nullptr) {
		if (lst->head != nullptr) {
			return reverse(lst, nullptr, lst->head);
		}
	}
	if (atual->next != nullptr) {
		if (prev == lst->head)
			lst->tail = prev;
		reverse(lst, atual, atual->next);
	} else
		lst->head = atual;
	atual->next = prev;
}

int num=1;
void mover(int quant, int orig, int dest, int tmp) {
	if (quant > 0) {
		mover(quant - 1, orig, tmp, dest); // move todos-1 pro temporário
		cout << num++ << ": " << orig << " -> " << dest << endl;
		mover(quant - 1, tmp, dest, orig); // move de volta pra ele
	} // no ultimo caso antes do base, ele imprime qual o ultimo anel a ser
	  // movido, essencialmente o anel que sobrou
}

int main() {

	// inverter lista
	// list* lst = new_list();
	// for (int i = 0; i < 10; i++) {
	// 	push_end(lst, i);
	// }
	// print_linked(lst);
	// reverse(lst);
	// print_linked(lst);

	// cout << endl
	//      << "digite o número de aneis:\n";
	int aneis = 19;
//	cin >> aneis;

	// hanoi, ai minha cabeça
	mover(aneis, 1, 3, 2);
	return 0;
}