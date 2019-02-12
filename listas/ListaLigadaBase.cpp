//Cauê Felchar //Vithor Tozetto
#include <iostream>
#include <string>

using namespace std;

struct No {
	int chave;
	No* proximo;

	string nome;
	int idade;
};

struct Lista {
	No* cabeca;
};

No* novoNo(int chave, string nome, int idade) {
	No* novo = new No();
	novo->chave = chave;
	novo->nome = nome;
	novo->idade = idade;

	return novo;
} 

Lista* novaLista() {
	Lista* nova = new Lista();
	return nova;
}

void inserir (Lista* lista, int chave, string nome, int idade) {
	No * ins = novoNo(chave, nome, idade);
	ins->proximo = lista->cabeca;
	lista->cabeca = ins;
	return;
}

void remover (Lista* lista, int chave) {
	No * atual = lista->cabeca;
	No * anterior;
	do{
		if(atual->chave == chave){
			if(atual == lista->cabeca){
				lista->cabeca = atual->proximo;
			}
			else{
				anterior->proximo = atual->proximo;
			}
			delete(atual);
			break;
		}
		anterior = atual;
		atual = atual->proximo;
	}while(atual!=NULL);
	return;
}

void imprimirLista(Lista* lista) {
	No * atual = lista->cabeca;
	cout << "Lista: |";
	if(lista->cabeca == NULL){
		cout << "_|";
		return;
	}
	do{
		cout << " {" << atual->chave << "} " << atual->nome << " : " << atual->idade << " |";
		atual = atual->proximo;
	}while(atual != NULL);

	cout << "\n";
}

int main () {
	Lista* lista = novaLista();
	inserir(lista, 3, "Neblina", 4);
	inserir(lista, 5, "Alessandro", 29);
	inserir(lista, 10, "Sarah", 27);
	inserir(lista, 30, "Luane", 28);
	imprimirLista(lista); //Lista: |{30} Luane : 28 | {10} Sarah : 27 | {5} Alessandro : 29 | {3} Neblina : 4 |
	remover(lista, 3); //remove Neblina
	remover(lista, 30); //remove Luane
	imprimirLista(lista); //Lista: |{10} Sarah : 27 | {5} Alessandro : 29 |

	remover(lista, 5); //remove Alessandro
	remover(lista, 10); //remove Sarah
	imprimirLista(lista); //Lista: |_|		
} 