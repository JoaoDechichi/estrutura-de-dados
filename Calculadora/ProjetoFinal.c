#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_EXP 100

typedef struct {
    double dados[MAX_EXP];
    int topo;
} Pilha;

typedef struct {
    Pilha pilha;
} Calculadora;

void inicializar(Pilha *pilha);
void empilhar(Pilha *pilha, double valor);
double desempilhar(Pilha *pilha);
double calcularLog(double valor);
double calcularSen(double valor);
double calcularCos(double valor);
double calcularTan(double valor);
double calcularPotencia(double base, double expoente);
double calcularRaiz(double valor);
double converterParaDouble(const char *expressao, int *posicao);
double avaliarExpressaoPosFixa(const char *expressao);

void inicializar(Pilha *pilha) {
    pilha->topo = -1;
}

void empilhar(Pilha *pilha, double valor) {
    if (pilha->topo < MAX_EXP - 1) {
        pilha->dados[++pilha->topo] = valor;
    } else {
        fprintf(stderr, "Erro: Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
}

double desempilhar(Pilha *pilha) {
    if (pilha->topo >= 0) {
        return pilha->dados[pilha->topo--];
    } else {
        fprintf(stderr, "Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

double calcularLog(double valor) {
    return log10(valor);
}

double calcularSen(double valor) {
    return sin(valor);
}

double calcularCos(double valor) {
    return cos(valor);
}

double calcularTan(double valor) {
    return tan(valor);
}

double calcularPotencia(double base, double expoente) {
    return pow(base, expoente);
}

double calcularRaiz(double valor) {
    return sqrt(valor);
}

double converterParaDouble(const char *expressao, int *posicao) {
    double resultado = 0.0;
    int pontoEncontrado = 0;
    int casasDecimais = 0;

    while (isdigit(expressao[*posicao]) || expressao[*posicao] == '.') {
        if (expressao[*posicao] == '.') {
            pontoEncontrado = 1;
        } else {
            resultado = resultado * 10 + (expressao[*posicao] - '0');
            if (pontoEncontrado) {
                casasDecimais++;
            }
        }
        (*posicao)++;
    }

    while (casasDecimais > 0) {
        resultado /= 10.0;
        casasDecimais--;
    }

    return resultado;
}

double avaliarExpressaoPosFixa(const char *expressao) {
    Calculadora calculadora;
    inicializar(&calculadora.pilha);

    for (int i = 0; expressao[i] != '\0'; ++i) {
        if (isdigit(expressao[i]) || (expressao[i] == '-' && isdigit(expressao[i + 1]))) {
            int posicao = i;
            double valor = converterParaDouble(expressao, &posicao);
            empilhar(&calculadora.pilha, valor);
            i = posicao - 1;
        } else if (expressao[i] == ' ' || expressao[i] == '\t') {
            continue;
        } else {
            double operando2, operando1;

            switch (expressao[i]) {
                case '+':
                    operando2 = desempilhar(&calculadora.pilha);
                    operando1 = desempilhar(&calculadora.pilha);
                    empilhar(&calculadora.pilha, operando1 + operando2);
                    break;
                case '-':
                    operando2 = desempilhar(&calculadora.pilha);
                    operando1 = desempilhar(&calculadora.pilha);
                    empilhar(&calculadora.pilha, operando1 - operando2);
                    break;
                case '*':
                    operando2 = desempilhar(&calculadora.pilha);
                    operando1 = desempilhar(&calculadora.pilha);
                    empilhar(&calculadora.pilha, operando1 * operando2);
                    break;
                case '/':
                    operando2 = desempilhar(&calculadora.pilha);
                    operando1 = desempilhar(&calculadora.pilha);
                    if (operando2 != 0.0) {
                        empilhar(&calculadora.pilha, operando1 / operando2);
                    } else {
                        fprintf(stderr, "Erro: Divisão por zero\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'l':
                    empilhar(&calculadora.pilha, calcularLog(desempilhar(&calculadora.pilha)));
                    break;
                case 's':
                    empilhar(&calculadora.pilha, calcularSen(desempilhar(&calculadora.pilha)));
                    break;
                case 'c':
                    empilhar(&calculadora.pilha, calcularCos(desempilhar(&calculadora.pilha)));
                    break;
                case 't':
                    empilhar(&calculadora.pilha, calcularTan(desempilhar(&calculadora.pilha)));
                    break;
                case '^':
                    operando2 = desempilhar(&calculadora.pilha);
                    operando1 = desempilhar(&calculadora.pilha);
                    empilhar(&calculadora.pilha, calcularPotencia(operando1, operando2));
                    break;
                case 'r':
                    empilhar(&calculadora.pilha, calcularRaiz(desempilhar(&calculadora.pilha)));
                    break;
                default:
                    fprintf(stderr, "Erro: Operador inválido\n");
                    exit(EXIT_FAILURE);
            }
        }
    }

    return desempilhar(&calculadora.pilha);
}

int main() {
    const char *expressoes[] = {
        "3 4 + 5 *",
        "7 2 * 4 +",
        "8 5 2 4 + * +",
        "6 2 / 3 + 4 *",
        "9 5 2 8 * 4 + * +",
        "2 3 + l 5 /",
        "10 l 3 ^ 2 + ",
        "45 60 + 30 c *",
        "0.5 45 s 2 ^ + ",
        "3 4 + 5 t *"
    };

    for (int i = 0; i < sizeof(expressoes) / sizeof(expressoes[0]); ++i) {
        double resultado = avaliarExpressaoPosFixa(expressoes[i]);
        printf("Teste %d: Resultado: %f\n", i + 1, resultado);
    }

    return 0;
}
