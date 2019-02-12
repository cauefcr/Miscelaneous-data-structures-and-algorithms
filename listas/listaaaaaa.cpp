#include <iostream>

using namespace std;

typedef struct no {
	int chave;
	struct no * proximo;
	float nota;
}no;

typedef struct lista{
	no * cabeca;
}lista;

typedef struct aluno{
	int chave;
	float nota;
}aluno;

no * novo_no(int key,float grade){
	// no * novo = new(no);
	no * novo = new no();
	novo->chave = key;
	novo->nota = grade;
	return novo;
}

void colocar(lista * lst, int key, float grade){
	no * atual = lst->cabeca;
	no * antigo = atual;
	no * novo = novo_no(key, grade);
	if(atual == nullptr){//se a lista estiver vazia 
		lst->cabeca = novo;
		return;
	}
	while (atual != nullptr){ //todos os casos antes de ele ser o ultimo
		if (atual->chave == key){
			atual->nota = grade;
			delete(novo); //sem vazar essa memória
			return;
		}
		if (atual->chave > key) {
			novo->proximo = atual;
			if(antigo == atual){
				lst->cabeca = novo;
			}else{
				antigo->proximo = novo; 
			}
			return;
		}
		antigo = atual;
		atual = atual->proximo;
	}//passou a lista toda, então coloca no ultimo elemento;
	antigo->proximo = novo;
	return;
}

int tamanho(lista * lst){
	int i = 1;
	no * tmp = lst->cabeca;
	while(tmp->proximo != nullptr){
		i++;
		tmp = tmp->proximo;
	}
	return i;
}

//Se a lista tiver 0 elementos a 
//função explode, pois dereferencia nulo
//(primeira iteração tmp->chave onde tmp == nulptr)
void printlista(lista * lst){
	no * tmp = lst->cabeca;
	int i = 0;
	if (tmp!=nullptr) {
		do{
			cout << " {" << tmp->chave << "} : " << tmp->nota 
				 << ",";//pra ficar bonitinho no final
			tmp = tmp->proximo;
			i++;
		}while(tmp != nullptr);
	}
	cout << " tamanho: " << i << endl;
}

lista * vetor_para_ligada(aluno vec[],int tam){
	// lista * lst = new(lista);
	lista * lst = new lista();

	for(int i = 0; i<tam; i++){
		colocar(lst,vec[i].chave,vec[i].nota);
	}
	return lst;
}

void kill_list(lista * lst){
	no * liberar = lst->cabeca;
	delete(lst);
	
	//lista tem 0 elementos:
	if (liberar == nullptr) {
		return;
	}

	no * curr;
	do{
		curr = liberar->proximo; 
		delete(liberar);
		liberar = curr;
	}while(curr != nullptr);
}

//a forma que acho mais simples
void assassinate_list(lista * lst){
	no * atual = lst->cabeca;
	delete(lst);
	while (atual != nullptr) {
		no* liberar = atual;
		atual = atual->proximo;
		delete(liberar);
	}	
}

int main(){
	//1
	// lista * list = new(lista);
	lista * list = new lista();

//	cout << "Criando lista:\n";
	colocar(list,183,9.5);
	colocar(list,125,6.2);
	colocar(list,210,8.8);
	colocar(list,90,5.3);
	colocar(list,125,7.8);
	cout << "Imprimindo lista:\n";
	printlista(list);
	//limpar a lista aqui gera um segfault, what
	assassinate_list(list); 

	//2
	aluno vetor[] = {
		{183,9.5},
		{125,6.2},
		{210,8.8},
		{ 90,5.3},
		{125,7.8}
	}; 
	lista * list2 = vetor_para_ligada(vetor,5);
	printlista(list2);
	cout << "tamanho da lista: " << tamanho(list2) << "\n"; //3
	assassinate_list(list2); //finalizando tudo bonitinho;
//	kill_list(list2);
}