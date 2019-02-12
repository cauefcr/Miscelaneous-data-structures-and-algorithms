//Cauê Felchar
//Thiago da Silva Teixeira

#include <iostream>
using namespace std;

typedef struct no{
	int valor;
	no * proximo;
}no;

typedef struct pilha{
	no * cabeca;
}pilha;

pilha * new_pilha(){
	pilha * nova = new pilha();
//	pilha * nova = (pilha*) malloc(sizeof(pilha))
//	nova->cabeca=NULL
	return nova;
}

no * novoNo(int val){
	no * novo = new no();
	novo->valor = val;
	return novo;
}

void add_to_pilha(pilha * pil, int val){
	no * novo = novoNo(val);
	novo->proximo = pil->cabeca;
	pil->cabeca = novo;
	return;
}

int desempilhar(pilha * pil){
	if(pil->cabeca == nullptr){
		cerr << "Fim da pilha!";
		return 0;
	}
	no * top = pil->cabeca;
	int tmp = top->valor;
	pil->cabeca = top->proximo;
	delete(top);
	return tmp;
}

void printpilha(pilha * pil){
	no * tmp = pil->cabeca;
	while(tmp != nullptr){
		cout << tmp->valor << ", ";
		tmp = tmp->proximo;
	}
}

int topo(pilha * pil){
	if(pil->cabeca != nullptr){ 
		return (pil->cabeca)->valor;
	}
	return 0;
}

void cleanup(pilha * pil){
	no * atual =  pil->cabeca;
	no * anterior;
	delete(pil);
	while(atual != nullptr){
		anterior = atual;
		atual = atual->proximo;
		delete(anterior);
	}
	return;
}

int main(){
	pilha * pillz = new_pilha();
	add_to_pilha(pillz,666);
	add_to_pilha(pillz,667);
	add_to_pilha(pillz,668);
	printpilha(pillz);
	cout << "\ntopo: " << topo(pillz) << " desempilhar: " << desempilhar(pillz) << " topo: " << topo(pillz) << "\n";
	cleanup(pillz);
	cout << "topo: " << topo(pillz);
	return 0;
}