#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "codegen/codegen.hpp"

int main() {
    std::ifstream source("program.hg");
    std::ofstream compiled("program.asm");

    std::string s;

    lexer.pos_in_vector_tokens = -1;

    while (std::getline(source, s)) {
        tokenize(s); // Tokenize each line of code

    }

    for (int i = 0; i < tokens.size(); ++i) {
        Token* newToken = requestAnotherToken();
        std::cout << "{Value: " << newToken->value << " | Token Type: " << typeToString(newToken->type) << " | Line: " << newToken->line << "}" << std::endl;
    }

}