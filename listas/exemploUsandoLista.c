#include "ListaLigada.h"

int main() {

	Lista* lista = novaLista();

	inserir(lista, 1);
	inserir(lista, 2);
	inserir(lista, 3);
	inserir(lista, 4);
	inserir(lista, 5);

	imprimirLista(lista);

}