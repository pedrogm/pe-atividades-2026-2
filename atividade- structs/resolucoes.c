```c
#include <stdio.h>
#include <string.h>
#include <math.h>

// Estrutura QUESTÃO 1
typedef struct {
    int hora;
    int minutos;
    int segundos;
} Horario;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    Data data;
    Horario horario;
    char descricao[100];
} Compromisso;

// Estrutura QUESTÃO 2
typedef struct {
    char nome[50];
    int idade;
    char endereco[100];
} Pessoa;

// Estrutura QUESTÃO 3
struct VetorR3 {
    double x;
    double y;
    double z;
};

struct VetorR3 somarVetores(struct VetorR3 v1, struct VetorR3 v2) {
    struct VetorR3 resultado;
    resultado.x = v1.x + v2.x;
    resultado.y = v1.y + v2.y;
    resultado.z = v1.z + v2.z;
    return resultado;
}

// Estrutura QUESTÃO 4
typedef struct {
    double r; // Raio
    double a; // Argumento em radianos
} Polar;

typedef struct {
    double x;
    double y;
} Cartesiana;

int main() {
    int opcao;

    do {
        printf("\n===============================\n");
        printf("       MENU DE ATIVIDADES      \n");
        printf("===============================\n");
        printf("1. Questao 1 (Tipos: Horario, Data, Compromisso)\n");
        printf("2. Questao 2 (Ler dados de uma Pessoa)\n");
        printf("3. Questao 3 (Soma de vetores no R3)\n");
        printf("4. Questao 4 (Conversao Polar para Cartesiana)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do enter

        switch (opcao) {
            case 1: {
                printf("\n--- EXECUTANDO QUESTAO 1 ---\n");

                Horario h = {14, 30, 0};
                Data d = {24, 5, 2026};
                Compromisso c = {d, h, "Aula de Estrutura de Dados"};

                printf("Compromisso cadastrado com sucesso!\n");
                printf("Data: %02d/%02d/%d\n", c.data.dia, c.data.mes, c.data.ano);
                printf("Horario: %02d:%02d:%02d\n", c.horario.hora, c.horario.minutos, c.horario.segundos);
                printf("Descricao: %s\n", c.descricao);
                break;
            }

            case 2: {
                printf("\n--- EXECUTANDO QUESTAO 2 ---\n");
                Pessoa p;

                printf("Digite o nome: ");
                fgets(p.nome, 50, stdin);
                p.nome[strcspn(p.nome, "\n")] = '\0';

                printf("Digite a idade: ");
                scanf("%d", &p.idade);
                getchar(); // Limpa o buffer

                printf("Digite o endereco: ");
                fgets(p.endereco, 100, stdin);
                p.endereco[strcspn(p.endereco, "\n")] = '\0';

                printf("\n--- Dados Armazenados ---\n");
                printf("Nome: %s\n", p.nome);
                printf("Idade: %d\n", p.idade);
                printf("Endereco: %s\n", p.endereco);
                break;
            }

            case 3: {
                printf("\n--- EXECUTANDO QUESTAO 3 ---\n");
                struct VetorR3 v1, v2, soma;

                printf("Digite as coordenadas do primeiro vetor (x y z): ");
                scanf("%lf %lf %lf", &v1.x, &v1.y, &v1.z);

                printf("Digite as coordenadas do segundo vetor (x y z): ");
                scanf("%lf %lf %lf", &v2.x, &v2.y, &v2.z);

                soma = somarVetores(v1, v2);

                printf("Vetor Soma: (%.2lf, %.2lf, %.2lf)\n", soma.x, soma.y, soma.z);
                break;
            }

            case 4: {
                printf("\n--- EXECUTANDO QUESTAO 4 ---\n");
                Polar pPolar;
                Cartesiana pCartesiana;

                printf("Digite o raio (r): ");
                scanf("%lf", &pPolar.r);

                printf("Digite o argumento em radianos (a): ");
                scanf("%lf", &pPolar.a);

                pCartesiana.x = pPolar.r * cos(pPolar.a);
                pCartesiana.y = pPolar.r * sin(pPolar.a);

                printf("Coordenadas Cartesianas correspondentes:\n");
                printf("x = %.2lf\n", pCartesiana.x);
                printf("y = %.2lf\n", pCartesiana.y);
                break;
            }

            case 0:
                printf("\nEncerrando o programa. Ate mais!\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n');
        }

    } while (opcao != 0);

    return 0;
}
```
