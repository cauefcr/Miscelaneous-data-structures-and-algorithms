#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
	int *vec; // ponteiro pra array de fato
	int first; // indice do first valor preenchido
	int last;  // indice do last valor preenchido
	int size;  // size atual da array
} queue;

queue *queue_new(int tam) { // aloca a a array e inicia os valores
	queue *nova = (queue *) malloc(sizeof(queue));
	nova->size = tam;
	nova->first = 0;
	nova->last = 0;
	nova->vec = (int *)malloc(sizeof(int) * tam); // aloca a array de fato
	return nova;
}

void queue_grow(queue *que) { // também arruma o vetor
	// int* new_vec = new int[que->size * 2]; // cria um vetor novo
	int *new_vec = (int *)malloc(sizeof(int) * (que->size * 2));
	if (que->last > que->first) { // se estiver em ordem
		for (int i = que->first; i <= que->last;
		     i++) { // copia do first elemento ao last
			new_vec[i - que->first] = que->vec[i];
		}
		que->last = que->last - que->first;
		que->first = 0;
	} else if (que->last < que->first) { // se já tiver dado a volta
		for (int i = que->first; i <= que->size;
		     i++) { // copia first a parte final
			new_vec[i - que->first] = que->vec[i];
		}
		for (int i = 0; i < que->last; i++) { // depois a do começo
			new_vec[que->size - que->first + i] = que->vec[i];
		}
		que->last += que->size - que->first;
		que->first = 0;
	}
	free(que->vec);     // desaloca a array antiga
	que->vec = new_vec; // guarda o ponteiro da nova, agora que ja a utilizamos
	que->size *=
	    2; // só consegue dobrar a size, parece uma utilização ok para mim
}

int queue_len(
    queue *que) { // não precisa guardar o int tamanho na struct vetor!
	if (que->last == que->first) { // se estiver vazio, tamanho 0
		return 0;
	} else if (que->last > que->first) { // se estiver na ordem esperada
		return que->last - que->first;
	} else { // que->last < que->first      caso esteja trocado
		return que->size - que->first + que->last;
	}
}

void queue_push(queue *que, int valor) { // coloca no fim da queue, bem
	                                     // literalmente
	if (queue_len(que) < que->size) {    // se tiver espaço
		if (que->last < que->size) {
			que->vec[que->last++] = valor;
		} else if (que->last == que->size) { // da a volta
			que->last = 0;
			que->vec[que->last++] = valor;
		}
	} else { // sem espaço a queue cresce
		queue_grow(que);
		queue_push(que, valor);
		return;
	}
}

int queue_pop(queue *que) { // da a volta ao contrário
	if (que->first == que->size) {
		que->first = 0;
	}
	int val = que->vec[que->first]; // retira o first valor
	que->first += 1;
	if (que->first == que->last) { // se está vazia
		que->first = 0;
		que->last = 0;
		return 0;
	}
	return val;
}

void queue_print(queue *que, bool dbg) {
	if (dbg) {
		// cout << "na memória:\n";
		puts("na memória:");
		for (int i = 0; i < que->size; i++) {
			printf("%d,", que->vec[i]);
			// cout << que->vec[i] << ",";
		}
		printf(" tamanho: %d, prim: %d, ult: %d, size: %d, Em ordem:\n",
		       queue_len(que), que->first, que->last, que->size);
		// cout << " tamanho: " << queue_len(que) << ", prim: " << que->first
		//      << ", ult: " << que->last << ", size: " << que->size
		//      << ", Em ordem:\n";
	}

	// cout << "[";
	putchar('[');
	int i = que->first;
	while (true) {
		if (i == que->last) {
			break;
		}
		// cout << que->vec[i] << ",";
		printf ("%d,", que->vec[i] );
		if (i >= que->size) {
			i = 0;
		} else { i++; }
	}
	// cout << "]\n";
	puts("]");
}

// int main() {
// 	queue *queueaa = queue_new(8);
// 	queue_print(queueaa, true);
// 	for (int i = 0; i < 8; i++) {
// 		queue_push(queueaa, i);
// 	}
// 	queue_print(queueaa, true);
// 	for (int i = 0; i < 4; i++) {
// 		queue_pop(queueaa);
// 	}
// 	queue_push(queueaa, 666);
// 	queue_print(queueaa, true);
// 	return 0;
// }
