#pragma once

#include <string>
#include <ostream>

typedef enum TokenType {
    IDENTIFIER,
    STRING,
    NUMBER,
    ENDPOINT,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    UNKNOWN,
    END_OF_FILE
} TokenType;

typedef struct Token {
    std::string literal;
    TokenType type;

    bool isTypeIn(TokenType const arr[], size_t size) const;
} Token;

std::ostream &operator<<(std::ostream &o, Token const &t);
std::ostream &operator<<(std::ostream &o, TokenType t);
