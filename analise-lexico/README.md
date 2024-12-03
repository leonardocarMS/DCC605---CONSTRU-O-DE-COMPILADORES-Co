# Analisador Léxico

## 📋 Funcionalidades

- **Entrada:** Expressões infixadas (ex.:
`int a = 20;
if (a <= 40) { // Comentário de linha
    /* Comentário de bloco
       múltiplas linhas */
    cout << "a é menor ou igual a 10" << endl;
}
`).
- **Saída:** Expressões pós-fixadas (ex.:
`Word: int
Word: a
Word: =
Num: 5
Word: ;
Word: if
Word: (
Word: a
Word: <=
Word: =
Num: 10
Word: )
Word: {`).

## 🚀 Compilação

1. Certifique-se de que o arquivo-fonte está salvo como `lexer.cpp`.
2. Abra o terminal na pasta onde o arquivo está localizado.
3. Execute o comando abaixo para compilar o programa:

   ```bash
   g++ lexer.cpp -o lexer
-------
   ```bash
   ./lexer
