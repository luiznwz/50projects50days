#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

typedef struct no {
    char nome[100];
    struct no *proximo;
} No;

typedef struct {
    No *inicio;
    int tamanho;
} Lista;

void criar_lista(Lista *lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void inserir_no_inicio(Lista *lista, const char *nome) {
    No *novo = malloc(sizeof(No));

    if (novo) {
        strcpy(novo->nome, nome);
        if (lista->inicio == NULL) {
            novo->proximo = novo;
        } else {
            No *ultimo = lista->inicio;
            while (ultimo->proximo != lista->inicio) {
                ultimo = ultimo->proximo;
            }
            novo->proximo = lista->inicio;
            ultimo->proximo = novo;
        }
        lista->inicio = novo;
        lista->tamanho++;
    } else {
        printf("Erro ao alocar nó!\n");
    }
}

void inserir_no_fim(Lista *lista, const char *nome) {
    No *novo = malloc(sizeof(No));

    if (novo) {
        strcpy(novo->nome, nome);

        if (lista->inicio == NULL) {
            novo->proximo = novo; 
            lista->inicio = novo;
        } else {
            No *ultimo = lista->inicio;
            while (ultimo->proximo != lista->inicio) {
                ultimo = ultimo->proximo;
            }
            novo->proximo = lista->inicio;
            ultimo->proximo = novo;
        }

        lista->tamanho++;
    } else {
        printf("Erro ao alocar nó!\n");
    }
}

void remover(Lista *lista, const char *nome) {
    if (lista->inicio) {
        No *anterior = NULL;
        No *atual = lista->inicio;
        do {
            if (strcmp(atual->nome, nome) == 0) {
                if (anterior) {
                    anterior->proximo = atual->proximo;
                    if (atual == lista->inicio) {
                        lista->inicio = atual->proximo;
                    }
                    free(atual);
                    lista->tamanho--;
                    return;
                }
            }
            anterior = atual;
            atual = atual->proximo;
        } while (atual != lista->inicio);
    }
}

No *buscar(Lista *lista, const char *nome) {
    if (lista->inicio) {
        No *atual = lista->inicio;
        do {
            if (strcmp(atual->nome, nome) == 0) {
                return atual;
            }
            atual = atual->proximo;
        } while (atual != lista->inicio);
    }
    return NULL;
}

void imprimir(Lista *lista) {
    if (lista->inicio) {
        No *atual = lista->inicio;
        do {
            printf("%s\n", atual->nome);
            atual = atual->proximo;
        } while (atual != lista->inicio);
    } else {
        printf("A lista está vazia.\n");
    }
}

int contar_elementos(Lista *lista) {
    int count = 0;
    if (lista->inicio) {
        No *atual = lista->inicio;
        do {
            count++;
            atual = atual->proximo;
        } while (atual != lista->inicio);
    }
    return count;
}

void liberar_lista(Lista *lista) {
    if (lista->inicio) {
        No *atual = lista->inicio;
        No *primeiro = lista->inicio;
        do {
            No *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        } while (atual != primeiro);
        lista->inicio = NULL;
        lista->tamanho = 0;
    }
}

void proximo_lista(Lista *lista) {
    if (lista->inicio) {
        lista->inicio = lista->inicio->proximo;
    }
}

int main() {
    system("color 0C"); 
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    char nome[100];
    Lista lista;
    criar_lista(&lista);

    do {
        printf("\t0 - Inserir no início\n\t1 - Inserir no Fim\n\t2 - Remover\n\t3 - Imprimir\n\t4 - Contar elementos\n\t5 - Buscar\n\t6 - Próximo \n\t7 - Sair\n");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 0:
                printf("Digite o nome da música: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; 
                inserir_no_inicio(&lista, nome);
                break;
            case 1:
            	printf("Digite o nome da música: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                inserir_no_fim(&lista, nome);
                break;
            case 2:
            	printf("Digite o nome da música a ser removida: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                remover(&lista, nome);
                break;
            case 3:
            	imprimir(&lista);
                break;
            case 4:
                printf("Quantidade de elementos na lista: %d\n", contar_elementos(&lista));
                break;
            case 5:
                printf("Digite o nome da música a ser buscada: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                No *encontrado = buscar(&lista, nome);
                if (encontrado) {
                    printf("Música encontrada na lista: %s\n", encontrado->nome);
                } else {
                    printf("Música não encontrada na lista.\n");
                }
                break;
            case 6:
                proximo_lista(&lista);
                printf("O próximo item da lista é %s.\n");
                break;
            case 7:
                liberar_lista(&lista);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 7);

    return 0;
}
