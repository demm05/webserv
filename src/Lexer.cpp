#include "Parse.hpp"
#include <iostream>

Lexer::Lexer(std::string const &content, std::vector<Token> &res)
    : content_(content), tokens_(res), csize_(content_.size()), pos_(0), read_pos_(0), ch_(0) {
    readChar();
}

void Lexer::tokenize() {
    while (pos_ < csize_ - 1) {
        eatWhitespaces();
        if (isFixedType()) {
            pushFixedType();
            continue;
        }
        parseWord();
    }
}

void Lexer::pushFixedType() {
    switch (ch_) {
    case '#':
        read_pos_ = content_.find('\n', pos_);
        break;
    case '{':
        pushToken(LEFT_BRACE, ch_);
        break;
    case '}':
        pushToken(RIGHT_BRACE, ch_);
        break;
    case ';':
        pushToken(SEMICOLON, ch_);
        break;
    default:
        return;
    };
    readChar();
}

bool Lexer::isFixedType() {
    static const char cases[] = {'#', '{', '}', ';'};
    static const size_t size = sizeof(cases) / sizeof(cases[0]);
    for (size_t i = 0; i < size; i++)
        if (ch_ == cases[i])
            return true;
    return false;
}

void Lexer::parseWord() {
    std::string word;
    while (pos_ < csize_ && !isFixedType() && !std::isspace(ch_)) {
        word.append(&ch_);
        readChar();
    }
    pushToken(STRING, word);
}

void Lexer::readChar() {
    if (read_pos_ >= csize_)
        ch_ = 0;
    else
        ch_ = content_[read_pos_];
    pos_ = read_pos_++;
}

char Lexer::peekChar() {
    if (read_pos_ >= csize_)
        return 0;
    return content_[read_pos_];
}

void Lexer::eatWhitespaces() {
    while (std::isspace(ch_))
        readChar();
}

void Lexer::pushToken(TokenType type, char c) {
    Token tok;
    tok.literal = std::string();
    tok.literal += c;
    tok.type = type;
    tokens_.push_back(tok);
}

void Lexer::pushToken(TokenType type, std::string const &literal) {
    Token tok;
    tok.literal = literal;
    tok.type = type;
    tokens_.push_back(tok);
}

void Lexer::pushToken(Token &tok) {
    tokens_.push_back(tok);
}

void Lexer::printTokens() {
    for (size_t i = 0; i < tokens_.size(); i++) {
        std::cout << tokens_[i].literal << " -> ";
    }
    std::cout << std::endl;
}
