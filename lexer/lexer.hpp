#ifndef LEXER_H
#define LEXER_H

enum IdentifierType {
    Function,
    Variable,
};

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

struct AIdentifier {
    std::string value;
    IdentifierType type;

    /* METADATA */
    int line;
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

std::vector<AIdentifier> identifiers = {};

std::vector<char> operator_symbols = {
    '=', '+', '-', '*', '/', '&', '|'
};

std::vector<char> special_symbols = {
    '%', '$', '#', '!', '?', '"'
};

std::vector<char> separator_symbols = {
    '{', '}', '(', ')', ';', '.', ':', '[', ']', ' '
};

Token lastTypeToken;

std::string typeToString(TokenType type) {
    switch (type) {
        case TokenType::Identifier: return "TOKEN_IDENTIFIER";
        case TokenType::Number: return "TOKEN_NUMBER";
        case TokenType::String: return "TOKEN_STRING";
        case TokenType::Equals: return "TOKEN_EQUALS";
        case TokenType::Spot: return "TOKEN_SPOT";
        case TokenType::OpenParen: return "TOKEN_OPEN_PAREN";
        case TokenType::CloseParen: return "TOKEN_CLOSE_PAREN";
        case TokenType::OpenKey: return "TOKEN_OPEN_KEY";
        case TokenType::CloseKey: return "TOKEN_CLOSE_KEY";
        case TokenType::Operator: return "TOKEN_OPERATOR";
        case TokenType::Keyword: return "TOKEN_KEYWORD";
        case TokenType::Separator: return "TOKEN_SEPARATOR";
        default: return "TOKEN_UNKNOWN";
    }
}

std::string typeIdenttoString(IdentifierType type) {
    switch (type) {
        case IdentifierType::Function: return "FUNCTION";
        case IdentifierType::Variable: return "VARIABLE";
        default: return "UNKNOWN";
    }
}

bool theIdentifierIsInTheList(AIdentifier* identifier) {
    for (auto a : identifiers) {
        if (a.value == identifier->value) {
            return true;
        }
    }

    return false;

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
    else if (buf == "function") {return true;}
    else if (buf == "print") {return true;}
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

void separationDetected(std::string &buf, char op_separador) {
    if (detectKeyword(buf)) {
        tokens.push_back({buf, TokenType::Keyword, lexer.line});
        lastTypeToken = {buf, TokenType::Keyword, lexer.line};
        buf = "";

    } else if (detectNumber(buf)) {
        tokens.push_back({buf, TokenType::Number, lexer.line});
        lastTypeToken = {buf, TokenType::Number, lexer.line};
        buf = "";
    
    } else {
        if (buf != "") {
            tokens.push_back({buf, TokenType::Identifier, lexer.line});
            
            AIdentifier* newIdentifier = new AIdentifier();
            newIdentifier->value = buf;

            if (!theIdentifierIsInTheList(newIdentifier)) {
                // No está en la lista de identificadores, vamos a añadirlo a la lista
                if (lastTypeToken.value == "function" && lastTypeToken.type == TokenType::Keyword) {
                    identifiers.push_back({buf, IdentifierType::Function, lexer.line});
                    buf = "";
                    
                } else if (lastTypeToken.value == "int"
                        || lastTypeToken.value == "char"
                        && lastTypeToken.type == TokenType::Keyword) {
                            identifiers.push_back({buf, IdentifierType::Variable, lexer.line});
                            buf = "";
                        }    
            } else {

            }
            

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
                        separationDetected(buf, op_separador);
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
