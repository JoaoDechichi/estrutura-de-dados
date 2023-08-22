#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *arquivo;
    arquivo=fopen("arquivo.txt", "wb");

    if(arquivo == NULL){
        printf("erro ao abrir o arquivo.\n");
        exit(1);
    }
    
    fclose(arquivo);
    return 0;
}
