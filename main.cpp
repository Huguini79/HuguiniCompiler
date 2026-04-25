#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "codegen/codegen.hpp"

int main()
{
    std::ifstream source("program.hg");

    std::string s;

    lexer.pos_in_vector_tokens = -1;

    while (std::getline(source, s))
    {
        tokenize(s); // Tokenize each line of code
    }

    std::cout << "-------------------------------------------------------" << std::endl
              << "LEXER" << std::endl
              << "-------------------------------------------------------" << std::endl
              << std::endl;
    if (tokens.size() == 0)
    {
        std::cout << "NO TOKENS GENERATED" << std::endl;
    }
    else
    {
        Token *newToken;
        for (int i = 0; i < tokens.size(); ++i)
        {
            newToken = requestAnotherToken();
            std::cout << "{Value: " << newToken->value << " | Token Type: " << typeToString(newToken->type) << " | Line: " << newToken->line << "}" << std::endl;
        }
    }

    lexer.pos_in_vector_tokens = -1;

    std::cout << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl
              << "IDENTIFIERS DECLARATION" << std::endl
              << "-------------------------------------------------------" << std::endl
              << std::endl;
    if (identifiers.size() == 0)
    {
        std::cout << "NO IDENTIFIERS GENERATED" << std::endl
                  << std::endl;
    }
    else
    {

        for (int i = 0; i < identifiers.size(); ++i)
        {
            std::cout << identifiers[i].value << " " << typeIdenttoString(identifiers[i].type) << " " << keywordTypeIdentToString(identifiers[i].keyword_type) << " | Line: " << identifiers[i].line << std::endl;
        }
    }

    initParser();
}