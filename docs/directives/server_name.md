# Directive: server_name

Sets the names of the virtual server.

|             |                                   |
| ----------- | --------------------------------- |
| **Syntax**  | `server_name [name1] [name2]...;` |
| **Default** | `---`                             |
| **Context** | `server`                          |

---

## Description

The `server_name` directive defines one or more hostnames for the server block.
Incoming requests are matched against these names using the Host header.
Multiple names can be specified, separated by spaces.

---

## Examples

### Example 1: Single server name

```nginx
server {
    server_name example.com;
}
```

### Example 2: Multiple server names

```nginx
server {
    server_name example.com www.example.com api.example.com;
}
```