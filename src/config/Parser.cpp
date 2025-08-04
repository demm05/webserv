#include "Parser.hpp"
#include <fstream>
#include <sstream>

Parser::Parser(char const *fpath) : pos_(0) {
    std::ifstream infile(fpath);
    if (!infile.is_open())
        throw std::runtime_error("`" + std::string(fpath) + "`: cannot be opened");
    std::stringstream buffer;
    buffer << infile.rdbuf();
    content_ = buffer.str();
    infile.close();
}

ServerConfig Parser::parseFile(char const *fpath) {
    Parser parser(fpath);
    parser.run();
    return parser.config_;
}

void Parser::run() {
    Lexer::tokenize(content_, tokens_);
    Lexer::printTokens(tokens_);
    handleServerBlock();
}

size_t Parser::size() {
    return tokens_.size();
}

Token const &Parser::currentToken() {
    if (pos_ > size())
        return tokens_.back();
    return tokens_[pos_];
}

Token const &Parser::peekToken() {
    if (pos_ > size())
        return tokens_.back();
    return tokens_[pos_ + 1];
}

void Parser::consumeToken() {
    if (pos_ < size())
        pos_++;
}

void Parser::expectToken(TokenType type) {
    if (currentToken().type != type)
        throw std::runtime_error("non matching token types");
    consumeToken();
}

void Parser::expectToken(std::string literal) {
    if (currentToken().literal != literal)
        throw std::runtime_error("non matching token literals");
    consumeToken();
}

void Parser::handleServerBlock() {
    while (pos_ < size()) {
        expectToken("server");
        expectToken(LEFT_BRACE);
        handleStatement();
        expectToken(RIGHT_BRACE);
    }
}

void Parser::handleStatement() {
    if (currentToken().literal == "location")
        handleLocationBlock();
    else
        handleDirective();
}

void Parser::handleLocationBlock() {
    expectToken("location");
    expectToken(IDENTIFIER);
    expectToken(LEFT_BRACE);
    handleDirective();
    expectToken(RIGHT_BRACE);
}

void Parser::handleDirective() {
}
