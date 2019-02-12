#include "linked_list.h"
#include <vector>

using namespace std;

void imprimirVetor(int vetor[], int tam, int i = 0) { // 1
	if (i < tam && i >= 0) {
		cout << vetor[i] << ", ";
		return imprimirVetor(vetor, tam, i + 1);
	} else { return; }
}

void imprimirListaLigada(no* node) { // 2
	if (node != nullptr) {
		cout << node->val << ", ";
		return imprimirListaLigada(node->next);
	}
}

void imprimirLista(list* lst) { // 2
	imprimirListaLigada(lst->head);
}

vector<int> fib(3, 1); // tres valores 1 como começo

int fibonacci(int n) { // 3
	if (n >= fib.size()) {
		fib.push_back(fibonacci(n - 1) + fibonacci(n - 2));
	}
	return fib[n];
}

bool palindromo(const string texto, int primeiro = 0, int ultimo = 0) { //4
	if (ultimo == 0)
		return palindromo(texto, 0, texto.length() - 1);
	if (texto[primeiro] == texto[ultimo]) {
		if (ultimo > primeiro) {
			return palindromo(texto, primeiro + 1, ultimo - 1);
		} else { return true; }
	} else { return false; }
}

int minimo(int vetor[], int tam, int i = -1, int mini = 0) { //5
	if (i == -1)
		return minimo(vetor, tam, 0, vetor[0]);
	if (i == tam)
		return mini;
	if (vetor[i] < mini) {
		return minimo(vetor, tam, i + 1, vetor[i]);
	}
	return minimo(vetor, tam, i + 1, mini);
}

int main() {
	/*
	//1
	int vec[10];
	for(int i = 0; i < 10; i++){
	    vec[i] = i;
	}
	imprimirVetor(vec,10);
	*/

	/*
	//2
	list* lst = new_list();
	for(int i = 0; i < 10; i++){
	    push_end(lst,i);
	}
	//print_linked(lst);
	imprimirLista(lst);
	*/

	/*
	//3
	fib.reserve(70); //ridiculamente mais rápido, de fato
	for(int i = 0; i < 70; i++){
	    cout << fibonacci(i) << endl;
	}
	*/

	/*
	//4
	cout << palindromo("kayak arara kayak");
	*/

	/*
	// 5
	int vec[50];
	for (int i = 0; i < 50; i++) {
		vec[i] = 50 - i;
	}
	// imprimirVetor(vec, 50);
	cout << minimo(vec,50);
	*/
	return 0;
}