#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

struct tlivro {
    int id;
    char titulo[80];
    char autor[80];
    int ano;
    int status;
    char email[80];
    struct tlivro *next;
};
typedef struct tlivro Livro;

struct tusuario {
    char email[80];
    char nome[80];
    struct tusuario *next;
};
typedef struct tusuario Usuario;

struct tbiblioteca {
    Livro *livros;
    Usuario *usuarios;
    int nextid;
};
typedef struct tbiblioteca Biblioteca;

void initBib(Biblioteca *bib);
int leInteiro(int *valor);
void menuCadastro(Biblioteca *bib);
void menuConsulta(Biblioteca *bib);
void menuAtualizacao(Biblioteca *bib);
void menuExclusao(Biblioteca *bib);
void emprestar(Biblioteca *bib);
void devolver(Biblioteca *bib);
void mostraEstatisticas(Biblioteca *bib);
void liberaBib(Biblioteca *bib);

#endif
