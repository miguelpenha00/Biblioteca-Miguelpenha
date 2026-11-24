
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Referencias:
//Atividades realizadas em sala e exercicios propostos pra casa.
//Trabalho final de algoritimos(python)
//codigo revisado por LLM

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
} Listausuario;

typedef struct {
    Livro *sent;
    int codigol;
} Listalivro;

void iniciarlistausuario(Listausuario *lista) {
    lista->sent = (Usuario*) malloc(sizeof(Usuario));
    lista->sent->next = lista->sent;
}

void iniciarlistaLivro(Listalivro *lista) {
    lista->sent = (Livro*) malloc(sizeof(Livro));
    lista->sent->next = lista->sent;
    lista->codigol=1
}

Livro* buscarlivro(Listalivro *lista, int codigo) {
    Livro *aux = lista->sent->next;       
    while (aux != lista->sent) {          
        if (aux->codigo == codigo) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}
Usuario* buscarusuario(Listausuario *lista, char *email) {
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
void cadastrarlivro(Listalivro *lista) {
    int id;

    printf("Codigo (ID): ");
    scanf("%d", &id);

    if (buscarlivro(lista, id) != NULL) {
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
void cadastrarusuario(Listausuario *lista) {
    char email[MAX];

    printf("Email: ");
    scanf("%99s", email);

    if (buscarusuario(lista, email) != NULL) {
        printf("Email ja cadastrado\n");
        return;
    }

    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    strcpy(novo->email, email);
    printf("Nome: ");
    scanf("%99s", novo->nome);

    novo->next = lista->sent->next;
    lista->sent->next = novo;

    printf("Usuario cadastrado\n");
}
void cadastro(Listalivro *livros, Listausuario *usuarios){
    int op;
    while(op!=0){
         printf("---CADASTRO---\n 1-Livros\n 2-Usuarios\n 0-Sair\n");
        scanf("%d", &op);
        if (op == 1) cadastrarivro(livros);
        else if (op == 2) cadastrarusuario(usuarios);
    }
}
//comecar o consulta
void infolivro(Livro *l) {
printf("ID: %d", l->id);
printf("  Titulo: %s", l->titulo);
printf("  Autor: %s", l->autor);
printf("  Ano: %d", l->ano);
if (l->status == 0) {
    printf("Status: Disponivel");
} else {
    printf("Status: Emprestado");
}
}
void consultarlivros(Listalivro *lista) {
    int op;
    printf("1-Por codigo\n2-Por autor\n");
    scanf("%d", &op);

    if (op == 1) {
        int id;
        printf("Codigo: ");
        scanf("%d", &id);
        Livro *aux = buscarlivro(lista, id);
        if (aux == NULL) printf("Livro nao encontrado\n");
        else infolivro(aux);
    } else if (op == 2) {
        char autor[MAX];
        int achou = 0;
        printf("Autor: ");
        scanf("%99s", autor);
        Livro *aux = lista->sent->next;
        while (aux != lista->sent) {
            if (strcmp(aux->autor, autor) == 0) {
                infolivro(aux);
                achou = 1;
            }
            aux = aux->next;
        }
        if (achou!=1)
        {printf("Livro nao encontrado\n");}
    }
}





int main(){
    Listalivro livros;
    Listausuario usuarios;
    int op;

    iniciarllivro(&livros);
    iniciarlusuario(&usuarios);
    while(op!=0){
         printf("---BIBLIOTECA---\n");
        printf("1-Cadastro\n 2-Consulta\n 3-Atualizacao\n 4-Exclusao\n");
        printf("5-Emprestimo\n 6-Devolucao\n 0-Sair");
        scanf("%d", &op);
        if(op==1){cadastro(&livros, &usuarios)}
        if(op==2{consulta(&livros, &usuarios)})
    }
    
    
    
    
    
    
    
    
    return 0;
}
    
    
