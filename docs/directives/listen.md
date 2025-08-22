# Directive: listen

Specifies the IP address and port for the server to listen on.

|             |                                   |
| ----------- | --------------------------------- |
| **Syntax**  | `listen [address]:[port];`        |
| **Default** | `listen 0.0.0.0:9191;`            |
| **Context** | `server`                          |

---

## Description

The `listen` directive sets the network address and port where the server will accept incoming connections.
If only a port is specified, the server listens on all available interfaces.
You may specify multiple `listen` directives in a single server block to listen on multiple addresses or ports.

---

## Examples

### Example 1: Listen on all interfaces, port 8080

```nginx
server {
    listen 8080;
}
```

### Example 2: Listen on a specific IP and port

```nginx
server {
    listen 127.0.0.1:8081;
}
```
