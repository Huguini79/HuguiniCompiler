#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.hpp"
#include "../codegen/codegen.hpp"

// Palabra reservada + Identificador + Operador + Token numérico + Separador (punto y coma)
std::vector<TokenType> variable_int_grammar = {TokenType::Keyword, TokenType::Identifier, TokenType::Operator, TokenType::Number, TokenType::Separator};

// Palabra reservada + Token numérico + Separador (punto y coma)
std::vector<TokenType> return_grammar = {TokenType::Keyword, TokenType::Number, TokenType::Separator};

bool checkReturn(Token *newToken)
{
    if (newToken->type == return_grammar[0])
    {
        Token *anotherToken = requestAnotherToken();
        if (anotherToken->type == return_grammar[1])
        {
            Token *anotherToken2 = requestAnotherToken();
            if (anotherToken2->type == return_grammar[2])
            {
                CodeGenCreateReturn(anotherToken);
                return true;
            }
        }
    }

    return false;
}

bool checkStart(Token *newToken)
{
    if (newToken->value == "start")
    {
        CodeGenCreateStart();
        return true;
    }

    return false;
}

void checkGrammar()
{
    Token *newToken = requestAnotherToken();
    if (checkStart(newToken))
    {
        lexer.pos_in_vector_tokens++;
        newToken = requestAnotherToken();
    }
    else
    {
    }

    if (checkReturn(newToken))
    {
        newToken = requestAnotherToken();
    }
}

void initParser()
{
    checkGrammar();
}

#endif