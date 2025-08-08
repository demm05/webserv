# Coding Style Guide

This document outlines the coding style for the `webserv` project.
All code must comply with the **C++98 standard** as required by the project subject.

## Automated Formatting

Use `clang-format` before committing:

## Naming Conventions

- **Classes & Structs:** `PascalCase`
- **Functions & Methods:** `camelCase`  
- **Variables:** `camelCase`
- **Private Members:** `camelCase_` (trailing underscore)
- **Constants:** `UPPER_CASE_SNAKE_CASE`

## C++98 Essentials

### Header Guards
Use `#pragma once` in all headers.

### Memory Management  
Implement Rule of Three for any class managing resources:
- Destructor
- Copy Constructor
- Copy Assignment Operator

### Include Order
1. Related header (for .cpp files)
2. System headers (`<iostream>`, etc.)
3. Project headers (`"config.hpp"`, etc.)

### Project Constraints
- C++98 standard library only
- No external libraries
- Non-blocking I/O with `poll()`/`select()`/`kqueue()`

## Code Quality
- Keep functions under 30 lines
- Use meaningful names
- Comment complex logic only
- Prefer RAII for resource management

See `DOCUMENTATION.md` for documentation standards.
