#pragma once

#include <string>

typedef enum TokenType {
    IDENTIFIER,
    STRING,
    NUMBER,
    ENDPOINT,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    UNKNOWN
} TokenType;

typedef struct Token {
    std::string literal;
    TokenType type;
} Token;
