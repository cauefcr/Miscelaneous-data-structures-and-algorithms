#include <stdio.h>
#include <stdlib.h>

//lista que cabe no máximo CAPACIDADE_MAXIMA elementos 
const int CAPACIDADE_MAXIMA = 100;
typedef struct {
	int array[CAPACIDADE_MAXIMA];
	int nElementos;
} Lista; 

Lista* novaLista() { 
	Lista* nova = (Lista*) malloc (sizeof(Lista));
	nova->nElementos = 0;
	return nova;
}

void inserir (Lista* lista, int valor) {
	if (lista->nElementos >= CAPACIDADE_MAXIMA) {
		printf("ERRO FATAL: LISTA EXPLODIU!\n");
		exit(12345);
	}
	lista->array[lista->nElementos++] = valor;
}

void imprimirLista(Lista* lista) {
	for (int i = 0; i < lista->nElementos; ++i) {
		printf("%d ", lista->array[i]);
	}
	printf("\n");
} 