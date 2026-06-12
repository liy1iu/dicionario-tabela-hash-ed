#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABELA 211
#define MAX_PAL 50
#define MAX_DEF 200

typedef struct Node {
    char palavra[MAX_PAL];
    char definicao[MAX_DEF];
    struct Node *prox;
} Node;

typedef struct {
    Node *tabela[TAM_TABELA];
    int totalElementos;
    int totalColisoes;
} TabelaHash;

unsigned int hash(const char *str) {
    unsigned int h = 0;
    while (*str) {
        h = h * 31 + (unsigned char)(*str);
        str++;
    }
    return h % TAM_TABELA;
}

TabelaHash* criarTabela() {
    TabelaHash *t = malloc(sizeof(TabelaHash));
    for (int i = 0; i < TAM_TABELA; i++)
        t->tabela[i] = NULL;
    t->totalElementos = 0;
    t->totalColisoes = 0;
    return t;
}

void inserir(TabelaHash *t, const char *palavra, const char *definicao) {
    unsigned int idx = hash(palavra);

    Node *atual = t->tabela[idx];
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            strcpy(atual->definicao, definicao);
            printf("Palavra já existia. Definição atualizada.\n");
            return;
        }
        atual = atual->prox;
    }

    Node *novo = malloc(sizeof(Node));
    strcpy(novo->palavra, palavra);
    strcpy(novo->definicao, definicao);

    if (t->tabela[idx] != NULL) {
        t->totalColisoes++;
    }

    novo->prox = t->tabela[idx];
    t->tabela[idx] = novo;
    t->totalElementos++;

    printf("Palavra inserida com sucesso.\n");
}

Node* buscar(TabelaHash *t, const char *palavra) {
    unsigned int idx = hash(palavra);
    Node *atual = t->tabela[idx];
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

void buscarEExibir(TabelaHash *t, const char *palavra) {
    Node *res = buscar(t, palavra);
    if (res != NULL) {
        printf("Palavra: %s\nDefinição: %s\n", res->palavra, res->definicao);
    } else {
        printf("Palavra não encontrada.\n");
    }
}

int remover(TabelaHash *t, const char *palavra) {
    unsigned int idx = hash(palavra);
    Node *atual = t->tabela[idx];
    Node *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            if (anterior == NULL)
                t->tabela[idx] = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual);
            t->totalElementos--;

            if (t->tabela[idx] != NULL)
                t->totalColisoes--;

            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

void exibirTabela(TabelaHash *t) {
    for (int i = 0; i < TAM_TABELA; i++) {
        if (t->tabela[i] != NULL) {
            printf("[%d]: ", i);
            Node *atual = t->tabela[i];
            while (atual != NULL) {
                printf("(%s -> %s)", atual->palavra, atual->definicao);
                if (atual->prox != NULL) printf(" -> ");
                atual = atual->prox;
            }
            printf("\n");
        }
    }
}

void exibirEstatisticas(TabelaHash *t) {
    int maiorLista = 0;

    for (int i = 0; i < TAM_TABELA; i++) {
        int tamanho = 0;
        Node *atual = t->tabela[i];
        while (atual != NULL) {
            tamanho++;
            atual = atual->prox;
        }
        if (tamanho > maiorLista)
            maiorLista = tamanho;
    }

    double fatorCarga = (double) t->totalElementos / TAM_TABELA;

    printf("\n===== ESTATÍSTICAS =====\n");
    printf("Tamanho da tabela: %d\n", TAM_TABELA);
    printf("Quantidade de elementos: %d\n", t->totalElementos);
    printf("Quantidade de colisões: %d\n", t->totalColisoes);
    printf("Fator de carga: %.2f\n", fatorCarga);
    printf("Maior lista encadeada: %d\n", maiorLista);
    printf("========================\n");
}

void liberarTabela(TabelaHash *t) {
    for (int i = 0; i < TAM_TABELA; i++) {
        Node *atual = t->tabela[i];
        while (atual != NULL) {
            Node *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(t);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    TabelaHash *dicionario = criarTabela();
    int opcao;
    char palavra[MAX_PAL];
    char definicao[MAX_DEF];

    do {
        printf("\n===== DICIONÁRIO (TABELA HASH) =====\n");
        printf("1 - Inserir palavra\n");
        printf("2 - Buscar palavra\n");
        printf("3 - Remover palavra\n");
        printf("4 - Exibir tabela\n");
        printf("5 - Exibir estatísticas\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("Palavra: ");
                fgets(palavra, MAX_PAL, stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                printf("Definição: ");
                fgets(definicao, MAX_DEF, stdin);
                definicao[strcspn(definicao, "\n")] = '\0';

                inserir(dicionario, palavra, definicao);
                break;

            case 2:
                printf("Palavra a buscar: ");
                fgets(palavra, MAX_PAL, stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                buscarEExibir(dicionario, palavra);
                break;

            case 3:
                printf("Palavra a remover: ");
                fgets(palavra, MAX_PAL, stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                if (remover(dicionario, palavra))
                    printf("Palavra removida com sucesso.\n");
                else
                    printf("Palavra não encontrada.\n");
                break;

            case 4:
                exibirTabela(dicionario);
                break;

            case 5:
                exibirEstatisticas(dicionario);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    liberarTabela(dicionario);
    return 0;
}
