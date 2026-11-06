#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "biblioteca.h"

void initBib(Biblioteca *bib)
{
    bib->livros = NULL;
    bib->usuarios = NULL;
    bib->nextid = 1;
}

static Livro *buscaLivro(Biblioteca *bib, int id)
{
    Livro *aux = bib->livros;

    while (aux != NULL) {
        if (aux->id == id)
            return aux;
        aux = aux->next;
    }

    return NULL;
}

static Usuario *buscaUsuario(Biblioteca *bib, char email[])
{
    Usuario *aux = bib->usuarios;

    while (aux != NULL) {
        if (strcmp(aux->email, email) == 0)
            return aux;
        aux = aux->next;
    }

    return NULL;
}

static void mostraLivro(Livro *livro)
{
    printf("Codigo: %d\n", livro->id);
    printf("Titulo: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Ano: %d\n", livro->ano);

    if (livro->status == 0)
        printf("Status: Disponivel\n");
    else {
        printf("Status: Emprestado\n");
        printf("Email: %s\n", livro->email);
    }
}

static void mostraUsuario(Usuario *usuario)
{
    printf("Nome: %s\n", usuario->nome);
    printf("Email: %s\n", usuario->email);
}

static void cadLivro(Biblioteca *bib)
{
    Livro *novo = (Livro *)malloc(sizeof(Livro));

    if (novo == NULL) {
        printf("Erro de memoria\n");
        return;
    }

    printf("Titulo: ");
    scanf("%79s", novo->titulo);
    printf("Autor: ");
    scanf("%79s", novo->autor);
    printf("Ano: ");
    scanf("%d", &novo->ano);

    novo->id = bib->nextid;
    novo->status = 0;
    novo->email[0] = '\0';
    novo->next = NULL;

    /* O ID e sequencial e a insercao no fim mantem os livros ordenados */
    if (bib->livros == NULL)
        bib->livros = novo;
    else {
        Livro *aux = bib->livros;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = novo;
    }

    bib->nextid++;
    printf("Livro cadastrado, codigo %d\n", novo->id);
}

static void cadUsuario(Biblioteca *bib)
{
    char email[80];

    printf("Email: ");
    scanf("%79s", email);

    if (buscaUsuario(bib, email) != NULL) {
        printf("Usuario ja cadastrado\n");
        return;
    }

    Usuario *novo = (Usuario *)malloc(sizeof(Usuario));

    if (novo == NULL) {
        printf("Erro de memoria\n");
        return;
    }

    strcpy(novo->email, email);
    printf("Nome: ");
    scanf("%79s", novo->nome);

    novo->next = bib->usuarios;
    bib->usuarios = novo;

    printf("Usuario cadastrado\n");
}

void menuCadastro(Biblioteca *bib)
{
    int op = -1;

    while (op != 0) {
        printf("\n1 - Livros\n2 - Usuarios\n0 - Voltar\nOpcao: ");
        if (scanf("%d", &op) != 1)
            return;

        switch (op) {
            case 1: cadLivro(bib); break;
            case 2: cadUsuario(bib); break;
            case 0: break;
            default: printf("Opcao invalida\n");
        }
    }
}

static void consLivro(Biblioteca *bib)
{
    int op, id, achou = 0;
    char autor[80];
    Livro *aux;

    printf("1 - Por codigo\n2 - Por autor\nOpcao: ");
    scanf("%d", &op);

    if (op == 1) {
        printf("Codigo: ");
        scanf("%d", &id);
        aux = buscaLivro(bib, id);

        if (aux == NULL)
            printf("Livro nao encontrado\n");
        else
            mostraLivro(aux);
    } else if (op == 2) {
        printf("Autor: ");
        scanf("%79s", autor);

        for (aux = bib->livros; aux != NULL; aux = aux->next) {
            if (strcmp(aux->autor, autor) == 0) {
                mostraLivro(aux);
                printf("\n");
                achou = 1;
            }
        }

        if (achou == 0)
            printf("Livro nao encontrado\n");
    } else
        printf("Opcao invalida\n");
}

static void consUsuario(Biblioteca *bib)
{
    int op, achou = 0;
    char dado[80];
    Usuario *aux;

    printf("1 - Por email\n2 - Por nome\nOpcao: ");
    scanf("%d", &op);

    if (op == 1) {
        printf("Email: ");
        scanf("%79s", dado);
        aux = buscaUsuario(bib, dado);

        if (aux == NULL)
            printf("Usuario nao cadastrado\n");
        else
            mostraUsuario(aux);
    } else if (op == 2) {
        printf("Nome: ");
        scanf("%79s", dado);

        for (aux = bib->usuarios; aux != NULL; aux = aux->next) {
            if (strcmp(aux->nome, dado) == 0) {
                mostraUsuario(aux);
                printf("\n");
                achou = 1;
            }
        }

        if (achou == 0)
            printf("Usuario nao cadastrado\n");
    } else
        printf("Opcao invalida\n");
}

static void consEmprestimos(Biblioteca *bib)
{
    char email[80];
    int achou = 0;
    Livro *aux;

    printf("Email: ");
    scanf("%79s", email);

    if (buscaUsuario(bib, email) == NULL) {
        printf("Usuario nao cadastrado\n");
        return;
    }

    for (aux = bib->livros; aux != NULL; aux = aux->next) {
        if (aux->status == 1 && strcmp(aux->email, email) == 0) {
            mostraLivro(aux);
            printf("\n");
            achou = 1;
        }
    }

    if (achou == 0)
        printf("Nenhum emprestimo\n");
}

void menuConsulta(Biblioteca *bib)
{
    int op = -1;

    while (op != 0) {
        printf("\n1 - Livros\n2 - Usuarios\n3 - Emprestimos\n0 - Voltar\nOpcao: ");
        if (scanf("%d", &op) != 1)
            return;

        switch (op) {
            case 1: consLivro(bib); break;
            case 2: consUsuario(bib); break;
            case 3: consEmprestimos(bib); break;
            case 0: break;
            default: printf("Opcao invalida\n");
        }
    }
}

static void alteraLivro(Biblioteca *bib)
{
    int id, op;
    Livro *livro;

    printf("Codigo: ");
    scanf("%d", &id);
    livro = buscaLivro(bib, id);

    if (livro == NULL) {
        printf("Livro nao encontrado\n");
        return;
    }

    printf("1 - Titulo\n2 - Autor\n3 - Ano\n0 - Voltar\nOpcao: ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            printf("Novo titulo: ");
            scanf("%79s", livro->titulo);
            break;
        case 2:
            printf("Novo autor: ");
            scanf("%79s", livro->autor);
            break;
        case 3:
            printf("Novo ano: ");
            scanf("%d", &livro->ano);
            break;
        case 0:
            return;
        default:
            printf("Opcao invalida\n");
            return;
    }

    printf("Livro atualizado\n");
}

static void alteraUsuario(Biblioteca *bib)
{
    char email[80];
    Usuario *usuario;

    printf("Email: ");
    scanf("%79s", email);
    usuario = buscaUsuario(bib, email);

    if (usuario == NULL) {
        printf("Usuario nao cadastrado\n");
        return;
    }

    printf("Novo nome: ");
    scanf("%79s", usuario->nome);
    printf("Usuario atualizado\n");
}

void menuAtualizacao(Biblioteca *bib)
{
    int op = -1;

    while (op != 0) {
        printf("\n1 - Livros\n2 - Usuarios\n0 - Voltar\nOpcao: ");
        if (scanf("%d", &op) != 1)
            return;

        switch (op) {
            case 1: alteraLivro(bib); break;
            case 2: alteraUsuario(bib); break;
            case 0: break;
            default: printf("Opcao invalida\n");
        }
    }
}

static void removeLivro(Biblioteca *bib)
{
    int id;
    Livro *aux = bib->livros;
    Livro *ant = NULL;

    printf("Codigo: ");
    scanf("%d", &id);

    while (aux != NULL && aux->id != id) {
        ant = aux;
        aux = aux->next;
    }

    if (aux == NULL) {
        printf("Livro nao encontrado\n");
        return;
    }

    if (aux->status == 1) {
        printf("Livro emprestado, devolva antes de excluir\n");
        return;
    }

    if (ant == NULL)
        bib->livros = aux->next;
    else
        ant->next = aux->next;

    free(aux);
    printf("Livro excluido\n");
}

static void removeUsuario(Biblioteca *bib)
{
    char email[80];
    Usuario *aux = bib->usuarios;
    Usuario *ant = NULL;
    Livro *livro;

    printf("Email: ");
    scanf("%79s", email);

    while (aux != NULL && strcmp(aux->email, email) != 0) {
        ant = aux;
        aux = aux->next;
    }

    if (aux == NULL) {
        printf("Usuario nao cadastrado\n");
        return;
    }

    /* nao exclui usuario que ainda possui livros emprestados */
    for (livro = bib->livros; livro != NULL; livro = livro->next) {
        if (livro->status == 1 && strcmp(livro->email, email) == 0) {
            printf("Usuario com emprestimos, devolva antes de excluir\n");
            return;
        }
    }

    if (ant == NULL)
        bib->usuarios = aux->next;
    else
        ant->next = aux->next;

    free(aux);
    printf("Usuario excluido\n");
}

void menuExclusao(Biblioteca *bib)
{
    int op = -1;

    while (op != 0) {
        printf("\n1 - Livros\n2 - Usuarios\n0 - Voltar\nOpcao: ");
        if (scanf("%d", &op) != 1)
            return;

        switch (op) {
            case 1: removeLivro(bib); break;
            case 2: removeUsuario(bib); break;
            case 0: break;
            default: printf("Opcao invalida\n");
        }
    }
}

void emprestar(Biblioteca *bib)
{
    int id;
    char email[80];
    Livro *livro;

    printf("Codigo: ");
    scanf("%d", &id);
    livro = buscaLivro(bib, id);

    if (livro == NULL) {
        printf("Livro nao encontrado\n");
        return;
    }

    if (livro->status == 1) {
        printf("Livro ja emprestado\n");
        return;
    }

    printf("Email: ");
    scanf("%79s", email);

    if (buscaUsuario(bib, email) == NULL) {
        printf("Usuario nao cadastrado\n");
        return;
    }

    livro->status = 1;
    strcpy(livro->email, email);
    printf("Emprestimo realizado\n");
}

void devolver(Biblioteca *bib)
{
    int id;
    Livro *livro;

    printf("Codigo: ");
    scanf("%d", &id);
    livro = buscaLivro(bib, id);

    if (livro == NULL) {
        printf("Livro nao encontrado\n");
        return;
    }

    if (livro->status == 0) {
        printf("Livro nao estava emprestado\n");
        return;
    }

    livro->status = 0;
    livro->email[0] = '\0';
    printf("Devolucao realizada\n");
}

static int contaEmprestimosAtivos(Biblioteca *bib, char email[])
{
    Livro *livro;
    int total = 0;

    for (livro = bib->livros; livro != NULL; livro = livro->next) {
        if (livro->status == 1 && strcmp(livro->email, email) == 0)
            total++;
    }

    return total;
}

void mostraEstatisticas(Biblioteca *bib)
{
    Usuario *usuario;
    int maior = 0;

    for (usuario = bib->usuarios; usuario != NULL; usuario = usuario->next) {
        int total = contaEmprestimosAtivos(bib, usuario->email);
        if (total > maior)
            maior = total;
    }

    if (maior == 0) {
        printf("Nenhum emprestimo ativo\n");
        return;
    }

    printf("Usuario(s) com mais emprestimos ativos: %d\n", maior);
    for (usuario = bib->usuarios; usuario != NULL; usuario = usuario->next) {
        if (contaEmprestimosAtivos(bib, usuario->email) == maior) {
            printf("Nome: %s\n", usuario->nome);
            printf("Email: %s\n", usuario->email);
        }
    }
}

void liberaBib(Biblioteca *bib)
{
    Livro *livro;
    Usuario *usuario;

    while (bib->livros != NULL) {
        livro = bib->livros;
        bib->livros = livro->next;
        free(livro);
    }

    while (bib->usuarios != NULL) {
        usuario = bib->usuarios;
        bib->usuarios = usuario->next;
        free(usuario);
    }
}

