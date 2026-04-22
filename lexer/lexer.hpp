#ifndef LEXER_H
#define LEXER_H

enum TokenType {
    Identifier,     // pos in enum = 0
    Number,         // pos in enum = 1
    String,         // pos in enum = 2
    Equals,         // pos in enum = 3
    Spot,           // pos in enum = 4
    OpenParen,      // pos in enum = 5
    CloseParen,     // pos in enum = 6
    OpenKey,        // pos in enum = 7
    CloseKey,       // pos in enum = 8
    Operator,       // pos in enum = 9
    Keyword,        // pos in enum = 10
    Separator,      // pos in enum = 11
};

struct Token {
    std::string value;
    TokenType type;

    /* METADATA */
    int line;
};

struct Lexer {
    int line;
    int pos_in_vector_tokens;
};

bool token_encontrado = false;

struct Lexer lexer;

std::vector<Token> tokens = {};

std::vector<char> operator_symbols = {
    '=', '+', '-', '*', '/', '&', '|'
};

std::vector<char> special_symbols = {
    '%', '$', '#', '!', '?', '"'
};

std::vector<char> separator_symbols = {
    '{', '}', '(', ')', ';', '.', ':', '[', ']', ' '
};

TokenType lastTypeToken;

std::string typeToString(TokenType type) {
    switch (type) {
        case 0: return "TOKEN_IDENTIFIER";
        case 1: return "TOKEN_NUMBER";
        case 2: return "TOKEN_STRING";
        case 3: return "TOKEN_EQUALS";
        case 4: return "TOKEN_SPOT";
        case 5: return "TOKEN_OPEN_PAREN";
        case 6: return "TOKEN_CLOSE_PAREN";
        case 7: return "TOKEN_OPEN_KEY";
        case 8: return "TOKEN_CLOSE_KEY";
        case 9: return "TOKEN_OPERATOR";
        case 10: return "TOKEN_KEYWORD";
        case 11: return "TOKEN_SEPARATOR";
        default: return "TOKEN_UNKNOWN";
    }
}

struct Token* requestAnotherToken() {
    lexer.pos_in_vector_tokens++;
    
    Token * token = new Token();
    token->value = tokens[lexer.pos_in_vector_tokens].value;
    token->type = tokens[lexer.pos_in_vector_tokens].type;
    token->line = tokens[lexer.pos_in_vector_tokens].line;

    return token;

}

bool isNumber(std::string &buffer) {
    for (auto a : buffer) {
        if (!isdigit(a)) return false;
    }

    return !buffer.empty();

}

bool detectKeyword(std::string &buf) {
    if (buf == "int") {return true;} 
    else if (buf == "return") {return true;}
    else if (buf == "char") {return true;}
    else {
        return false;
    }
}

bool detectNumber(std::string &buf) {
    if (isNumber(buf)) {return true;}
    else {
        return false;
    }
}

void separacionDetectada(std::string &buf, char op_separador) {
    if (detectKeyword(buf)) {
        tokens.push_back({buf, TokenType::Keyword, lexer.line});
        lastTypeToken = TokenType::Keyword;
        buf = "";

    } else if (detectNumber(buf)) {
        tokens.push_back({buf, TokenType::Number, lexer.line});
        lastTypeToken = TokenType::Number;
        buf = "";
    
    } else {
        if (lastTypeToken == TokenType::Keyword && buf != "") {
            tokens.push_back({buf, TokenType::Identifier, lexer.line});
            buf = "";
        }
    }
    if (op_separador != ' ') {tokens.push_back({std::string(1, op_separador), TokenType::Separator, lexer.line});}
}

void tokenize(std::string &source) {
    std::string buf;

    lexer.line++;
    
        for (int i = 0; i < source.size(); ++i) {
            if (std::isalpha(source[i])) {
                buf += source[i];
                
            }
            
            if (std::isdigit(source[i])) {
                buf += source[i];
                
            }

            for (auto a : operator_symbols) {
                if (source[i] == a) {
                    tokens.push_back({std::string(1, a), TokenType::Operator, lexer.line});
                    buf = "";
                }
                
            }

            for (auto a : special_symbols) {
                if (source[i] == a) {
                    buf += source[i];
                }
            }

            for (auto a : separator_symbols) {
                    if (source[i] == a) {
                        char op_separador = a;
                        separacionDetectada(buf, op_separador);
                    }
            }

            /*
            if (std::isspace(source[i])) {
                separacionDetectada(buf);
            }
                */
        }
    
}

#endif