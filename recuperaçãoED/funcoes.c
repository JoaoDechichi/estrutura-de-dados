#include "funcoes.h"
#include <math.h>
#include <stdio.h>

struct Produto {
    double VUnitario;
    double PMensal[12];
    double TAnual;
    double VAnual;
};


/*-----------------------------------------------------------
Protótipo: MatrizFinal(double matriz[12][14], int producao[10][12], double VUnitario[10])
Função: Calcula a matriz final com base nos dados de produção e valores unitários.
Entrada: Matriz de dados, matriz de produção e valores unitários.
Saída: Matriz de dados final
-----------------------------------------------------------*/
void MatrizFinal(double matriz[12][14], int producao[10][12], double VUnitario[10]) {
    struct Produto prod[10];

    for (int i = 0; i < 10; i++) {
        prod[i].VUnitario = VUnitario[i];
        prod[i].TAnual = 0.0;

        for (int j = 0; j < 12; j++) {
            prod[i].PMensal[j] = producao[i][j];

            prod[i].TAnual = prod[i].TAnual + (producao[i][j] * 1.0);
        }
        prod[i].VAnual = prod[i].TAnual * prod[i].VUnitario;
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 14; j++) {
            matriz[i][j] = 0.0;
        }
    }

    for (int prodInd = 0; prodInd < 10; prodInd++) {
        for (int mes = 0; mes < 12; mes++) {
            matriz[prodInd][mes] = prod[prodInd].PMensal[mes];
        }
    }

    double ATreais = 0.0;
    for (int prodInd = 0; prodInd < 10; prodInd++) {
        matriz[prodInd][12] = prod[prodInd].TAnual;
        matriz[prodInd][13] = prod[prodInd].VAnual;
        ATreais = ATreais + prod[prodInd].VAnual;
    }

    matriz[12][13] = ATreais;

    double produtosproduzAno = 0.0;
    for (int mes = 0; mes < 12; mes++) {
        double totalItensProduzidosNoMes = 0.0;
        double VProduzMes = 0.0;

        for (int prodInd = 0; prodInd < 10; prodInd++) {
            totalItensProduzidosNoMes = totalItensProduzidosNoMes + prod[prodInd].PMensal[mes];
            VProduzMes = VProduzMes + (prod[prodInd].PMensal[mes] * prod[prodInd].VUnitario);
        }

        matriz[10][mes] = totalItensProduzidosNoMes;
        produtosproduzAno = produtosproduzAno + totalItensProduzidosNoMes;
        matriz[11][mes] = VProduzMes;
    }

    matriz[10][12] = produtosproduzAno;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 14; j++) {
            printf("%lf ", matriz[i][j]);
        }
        printf("\n");
    }
}

/*-----------------------------------------------------------
Protótipo: LerProducaoSemest(char *nomeArquivo, int producao[10][6])
Função: Lê os dados de produção semestral a partir de um arquivo.
Entrada: Nome do arquivo e matriz de produção semestral.
Saída: Nenhuma
-----------------------------------------------------------*/
void LerProducaoSemest(char *nomeArquivo, int producao[10][6]) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo != NULL) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (fscanf(arquivo, "%d", &producao[i][j]) != 1) {
                    printf("Erro ao ler o arquivo %s\n", nomeArquivo);
                    fclose(arquivo);
                    return;
                }
            }
        }
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
    }
}


/*-----------------------------------------------------------
Protótipo: LerVUnitarios(double valores[10])
Função: Lê os valores unitários a partir de um arquivo.
Entrada: Vetor para armazenar os valores unitários.
Saída: Nenhuma
-----------------------------------------------------------*/
void LerVUniatrios(double valores[10]) {
    const char *nomesprod[10] = {
        "Sola inteira", "Meia sola", "Quarto de sola", "Entre sola", "Palmilha",
        "Meia palmilha", "Salto alto", "Salto médio", "Salto curto", "Salto baixo"};

    printf("Informe os valores unitários para cada produto:\n");
    for (int i = 0; i < 10; ++i) {
        printf("%s: ", nomesprod[i]);
        scanf("%lf", &valores[i]);
        printf("%lf: ", valores[i]);
    }
}

/*-----------------------------------------------------------
Protótipo: GerarSaida(char *nomeArquivo, double matriz[12][14])
Função: Gera o arquivo de saída conforme especificado.
Entrada: Nome do arquivo e a matriz de dados.
Saída: TXT final
-----------------------------------------------------------*/
void GerarSaida(char *nomeArquivo, double matriz[12][14]) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    const char *nomesprod[10] = {
        "Sola inteira", "Meia sola", "Quarto de sola", "Entre sola", "Palmilha",
        "Meia palmilha", "Salto alto", "Salto médio", "Salto curto", "Salto baixo"};
    const char *nomesMeses[12] = {
        "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

    if (arquivo != NULL) {
        int Maiorproduz = 0;
        int Menorproduz = 0;
        for (int i = 1; i < 10; ++i) {
            if (matriz[i][12] > matriz[Maiorproduz][12]) {
                Maiorproduz = i;
            }
            if (matriz[i][12] < matriz[Menorproduz][12]) {
                Menorproduz = i;
            }
        }

        fprintf(arquivo, "Produção anual total em unidades por produto\n");
        for (int i = 0; i < 10; ++i) {
            fprintf(arquivo, "%s: %d %s\n", nomesprod[i], (int)matriz[i][12], (i == Maiorproduz) ? "++" : ((i == Menorproduz) ? "--" : ""));
        }
        double TproducaoAnoUnit = 0.0;
        fprintf(arquivo, "Total: %d\n\n", (int)matriz[10][12]);

        fprintf(arquivo, "\nProdução anual total em reais por produto\n");
        for (int i = 0; i < 10; ++i) {
            fprintf(arquivo, "%s: %.2lf %s\n", nomesprod[i], matriz[i][13], (i == Maiorproduz) ? "++" : ((i == Menorproduz) ? "--" : ""));
        }
        fprintf(arquivo, "Total: %.2lf\n\n", matriz[12][13]);

        fprintf(arquivo, "Produção total mensal em unidades de prod\n");
        for (int j = 0; j < 12; ++j) {
            fprintf(arquivo, "%s: %d\n", nomesMeses[j], (int)matriz[10][j]);
        }
        fprintf(arquivo, "Total: %d\n\n", (int)matriz[10][12]);

        fprintf(arquivo, "Produção total mensal em reais por produto\n");
        for (int j = 0; j < 12; ++j) {
            fprintf(arquivo, "%s: %.2lf\n", nomesMeses[j], matriz[11][j]);
        }
        fprintf(arquivo, "Total: %.2lf\n", matriz[12][13]);

        fclose(arquivo);
    } else {
        printf("Erro ao criar o arquivo de saída %s\n", nomeArquivo);
    }
}


/*-----------------------------------------------------------
Protótipo: MaiorVColuna(double matriz[12][14], int ncol)
Função: Retorna o maior valor em uma coluna específica da matriz.
Entrada: Matriz de dados e número da coluna.
Saída: Maior valor da coluna
-----------------------------------------------------------*/
double MaiorVColuna(double matriz[12][14], int ncol) {
    double maior = matriz[0][ncol];
    for (int i = 1; i < 12; ++i) {
        if (matriz[i][ncol] > maior) {
            maior = matriz[i][ncol];
        }
    }
    return maior;
}

/*-----------------------------------------------------------
Protótipo: MenorVColuna(double matriz[12][14], int ncol)
Função: Retorna o menor valor em uma coluna específica da matriz.
Entrada: Matriz de dados e número da coluna.
Saída: Menor valor da coluna
-----------------------------------------------------------*/
double MenorVColuna(double matriz[12][14], int ncol) {
    double menor = matriz[0][ncol];
    for (int i = 1; i < 12; ++i) {
        if (matriz[i][ncol] < menor) {
            menor = matriz[i][ncol];
        }
    }
    return menor;
}


/*-----------------------------------------------------------
Protótipo: MaiorVLinha(double matriz[12][14], int nlin)
Função: Retorna o maior valor em uma linha específica da matriz.
Entrada: Matriz de dados e número da linha.
Saída: Maior valor da linha
-----------------------------------------------------------*/
double MaiorVLinha(double matriz[12][14], int nlin) {
    double maior = matriz[nlin][0];
    for (int j = 1; j < 14; ++j) {
        if (matriz[nlin][j] > maior) {
            maior = matriz[nlin][j];
        }
    }
    return maior;
}

/*-----------------------------------------------------------
Protótipo: MenorVLinha(double matriz[12][14], int nlin)
Função: Retorna o menor valor em uma linha específica da matriz.
Entrada: Matriz de dados e número da linha.
Saída: Menor valor da linha
-----------------------------------------------------------*/
double MenorVLinha(double matriz[12][14], int nlin) {
    double menor = matriz[nlin][0];
    for (int j = 1; j < 14; ++j) {
        if (matriz[nlin][j] < menor) {
            menor = matriz[nlin][j];
        }
    }
    return menor;
}


