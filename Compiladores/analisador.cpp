#include <iostream>
#include <cctype>
#include <stack>
using namespace std;

class Parser {
private:
    char lookahead;
    void match(char t) {
        if (lookahead == t) {
            cin >> noskipws >> lookahead;  // Próximo caractere
        } else {
            throw runtime_error("Syntax error");
        }
    }

    void expr() {
        term();
        while (lookahead == '+' || lookahead == '-') {
            char op = lookahead;
            match(op);
            term();
            cout << op;
        }
    }

    void term() {
        factor();
        while (lookahead == '*' || lookahead == '/') {
            char op = lookahead;
            match(op);
            factor();
            cout << op;
        }
    }

    void factor() {
        if (isdigit(lookahead)) {
            cout << lookahead;
            match(lookahead);
        } else if (lookahead == '(') {
            match('(');
            expr();
            match(')');
        } else {
            throw runtime_error("Syntax error");
        }
    }

public:
    void parse() {
        cin >> noskipws >> lookahead;  // Lê o primeiro caractere
        expr();
        cout << endl;
    }
};

int main() {
    try {
        Parser parser;
        parser.parse();
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
