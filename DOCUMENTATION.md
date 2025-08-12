# Documentation Standards

This guide covers documentation requirements for the webserv project.

## When to Document

Document these elements:
- **Public class interfaces** - What the class does and how to use it
- **Complex algorithms** - Non-obvious implementation details
- **Configuration parsing** - How config directives work
- **HTTP protocol specifics** - RFC compliance notes

## Doxygen Style

Use Doxygen comments for public APIs:

### Class Documentation
```cpp
/**
 * @brief Manages HTTP server configuration.
 * 
 * Parses configuration files and provides access to server settings.
 * Supports multiple server blocks and location directives.
 */
class ServerConfig {
    // ...
};
```

### Function Documentation
```cpp
/**
 * @brief Parses HTTP request line.
 * @param line Raw request line from client
 * @return true if parsing succeeded
 */
bool parseRequestLine(const std::string& line);
```

### Member Variables (when needed)
```cpp
private:
    int port_;                  //!< Server listening port
    std::string documentRoot_;  //!< Document root directory
```

## Documentation Levels

### Minimal
- Document public class interfaces
- Comment complex parsing logic
- Add brief function docs for non-obvious methods

### What NOT to Document
- Obvious getters/setters
- Simple utility functions
- Standard C++ patterns
- Self-explanatory code

## README Updates

Keep the main README current with:
- Build instructions
- Configuration format
- Usage examples
- Testing procedures

## Comments in Code

Use `//` for implementation comments:
```cpp
// Handle keep-alive connections differently
if (isKeepAlive()) {
    // Connection reuse logic here
}
```

Avoid over-documenting obvious code.