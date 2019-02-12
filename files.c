#include <stdio.h>

// struct FILE {
// 	tamanho;
// 	nome;
// 	ptr onde na memoria o arquivo foi carregado
// };

int main(){
	FILE * f;
	f = fopen("out.txt","r+");
	char buf[64];
	fgets(buf,64,f);
	printf("%s",buf);
	fclose(f)
	return 0;
}