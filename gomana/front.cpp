#include <iostream>
#include <fstream>  
#include <cctype>
#include <string>

using namespace std;

// Character classes
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

// Token codes
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26


// Class to define the cuurent and next charchter 
class Lexer {
private:
    int charClass;
    string lexeme;
    char nextChar;
    int lexLen;
    int token;
    int nextToken;
    ifstream inFile;

public:
    // Constructor to open the input file and get the first character
    Lexer(const string& filename) {
        inFile.open(filename);
        if (!inFile) {
            cerr << "ERROR - cannot open " << filename << endl;
            exit(1);
        }
        getChar();
    }

    // Function to add the next character to the lexeme string
    void addChar() {
        if (lexeme.length() < 99) {
            lexeme += nextChar;
        } else {
            cout << "Error - lexeme is too long\n";
        }
    }

    // Function to get the next character from the file and identify it
    void getChar() {
        if (inFile.get(nextChar)) {
            if (isalpha(nextChar))
                charClass = LETTER;
            else if (isdigit(nextChar))
                charClass = DIGIT;
            else
                charClass = UNKNOWN;
        } else {
            charClass = EOF;
        }
    }

    // Function to skip over whitespace characters
    void getNonBlank() {
        while (isspace(nextChar)) {
            getChar();
        }
    }

    // Function to handle the recognition of operators and parentheses
    //  a function to lookup operators and parentheses and return the token
    int lookup(char ch) {
        switch (ch) {
            case '(':
                addChar();
                nextToken = LEFT_PAREN;
                break;
            case ')':
                addChar();
                nextToken = RIGHT_PAREN;
                break;
            case '+':
                addChar();
                nextToken = ADD_OP;
                break;
            case '-':
                addChar();
                nextToken = SUB_OP;
                break;
            case '*':
                addChar();
                nextToken = MULT_OP;
                break;
            case '/':
                addChar();
                nextToken = DIV_OP;
                break;
            case '=':  // Handling the assignment operator (=)
                addChar();
                nextToken = ASSIGN_OP;
                break;
            default:
                addChar();
                nextToken = EOF;
                break;
        }
        return nextToken;
    }

    // Function to analyze the input and identify tokens
    int lex() {
        lexeme = "";  // Reset the lexeme string
        getNonBlank();  // Skip any leading whitespace

        switch (charClass) {
            case LETTER:
                addChar();
                getChar();
                while (charClass == LETTER || charClass == DIGIT) {
                    addChar();
                    getChar();
                }
                nextToken = IDENT;
                break;

            case DIGIT:
                addChar();
                getChar();
                while (charClass == DIGIT) {
                    addChar();
                    getChar();
                }
                nextToken = INT_LIT;
                break;

            case UNKNOWN:
                lookup(nextChar);  // Handle unknown characters (operators)
                getChar();
                break;

            case EOF:
                nextToken = EOF;
                lexeme = "EOF";
                break;
        }

        cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
        return nextToken;
    }

    // Function to check if the lexer has reached the end of the file
    bool isDone() const {
        return nextToken == EOF;
    }
};

// Main driver function
int main() {
    Lexer lexer("front.in");  // Create a lexer instance with the input file "front.in"

    do {
        lexer.lex();  // Get the next token
    } while (!lexer.isDone());  // Continue until the end of the file
    
        // Your code here
        system("pause"); // Wait for user input before closing

    

    return 0;
}
