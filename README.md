# HTTP Server in C++

A low-level HTTP server built from scratch in modern C++ using Linux sockets.

This project is focused on understanding how the web actually works internally instead of relying on existing frameworks or libraries.

The goal is to gradually build a real HTTP server while learning:

* TCP/IP networking
* Linux sockets
* HTTP protocol internals
* Request parsing
* Concurrency
* Server architecture
* Systems programming in C++

---

# Current Features

## TCP Socket Server

* Creates a TCP socket using Linux socket APIs
* Binds the socket to a port
* Listens for incoming client connections
* Accepts client connections manually

Concepts explored:

* `socket()`
* `bind()`
* `listen()`
* `accept()`
* `recv()`
* `send()`
* File descriptors
* TCP streams

---

## Basic HTTP Handling

The server can:

* Receive raw HTTP requests
* Parse incoming request data
* Detect HTTP methods and paths
* Send properly formatted HTTP responses

Example request:

```http
GET / HTTP/1.1
Host: localhost:8080
```

Example response:

```http
HTTP/1.1 200 OK
Content-Type: text/plain
Content-Length: 13

Hello, World!
```

---

## Manual HTTP Parsing

This project intentionally avoids external HTTP libraries.

Requests are parsed manually to understand:

* HTTP request structure
* Headers
* Methods
* Paths
* Body handling
* CRLF separation
* Content-Length

---

## Linux-Focused Development

The server is being developed primarily on Linux.

This project explores:

* POSIX socket APIs
* Terminal networking tools
* Linux networking behavior
* System-level programming

Useful tools used during development:

```bash
curl
netcat (nc)
ss
netstat
strace
```

---

# Project Goals

This is not intended to remain a simple "Hello World" socket server.

The long-term goal is to progressively evolve it into a more complete HTTP server framework.

Planned areas of exploration:

* Proper HTTP parser
* Incremental parsing
* Keep-alive connections
* Thread pool
* Routing system
* Middleware
* Static file serving
* MIME types
* Logging system
* Non-blocking sockets
* epoll
* Benchmarking
* Security protections
* HTTP compliance improvements

---

# Why Build an HTTP Server?

Building an HTTP server teaches concepts that are usually hidden behind frameworks.

This project helps understand:

* How browsers communicate with servers
* How APIs work internally
* How TCP differs from HTTP
* Why parsing network protocols is difficult
* How operating systems manage network communication
* How backend frameworks are designed internally

---

# Example Test Requests

Using curl:

```bash
curl http://localhost:8080
```

POST request:

```bash
curl -X POST \
     -H "Content-Type: application/json" \
     -d '{"message":"hello"}' \
     http://localhost:8080
```

Using netcat:

```bash
nc localhost 8080
```

Then manually type:

```http
GET / HTTP/1.1
Host: localhost

```

---

# Build

Example:

```bash
g++ -std=c++17 src/main.cpp -o server
```

Run:

```bash
./server
```

---

# Project Structure

Current structure is intentionally simple and will evolve over time.

```text
.
├── src/
├── include/
├── public/
└── README.md
```

Planned future structure:

```text
src/
├── tcp/
├── http/
├── parser/
├── routing/
├── utils/
└── server/
```

---

# Learning Focus

This project prioritizes:

* Understanding over abstraction
* Simplicity over premature optimization
* Systems knowledge over framework usage
* Building components manually

---

# References

Useful resources while learning:

* RFC 9110 (HTTP Semantics)
* Beej's Guide to Network Programming
* Linux man pages
* TCP/IP Illustrated

---

# Status

Work in progress.

The server is currently in the foundational stage where the focus is on:

* reliable socket communication
* understanding HTTP structure
* building parsing logic
* designing clean architecture

More features and refactoring will be added progressively.

---

# License

MIT License

# Author

Kairav Dutta