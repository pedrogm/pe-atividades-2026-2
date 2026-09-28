#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTD_COLUNAS 5

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void inverterSubcadeia(char str[], int inicio, int fim) {
    while (inicio < fim) {
        char temp = str[inicio];
        str[inicio] = str[fim];
        str[fim] = temp;
        inicio++;
        fim--;
    }
}
// a. remove elementos
int removerRepetidos(int v[], int tam) {
    if (tam <= 0) return 0;

    int k = 0;
    for (int i = 1; i < tam; i++) {
        if (v[i] != v[k]) {
            k++;
            v[k] = v[i];
        }
    }
    return k + 1;
}

// b. ordena usando bubble sort
void ordenar(int v[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
            }
        }
    }
}

// c. gera os primeiros tam números primos e guarda eles no vetor
void preencherPrimos(int v[], int tam) {
    if (tam <= 0) return;

    int cont = 0;
    int candidato = 2;

    while (cont < tam) {
        int ehPrimo = 1;

        for (int i = 0; i < cont; i++) {
            if (candidato % v[i] == 0) {
                ehPrimo = 0;
                break; 
            }
        }

        if (ehPrimo) {
            v[cont] = candidato;
            cont++;
        }
        candidato++;
    }
}

// d. preenche vetor v com o maior elemento de cada linha da matriz m
void maiorPorLinha(int m[][QTD_COLUNAS], int lin, int col, int v[]) {
    for (int i = 0; i < lin; i++) {
        int maior = m[i][0]; 
        for (int j = 1; j < col; j++) {
            if (m[i][j] > maior) {
                maior = m[i][j];
            }
        }
        v[i] = maior;
    }
}

// e. inverte as letras de cada palavra mantendo a posição dos espaços
void inverterPalavras(char str[]) {
    int inicio = 0;
    int i = 0;

    while (1) {
        if (str[i] == ' ' || str[i] == '\0') {
            inverterSubcadeia(str, inicio, i - 1);
            if (str[i] == '\0') break;
            inicio = i + 1;
        }
        i++;
    }
}

int main() {
    printf("--- TESTANDO AS FUNÇÕES DA PROVA ---\n\n");

    // teste item a
    int vA[] = {3, 3, 4, 5, 6, 6, 7};
    int tamA = 7;
    printf("[Item A] Vetor original: ");
    for(int i=0; i<tamA; i++) printf("%d ", vA[i]);
    
    int novoTam = removerRepetidos(vA, tamA);
    printf("\n[Item A] Novo tamanho: %d", novoTam);
    printf("\n[Item A] Vetor compactado: ");
    for(int i=0; i<novoTam; i++) printf("%d ", vA[i]);
    printf("\n\n--------------------------------------\n\n");

    // teste item b
    int vB[] = {9, 2, 7, 1, 5, 4};
    int tamB = 6;
    printf("[Item B] Vetor desordenado: ");
    for(int i=0; i<tamB; i++) printf("%d ", vB[i]);
    
    ordenar(vB, tamB);
    printf("\n[Item B] Vetor ordenado: ");
    for(int i=0; i<tamB; i++) printf("%d ", vB[i]);
    printf("\n\n--------------------------------------\n\n");

    // teste item c
    int tamC = 5;
    int vC[5];
    preencherPrimos(vC, tamC);
    printf("[Item C] Primos (tam=5): ");
    for(int i=0; i<tamC; i++) printf("%d ", vC[i]);
    printf("\n\n--------------------------------------\n\n");

    // teste item d
    int mat[3][QTD_COLUNAS] = {
        {10, 5, 20, -2, 14},
        {-5, -1, -12, -8, -30},mentos por linha: ");
    for(int i=0; i<3; i++) prin
        {100, 45, 12, 88, 99}
    };
    int vD[3];
    maiorPorLinha(mat, 3, 5, vD);
    printf("[Item D] Maiores eletf("%d ", vD[i]);
    printf("\n\n--------------------------------------\n\n");

    // teste item e
    char frase[] = "o rato roeu";
    printf("[Item E] Frase original: \"%s\"\n", frase);
    inverterPalavras(frase);
    printf("[Item E] Frase invertida: \"%s\"\n", frase);

    return 0;
}
