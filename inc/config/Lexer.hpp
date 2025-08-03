#pragma once

#include "Token.hpp"

#include <vector>

class Lexer {
public:
    Lexer(std::string const &content, std::vector<Token> &res);
    void tokenize();
    void printTokens();

private:
    std::string const &content_;
    std::vector<Token> tokens_;
    size_t pos_;
    char ch_;

    void pushToken(TokenType type, std::string const &literal);
    void pushToken(TokenType type, char);
    void readChar();
    void eatWhitespaces();
    void identifyLastToken();

    bool isPunctuation();
    bool handleValue();
    void handleComment();
    void handleUnknown();
    void handlePunctuation();
};
