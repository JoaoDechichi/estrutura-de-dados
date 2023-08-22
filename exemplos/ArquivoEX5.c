#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *arquivo;

     arquivo = fopen("saida.txt", "a");

    if(arquivo == NULL){
        printf("erro ao abrir o arquivo.\n");
        exit(1);
    }

    const char *mensagem = "\n segundo teste do exemplo numero 5";
    fputs(mensagem, arquivo);

    fclose(arquivo);

    return 0;
}