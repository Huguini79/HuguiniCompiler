#ifndef LEXER_H
#define LEXER_H

enum IdentifierType
{
    Function, // pos in enum = 0
    Variable, // pos in enum = 1
};

enum IdentifierKeywordType
{
    Int,       // pos in enum = 0
    Char,      // pos in enum = 1
    Float,     // pos in enum = 2
    Uint8_t,   // pos in enum = 3
    Uint16_t,  // pos in enum = 4
    Uint32_t,  // pos in enum = 5
    Uint64_t,  // pos in enum = 6
    AFunction, // pos in enum = 7
};

enum TokenType
{
    Identifier, // pos in enum = 0
    Number,     // pos in enum = 1
    String,     // pos in enum = 2
    Equals,     // pos in enum = 3
    Spot,       // pos in enum = 4
    OpenParen,  // pos in enum = 5
    CloseParen, // pos in enum = 6
    OpenKey,    // pos in enum = 7
    CloseKey,   // pos in enum = 8
    Operator,   // pos in enum = 9
    Keyword,    // pos in enum = 10
    Separator,  // pos in enum = 11
    Start,      // pos in enum = 12
};

struct AIdentifier
{
    std::string value;
    IdentifierType type;
    IdentifierKeywordType keyword_type;

    /* METADATA */
    int line;
};

struct Token
{
    std::string value;
    TokenType type;

    /* METADATA */
    int line;
};

struct Lexer
{
    int line;
    int pos_in_vector_tokens;
};

bool token_encontrado = false;

bool token_string_encontrado = false;

struct Lexer lexer;

std::vector<Token> tokens = {};

// Tabla de símbolos
std::vector<AIdentifier> identifiers = {};

std::vector<char> operator_symbols = {
    '=', '+', '-', '*', '/', '&', '|'};

std::vector<char> special_symbols = {
    '%', '$', '#', '!', '?', '"'};

std::vector<char> separator_symbols = {
    '{', '}', '(', ')', ';', ':', '.', '[', ']', ' '};

std::vector<std::string> Keywords = {
    "int", "char", "void", "return", "param", "print", "float",
    "uint16_t", "uint32_t", "uint64_t", "uint8_t"};

Token lastTypeToken;

std::string typeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::Identifier:
        return "TOKEN_IDENTIFIER";
    case TokenType::Number:
        return "TOKEN_NUMBER";
    case TokenType::String:
        return "TOKEN_STRING";
    case TokenType::Equals:
        return "TOKEN_EQUALS";
    case TokenType::Spot:
        return "TOKEN_SPOT";
    case TokenType::OpenParen:
        return "TOKEN_OPEN_PAREN";
    case TokenType::CloseParen:
        return "TOKEN_CLOSE_PAREN";
    case TokenType::OpenKey:
        return "TOKEN_OPEN_KEY";
    case TokenType::CloseKey:
        return "TOKEN_CLOSE_KEY";
    case TokenType::Operator:
        return "TOKEN_OPERATOR";
    case TokenType::Keyword:
        return "TOKEN_KEYWORD";
    case TokenType::Separator:
        return "TOKEN_SEPARATOR";
    case TokenType::Start:
        return "TOKEN_START";
    default:
        return "TOKEN_UNKNOWN";
    }
}

std::string typeIdenttoString(IdentifierType type)
{
    switch (type)
    {
    case IdentifierType::Function:
        return "FUNCTION";
    case IdentifierType::Variable:
        return "VARIABLE";
    default:
        return "UNKNOWN";
    }
}

std::string keywordTypeIdentToString(IdentifierKeywordType type)
{
    switch (type)
    {
    case IdentifierKeywordType::Int:
        return "INT";
    case IdentifierKeywordType::Char:
        return "CHAR";
    case IdentifierKeywordType::Float:
        return "FLOAT";
    case IdentifierKeywordType::Uint8_t:
        return "UINT8_T";
    case IdentifierKeywordType::Uint16_t:
        return "UINT16_T";
    case IdentifierKeywordType::Uint32_t:
        return "UINT32_T";
    case IdentifierKeywordType::Uint64_t:
        return "UINT64_T";
    case IdentifierKeywordType::AFunction:
        return "FUNCTION";
    default:
        return "UNKNOWN";
    }
}

bool theIdentifierIsInTheList(AIdentifier identifier)
{
    for (auto a : identifiers)
    {
        if (a.value == identifier.value)
        {
            return true;
        }
    }

    return false;
}

struct Token *requestAnotherToken()
{
    lexer.pos_in_vector_tokens++;

    return &tokens[lexer.pos_in_vector_tokens];
}

bool isNumber(std::string &buffer)
{
    for (auto a : buffer)
    {
        if (!isdigit(a))
            return false;
    }

    return !buffer.empty();
}

bool detectKeyword(std::string &buf)
{
    for (auto a : Keywords)
    {
        if (buf == a)
        {
            return true;
        }
    }

    return false;
}

bool detectNumber(std::string &buf)
{
    if (isNumber(buf))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool detectStart(std::string &buf)
{
    if (buf == "start")
    {
        return true;
    }

    return false;
}

void separationDetected(std::string &buf, char op_separador)
{
    if (detectKeyword(buf))
    {
        tokens.push_back({buf, TokenType::Keyword, lexer.line});
        lastTypeToken = {buf, TokenType::Keyword, lexer.line};
        buf = "";
    }
    else if (detectNumber(buf))
    {
        tokens.push_back({buf, TokenType::Number, lexer.line});
        lastTypeToken = {buf, TokenType::Number, lexer.line};
        buf = "";
    }
    else if (detectStart(buf))
    {
        tokens.push_back({buf, TokenType::Start, lexer.line});
        lastTypeToken = {buf, TokenType::Start, lexer.line};
        buf = "";
    }

    else
    {
        if (buf != "")
        {
            tokens.push_back({buf, TokenType::Identifier, lexer.line});

            AIdentifier newIdentifier;
            newIdentifier.value = buf;

            if (!theIdentifierIsInTheList(newIdentifier))
            {
                // No está en la lista de identificadores, vamos a añadirlo a la lista
                if (lastTypeToken.value == "void" && lastTypeToken.type == TokenType::Keyword)
                {
                    identifiers.push_back({buf, IdentifierType::Function, IdentifierKeywordType::AFunction, lexer.line});
                    lastTypeToken = {buf, TokenType::Identifier, lexer.line};
                    buf = "";
                }
                else if ((lastTypeToken.value == "int") && lastTypeToken.type == TokenType::Keyword)
                {
                    identifiers.push_back({buf, IdentifierType::Variable, IdentifierKeywordType::Int, lexer.line});
                    lastTypeToken = {buf, TokenType::Identifier, lexer.line};
                    buf = "";
                }
                else if ((lastTypeToken.value == "char") && lastTypeToken.type == TokenType::Keyword)
                {
                    identifiers.push_back({buf, IdentifierType::Variable, IdentifierKeywordType::Char, lexer.line});
                    lastTypeToken = {buf, TokenType::Identifier, lexer.line};
                    buf = "";
                }

                else if ((lastTypeToken.value == "float") && lastTypeToken.type == TokenType::Keyword)
                {
                    identifiers.push_back({buf, IdentifierType::Variable, IdentifierKeywordType::Float, lexer.line});
                    lastTypeToken = {buf, TokenType::Identifier, lexer.line};
                    buf = "";
                }

                else if ((lastTypeToken.value == "uint8_t") && lastTypeToken.type == TokenType::Keyword)
                {
                    identifiers.push_back({buf, IdentifierType::Variable, IdentifierKeywordType::Uint8_t, lexer.line});
                    lastTypeToken = {buf, TokenType::Identifier, lexer.line};
                    buf = "";
                }
                else if ((lastTypeToken.value == "uint16_t") && lastTypeToken.type == TokenType::Keyword)
                {
                    identifiers.push_back({buf, IdentifierType::Variable, IdentifierKeywordType::Uint16_t, lexer.line});
                    lastTypeToken = {buf, TokenType::Identifier, lexer.line};
                    buf = "";
                }

                else if ((lastTypeToken.value == "uint32_t") && lastTypeToken.type == TokenType::Keyword)
                {
                    identifiers.push_back({buf, IdentifierType::Variable, IdentifierKeywordType::Uint32_t, lexer.line});
                    lastTypeToken = {buf, TokenType::Identifier, lexer.line};
                    buf = "";
                }
                else if ((lastTypeToken.value == "uint64_t") && lastTypeToken.type == TokenType::Keyword)
                {
                    identifiers.push_back({buf, IdentifierType::Variable, IdentifierKeywordType::Uint64_t, lexer.line});
                    lastTypeToken = {buf, TokenType::Identifier, lexer.line};
                    buf = "";
                }
            }
            else
            {
                if ((lastTypeToken.value == "int" || lastTypeToken.value == "char" || lastTypeToken.value == "float" || lastTypeToken.value == "uint8_t" || lastTypeToken.value == "uint16_t" || lastTypeToken.value == "uint32_t" || lastTypeToken.value == "uint64_t" || lastTypeToken.value == "void") && lastTypeToken.type == TokenType::Keyword)
                {
                    std::cerr << "ERROR, THIS IDENTIFIER ALREDY EXITS: " << buf << " | Error in line: " << lexer.line << std::endl
                              << std::endl;
                    exit(1);
                }
            }

            buf = "";
        }
    }
    if (op_separador != ' ')
    {
        tokens.push_back({std::string(1, op_separador), TokenType::Separator, lexer.line});
    }
    // token_string_encontrado = false;
}

void tokenize(std::string &source)
{
    std::string buf;

    lexer.line++;

    for (int i = 0; i < source.size(); ++i)
    {

        if (source[i] == '/' && source[i + 1] == '/')
        {
            break;
        }

        if (std::isalpha(source[i]))
        {
            buf += source[i];
            continue;
        }

        if (std::isdigit(source[i]))
        {
            buf += source[i];
            continue;
        }

        if (std::isspace(source[i]) && token_string_encontrado == true)
        {
            buf += source[i];
        }

        for (auto a : operator_symbols)
        {
            if (source[i] == a)
            {
                tokens.push_back({std::string(1, a), TokenType::Operator, lexer.line});
                lastTypeToken = {std::string(1, a), TokenType::Operator, lexer.line};
                buf = "";
            }
        }

        for (auto a : special_symbols)
        {
            if (source[i] == a)
            {
                buf += source[i];
            }
        }

        if (token_string_encontrado == true)
        {
            tokens.push_back({buf, TokenType::String, lexer.line});
            lastTypeToken = {buf, TokenType::String, lexer.line};
            buf = "";
        }

        if (source[i] == '"')
        {
            token_string_encontrado = !token_string_encontrado;
        }

        for (auto a : separator_symbols)
        {
            if (source[i] == a && token_string_encontrado == false)
            {
                char op_separador = a;
                separationDetected(buf, op_separador);
            }
        }

        if (source[i] == '_')
        {
            buf += source[i];
        }
    }
}

#endif