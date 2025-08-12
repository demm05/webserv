# Directive: root

Sets the root directory for requests.

|             |                                   |
| ----------- | --------------------------------- |
| **Syntax**  | `root [path];`                    |
| **Default** | `---`                             |
| **Context** | `server`, `location`              |

---

## Description

The `root` directive defines the filesystem path that will be prepended to the URI to form the full path to the requested file.
When used inside a `location` block, it overrides the root set in the enclosing `server` block.

---

## Examples

### Example 1: Set root for all requests

```nginx
server {
    root /var/www/html;
}
```

### Example 2: Override root for a specific location

```nginx
server {
    root /var/www/html;
    location /images/ {
        root /var/www/media;
    }
}
```