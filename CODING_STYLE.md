# Webserv Coding Style Guide

This document outlines the coding style for the `webserv` project.
[cite_start]All code must comply with the **C++98 standard** as required by the
project subject. [cite: 37, 45]

## Naming Conventions

- **Classes & Structs:** `PascalCase`
  - _Example:_ `class HttpRequest;` `struct ServerConfig;`
- **Functions & Methods:** `camelCase`
  - _Example:_ `void parseRequest();`
- **Variables (Local & Member):** `camelCase`
- **Private Member Variables:** `camelCase` with a trailing underscore `_`.
  - _Example:_ `std::string clientAddress_;` `int port_;`
- **Constants:** `UPPER_CASE_SNAKE_CASE`. Use `const` for compile-time
  constants.
  - _Example:_ `const int MAX_CONNECTIONS = 1024;`
- **File Names:** `snake_case`. Headers should be `.hpp` and sources `.cpp`.
  - _Example:_ `http_request.hpp`, `http_request.cpp`

## C++98 Best Practices

- **Header Guards:** We will use `#pragma once` for include guards in all header
  files. It's more concise than traditional guards and prevents a header from
  being included multiple times. Place it at the very top of every `.hpp` file.

  ```cpp
  #pragma once

  #include <string>
  // ... rest of the header file
  ```

- **Memory Management:** This project forbids external libraries, and C++98 does
  not have smart pointers like `std::unique_ptr`. You are responsible for manual
  memory management (`new`/`delete`).
  - **CRITICAL:** Any class that manages a resource (memory, file descriptors)
    MUST implement the **Rule of Three**:
    1. Destructor
    2. Copy Constructor
    3. Copy Assignment Operator
  - Failure to do this will lead to memory leaks, double frees, and crashes. Be
    very careful.

- **Containers:** Use the C++98 standard library containers (`std::vector`,
  `std::map`, etc.).

- [cite_start]**Libraries:** No external libraries (like Boost) are allowed.
  [cite: 40] [cite_start]All functionality must be implemented using C++98
  features and the allowed system calls.

- [cite_start]**Non-Blocking I/O:** The server must be non-blocking. [cite: 63]
  [cite_start]Use `poll()` (or an equivalent like `select`, `kqueue`) to monitor
  all file descriptors for reading and writing. [cite: 64, 65] [cite_start]You
  must not call `read`, `recv`, `write`, or `send` without it being indicated as
  ready by your polling mechanism. [cite: 66, 72]
