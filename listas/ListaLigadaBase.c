#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
	struct No* proximo;
	int val;
} No;

typedef struct Lista{
	No* cabeca;
} Lista;

No* novoNo(int valor) {
	No* tmp = (No*) malloc(sizeof(No));
	tmp->val = valor;
	tmp->proximo = NULL;
	return tmp;
} 

Lista* novaLista() {
	Lista* nova = (Lista*) malloc (sizeof(Lista));
	nova->cabeca = NULL;
	return nova;
}

void empilhar (Lista* joao, int valor) {
	No* novo = novoNo(valor);
	novo->proximo = joao->cabeca;
	joao->cabeca = novo;
	return;
}

int desempilhar (Lista* joao) {
	if(joao->cabeca != NULL){
		int valor = (joao->cabeca)->val;
		No* carlos = (joao->cabeca)->proximo;
		free(joao->cabeca);
		joao->cabeca = carlos;
		return valor;
	} else {
		return 0;
	}
}

void imprimirLista(Lista* lista) {
	printf("Lista: |");
	for(No* tmp = lista->cabeca; tmp != NULL; tmp = tmp->proximo){
		printf("%d,",tmp->val);
	}
	printf("\n");
}

int main () {
	Lista* joao = novaLista();
	int c;
	for(int i = 4; i>=1; i--){
		empilhar(joao,i);
	}
	imprimirLista(joao);
	while ((c = desempilhar(joao)) != 0) {
		printf("%d,",c);
	}
	free(joao);
} 