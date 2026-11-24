#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQ_VIDEOS   "videos.dat"
#define ARQ_USUARIOS "usuarios.dat"
#define MAX_FAV 10
#define TAM_STR 50

typedef struct {
    int  id;
    char titulo[TAM_STR];
    char genero[30];
    int  duracao;
    int  ano;
} Video;

typedef struct {
    int  id;
    char nome[TAM_STR];
    int  qtd_fav;
    int  favoritos[MAX_FAV];
} Usuario;

void ler_texto(const char *msg, char *dest, int tam) {
    printf("%s", msg);
    fgets(dest, tam, stdin);
    dest[strcspn(dest, "\n")] = '\0';
}

int ler_int(const char *msg) {
    char buf[32];
    printf("%s", msg);
    fgets(buf, sizeof(buf), stdin);
    return atoi(buf);
}

int proximo_id(const char *arq, size_t tam) {
    FILE *f = fopen(arq, "rb");
    if (f == NULL) return 1;
    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0) { fclose(f); return 1; }
    fseek(f, -(long)tam, SEEK_END);
    int id;
    fread(&id, sizeof(int), 1, f);
    fclose(f);
    return id + 1;
}

void anexar(const char *arq, const void *reg, size_t tam) {
    FILE *f = fopen(arq, "ab");
    if (f == NULL) { printf("Erro ao abrir %s\n", arq); return; }
    fwrite(reg, tam, 1, f);
    fclose(f);
}

long buscar(const char *arq, size_t tam, int id, void *out) {
    FILE *f = fopen(arq, "rb");
    if (f == NULL) return -1;
    long pos = 0;
    while (fread(out, tam, 1, f) == 1) {
        if (*(int *)out == id) { fclose(f); return pos; }
        pos++;
    }
    fclose(f);
    return -1;
}

void gravar_em(const char *arq, size_t tam, long pos, const void *reg) {
    FILE *f = fopen(arq, "r+b");
    if (f == NULL) return;
    fseek(f, pos * (long)tam, SEEK_SET);
    fwrite(reg, tam, 1, f);
    fclose(f);
}

int remover(const char *arq, size_t tam, int id) {
    FILE *orig = fopen(arq, "rb");
    if (orig == NULL) return 0;
    FILE *novo = fopen("temp.dat", "wb");
    if (novo == NULL) { fclose(orig); return 0; }

    void *buf = malloc(tam);
    int achou = 0;
    while (fread(buf, tam, 1, orig) == 1) {
        if (*(int *)buf == id) achou = 1;
        else fwrite(buf, tam, 1, novo);
    }
    free(buf);
    fclose(orig);
    fclose(novo);

    remove(arq);
    rename("temp.dat", arq);
    return achou;
}

void imprimir_video(const Video *v) {
    printf("ID %d | %s | %s | %d min | %d\n",
           v->id, v->titulo, v->genero, v->duracao, v->ano);
}

void cadastrar_video(void) {
    Video v;
    v.id = proximo_id(ARQ_VIDEOS, sizeof(Video));
    ler_texto("Titulo: ", v.titulo, TAM_STR);
    ler_texto("Genero: ", v.genero, 30);
    v.duracao = ler_int("Duracao (min): ");
    v.ano     = ler_int("Ano: ");
    anexar(ARQ_VIDEOS, &v, sizeof(Video));
    printf("Video cadastrado com ID %d.\n", v.id);
}

void listar_videos(void) {
    FILE *f = fopen(ARQ_VIDEOS, "rb");
    if (f == NULL) { printf("Nenhum video cadastrado.\n"); return; }
    Video v;
    printf("\n--- VIDEOS ---\n");
    while (fread(&v, sizeof(Video), 1, f) == 1) imprimir_video(&v);
    fclose(f);
}

void buscar_video(void) {
    Video v;
    int id = ler_int("ID do video: ");
    if (buscar(ARQ_VIDEOS, sizeof(Video), id, &v) >= 0) imprimir_video(&v);
    else printf("Video nao encontrado.\n");
}

void atualizar_video(void) {
    Video v;
    int id = ler_int("ID do video a atualizar: ");
    long pos = buscar(ARQ_VIDEOS, sizeof(Video), id, &v);
    if (pos < 0) { printf("Video nao encontrado.\n"); return; }
    ler_texto("Novo titulo: ", v.titulo, TAM_STR);
    ler_texto("Novo genero: ", v.genero, 30);
    v.duracao = ler_int("Nova duracao (min): ");
    v.ano     = ler_int("Novo ano: ");
    gravar_em(ARQ_VIDEOS, sizeof(Video), pos, &v);
    printf("Video atualizado.\n");
}

void limpar_favorito_removido(int id_video) {
    FILE *f = fopen(ARQ_USUARIOS, "r+b");
    if (f == NULL) return;
    Usuario u;
    while (fread(&u, sizeof(Usuario), 1, f) == 1) {
        int mudou = 0;
        for (int i = 0; i < u.qtd_fav; i++) {
            if (u.favoritos[i] == id_video) {
                for (int j = i; j < u.qtd_fav - 1; j++)
                    u.favoritos[j] = u.favoritos[j + 1];
                u.qtd_fav--;
                mudou = 1;
                break;
            }
        }
        if (mudou) {
            fseek(f, -(long)sizeof(Usuario), SEEK_CUR);
            fwrite(&u, sizeof(Usuario), 1, f);
            fseek(f, 0, SEEK_CUR);
        }
    }
    fclose(f);
}

void remover_video(void) {
    int id = ler_int("ID do video a remover: ");
    if (remover(ARQ_VIDEOS, sizeof(Video), id)) {
        limpar_favorito_removido(id);
        printf("Video removido.\n");
    } else printf("Video nao encontrado.\n");
}

void imprimir_usuario(const Usuario *u) {
    printf("ID %d | %s | %d favorito(s)\n", u->id, u->nome, u->qtd_fav);
}

void cadastrar_usuario(void) {
    Usuario u;
    u.id = proximo_id(ARQ_USUARIOS, sizeof(Usuario));
    ler_texto("Nome: ", u.nome, TAM_STR);
    u.qtd_fav = 0;
    memset(u.favoritos, 0, sizeof(u.favoritos));
    anexar(ARQ_USUARIOS, &u, sizeof(Usuario));
    printf("Usuario cadastrado com ID %d.\n", u.id);
}

void listar_usuarios(void) {
    FILE *f = fopen(ARQ_USUARIOS, "rb");
    if (f == NULL) { printf("Nenhum usuario cadastrado.\n"); return; }
    Usuario u;
    printf("\n--- USUARIOS ---\n");
    while (fread(&u, sizeof(Usuario), 1, f) == 1) imprimir_usuario(&u);
    fclose(f);
}

void buscar_usuario(void) {
    Usuario u;
    int id = ler_int("ID do usuario: ");
    if (buscar(ARQ_USUARIOS, sizeof(Usuario), id, &u) >= 0) imprimir_usuario(&u);
    else printf("Usuario nao encontrado.\n");
}

void atualizar_usuario(void) {
    Usuario u;
    int id = ler_int("ID do usuario a atualizar: ");
    long pos = buscar(ARQ_USUARIOS, sizeof(Usuario), id, &u);
    if (pos < 0) { printf("Usuario nao encontrado.\n"); return; }
    ler_texto("Novo nome: ", u.nome, TAM_STR);
    gravar_em(ARQ_USUARIOS, sizeof(Usuario), pos, &u);
    printf("Usuario atualizado.\n");
}

void remover_usuario(void) {
    int id = ler_int("ID do usuario a remover: ");
    if (remover(ARQ_USUARIOS, sizeof(Usuario), id)) printf("Usuario removido.\n");
    else printf("Usuario nao encontrado.\n");
}

void favoritar_video(void) {
    Usuario u;
    Video v;
    int id_u = ler_int("ID do usuario: ");
    long pos = buscar(ARQ_USUARIOS, sizeof(Usuario), id_u, &u);
    if (pos < 0) { printf("Usuario nao encontrado.\n"); return; }

    int id_v = ler_int("ID do video a favoritar: ");
    if (buscar(ARQ_VIDEOS, sizeof(Video), id_v, &v) < 0) {
        printf("Video nao encontrado.\n"); return;
    }
    if (u.qtd_fav >= MAX_FAV) { printf("Limite de favoritos atingido.\n"); return; }
    for (int i = 0; i < u.qtd_fav; i++)
        if (u.favoritos[i] == id_v) { printf("Ja e favorito.\n"); return; }

    u.favoritos[u.qtd_fav++] = id_v;
    gravar_em(ARQ_USUARIOS, sizeof(Usuario), pos, &u);
    printf("'%s' adicionado aos favoritos de %s.\n", v.titulo, u.nome);
}

void relatorio_favoritos(void) {
    FILE *f = fopen(ARQ_USUARIOS, "rb");
    if (f == NULL) { printf("Nenhum usuario cadastrado.\n"); return; }
    Usuario u;
    Video v;
    printf("\n--- RELATORIO: USUARIOS E FAVORITOS ---\n");
    while (fread(&u, sizeof(Usuario), 1, f) == 1) {
        printf("\n%s (ID %d):\n", u.nome, u.id);
        if (u.qtd_fav == 0) printf("  (sem favoritos)\n");
        for (int i = 0; i < u.qtd_fav; i++) {
            if (buscar(ARQ_VIDEOS, sizeof(Video), u.favoritos[i], &v) >= 0)
                printf("  - %s (%s, %d)\n", v.titulo, v.genero, v.ano);
            else
                printf("  - [video ID %d nao existe mais]\n", u.favoritos[i]);
        }
    }
    fclose(f);
}

int main(void) {
    int op;
    do {
        printf("\n===== STREAMING =====\n");
        printf(" 1 - Cadastrar video\n");
        printf(" 2 - Cadastrar usuario\n");
        printf(" 3 - Listar videos\n");
        printf(" 4 - Listar usuarios\n");
        printf(" 5 - Buscar video por ID\n");
        printf(" 6 - Buscar usuario por ID\n");
        printf(" 7 - Atualizar video\n");
        printf(" 8 - Atualizar usuario\n");
        printf(" 9 - Favoritar video para usuario\n");
        printf("10 - Remover video\n");
        printf("11 - Remover usuario\n");
        printf("12 - Relatorio: usuarios e videos favoritos\n");
        printf(" 0 - Sair\n");
        op = ler_int("Opcao: ");

        switch (op) {
            case 1:  cadastrar_video();      break;
            case 2:  cadastrar_usuario();    break;
            case 3:  listar_videos();        break;
            case 4:  listar_usuarios();      break;
            case 5:  buscar_video();         break;
            case 6:  buscar_usuario();       break;
            case 7:  atualizar_video();      break;
            case 8:  atualizar_usuario();    break;
            case 9:  favoritar_video();      break;
            case 10: remover_video();        break;
            case 11: remover_usuario();      break;
            case 12: relatorio_favoritos();  break;
            case 0:  printf("Ate logo!\n");  break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0);
    return 0;
}
