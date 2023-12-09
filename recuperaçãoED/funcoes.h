#ifndef FUNCOES_H
#define FUNCOES_H

struct Produto {
    double VUnitario;
    double PMensal[12];
    double TAnual;
    double VAnual;
};

void GerarSaida(char *nomeArquivo, double matriz[12][14]);
void MatrizFinal(double matriz[12][14], int producao[10][12], double VUnitario[10]);
void LerProducaoSemest(char *nomeArquivo, int producao[10][6]);
void LerVUnitarios(double valores[10]);
double MaiorVColuna(double matriz[12][14], int ncol);
double MenorVColuna(double matriz[12][14], int ncol);
double MaiorVLinha(double matriz[12][14], int nlin);
double MenorVLinha(double matriz[12][14], int nlin);

#endif
