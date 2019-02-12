#include <stdio.h>
#include <stdlib.h>

void trocar(int * a, int * b){
    int c = *a;
    *a = *b;
    *b = c;
}

void imprimir(char * letra){
    printf("%c %i %i",*letra,*letra,letra);
}

int * criarVetorPonteiro(int tam){
    int * vec = (int *) calloc(tam,sizeof(int));
    return vec;
}

int guardarSomar(int N){
    int * vp = criarVetorPonteiro(N);
    int soma=0;
    for (int i = 0; i<N; i++){
        scanf(" %d",&vp[i]);
        soma+=vp[i];
    }
    free(vp);
    return soma;
}

int * dobrar(int * vetP, int tam){
    int * vr = (int *) calloc(tam*2,sizeof(int));
    for (int i = 0; i<tam;i++){
        vr[i]=vetP[i];
    }
    free(vetP);
    return vr;
}

int main(){
    int * vet = (int *) calloc(3,sizeof(int));
    for(int i = 0; i<3; i++){
        vet[i]=i;
    }
    vet = dobrar(vet,3);
    for(int i =0; i< 6; i++){
        printf("%d\n",vet[i]);
    }
}