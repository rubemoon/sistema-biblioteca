![Banner do Sistema de Controle de Biblioteca](./banner-biblioteca.png)

# Sistema de Controle de Biblioteca

Trabalho final de Estrutura de Dados I em C

## Funcionalidades

- Cadastro, consulta, atualização e exclusão de livros e usuários
- Busca de livros por código ou autor
- Busca de usuários por email ou nome
- Listagem de todos os livros
- Empréstimo e devolução
- Consulta dos empréstimos ativos de um usuário
- Estatística do usuário com mais empréstimos ativos

## Estruturas utilizadas

Livros e usuários são armazenados em listas simplesmente encadeadas com alocação dinâmica

Os livros são mantidos em ordem de código

Os dados ficam em memória e são perdidos ao sair

As entradas de texto não devem conter espaços, conforme o enunciado

## Compilar e executar

Na pasta do projeto, compile com o comando apresentado nas aulas:

```sh
gcc -Wall main.c biblioteca.c -o biblioteca
```

Execute:

```sh
./biblioteca
```

## Exemplo de uso

Escolha `1 - Cadastro` e depois `1 - Livros` para cadastrar um livro

Use `2 - Consulta`, `1 - Livros` e `3 - Todos` para listar os livros

Escolha `7 - Estatisticas` para ver o usuário com mais empréstimos ativos

## Demonstração do sistema

Menu principal com as opções disponíveis

![Menu principal do sistema](docs/imagens/menu.png)

Cadastro de um livro

![Cadastro de um livro](docs/imagens/cadastro.png)

Cadastro de um usuário

![Cadastro de um usuário](docs/imagens/usuario.png)

Consulta dos dados de um livro

![Consulta dos dados de um livro](docs/imagens/consulta.png)

Listagem dos livros cadastrados

![Listagem dos livros cadastrados](docs/imagens/listagem.png)

Empréstimo de um livro

![Empréstimo de um livro](docs/imagens/emprestimo.png)

Consulta de um livro emprestado

![Consulta de um livro emprestado](docs/imagens/livroemprestado.png)

Devolução de um livro

![Devolução de um livro](docs/imagens/devolucao.png)

Estatísticas de empréstimos ativos

![Estatísticas de empréstimos ativos](docs/imagens/estatisticas.png)
