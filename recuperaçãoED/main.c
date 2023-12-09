#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{
    int prodAno[10][12];
    int primeiroSemestre[10][6];
    int segundoSemestre[10][6];
    double valorPorProduto[10];
    double final[12][14];

    LerProducaoSemest("entrada.txt", primeiroSemestre);
    LerProducaoSemest("prod-2023-2.txt", segundoSemestre);

    for (int prodInd = 0; prodInd < 10; prodInd++)
    {
        for (int mes = 0; mes < 12; mes++)
        {
            if (mes < 6)
            {
                prodAno[prodInd][mes] = primeiroSemestre[prodInd][mes];
            }
            else
            {
                prodAno[prodInd][mes] = segundoSemestre[prodInd][mes - 6];
            }
        }
    }

    LerVUnitarios(valorPorProduto);
    MatrizFinal(final, prodAno, valorPorProduto);
    GerarSaida("2024-2023.txt", final);

    return 0;
}
