# Server Configuration (nginx-style)

Our server uses a configuration file syntax inspired by nginx.
The configuration is built from **directives**, which are organized into **blocks** (also called contexts).

## Main Blocks

- `server`: Defines a virtual server to handle requests.
- `location`: Defines how to process requests for specific URIs.
    A `location` block lives inside a `server` block.

## Directives

Here is a list of all supported directives, their arguments, and the context in
which they can be used.

| Directive                                    | Context              | Brief Description                            |
| -------------------------------------------- | -------------------- | -------------------------------------------- |
| [`listen`](./directives/listen.md)           | `server`             | Specifies the port and address to listen on. |
| [`server_name`](./directives/server_name.md) | `server`             | Sets the names of the virtual server.        |
| [`root`](./directives/root.md)               | `server`, `location` | Sets the root directory for requests.        |
| [`index`](./directives/index.md)             | `location`           | ---                                          |
