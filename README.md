# ServerX

A lightweight HTTP/1.1 server implementation in C++98.

## Overview

Webserv is a non-blocking HTTP server that handles multiple clients simultaneously using I/O multiplexing.
The server supports basic HTTP operations, static file serving, and CGI execution.

## Features

- HTTP/1.1 protocol support
- Non-blocking I/O with `poll()`/`select()`/`kqueue()`
- Multiple server configurations
- Static file serving
- CGI script execution
- Custom error pages
- Request timeout handling

## Building

### Requirements

- C++98 compatible compiler (g++, clang++)
- Make
- Standard C++ library only

### Compilation

```bash
# Build the server
make

# Clean build files
make clean
```

## Usage

```bash
# Run with custom configuration
./webserv config/custom.conf

# Quick run (builds if needed)
make run ARGS="config/default.conf"
```

## Configuration

The server uses nginx-style configuration files:

## Project Structure

```
webserv/
├── src/           # Source files
├── inc/           # Header files
├── config/        # Configuration files
├── tests/         # Unit tests
├── mk/            # Makefile modules
└── docs/          # Documentation
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for development workflow and coding standards.

## Documentation

- [Coding Style Guide](CODING_STYLE.md)
- [Documentation Standards](DOCUMENTATION.md)

## License

This project is part of the 42 School curriculum.