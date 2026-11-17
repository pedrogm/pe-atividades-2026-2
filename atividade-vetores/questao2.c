
#include <stdio.h>

#define MAX_PRODUTOS 100

typedef struct {
    int codigo;
    char descricao[100];
    float valorUnitario;
    int quantidade;
} Produto;

int buscarProduto(Produto produtos[], int total, int codigo);
void cadastrarProduto(Produto produtos[], int *total);
void alterarValor(Produto produtos[], int total);
float consultarValor(Produto produtos[], int total, int codigo);
int consultarEstoque(Produto produtos[], int total, int codigo);
void venderProduto(Produto produtos[], int total);
void atualizarEstoque(Produto produtos[], int total);
void exibirProdutos(Produto produtos[], int total);
void exibirProdutosSemEstoque(Produto produtos[], int total);

int main() {
    Produto produtos[MAX_PRODUTOS];
    int total = 0;
    int opcao;

    do {
        printf("\n===== PAPELARIA ESCOLAR =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Alterar valor unitario\n");
        printf("3 - Consultar valor do produto\n");
        printf("4 - Consultar estoque do produto\n");
        printf("5 - Vender produto\n");
        printf("6 - Atualizar estoque\n");
        printf("7 - Exibir todos os produtos\n");
        printf("8 - Exibir produtos sem estoque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &total);
                break;

            case 2:
                alterarValor(produtos, total);
                break;

            case 3: {
                int codigo;
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);

                float valor = consultarValor(produtos, total, codigo);

                if (valor >= 0)
                    printf("Valor unitario: R$ %.2f\n", valor);
                else
                    printf("Produto nao encontrado.\n");
                break;
            }

            case 4: {
                int codigo;
                printf("Digite o codigo do produto: ");
                scanf("%d", &codigo);

                int quantidade = consultarEstoque(produtos, total, codigo);

                if (quantidade >= 0)
                    printf("Quantidade em estoque: %d\n", quantidade);
                else
                    printf("Produto nao encontrado.\n");
                break;
            }

            case 5:
                venderProduto(produtos, total);
                break;

            case 6:
                atualizarEstoque(produtos, total);
                break;

            case 7:
                exibirProdutos(produtos, total);
                break;

            case 8:
                exibirProdutosSemEstoque(produtos, total);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

int buscarProduto(Produto produtos[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }

    return -1;
}

void cadastrarProduto(Produto produtos[], int *total) {
    if (*total >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    int codigo;

    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    if (buscarProduto(produtos, *total, codigo) != -1) {
        printf("Ja existe um produto com esse codigo!\n");
        return;
    }

    produtos[*total].codigo = codigo;

    printf("Descricao: ");
    scanf(" %99[^\n]", produtos[*total].descricao);

    printf("Valor unitario: ");
    scanf("%f", &produtos[*total].valorUnitario);

    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[*total].quantidade);

    (*total)++;

    printf("Produto cadastrado com sucesso!\n");
}

void alterarValor(Produto produtos[], int total) {
    int codigo;

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    int posicao = buscarProduto(produtos, total, codigo);

    if (posicao == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Novo valor unitario: ");
    scanf("%f", &produtos[posicao].valorUnitario);

    printf("Valor atualizado com sucesso!\n");
}

float consultarValor(Produto produtos[], int total, int codigo) {
    int posicao = buscarProduto(produtos, total, codigo);

    if (posicao == -1) {
        return -1;
    }

    return produtos[posicao].valorUnitario;
}

int consultarEstoque(Produto produtos[], int total, int codigo) {
    int posicao = buscarProduto(produtos, total, codigo);

    if (posicao == -1) {
        return -1;
    }

    return produtos[posicao].quantidade;
}

void venderProduto(Produto produtos[], int total) {
    int codigo, quantidade;

    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    int posicao = buscarProduto(produtos, total, codigo);

    if (posicao == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    if (produtos[posicao].quantidade == 0) {
        printf("Produto sem estoque!\n");
        return;
    }

    printf("Quantidade desejada: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    if (quantidade > produtos[posicao].quantidade) {
        char resposta;

        printf("Quantidade solicitada maior que o estoque.\n");
        printf("Deseja comprar as %d unidades disponiveis? (S/N): ",
               produtos[posicao].quantidade);
        scanf(" %c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            float valor = produtos[posicao].quantidade *
                          produtos[posicao].valorUnitario;

            produtos[posicao].quantidade = 0;

            printf("Venda realizada!\n");
            printf("Valor a pagar: R$ %.2f\n", valor);
        } else {
            printf("Compra cancelada.\n");
        }

    } else {
        float valor = quantidade * produtos[posicao].valorUnitario;

        produtos[posicao].quantidade -= quantidade;

        printf("Venda realizada!\n");
        printf("Valor a pagar: R$ %.2f\n", valor);
    }
}

void atualizarEstoque(Produto produtos[], int total) {
    int codigo, quantidade;

    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    int posicao = buscarProduto(produtos, total, codigo);

    if (posicao == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Nova quantidade em estoque: ");
    scanf("%d", &quantidade);

    if (quantidade < 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    produtos[posicao].quantidade = quantidade;

    printf("Estoque atualizado com sucesso!\n");
}

void exibirProdutos(Produto produtos[], int total) {
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n===== TODOS OS PRODUTOS =====\n");

    for (int i = 0; i < total; i++) {
        printf("\nCodigo: %d\n", produtos[i].codigo);
        printf("Descricao: %s\n", produtos[i].descricao);
        printf("Valor unitario: R$ %.2f\n",
               produtos[i].valorUnitario);
        printf("Quantidade em estoque: %d\n",
               produtos[i].quantidade);
    }
}

void exibirProdutosSemEstoque(Produto produtos[], int total) {
    int encontrou = 0;

    printf("\n===== PRODUTOS SEM ESTOQUE =====\n");

    for (int i = 0; i < total; i++) {
        if (produtos[i].quantidade == 0) {
            printf("Codigo: %d | Descricao: %s\n",
                   produtos[i].codigo,
                   produtos[i].descricao);

            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum produto sem estoque.\n");
    }
}

