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

size_t Parser::size() const {
    return tokens_.size();
}

Token const &Parser::currentToken() const{
    if (pos_ > size())
        return tokens_.back();
    return tokens_[pos_];
}

Token const &Parser::peekToken() const {
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

bool Parser::isTokenAValue() const {
    static const TokenType validTypes[] = {IDENTIFIER, STRING, NUMBER};
    static const size_t size = sizeof(validTypes) / sizeof(validTypes[0]);
    return currentToken().isTypeIn(validTypes, size);
}

void Parser::handleServerBlock() {
    while (currentToken().type != END_OF_FILE) {
        expectToken("server");
        expectToken(LEFT_BRACE);
        while (currentToken().type != RIGHT_BRACE)
            handleStatement();
        expectToken(RIGHT_BRACE);
    }
}

void Parser::handleStatement() {
    if (currentToken().literal == "location")
        handleLocationBlock();
    else
        handleDirective(config_);
}

void Parser::handleLocationBlock() {

    expectToken("location");
    if (peekToken().type != LEFT_BRACE)
        throw std::runtime_error("non matching token types");
    if (!isTokenAValue())
        throw std::runtime_error("Expected a location name (identifier).");
    std::string key = currentToken().literal;
    consumeToken();
    expectToken(LEFT_BRACE);
    LocationBlock loc_block;
    while (currentToken().type != RIGHT_BRACE)
        handleDirective(loc_block);
    expectToken(RIGHT_BRACE);
    config_.addLocation(currentToken().literal, loc_block);
}

void Parser::handleDirective(DirectiveBlock &db) {
    if (!isTokenAValue())
        throw std::runtime_error("Expected a directive name (identifier).");
    std::string const &key = currentToken().literal;
    consumeToken();

    std::vector<std::string> values;
    while (isTokenAValue()) {
        values.push_back(currentToken().literal);
        consumeToken();
    }
    db.addDirective(key, values);
    expectToken(SEMICOLON);
}