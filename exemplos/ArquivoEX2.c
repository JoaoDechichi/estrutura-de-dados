#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *arquivo;
    int numero = 125;
    char palavra[] = "Esta eh uma frase que sera gravada no arquivo!";

    arquivo = fopen("saida.txt", "w");

    if(arquivo == NULL){
        printf("erro ao abrir o arquivo.\n");
        exit(1);
    }

    fprintf(arquivo, "numero: %d\nPalavra: %s\n", numero, palavra);

    return 0
}