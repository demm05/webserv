# Runtime Configuration API Reference

This document explains how to work with the runtime configuration API in webserv.
It is intended as a high-level guide for developers to understand where and how to access configuration data at runtime.

## Overview

The configuration API provides read-only access to all server settings loaded from the configuration file.
All configuration classes and their public interfaces are fully documented with Doxygen.
For detailed usage, refer to the generated Doxygen documentation or header files.

## Main Entry Point

- The main configuration object is `config::ServerConfig`.
- Create a single instance at server startup, passing the path to your configuration file.
- Use this object to access server and location settings for each incoming request.

## Typical Workflow

1. **Initialize Configuration**
   - Create a `config::ServerConfig` object at startup with the path to your config file.

2. **Handle Incoming Requests**
   - For each request, use the config object to find the appropriate server and location blocks.
   - Use the returned configuration data to determine how to process the request.

## Example

```cpp
#include "ServerConfig.hpp"

void handle_request(int port, const std::string& host, const std::string& uri) {
    static config::ServerConfig server_config("config/default.conf");
    const config::ServerBlock* server = server_config.getServer(port, host);
    if (!server) {
        // Handle error: no matching server
        return;
    }
    const config::LocationBlock* location = server->getLocation(uri);
    if (!location) {
        // Handle error: no matching location
        return;
    }
    // Use location->root, location->index, etc. as needed
}
```

## Where to Look Up Details

- **Class and function details:**  
  Refer to the Doxygen documentation or header files in `inc/config/`.
- **Configuration file format:**  
  See example config files in the `config/` directory.
- **Error handling and exceptions:**  
  Refer to Doxygen for exception types and error conditions.

## Summary

- Use `config::ServerConfig` as your entry point for all configuration queries.
- For specifics about classes, functions, and members, consult Doxygen or header files.
- This document is a workflow guide; Doxygen provides
