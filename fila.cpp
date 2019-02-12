#include <iostream>

using namespace std;

typedef struct fila {
	int* vect;      // ponteiro pra array de fato
	int primeiro;   // indice do primeiro valor preenchido
	int ultimo;     // indice do ultimo valor preenchido
	int capacidade; // capacidade atual da array
} fila;

fila* fila_new(int tam = 8) { // aloca a a array e inicia os valores
	fila* nova = new fila();
	nova->capacidade = tam;
	nova->primeiro = 0;
	nova->ultimo = 0;
	nova->vect = new int[nova->capacidade]; // aloca a array de fato
	return nova;
}

void fila_grow(fila* fil) {                      // também arruma o vetor
	int* new_vec = new int[fil->capacidade * 2]; // cria um vetor novo
	if (fil->ultimo > fil->primeiro) {           // se estiver em ordem
		for (int i = fil->primeiro; i <= fil->ultimo;
		     i++) { // copia do primeiro elemento ao ultimo
			new_vec[i - fil->primeiro] = fil->vect[i];
		}
		fil->ultimo = fil->ultimo - fil->primeiro;
		fil->primeiro = 0;
	} else if (fil->ultimo < fil->primeiro) { // se já tiver dado a volta
		for (int i = fil->primeiro; i <= fil->capacidade;
		     i++) { // copia primeiro a parte final
			new_vec[i - fil->primeiro] = fil->vect[i];
		}
		for (int i = 0; i < fil->ultimo; i++) { // depois a do começo
			new_vec[fil->capacidade - fil->primeiro + i] = fil->vect[i];
		}
		fil->ultimo += fil->capacidade - fil->primeiro;
		fil->primeiro = 0;
	}
	delete (fil->vect);  // desaloca a array antiga
	fil->vect = new_vec; // guarda o ponteiro da nova, agora que ja a utilizamos
	fil->capacidade *=
	    2; // só consegue dobrar a capacidade, parece uma utilização ok para mim
}

int fila_len(fila* fil) { // não precisa guardar o int tamanho na struct vetor!
	if (fil->ultimo == fil->primeiro) { // se estiver vazio, tamanho 0
		return 0;
	} else if (fil->ultimo > fil->primeiro) { // se estiver na ordem esperada
		return fil->ultimo - fil->primeiro;
	} else { // fil->ultimo < fil->primeiro      caso esteja trocado
		return fil->capacidade - fil->primeiro + fil->ultimo;
	}
}

void fila_push(fila* fil, int valor) { // coloca no fim da fila, bem
                                       // literalmente
	if (fila_len(fil) < fil->capacidade) { // se tiver espaço
		if (fil->ultimo < fil->capacidade) {
			fil->vect[fil->ultimo++] = valor;
		} else if (fil->ultimo == fil->capacidade) { // da a volta
			fil->ultimo = 0;
			fil->vect[fil->ultimo++] = valor;
		}
	} else { // sem espaço a fila cresce
		fila_grow(fil);
		return fila_push(fil, valor);
	}
}

int fila_pop(fila* fil) { // da a volta ao contrário
	if (fil->primeiro == fil->capacidade) {
		fil->primeiro = 0;
	}
	int val = fil->vect[fil->primeiro]; // retira o primeiro valor
	fil->primeiro += 1;
	if (fil->primeiro == fil->ultimo) { // se está vazia
		fil->primeiro = 0;
		fil->ultimo = 0;
		return 0;
	}
	return val;
}

void fila_print(fila* fil, bool dbg) {
	if (dbg) {
		cout << "na memória:\n";
		for (int i = 0; i < fil->capacidade; i++) {
			cout << fil->vect[i] << ",";
		}
		cout << " tamanho: " << fila_len(fil) << ", prim: " << fil->primeiro
		     << ", ult: " << fil->ultimo << ", capacidade: " << fil->capacidade
		     << ", Em ordem:\n";
	}

	cout << "[";
	int i = fil->primeiro;
	while (true) {
		if (i == fil->ultimo) {
			break;
		}
		cout << fil->vect[i] << ",";
		if (i >= fil->capacidade) {
			i = 0;
		} else { i++; }
	}
	cout << "]\n";
}

int main() {
	fila* filaaa = fila_new();
	fila_print(filaaa, true);
	for (int i = 0; i < 8; i++) {
		fila_push(filaaa, i);
	}
	fila_print(filaaa, true);
	for (int i = 0; i < 4; i++) {
		fila_pop(filaaa);
	}
	fila_push(filaaa, 666);
	fila_print(filaaa, true);
	return 0;
}