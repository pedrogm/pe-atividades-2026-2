
#include <stdio.h>

#define MAX_CONTAS 100

typedef struct {
    int numero;
    char nome[100];
    char cpf[15];
    char telefone[20];
    float saldo;
} Conta;

int buscarConta(Conta contas[], int total, int numero);
void cadastrarConta(Conta contas[], int *total);
void consultarSaldo(Conta contas[], int total);
void fazerDeposito(Conta contas[], int total);
void fazerSaque(Conta contas[], int total);
void exibirContas(Conta contas[], int total);

int main() {
    Conta corrente[MAX_CONTAS];
    Conta poupanca[MAX_CONTAS];

    int totalCorrente = 0;
    int totalPoupanca = 0;
    int tipo, opcao;

    do {
        printf("\n===== BANCO DINHEIRO CERTO =====\n");
        printf("1 - Conta corrente\n");
        printf("2 - Conta poupanca\n");
        printf("0 - Sair\n");
        printf("Escolha o tipo de conta: ");
        scanf("%d", &tipo);

        if (tipo == 0) {
            printf("Encerrando o programa...\n");
            break;
        }

        if (tipo != 1 && tipo != 2) {
            printf("Tipo de conta invalido!\n");
            continue;
        }

        do {
            printf("\n===== MENU DE CONTAS =====\n");
            printf("1 - Cadastrar conta\n");
            printf("2 - Consultar saldo\n");
            printf("3 - Fazer deposito\n");
            printf("4 - Fazer saque\n");
            printf("5 - Exibir contas\n");
            printf("0 - Voltar\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    if (tipo == 1)
                        cadastrarConta(corrente, &totalCorrente);
                    else
                        cadastrarConta(poupanca, &totalPoupanca);
                    break;

                case 2:
                    if (tipo == 1)
                        consultarSaldo(corrente, totalCorrente);
                    else
                        consultarSaldo(poupanca, totalPoupanca);
                    break;

                case 3:
                    if (tipo == 1)
                        fazerDeposito(corrente, totalCorrente);
                    else
                        fazerDeposito(poupanca, totalPoupanca);
                    break;

                case 4:
                    if (tipo == 1)
                        fazerSaque(corrente, totalCorrente);
                    else
                        fazerSaque(poupanca, totalPoupanca);
                    break;

                case 5:
                    if (tipo == 1)
                        exibirContas(corrente, totalCorrente);
                    else
                        exibirContas(poupanca, totalPoupanca);
                    break;

                case 0:
                    printf("Voltando ao menu principal...\n");
                    break;

                default:
                    printf("Opcao invalida!\n");
            }

        } while (opcao != 0);

    } while (tipo != 0);

    return 0;
}

int buscarConta(Conta contas[], int total, int numero) {
    if (total == 0) {
        return -1;
    }

    for (int i = 0; i < total; i++) {
        if (contas[i].numero == numero) {
            return i;
        }
    }

    return -2;
}

void cadastrarConta(Conta contas[], int *total) {
    if (*total >= MAX_CONTAS) {
        printf("Limite de contas atingido!\n");
        return;
    }

    int numero;

    printf("Numero da conta: ");
    scanf("%d", &numero);

    if (buscarConta(contas, *total, numero) >= 0) {
        printf("Esse numero de conta ja esta cadastrado!\n");
        return;
    }

    contas[*total].numero = numero;

    printf("Nome do titular: ");
    scanf(" %99[^\n]", contas[*total].nome);

    printf("CPF: ");
    scanf(" %14s", contas[*total].cpf);

    printf("Telefone: ");
    scanf(" %19s", contas[*total].telefone);

    printf("Saldo inicial: ");
    scanf("%f", &contas[*total].saldo);

    if (contas[*total].saldo < 0) {
        printf("Saldo invalido!\n");
        return;
    }

    (*total)++;

    printf("Conta cadastrada com sucesso!\n");
}

void consultarSaldo(Conta contas[], int total) {
    int numero;

    printf("Numero da conta: ");
    scanf("%d", &numero);

    int posicao = buscarConta(contas, total, numero);

    if (posicao < 0) {
        printf("Conta nao cadastrada.\n");
        return;
    }

    printf("Saldo da conta: R$ %.2f\n", contas[posicao].saldo);
}

void fazerDeposito(Conta contas[], int total) {
    int numero;
    float valor;

    printf("Numero da conta: ");
    scanf("%d", &numero);

    int posicao = buscarConta(contas, total, numero);

    if (posicao < 0) {
        printf("Conta nao cadastrada.\n");
        return;
    }

    printf("Valor do deposito: ");
    scanf("%f", &valor);

    if (valor <= 0) {
        printf("Valor de deposito invalido!\n");
        return;
    }

    contas[posicao].saldo += valor;

    printf("Deposito realizado com sucesso!\n");
    printf("Novo saldo: R$ %.2f\n", contas[posicao].saldo);
}

void fazerSaque(Conta contas[], int total) {
    int numero;
    float valor;

    printf("Numero da conta: ");
    scanf("%d", &numero);

    int posicao = buscarConta(contas, total, numero);

    if (posicao < 0) {
        printf("Conta nao cadastrada.\n");
        return;
    }

    printf("Valor do saque: ");
    scanf("%f", &valor);

    if (valor <= 0) {
        printf("Valor de saque invalido!\n");
        return;
    }

    if (valor <= contas[posicao].saldo) {
        contas[posicao].saldo -= valor;

        printf("Saque realizado com sucesso!\n");
        printf("Novo saldo: R$ %.2f\n", contas[posicao].saldo);
    } else {
        printf("Saldo insuficiente!\n");
    }
}

void exibirContas(Conta contas[], int total) {
    if (total == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }

    printf("\n===== CONTAS CADASTRADAS =====\n");

    for (int i = 0; i < total; i++) {
        printf("\nNumero da conta: %d\n", contas[i].numero);
        printf("Nome do titular: %s\n", contas[i].nome);
        printf("CPF: %s\n", contas[i].cpf);
        printf("Telefone: %s\n", contas[i].telefone);
    }
}

