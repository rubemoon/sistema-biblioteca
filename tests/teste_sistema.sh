#!/bin/sh
set -eu

raiz=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
executavel=$(mktemp)
trap 'rm -f "$executavel"' EXIT

gcc -Wall -Wextra -Wpedantic \
    "$raiz/main.c" "$raiz/biblioteca.c" -o "$executavel"

saida=$(printf 'x\n0\n' | "$executavel")
printf '%s\n' "$saida" | grep -Fq 'Entrada invalida'

saida=$(printf '1\n1\nLivroTeste\nAutorTeste\n0\n0\n0\n' | "$executavel")
printf '%s\n' "$saida" | grep -Fq 'Ano invalido'
if printf '%s\n' "$saida" | grep -Fq 'Livro cadastrado'; then
    echo 'Livro com ano invalido foi cadastrado' >&2
    exit 1
fi

saida=$(printf '1\n2\nana@example.com\nAna\n2\nbruno@example.com\nBruno\n2\nana@example.com\n0\n1\n1\nLivroA\nAutorA\n2001\n1\nLivroB\nAutorB\n2002\n1\nLivroC\nAutorC\n2003\n0\n2\n1\n3\n0\n5\n99\n5\n1\nmissing@example.com\n5\n1\nana@example.com\n5\n2\nana@example.com\n5\n3\nbruno@example.com\n5\n1\n6\n99\n6\n1\n6\n1\n5\n1\nana@example.com\n7\n2\n3\nana@example.com\n0\n0\n' | "$executavel")
printf '%s\n' "$saida" | grep -Fq 'Usuario ja cadastrado'
printf '%s\n' "$saida" | grep -Fq 'Livro nao encontrado'
printf '%s\n' "$saida" | grep -Fq 'Usuario nao cadastrado'
printf '%s\n' "$saida" | grep -Fq 'Livro ja emprestado'
printf '%s\n' "$saida" | grep -Fq 'Devolucao realizada'
printf '%s\n' "$saida" | grep -Fq 'Livro nao estava emprestado'
printf '%s\n' "$saida" | grep -Fq 'Usuario(s) com mais emprestimos ativos: 2'
printf '%s\n' "$saida" | grep -Fq 'Nome: Ana'
printf '%s\n' "$saida" | grep -Fq 'Email: ana@example.com'
printf '%s\n' "$saida" | grep -Fq 'Titulo: LivroA'
printf '%s\n' "$saida" | grep -Fq 'Titulo: LivroB'
printf '%s\n' "$saida" | grep -Fq 'Titulo: LivroC'

linha_a=$(printf '%s\n' "$saida" | grep -n -m 1 '^Titulo: LivroA$' | cut -d: -f1)
linha_b=$(printf '%s\n' "$saida" | grep -n -m 1 '^Titulo: LivroB$' | cut -d: -f1)
linha_c=$(printf '%s\n' "$saida" | grep -n -m 1 '^Titulo: LivroC$' | cut -d: -f1)
test "$linha_a" -lt "$linha_b"
test "$linha_b" -lt "$linha_c"

echo 'Testes do sistema aprovados'
