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

    std::cout << "-------------------------------------------------------" << std::endl << "LEXER" << std::endl << "-------------------------------------------------------" << std::endl << std::endl;

    for (int i = 0; i < tokens.size(); ++i) {
        Token* newToken = requestAnotherToken();
        std::cout << "{Value: " << newToken->value << " | Token Type: " << typeToString(newToken->type) << " | Line: " << newToken->line << "}" << std::endl;
    }

    std::cout << std::endl << std::endl;

    std::cout << lastTypeToken.value << std::endl << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl << "IDENTIFIERS DECLARATION" << std::endl << "-------------------------------------------------------" << std::endl << std::endl;

    for (int i = 0; i < identifiers.size(); ++i) {
        std::cout << identifiers[i].value << " " << typeIdenttoString(identifiers[i].type)<< " | Line: " << identifiers[i].line << std::endl;
    }

}