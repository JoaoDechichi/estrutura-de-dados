#include <stdio.h>

int main()
{
    // Exemplo de uma matriz de inteiros 2x3

    int matriz[2][3] = {
        {1, 2, 3},
        {4, 5, 6}};

    int soma = 0;

    // Acessando o ultimo elemento

    printf("Elemento da 2a linha 3a coluna: %d\n", matriz[1][2]);

    // somando todos os elementos da matriz

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            soma = soma + matriz[i][j];
         
         printf("a soma dos elementos eh %d\n", soma);
         

         return 0;
}