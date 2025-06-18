# My C++ Redis Server

---

## Overview

`my_redis_server` is a lightweight, Redis-compatible, in-memory data store written in C++.  
It supports strings, lists, and hashes, full RESP protocol parsing, multi-client concurrency, and periodic disk persistence.

---

## Features

- **Common Commands:** `PING`, `ECHO`, `FLUSHALL`
- **Key/Value:** `SET`, `GET`, `KEYS`, `TYPE`, `DEL`, `EXPIRE`, `RENAME`
- **Lists:** `LGET`, `LLEN`, `LPUSH`, `RPUSH`, `LPOP`, `RPOP`, `LREM`, `LINDEX`, `LSET`
- **Hashes:** `HSET`, `HGET`, `HEXISTS`, `HDEL`, `HKEYS`, `HVALS`, `HLEN`, `HGETALL`, `HMSET`
- **Persistence:** Data is dumped to `dump.my_rdb` every 5 minutes and on shutdown; loaded at startup if present.
- **Concurrency:** Handles multiple clients using threads.
- **RESP Protocol:** Fully parses both inline and array formats.

---

## Directory Structure

```
├── include/                  # Header files
│   ├── RedisCommandHandler.h
│   ├── RedisDatabase.h
│   └── RedisServer.h
├── src/                      # Source files
│   ├── RedisCommandHandler.cpp
│   ├── RedisDatabase.cpp
│   ├── RedisServer.cpp
│   └── main.cpp
├── Concepts,UseCases&Tests.md # Design and test documentation
├── Makefile                  # Build script
├── README.md                 # This file
└── test_all.sh               # Automated test script
```

---

## Installation

You need a C++17 (or later) compiler.

**Build with Make:**

```sh
make
```

**Clean build artifacts:**

```sh
make clean
```

**Manual compilation:**

```sh
g++ -std=c++17 -pthread -Iinclude src/*.cpp -o my_redis_server
```

---

## Usage

### Start the Server

```sh
./my_redis_server          # Default port 6379
./my_redis_server 6380     # Custom port
```

On startup, you’ll see:

```
Database Loaded From dump.my_rdb
# or
No dump found or load failed; starting with an empty database.
```

The server saves the database every 5 minutes and on shutdown (`Ctrl+C`).

---

### Connect with a Client

You can use the standard `redis-cli` or your own RESP client.

```sh
redis-cli -p 6379
```

**Example session:**

```
127.0.0.1:6379> PING
PONG

127.0.0.1:6379> SET bob "pawan kalyan"
OK

127.0.0.1:6379> GET bob
"pawan kalyan"
```

---

## Supported Commands

### Common

- `PING` → `PONG`
- `ECHO <msg>` → `<msg>`
- `FLUSHALL` → clear all data

### Key/Value

- `SET <key> <value>`
- `GET <key>`
- `KEYS *`
- `TYPE <key>`
- `DEL <key>`
- `EXPIRE <key> <seconds>`
- `RENAME <old> <new>`

### Lists

- `LGET <key>` — get all elements
- `LLEN <key>`
- `LPUSH <key> <v1> [v2 ...]`
- `RPUSH <key> <v1> [v2 ...]`
- `LPOP <key>`
- `RPOP <key>`
- `LREM <key> <count> <value>`
- `LINDEX <key> <index>`
- `LSET <key> <index> <value>`

### Hashes

- `HSET <key> <field> <value>`
- `HGET <key> <field>`
- `HEXISTS <key> <field>`
- `HDEL <key> <field>`
- `HLEN <key>`
- `HKEYS <key>`
- `HVALS <key>`
- `HGETALL <key>`
- `HMSET <key> <f1> <v1> [f2 v2 ...]`

---

## Design & Architecture

- **Concurrency:** Each client handled in a separate thread.
- **Synchronization:** Single mutex guards all data structures.
- **Data Stores:**
  - `kv_store` for strings
  - `list_store` for lists
  - `hash_store` for hashes
- **Expiration:** Lazy eviction on access, with TTL map.
- **Persistence:** Simple text-based RDB dump/load (`dump.my_rdb`).
- **Singleton Pattern:** One shared database instance.
- **RESP Parsing:** Custom parser for both inline and array formats.

---

## Testing

- Use `test_all.sh` to run a suite of commands for validation:
  ```sh
  ./test_all.sh
  ```
- See `Concepts,UseCases&Tests.md` for more examples and test cases.

---


