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
        if (aux == NULL){
            printf("Livro nao encontrado\n");
        }
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
void consultarusuarios(Listausuario *lista) {
    int op;
    printf("1-Por email\n2-Por nome\n");
    scanf("%d", &op);

    if (op == 1) {
        char email[MAX];
        printf("Email: ");
        scanf("%99s", email);
        Usuario *aux = buscarusuario(lista, email);
        if (aux == NULL){ printf("Usuario nao cadastrado\n");}
        else printf("Nome: %s  Email: %s\n", aux->nome, aux->email);
    } else if (op == 2) {
        char nome[MAX];
        int achou = 0;
        printf("Nome: ");
        scanf("%99s", nome);
        Usuario *aux = lista->sent->next;
        while (aux != lista->sent) {
            if (strcmp(aux->nome, nome) == 0) {
                printf("Nome: %s  Email: %s\n", aux->nome, aux->email);
                achou = 1;
            }
            aux = aux->next;
        }
        if (achou!=0){printf("Usuario nao cadastrado\n");} 
    }
}
void consultaremprestimos(Listalivro *livros,Listausuario *usuarios) {
    char email[MAX];
    int achou = 0;
    printf("Email do usuario: ");
    scanf("%99s", email);
    if (buscarusuario(usuarios, email) == NULL) {
        printf("Usuario nao cadastrado!\n");
        return;
    }
    Livro *aux = livros->sent->next;
    while (aux != livros->sent) {
        if (aux->status == 1 && strcmp(aux->emailUsuario, email) == 0) {
            infolivro(aux);
            achou = 1;
        }
        aux = aux->next;
    }
    if (achou == 0) {
        printf("Usuario nao possui emprestimos\n");
    }
}
void consulta(Listalivro *livros, Listausuario *usuarios) {
    int op;
    while(op!=0){
        printf("--- CONSULTA ---\n");
        printf("1 - Livros\n");
        printf("2 - Usuarios\n");
        printf("3 - Emprestimos\n");
        printf("0 - Voltar\n");
        scanf("%d", &op);
        if (op == 1) {
            consultarlivros(livros);
        }
        if (op == 2) {
            consultarusuarios(usuarios);
        }
        if (op == 3) {
            consultaremprestimos(livros, usuarios);
        }

}
//fazer atualizacoes
void atualizacao(Listalivro *livros, Listausuario *usuarios) {
    int op;
    while(op!=0){
        printf("---ATUALIZACAO ---");
        printf("1 - Livros\n");
        printf("2 - Usuarios\n");
        printf("0 - Voltar\n");
        scanf("%d", &op);
        if (op == 1) {
            atualizarlivro(livros);
        }
        if (op == 2) {
            atualizarusuario(usuarios);
        }
    } 
}
void atualizarlivro(Listalivro *lista) {
    int id;
    printf("ID do livro: ");
    scanf("%d", &id);
    Livro *aux = buscarlivro(lista, id);
    if (aux == NULL) {
        printf("Livro nao encontrado!\n");
        return;
    }
    printf("Novo titulo: ");
    scanf("%99s", aux->titulo);
    printf("Novo autor: ");
    scanf("%99s", aux->autor);
    printf("Novo ano: ");
    scanf("%d", &aux->ano);
    printf("Livro atualizado\n");
}
void atualizarusuario(Listausuario *lista) {
    char email[MAX];
    printf("Email do usuario: ");
    scanf("%99s", email);
    Usuario *aux = buscarusuario(lista, email);
    if (aux == NULL) {
        printf("Usuario nao cadastrado\n");
        return;
    }
    printf("Novo nome: ");
    scanf("%99s", aux->nome);
    printf("Usuario atualizado\n");
}
void excluirlivro(Listalivro *lista) {
    int id;
    printf("ID do livro: ");
    scanf("%d", &id);
    Livro *prev = lista->sent;
    Livro *aux = lista->sent->next;
    while (aux != lista->sent && aux->id != id) {
        prev = aux;
        aux = aux->next;
    }
    if (aux == lista->sent) {
        printf("Livro nao encontrado!\n");
        return;
    }
    if (aux->status == 1) {
        printf("O livro esta emprestado\n");
        return;
    }
    prev->next = aux->next;
    free(aux);
    printf("Livro excluido\n");
}  

void exclusao(Listalivro *livros, Listausuario *usuarios) {
    int op;
    while (op != 0);{
        printf("\n--- EXCLUSAO ---\n");
        printf("1 - Livros\n");
        printf("2 - Usuarios\n");
        printf("0 - Voltar\n");
        scanf("%d", &op);
        if (op == 1) {
            excluirlivro(livros);
        }
        if (op == 2) {
            excluirusuario(usuarios, livros);
        }
}

// exclusao usuario
void emprestimo(Listalivro *livros, Listausuario *usuarios) {
    int id;
    char email[MAX];
    printf("ID do livro: ");
    scanf("%d", &id);
    Livro *aux = buscarlivro(livros, id);
    if (aux == NULL) {
        printf("Livro nao encontrado\n");
        return;
    }
    if (aux->status == 1) {
        printf("Livro ja esta emprestado\n");
        return;
    }
    printf("Email do usuario: ");
    scanf("%99s", email);
    if (buscarusuario(usuarios, email) == NULL) {
        printf("Usuario nao cadastrado!\n");
        return;
    }
    aux->status = 1;
    strcpy(aux->emailusuario, email);
    printf("Emprestimo realizado\n");
}


//devolucao

//liberaçao de memoria
int main(){//ORGANIZAR AS FUNÇOES
    Listalivro livros;
    Listausuario usuarios;
    int op;

    iniciarllivro(&livros);
    iniciarlusuario(&usuarios);
    while(op!=0){
       printf("---BIBLIOTECA---\n");
        printf("1 - Cadastro\n");
        printf("2 - Consulta\n");
        printf("3 - Atualizacao\n");
        printf("4 - Exclusao\n");
        printf("5 - Emprestimo\n");
        printf("6 - Devolucao\n");
        printf("0 - Sair\n");
        scanf("%d", &op);
        if (op == 1) {
            cadastro(&livros, &usuarios);
        }
        if (op == 2) {
            consulta(&livros, &usuarios);
        }
        if (op == 3) {
            atualizacao(&livros, &usuarios);
        }
        if (op == 4) {
            exclusao(&livros, &usuarios);
        }
        if (op == 5) {
            emprestimo(&livros, &usuarios);
        }
        if (op == 6) {
            devolucao(&livros);
        }
        if (op == 0) {
            printf("Encerrando programa...\n");
        }
    } 

    
    //liberar memoriaaaaaaaaaaaaaaaaaaaaaa
    
    return 0;
}
