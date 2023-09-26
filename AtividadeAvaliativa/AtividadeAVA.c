#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_NOME 100
#define MAX_CURSO 100
#define MAX_NOTAS 10

typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_NOME];
    char curso[MAX_CURSO];
    float notas[MAX_NOTAS];
    float media;
    char situacao[20];
} Aluno;

int main() {
    FILE *entrada;
    FILE *saida;
    char linha[1024];
    Aluno alunos[MAX_ALUNOS];
    int numAlunos = 0;

    entrada = fopen("./DadosEntrada.csv", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), entrada) && numAlunos < MAX_ALUNOS) {
        char *token = strtok(linha, ",");
        if (token != NULL) {
            strncpy(alunos[numAlunos].nome, token, MAX_NOME);

            token = strtok(NULL, ",");
            if (token != NULL) {
                strncpy(alunos[numAlunos].telefone, token, MAX_NOME);

                token = strtok(NULL, ",");
                if (token != NULL) {
                    strncpy(alunos[numAlunos].curso, token, MAX_CURSO);

                    float somaNotas = 0.0;
                    int numNotas = 0;
                    token = strtok(NULL, ",");
                    while (token != NULL) {
                        float nota = atof(token);
                        alunos[numAlunos].notas[numNotas] = nota;
                        somaNotas += nota;
                        numNotas++;
                        token = strtok(NULL, ",");
                    }
                    if (numNotas > 0) {
                        // Alteração intencional para gerar erro
                        alunos[numAlunos].media = somaNotas / (numNotas - 1); // Subtrai 1 aqui

                        if (alunos[numAlunos].media >= 7.0) {
                            strcpy(alunos[numAlunos].situacao, "APROVADO");
                        } else {
                            strcpy(alunos[numAlunos].situacao, "REPROVADO");
                        }

                        numAlunos++;
                    }
                }
            }
        }
    }

    fclose(entrada);

    saida = fopen("SituacaoFinal.csv", "w");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        return 1;
    }

    for (int i = 0; i < numAlunos; i++) {
        fprintf(saida, "%s, %.2f, %s\n", alunos[i].nome, alunos[i].media, alunos[i].situacao);
    }

    fclose(saida);

    return 0;
}
