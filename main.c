#include <stdio.h>
#include "biblioteca.h"

/* Uso de LLM: apoio na estatistica implementada em biblioteca.c */
static void mostraBanner(void)
{
    printf("\n=================================\n");
    printf("      SISTEMA DE BIBLIOTECA\n");
    printf("=================================\n");
}

int main(void)
{
    Biblioteca bib;
    int op = -1;

    initBib(&bib);
    mostraBanner();

    while (op != 0) {
        printf("\n=== Biblioteca ===\n");
        printf("1 - Cadastro\n");
        printf("2 - Consulta\n");
        printf("3 - Atualizacao\n");
        printf("4 - Exclusao\n");
        printf("5 - Emprestimo\n");
        printf("6 - Devolucao\n");
        printf("7 - Estatisticas\n");
        printf("0 - Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &op) != 1)
            break;

        switch (op) {
            case 1: menuCadastro(&bib); break;
            case 2: menuConsulta(&bib); break;
            case 3: menuAtualizacao(&bib); break;
            case 4: menuExclusao(&bib); break;
            case 5: emprestar(&bib); break;
            case 6: devolver(&bib); break;
            case 7: mostraEstatisticas(&bib); break;
            case 0: break;
            default: printf("Opcao invalida\n");
        }
    }

    liberaBib(&bib);
    return 0;
}
