#include "DirectiveBlock.hpp"

DirectiveBlock::~DirectiveBlock() {
}

void DirectiveBlock::addDirective(std::string const &key,
                                  std::vector<std::string> const &directive) {
    directives_[key] = directive;
}

std::vector<std::string> const &DirectiveBlock::getDirective(std::string const &key) const {
    return directives_.at(key);
}

bool DirectiveBlock::getDirective(std::string const &key,
                                  std::vector<std::string> const **out_directive) const {
    if (!out_directive)
        return false;
    DirectiveMap::const_iterator it = directives_.find(key);
    if (it != directives_.end()) {
        *out_directive = &(it->second);
        return true;
    }
    *out_directive = NULL;
    return false;
}
