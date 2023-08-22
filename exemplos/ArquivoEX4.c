#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *arquivo;
    char linha[100];
    int i= 0;

     arquivo = fopen("dados.txt", "r");

    if(arquivo == NULL){
        printf("erro ao abrir o arquivo.\n");
        exit(1);
    }

    while(fgets(linha, 100, arquivo) != NULL){
        i++;
        printf("%d\t%s", i, linha);
    }

    fclose(arquivo);

    return 0;
}