#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

string expression;
int pos = 0;


void skipWhitespace() {
    while (pos < expression.size() && isspace(expression[pos])) {
        pos++;
    }
}

int parseExpression();

int parseFactor() {
    skipWhitespace();

    bool isNegative = false;
    if (expression[pos] == '-') {
        isNegative = true;
        pos++;
    }

    skipWhitespace();

    if (pos < expression.size() && expression[pos] == '(') {
        pos++; 
        int result = parseExpression();
        skipWhitespace();
        if (pos < expression.size() && expression[pos] == ')') {
            pos++; 
        } else {
            cout << "Error: Missing closing parenthesis\n";
            exit(1);
        }
        return isNegative ? -result : result;
    }

    int number = 0;
    bool found = false;
    while (pos < expression.size() && isdigit(expression[pos])) {
        found = true;
        number = number * 10 + (expression[pos] - '0');
        pos++;
    }

    if (!found) {
        cout << "Error: Expected a number\n";
        exit(1);
    }

    return isNegative ? -number : number;
}

int parseTerm() {
    int result = parseFactor();
    skipWhitespace();

    while (pos < expression.size()) {
        skipWhitespace();
        char op = expression[pos];

        if (op == '*' || op == '/') {
            pos++;
            int next = parseFactor();

            if (op == '*') {
                result *= next;
            } else {
                if (next == 0) {
                    cout << "Error: Division by zero\n";
                    exit(1);
                }
                result /= next;
            }
        } else {
            break;
        }
    }

    return result;
}

int parseExpression() {
    int result = parseTerm();
    skipWhitespace();

    while (pos < expression.size()) {
        skipWhitespace();
        char op = expression[pos];

        if (op == '+' || op == '-') {
            pos++;
            int next = parseTerm();

            if (op == '+') {
                result += next;
            } else {
                result -= next;
            }
        } else {
            break;
        }
    }

    return result;
}

int main() {
    cout << "=== Arithmetic Expression Compiler ===" << endl;
    cout << "Type 'exit' to quit.\n" << endl;

    while (true) {
        cout << "Enter an arithmetic expression: ";
        getline(cin, expression);

        if (expression == "exit") break;

        pos = 0;
        int result = 0;

        try {
            result = parseExpression();
            skipWhitespace();
            if (pos != expression.size()) {
                cout << "Error: Unexpected character at position " << pos << endl;
            } else {
                cout << "Result: " << result << endl;
            }
        } catch (...) {
            cout << "Error: Invalid expression.\n";
        }
    }

    return 0;
}
