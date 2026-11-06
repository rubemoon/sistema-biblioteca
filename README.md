![Banner do Sistema de Controle de Biblioteca](./banner-biblioteca.png)

# Sistema de Controle de Biblioteca

Trabalho final de Estrutura de Dados I em C

## Funcionalidades

- Cadastro, consulta, atualização e exclusão de livros e usuários
- Consulta de empréstimos ativos
- Empréstimo e devolução
- Código sequencial para os livros
- Estatística de usuário com mais empréstimos ativos

## Implementação

Listas encadeadas com alocação dinâmica e livros ordenados por código

Os dados ficam em memória e são perdidos ao sair

Entradas de texto sem espaços, conforme o enunciado

## Compilar e executar

Na pasta do projeto:

```sh
gcc -Wall main.c biblioteca.c -o biblioteca
```

Execute:

```sh
./biblioteca
```
