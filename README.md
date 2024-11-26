# Conversor de Expressões Infixadas para Pós-Fixadas

Este projeto implementa um **tradutor de expressões aritméticas infixadas para pós-fixadas** (notação polonesa reversa) em **C++**. O programa converte expressões matemáticas que envolvem números, operadores básicos (`+`, `-`, `*`, `/`) e parênteses.

---

## 📋 Funcionalidades

- **Entrada:** Expressões infixadas (ex.: `3+(2*5)-8/4`).
- **Saída:** Expressões pós-fixadas (ex.: `325*+84/-`).
- **Suporte aos operadores:** Soma (`+`), Subtração (`-`), Multiplicação (`*`), Divisão (`/`) e Parênteses (`(` e `)`).

---

## 🛠️ Pré-requisitos

- **Compilador C++:** `g++` (GNU Compiler Collection) ou equivalente.
- **Sistema Operacional:** Linux, macOS ou Windows (com MinGW configurado).

---

## 🚀 Compilação

1. Certifique-se de que o arquivo-fonte está salvo como `parser.cpp`.
2. Abra o terminal na pasta onde o arquivo está localizado.
3. Execute o comando abaixo para compilar o programa:

   ```bash
   g++ parser.cpp -o parser

