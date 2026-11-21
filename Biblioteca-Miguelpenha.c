
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Referencias:
//Atividades realizadas em sala e exercicios propostos pra casa.
//Trabalho final de algoritimos(python)

#define MAX 100

typedef struct usuario {
    char email[MAX];
    char nome[MAX];
    struct usuario *next;
} Usuario;


typedef struct livro {
    char titulo[MAX];
    char autor[MAX];
    int ano;
    int id;
    int status=0;
    char emailUsuario[MAX];
    struct livro *next;
} Livro;

// LISTAS
typedef struct {
    Usuario *sent;
} ListaUsuario;

typedef struct {
    Livro *sent;
    int codigol;
} ListaLivro;

void iniciarListaUsuario(ListaUsuario *lista) {
    lista->sent = (Usuario*) malloc(sizeof(Usuario));
    lista->sent->next = lista->sent;
}

void iniciarListaLivro(ListaLivro *lista) {
    lista->sent = (Livro*) malloc(sizeof(Livro));
    lista->sent->next = lista->sent;
    lista->codigol=1
}

Livro* buscarLivro(ListaLivro *lista, int codigo) {
    Livro *aux = lista->sent->next;       
    while (aux != lista->sent) {          
        if (aux->codigo == codigo) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}
Usuario* buscarUsuario(ListaUsuario *lista, char *email) {
    Usuario *aux = lista->sent->next;
    while (aux != lista->sent) {
        if (strcmp(aux->email, email) == 0) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}
//fazer a cadastrar usuario 
void cadastrarLivro(ListaLivro *lista) {
    int id;

    printf("Codigo (ID): ");
    scanf("%d", &id);

    if (buscarLivro(lista, id) != NULL) {
        printf("Codigo ja cadastrado!\n");
        return;
    }

    Livro *new = (Livro*) malloc(sizeof(Livro));
    new->id = id;
    printf("Titulo: ");
    scanf("%99s", new->titulo);
    printf("Autor: ");
    scanf("%99s", new->autor);
    printf("Ano de publicacao: ");
    scanf("%d", &new->ano);
    new->status = 0;                 
    strcpy(new->emailUsuario, "");


    Livro *prev = lista->sent;
    Livro *aux = lista->sent->next;
    while (aux != lista->sent && aux->id < id) {
        prev = aux;
        aux = aux->next;
    }
}




int main(){
    
    
    
    
    
    
    
    
    
    return 0;
}