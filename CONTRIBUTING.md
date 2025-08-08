# Contributing to ServerX

This document outlines our development workflow and coding standards.
Following these guidelines ensures code quality and demonstrates professional development practices.

## Development Workflow

### 1. Issues and Planning

All work starts with a GitHub Issue.
This ensures we track progress and avoid duplicate effort.

**Issue titles** should use type prefixes:
- `feat`: New feature
- `fix`: Bug fix
- `refactor`: Code improvement without functional changes
- `docs`: Documentation updates
- `test`: Adding or improving tests

**Example**: `feat: Implement HTTP request parsing`

### 2. Branching Strategy

Create feature branches from `main` using the format:
```
type/issue-number-description
```

**Example**: `feat/12-http-parser`

### 3. Commit Messages

Use clear, descriptive commit messages:
```
type(scope): brief description

Optional longer explanation if needed.
```

**Examples**:
```bash
git commit -m "feat(parser): Add HTTP method validation"
git commit -m "fix(server): Handle SIGPIPE in connection cleanup"
git commit -m "refactor(config): Simplify directive parsing logic"
```

### 4. Pull Requests

Before opening a PR:
1. Format code with `clang-format`
2. Ensure all tests pass
3. Update documentation if needed

**PR description should include**:
- Link to the issue: `Closes #12`
- Brief summary of changes
- Testing instructions if applicable

**Review process**:
- At least one team member must review and approve
- Address feedback constructively
- Merge after approval and delete the feature branch

## Code Standards

### Quality Requirements

- Follow the style guide in `CODING_STYLE.md`
- Document public interfaces (see `DOCUMENTATION.md`)
- Write meaningful variable and function names
- Keep functions focused and under 30 lines when possible

### Testing

- Write tests for new features and bug fixes
- Ensure existing tests continue to pass
- Test both success and error cases

### C++98 Compliance

- No external libraries beyond standard library
- Implement Rule of Three for resource-managing classes
- Use non-blocking I/O patterns throughout

### Recommended IDE Settings

- 4-space indentation (no tabs)
- Format on save
- Show trailing whitespace
- C++98 syntax highlighting
