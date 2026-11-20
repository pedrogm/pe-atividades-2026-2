
#include <stdio.h>
#include <string.h>

#define TAM_CONTAS 50
#define TAM_OPERACOES 10000

struct Conta {
    int id;
    char cliente[40];
    double saldo;
    double limite;
};

struct Operacao {
    int id;
    int idConta;
    char tipo;
    double valor;
};

int buscald(struct Conta v[], int tam, int x);


// QUESTAO 1

void cadastraConta(struct Conta v[], int *tam) {
    int id;

    if (*tam >= TAM_CONTAS) {
        printf("Vetor cheio!\n");
        return;
    }

    printf("Digite o ID da conta: ");
    scanf("%d", &id);

    if (id < 0 || buscald(v, *tam, id) != -1) {
        printf("ID invalido ou ja cadastrado!\n");
        return;
    }

    v[*tam].id = id;

    printf("Nome do cliente: ");
    scanf(" %[^\n]", v[*tam].cliente);

    printf("Saldo inicial: ");
    scanf("%lf", &v[*tam].saldo);

    printf("Limite da conta: ");
    scanf("%lf", &v[*tam].limite);

    if (v[*tam].limite < 0) {
        printf("Limite negativo!\n");
        return;
    }

    (*tam)++;
}


// QUESTAO 2

int buscaBinariaNome(struct Conta v[], int tam, char x[]) {
    int inicio = 0;
    int fim = tam - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        if (strcmp(v[meio].cliente, x) == 0) {
            return meio;
        }

        if (strcmp(v[meio].cliente, x) < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}


// QUESTAO 3

void filtraDevedores(struct Conta vContas[], int tamConta,
                     struct Conta vDevedores[], int *tamDevedores) {

    int i;

    *tamDevedores = 0;

    for (i = 0; i < tamConta; i++) {
        if (vContas[i].saldo < 0) {
            vDevedores[*tamDevedores] = vContas[i];
            (*tamDevedores)++;
        }
    }
}


// QUESTAO 4

int realizarSaque(struct Conta vContas[], int tamConta,
                  struct Operacao vOp[], int *tamOp) {

    int id;
    int pos;
    double valor;

    printf("Digite o ID da conta: ");
    scanf("%d", &id);

    pos = buscald(vContas, tamConta, id);

    if (pos == -1) {
        printf("Conta nao encontrada!\n");
        return 0;
    }

    printf("Digite o valor do saque: ");
    scanf("%lf", &valor);

    if (vContas[pos].saldo + vContas[pos].limite < valor) {
        printf("Saldo insuficiente!\n");
        return 0;
    }

    vContas[pos].saldo -= valor;

    vOp[*tamOp].id = *tamOp + 1;
    vOp[*tamOp].idConta = id;
    vOp[*tamOp].tipo = 'S';
    vOp[*tamOp].valor = -valor;

    (*tamOp)++;

    return 1;
}


// QUESTAO 5

void extrato(struct Conta vContas[], int tamConta,
             struct Operacao vOp[], int *tamOp) {

    int id;
    int pos;
    int i, j;
    int ultimas[5];
    int qtd = 0;
    int primeira;
    double saldo = 0;
    double valor;

    printf("Digite o ID da conta: ");
    scanf("%d", &id);

    pos = buscald(vContas, tamConta, id);

    if (pos == -1) {
        printf("Conta nao encontrada!\n");
        return;
    }

    for (i = *tamOp - 1; i >= 0 && qtd < 5; i--) {
        if (vOp[i].idConta == id) {
            ultimas[qtd] = i;
            qtd++;
        }
    }

    if (qtd > 0) {
        primeira = ultimas[qtd - 1];

        for (i = 0; i < primeira; i++) {
            if (vOp[i].idConta == id) {
                saldo += vOp[i].valor;
            }
        }
    }

    printf("\n");
    printf("-----------------------------------------------\n");
    printf("                    CONTA\n");
    printf("-----------------------------------------------\n");
    printf("CLIENTE: %s\n", vContas[pos].cliente);
    printf("ID: %d\n", vContas[pos].id);
    printf("-----------------------------------------------\n");
    printf("ID OPERACAO       VALOR          SALDO\n");

    printf("Saldo Anterior:              %.2f%c\n",
           saldo >= 0 ? saldo : -saldo,
           saldo >= 0 ? 'C' : 'D');

    for (j = qtd - 1; j >= 0; j--) {
        i = ultimas[j];

        valor = vOp[i].valor;
        saldo += valor;

        printf("%03d %-12s %10.2f%c %10.2f%c\n",
               vOp[i].id,
               vOp[i].tipo == 'D' ? "Deposito" :
               vOp[i].tipo == 'S' ? "Saque" :
               "Transferencia",
               valor >= 0 ? valor : -valor,
               valor >= 0 ? 'C' : 'D',
               saldo >= 0 ? saldo : -saldo,
               saldo >= 0 ? 'C' : 'D');
    }

    printf("-----------------------------------------------\n");
    printf("Saldo Atual:                 %.2f%c\n",
           saldo >= 0 ? saldo : -saldo,
           saldo >= 0 ? 'C' : 'D');

    printf("-----------------------------------------------\n");
}

