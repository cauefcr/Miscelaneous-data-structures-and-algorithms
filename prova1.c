#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(const char name[]){
	char nome[strlen(name)];
	for (int i =0; name[i]; i++){
		if (name[i] >= 'A' && name[i] <= 'Z'){
			nome[i] = name[i]+32;
		}
		else{
			nome[i] = name[i];
		}
	nome[i+1]=0;
	}
	int tam = strlen(name)-1;
	for(int i = 0; nome[i]; i++){
		if(nome[i] != nome[tam-i]){
			return false;
		}
	}
	return true;
}

typedef struct{
	int id;
	char nome[64];
	int ano;
}livro;

void printlivro(livro liv,int ln){
	printf("livro%d:\nid:%d, nome: %s, ano: %d\n\n",ln,liv.id,liv.nome,liv.ano);
}

void trocar_livro(livro *l1,livro *l2){
	livro tmp;
	tmp.id = l1->id;
	strcpy(tmp.nome,l1->nome);
	tmp.ano = l1->ano;
	
	l1->id=l2->id;
	strcpy(l1->nome,l2->nome);
	l1->ano = l2->ano;
	
	l2->id = tmp.id;
	strcpy(l2->nome,tmp.nome);
	l2->ano = tmp.ano;	
}

void procurar_livro_id(int procura, livro arr[], int tam){
	for (int i = 0; i<tam; i++){
		if(arr[i].id == procura){
			printf("Livro de ID %d encontrado: %s\n",procura,arr[i].nome);
			return;
		}
	}
	printf("O livro de ID %d não existe no acervo",procura);
}

//	gcc prova.c -o prova -std=c11
//	./prova 1 checa a questão 1
int main(int argc, char * argv[]){
	if (argc >1){
		int quest_num = atoi(argv[1]);
		if(quest_num <1 || quest_num>3){
			puts("So tem 3 questoes!");
			return -1;
		}
		//1
		if (quest_num == 1){
			printf("Arara é palindromo: %d, mas Araras não: %d\n",is_palindrome("Arara"),is_palindrome("Araras"));
		}
		//2
		if (quest_num == 2){
			livro livro1 = {1,"chocolate",2001};
			livro livro2 = {2,"marshmallow",2008};
			printlivro(livro1,1);
			printlivro(livro2,2);
			trocar_livro(&livro1,&livro2);
			printlivro(livro1,1);
			printlivro(livro2,2);
		}
		//3
		if (quest_num == 3){
			livro prateleira[4] = {
			{1,"chocolate",2001},
			{2,"marshmallow",2008},
			{3,"Harry Potter",1997},
			{4,"A Song Of Ice And Fire",1990}
			};
			procurar_livro_id(4,prateleira,4);
		}
	}
	else{
		puts("Utilização: \n./prova numero_da_questão");
	}
	return 0;
}
