#include "ServerBlock.hpp"
#include <algorithm>

namespace config {

bool ServerBlock::getLocation(std::string const &name, LocationBlock const *&res) const {
    (void)name;
    (void)res;
    return false;
}

// LocationBlock const *ServerBlock::getLocation(std::string const &server_name) const {
// 	(void)server_name;
// 	return ;
// }

bool ServerBlock::matchServerName(std::string const &needle) const {
    if (serverNames_.empty())
        return true;
    for (size_t i = 0; i < serverNames_.size(); i++) {
        if (std::find(serverNames_.begin(), serverNames_.end(), needle) != serverNames_.end())
            return true;
    }
    return false;
}

} // namespace config
