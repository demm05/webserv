#pragma once

#include "Token.hpp"

#include <vector>

class Lexer {
public:
    typedef std::vector<Token> TokenArray;
    static void tokenize(std::string const &content, TokenArray &res);
    static void printTokens(TokenArray const &tokens);

private:
    Lexer(std::string const &content, std::vector<Token> &res);

    std::string const &content_;
    TokenArray &tokens_;
    size_t pos_;
    char ch_;

    void run();

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
