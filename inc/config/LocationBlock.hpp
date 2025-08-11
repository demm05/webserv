#pragma once

#include <string>

namespace config {

/**
 * @class LocationBlock
 * @brief A strongly-typed data container for a location block's configuration.
 *
 * This class holds the final, validated settings for a single 'location' block
 * after it has been processed by the ConfigBuilder.
 */
class LocationBlock {
public:
    std::string path;
    std::string root;
};

}
