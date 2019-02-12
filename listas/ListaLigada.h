#include <stdio.h>
#include <stdlib.h>

typedef struct No {
	int valor;
	struct No* proximo;
} No;

typedef struct {
	No* cabeca;
} Lista;

No* novoNo(int valor) {
	No* novo = (No*) malloc (sizeof(No));
	novo->valor = valor;
	novo->proximo = NULL;

	/* C++:
	No* novo = new No();
	novo->valor = valor; */

	return novo;
} 

Lista* novaLista() {
	Lista* nova = (Lista*) malloc (sizeof(Lista));
	nova->cabeca = NULL;
	return nova;
}

void inserir (Lista* lista, int valor) {
	No* antigo = lista->cabeca;
	No* novo = novoNo(valor);
	novo->proximo = antigo;
	lista->cabeca = novo;
}

void imprimirLista(Lista* lista) {
	No* atual = lista->cabeca;

	while (atual != NULL) {
		printf("%d ", atual->valor);
		atual = atual->proximo;
	}
	printf("\n");
} 