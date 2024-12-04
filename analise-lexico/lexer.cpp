#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>
#include <memory> // Para smart pointers

using namespace std;

enum class Tag { TRUE, FALSE, ID, NUM, LT, LE, EQ, NE, GE, GT, OTHER };

class Token {
public:
    virtual ~Token() = default;
    virtual void print() const { cout << "Token" << endl; }
};

class Num : public Token {
public:
    int value;
    Num(int v) : value(v) {}
    void print() const override { cout << "Num: " << value << endl; }
};

class Word : public Token {
public:
    string lexeme;
    Tag tag;
    Word(Tag t, const string& lex) : tag(t), lexeme(lex) {}
    void print() const override { cout << "Word: " << lexeme << endl; }
};

class Lexer {
private:
    int line = 1;
    char peek = ' ';
    unordered_map<string, shared_ptr<Word>> words;

    void reserve(shared_ptr<Word> w) { words[w->lexeme] = w; }
    void readNextChar() { peek = cin.get(); }

public:
    Lexer() {
        reserve(make_shared<Word>(Tag::TRUE, "true"));
        reserve(make_shared<Word>(Tag::FALSE, "false"));
    }

    shared_ptr<Token> scan() {
        while (isspace(peek)) {
            if (peek == '\n') line++;
            readNextChar();
        }

        // Remoção de comentários
        if (peek == '/') {
            readNextChar();
            if (peek == '/') {
                while (peek != '\n' && !cin.eof()) readNextChar();
                return scan();
            } else if (peek == '*') {
                while (true) {
                    readNextChar();
                    if (peek == '*' && cin.peek() == '/') {
                        readNextChar(); readNextChar();
                        break;
                    }
                    if (cin.eof()) {
                        cerr << "Erro: Comentário não terminado!" << endl;
                        return nullptr;
                    }
                }
                return scan();
            } else {
                return make_shared<Word>(Tag::OTHER, "/");
            }
        }

        // Operadores relacionais
        if (peek == '<' || peek == '>' || peek == '=' || peek == '!') {
            char current = peek;
            readNextChar();
            if (peek == '=') {
                switch (current) {
                    case '<': return make_shared<Word>(Tag::LE, "<=");
                    case '>': return make_shared<Word>(Tag::GE, ">=");
                    case '=': return make_shared<Word>(Tag::EQ, "==");
                    case '!': return make_shared<Word>(Tag::NE, "!=");
                }
            } else {
                switch (current) {
                    case '<': return make_shared<Word>(Tag::LT, "<");
                    case '>': return make_shared<Word>(Tag::GT, ">");
                    default: return make_shared<Word>(Tag::OTHER, string(1, current));
                }
            }
        }

        // Números
        if (isdigit(peek)) {
            int v = 0;
            do {
                v = 10 * v + (peek - '0');
                readNextChar();
            } while (isdigit(peek));
            return make_shared<Num>(v);
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
            words[lexeme] = make_shared<Word>(Tag::ID, lexeme);
            return words[lexeme];
        }

        // Outros símbolos
        if (!cin.eof()) {
            auto t = make_shared<Word>(Tag::OTHER, string(1, peek));
            readNextChar();
            return t;
        }

        return nullptr;
    }
};

int main() {
    Lexer lexer;
    cout << "Digite a entrada (Ctrl+D para encerrar):" << endl;

    shared_ptr<Token> token;
    while (!cin.eof()) {
        token = lexer.scan();
        if (token) {
            token->print();
        }
    }

    return 0;
}
