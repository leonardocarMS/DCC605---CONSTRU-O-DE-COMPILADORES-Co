#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype> // Para funções como isdigit() e isspace()

using namespace std;

// Definição dos tokens básicos
enum class Tag { TRUE, FALSE, ID, NUM, LT, LE, EQ, NE, GE, GT, OTHER };

// Classe base para tokens
class Token {
public:
    virtual ~Token() = default;
    virtual void print() const { cout << "Token: " << endl; }
};

// Classe para números
class Num : public Token {
public:
    int value;
    Num(int v) : value(v) {}
    void print() const override { cout << "Num: " << value << endl; }
};

// Classe para palavras reservadas e identificadores
class Word : public Token {
public:
    string lexeme;
    Tag tag;

    Word(Tag t, const string &lex) : lexeme(lex), tag(t) {}
    void print() const override { cout << "Word: " << lexeme << endl; }
};

// Classe do analisador léxico (Lexer)
class Lexer {
private:
    int line = 1;
    char peek = ' ';
    unordered_map<string, Word*> words;

    void reserve(Word* w) { words[w->lexeme] = w; }
    void readNextChar() { peek = cin.get(); }

public:
    Lexer() {
        reserve(new Word(Tag::TRUE, "true"));
        reserve(new Word(Tag::FALSE, "false"));
    }

    ~Lexer() {
        for (auto &pair : words) {
            delete pair.second;
        }
    }

    Token* scan() {
        while (isspace(peek)) {
            if (peek == '\n') line++;
            readNextChar();
        }

        // Remoção de comentários
        if (peek == '/') {
            readNextChar();
            if (peek == '/') {
                while (peek != '\n' && peek != EOF) {
                    readNextChar();
                }
                return scan();
            } else if (peek == '*') {
                while (true) {
                    readNextChar();
                    if (peek == '*' && cin.peek() == '/') {
                        readNextChar();
                        readNextChar();
                        break;
                    }
                    if (cin.eof()) return nullptr; // Evita loop infinito
                }
                return scan();
            } else {
                return new Word(Tag::OTHER, "/");
            }
        }

        // Reconhecimento de operadores relacionais
        if (peek == '<' || peek == '>' || peek == '=' || peek == '!') {
            char current = peek;
            readNextChar();
            if (peek == '=') {
                switch (current) {
                    case '<': return new Word(Tag::LE, "<=");
                    case '>': return new Word(Tag::GE, ">=");
                    case '=': return new Word(Tag::EQ, "==");
                    case '!': return new Word(Tag::NE, "!=");
                }
            } else {
                switch (current) {
                    case '<': return new Word(Tag::LT, "<");
                    case '>': return new Word(Tag::GT, ">");
                    default: return new Word(Tag::OTHER, string(1, current));
                }
            }
        }

        // Reconhecimento de números
        if (isdigit(peek)) {
            int v = 0;
            do {
                v = 10 * v + (peek - '0');
                readNextChar();
            } while (isdigit(peek));
            return new Num(v);
        }

        // Identificadores e palavras reservadas
        if (isalpha(peek)) {
            string lexeme;
            do {
                lexeme += peek;
                readNextChar();
            } while (isalnum(peek));

            if (words.find(lexeme) != words.end()) {
                return words[lexeme];
            }
            Word* w = new Word(Tag::ID, lexeme);
            words[lexeme] = w;
            return w;
        }

        // Outros símbolos
        if (!cin.eof()) {
            Token* t = new Word(Tag::OTHER, string(1, peek));
            readNextChar();
            return t;
        }

        return nullptr; // Fim da entrada
    }
};

// Função principal (para teste)
int main() {
    Lexer lexer;

    cout << "Digite a entrada (Ctrl+D para encerrar):" << endl;
    Token* token;
    while (cin.peek() != EOF) {
        token = lexer.scan();
        if (token != nullptr) {
            token->print();
            delete token;
        }
    }

    return 0;
}
