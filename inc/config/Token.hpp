#pragma once

#include <string>
#include <iostream>

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
    bool isTypeIn(TokenType const arr[], size_t size) const {
        if (!arr)
            return false;
        for (size_t i = 0; i < size; i++) {
            if (arr[i] == type)
                return true;
        }
        return false;
    }
    bool isAValue() {
        static const TokenType validTypes[] = {IDENTIFIER, STRING, NUMBER};
        static const size_t size = sizeof(validTypes) / sizeof(validTypes[0]);
        return isTypeIn(validTypes, size);
    }
} Token;
