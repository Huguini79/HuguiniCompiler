#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.hpp"
#include "../codegen/codegen.hpp"

// Palabra reservada + Identificador + Operador + Token numérico + Separador (punto y coma)
std::vector<TokenType> variable_int_grammar = {TokenType::Keyword, TokenType::Identifier, TokenType::Operator, TokenType::Number, TokenType::Separator};

// Palabra reservada + Token numérico + Separador (punto y coma)
std::vector<TokenType> return_grammar = {TokenType::Keyword, TokenType::Number, TokenType::Separator};

// Palabra reservada + Identifier + Separador (punto y coma)
std::vector<TokenType> print_grammar = {TokenType::Keyword, TokenType::Identifier, TokenType::Separator};

// Tokens
Token *newToken;
Token *anotherToken;
Token *anotherToken2;
Token *anotherToken3;
Token *anotherToken4;
Token *anotherToken5;

bool checkReturn(Token *newToken)
{
    int origin = lexer.pos_in_vector_tokens;
    if (newToken->type == return_grammar[0] && newToken->value == "return") // return
    {
        anotherToken = requestAnotherToken();
        if (anotherToken->type == return_grammar[1]) // number
        {
            anotherToken2 = requestAnotherToken(); // ;
            if (anotherToken2->type == return_grammar[2])
            {
                return true;
            }
        }
        else if (anotherToken->type == TokenType::Identifier)
        {                                          // identifier
            anotherToken2 = requestAnotherToken(); // ;
            if (anotherToken2->type == return_grammar[2])
            {
                return true;
            }
        }
    }
    lexer.pos_in_vector_tokens = origin;
    return false;
}

bool checkStart(Token *newToken)
{
    int origin = lexer.pos_in_vector_tokens;
    if (newToken->value == "start" && newToken->type == TokenType::Start)
    {
        return true;
    }
    lexer.pos_in_vector_tokens = origin;
    return false;
}

bool checkVariable(Token *newToken)
{
    int origin = lexer.pos_in_vector_tokens;
    if (newToken->type == variable_int_grammar[0]) // int
    {
        anotherToken = requestAnotherToken();
        if (anotherToken->type == variable_int_grammar[1]) // identifier
        {
            anotherToken2 = requestAnotherToken();
            if (anotherToken2->type == variable_int_grammar[2]) // =
            {
                anotherToken3 = requestAnotherToken();
                if (anotherToken3->type == variable_int_grammar[3]) // number
                {
                    anotherToken4 = requestAnotherToken();
                    if (anotherToken4->type == variable_int_grammar[4]) // ;
                    {
                        return true;
                    }
                }
            }
        }
    }
    lexer.pos_in_vector_tokens = origin;
    return false;
}

bool checkPrint(Token *newToken)
{
    int origin = lexer.pos_in_vector_tokens;

    if (newToken->type == print_grammar[0] && newToken->value == "print")
    {
        anotherToken = requestAnotherToken();
        if (anotherToken->type == print_grammar[1])
        {
            anotherToken2 = requestAnotherToken();
            if (anotherToken2->type == print_grammar[2])
            {
                return true;
            }
        }
    }

    lexer.pos_in_vector_tokens = origin;
    return false;
}

void check(Token *newToken)
{
    lexer.pos_in_vector_tokens = -1;
    for (int i = 0; i < tokens.size(); ++i)
    {
        newToken = requestAnotherToken();

        if (checkStart(newToken))
        {
            CodeGenCreateStart();
        }
        else if (checkVariable(newToken))
        {
            CodeGenCreateVariable(anotherToken, anotherToken3);
        }
        else if (checkReturn(newToken))
        {
            CodeGenCreateReturn(anotherToken);
        }
        else if (checkPrint(newToken))
        {
            CodeGenCreatePrint(anotherToken);
        }
    }
}

void checkGrammar()
{
    newToken = requestAnotherToken();
    check(newToken);
}

void initParser()
{
    checkGrammar();
}

#endif