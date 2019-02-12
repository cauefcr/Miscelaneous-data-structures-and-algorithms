#include <stdio.h>
#include <stdlib.h>

//lista que permite inserir mais elementos enquanto houver memoria
typedef struct {
	int* vetor;
	int capacidade;
	int nElementos;
} Lista; 

Lista* novaLista() {
	Lista* nova = (Lista*) malloc (sizeof(Lista));
	nova->capacidade = 8;
	nova->vetor = (int*) malloc (sizeof(nova->capacidade * sizeof(int)));
	nova->nElementos = 0;
	return nova;
}

void inserir (Lista* lista, int valor) {
	if (lista->nElementos >= lista->capacidade) {
		lista->capacidade *= 2;
		lista->vetor = (int*) realloc (lista->vetor, lista->capacidade * sizeof(int));
	}
	lista->vetor[lista->nElementos++] = valor;
}

void imprimirLista(Lista* lista) {
	for (int i = 0; i < lista->nElementos; ++i) {
		printf("%d ", lista->vetor[i]);
	}
	printf("\n");
} 