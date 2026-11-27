#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Referencias:
//Atividades realizadas em sala e exercicios propostos pra casa.
//Trabalho final de algoritimos(python)
//codigo revisado por LLM(correção de erros de sintaxe e melhorias logicas)
//

#define MAX 100
//estrutura do usuario
typedef struct usuario {
    char email[MAX];
    char nome[MAX];
    struct usuario *next;
} Usuario;
//estrutura do livro
typedef struct livro {
    char titulo[MAX];
    char autor[MAX];
    int ano;
    int id;
    int status;
    char emailUsuario[MAX];
    struct livro *next;
} Livro;
//sentinela lista de usuario
typedef struct {
    Usuario *sent;
} Listausuario;
//sentinela lista de livros
typedef struct {
    Livro *sent;
    int codigol;
} Listalivro;
// inicializacao da lista de usuarios
void iniciarlistausuario(Listausuario *lista) {
    lista->sent = (Usuario*) malloc(sizeof(Usuario));
    lista->sent->next = lista->sent;
}
// iniciacao da lista de livros
void iniciarlistaLivro(Listalivro *lista) {
    lista->sent = (Livro*) malloc(sizeof(Livro));
    lista->sent->next = lista->sent;
    lista->codigol = 1;
}
//busca livro
Livro* buscarlivro(Listalivro *lista, int codigo) {
    Livro *aux = lista->sent->next;
    while (aux != lista->sent) {
        if (aux->id == codigo) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}
//busca usuario
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
// cadastro de livro
void cadastrarlivro(Listalivro *lista) {
    int id;
    id = lista->codigol;
    lista->codigol++;
    Livro *novo = (Livro*) malloc(sizeof(Livro));
    novo->id = id;
    printf("Titulo:\n");
    scanf("%99s", novo->titulo);
    printf("Autor:\n");
    scanf("%99s", novo->autor);
    printf("Ano de publicacao:\n");
    scanf("%d", &novo->ano);
    novo->status = 0;
    strcpy(novo->emailUsuario, "");
    Livro *prev = lista->sent;
    Livro *aux = lista->sent->next;
    while (aux != lista->sent && aux->id < id) {
        prev = aux;
        aux = aux->next;
    }
    novo->next = aux;
    prev->next = novo;
    printf("Livro cadastrado\n");
}
// cadastro de usuario
void cadastrarusuario(Listausuario *lista) {
    char email[MAX];
    printf("Email:\n");
    scanf("%99s", email);
    if (buscarusuario(lista, email) != NULL) {
        printf("Email ja cadastrado\n");
        return;
    }
    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    strcpy(novo->email, email);
    printf("Nome:\n");
    scanf("%99s", novo->nome);
    novo->next = lista->sent->next;
    lista->sent->next = novo;
    printf("Usuario cadastrado\n");
}
// menu cadastro
void cadastro(Listalivro *livros, Listausuario *usuarios) {
    int op;
    while (1) {
        printf("---CADASTRO---\n");
        printf("1-Livros\n");
        printf("2-Usuarios\n");
        printf("0-Sair\n");
        scanf("%d", &op);
        if (op == 0) {
            break;
        }
        if (op == 1) {
            cadastrarlivro(livros);
        } else if (op == 2) {
            cadastrarusuario(usuarios);
        }
    }
}
// informacoes do livro
void infolivro(Livro *l) {
    printf("ID: %d\n", l->id);
    printf("Titulo: %s\n", l->titulo);
    printf("Autor: %s\n", l->autor);
    printf("Ano: %d\n", l->ano);
    if (l->status == 0) {
        printf("Status: Disponivel\n");
    } else {
        printf("Status: Emprestado\n");
    }
}
//consulta de livro
void consultarlivros(Listalivro *lista) {
    int op;
    printf("1-Por codigo\n");
    printf("2-Por autor\n");
    scanf("%d", &op);
    if (op == 1) {
        int id;
        printf("Codigo: ");
        scanf("%d", &id);
        Livro *aux = buscarlivro(lista, id);
        if (aux == NULL) {
            printf("Livro nao encontrado\n");
        } else {
            infolivro(aux);
        }

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
        if (achou == 0) {
            printf("Livro nao encontrado\n");
        }
    }
}
//consulta usuario
void consultarusuarios(Listausuario *lista) {
    int op;
    printf("1-Por email\n");
    printf("2-Por nome\n");
    scanf("%d", &op);
    if (op == 1) {
        char email[MAX];
        printf("Email:\n");
        scanf("%99s", email);
        Usuario *aux = buscarusuario(lista, email);

        if (aux == NULL) {
            printf("Usuario nao cadastrado\n");
        } else {
            printf("Nome: %s  Email: %s\n", aux->nome, aux->email);
        }

    } else if (op == 2) {
        char nome[MAX];
        int achou = 0;
        printf("Nome:\n");
        scanf("%99s", nome);
        Usuario *aux = lista->sent->next;
        while (aux != lista->sent) {
            if (strcmp(aux->nome, nome) == 0) {
                printf("Nome: %s  Email: %s\n", aux->nome, aux->email);
                achou = 1;
            }
            aux = aux->next;
        }
        if (achou == 0) {
            printf("Usuario nao cadastrado\n");
        }
    }
}
//consulta emprestimo
void consultaremprestimos(Listalivro *livros, Listausuario *usuarios) {
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
//menu consulta
void consulta(Listalivro *livros, Listausuario *usuarios) {
    int op;
    while (1) {
        printf("--- CONSULTA ---\n");
        printf("1 - Livros\n");
        printf("2 - Usuarios\n");
        printf("3 - Emprestimos\n");
        printf("0 - Voltar\n");
        scanf("%d", &op);
        if (op == 0) {
            break;
        }
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
}
//atualizacao de livros
void atualizarlivro(Listalivro *lista) {
    int id;
    printf("ID do livro: ");
    scanf("%d", &id);
    Livro *aux = buscarlivro(lista, id);
    if (aux == NULL) {
        printf("Livro nao encontrado!\n");
        return;
    }
    printf("Novo titulo:\n");
    scanf("%99s", aux->titulo);
    printf("Novo autor:\n");
    scanf("%99s", aux->autor);
    printf("Novo ano:\n");
    scanf("%d", &aux->ano);
    printf("Livro atualizado\n");
}
//atualizacao de usuarios
void atualizarusuario(Listausuario *lista) {
    char email[MAX];
    printf("Email do usuario:\n");
    scanf("%99s", email);
    Usuario *aux = buscarusuario(lista, email);
    if (aux == NULL) {
        printf("Usuario nao cadastrado\n");
        return;
    }
    printf("Novo nome:\n");
    scanf("%99s", aux->nome);

    printf("Usuario atualizado\n");
}
//atualizacao menu
void atualizacao(Listalivro *livros, Listausuario *usuarios) {
    int op;
    while (1) {
        printf("---ATUALIZACAO ---\n");
        printf("1 - Livros\n");
        printf("2 - Usuarios\n");
        printf("0 - Voltar\n");
        scanf("%d", &op);
        if (op == 0) {
            break;
        }
        if (op == 1) {
            atualizarlivro(livros);
        }
        if (op == 2) {
            atualizarusuario(usuarios);
        }
    }
}
//exclusao de livro
void excluirlivro(Listalivro *lista) {
    int id;
    printf("ID do livro:\n");
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
//exclusao de usuario
void excluirusuario(Listausuario *lista) {
    char email[MAX];
    printf("Email do usuario:\n");
    scanf("%99s", email);
    Usuario *prev = lista->sent;
    Usuario *aux = lista->sent->next;
    while (aux != lista->sent && strcmp(aux->email, email) != 0) {
        prev = aux;
        aux = aux->next;
    }
    if (aux == lista->sent) {
        printf("Usuario nao cadastrado\n");
        return;
    }
    prev->next = aux->next;
    free(aux);
    printf("Usuario excluido\n");
}
// menu de exclusao
void exclusao(Listalivro *livros, Listausuario *usuarios) {
    int op;
    while (1) {
        printf("\n--- EXCLUSAO ---\n");
        printf("1 - Livros\n");
        printf("2 - Usuarios\n");
        printf("0 - Voltar\n");

        scanf("%d", &op);

        if (op == 0) {
            break;
        }

        if (op == 1) {
            excluirlivro(livros);
        }

        if (op == 2) {
            excluirusuario(usuarios);
        }
    }
}
//emprestimo de livros
void emprestimo(Listalivro *livros, Listausuario *usuarios) {
    int id;
    char email[MAX];
    printf("ID do livro:\n");
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
    strcpy(aux->emailUsuario, email);

    printf("Emprestimo realizado\n");
}
//devolucao de livros
void devolucao(Listalivro *lista) {
    int id;
    printf("ID do livro:\n");
    scanf("%d", &id);
    Livro *aux = buscarlivro(lista, id);
    if (aux == NULL) {
        printf("Livro nao encontrado\n");
        return;
    }
    if (aux->status == 0) {
        printf("Livro nao estava emprestado\n");
        return;
    }
    aux->status = 0;
    strcpy(aux->emailUsuario, "");
    printf("Devolucao realizada com sucesso\n");
}
//apagar livros
void liberarlistalivro(Listalivro *lista) {
    Livro *aux = lista->sent->next;
    Livro *temp;
    while (aux != lista->sent) {
        temp = aux;
        aux = aux->next;
        free(temp);
    }
    free(lista->sent);
}
//apagar usuarios
void liberarlistausuario(Listausuario *lista) {
    Usuario *aux = lista->sent->next;
    Usuario *temp;
    while (aux != lista->sent) {
        temp = aux;
        aux = aux->next;
        free(temp);
    }
    free(lista->sent);
}

int main() {
    Listalivro livros;
    Listausuario usuarios;
    int op;

    iniciarlistaLivro(&livros);
    iniciarlistausuario(&usuarios);

    while (1) {
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
            break;
        }
    }

    liberarlistalivro(&livros);
    liberarlistausuario(&usuarios);

    printf("Memoria liberada\n");

    return 0;
}
