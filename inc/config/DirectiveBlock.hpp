#pragma once

#include <vector>
#include <map>
#include <string>

class DirectiveBlock {
public:
    typedef std::map<std::string, std::vector<std::string> > DirectiveMap;
    virtual ~DirectiveBlock();

    void addDirective(std::string const &key, std::vector<std::string> const &directive);
    bool getDirective(std::string const &key, std::vector<std::string> const **out_directive) const;
    std::vector<std::string> const &getDirective(std::string const &key) const;

protected:
    DirectiveMap directives_;
};
