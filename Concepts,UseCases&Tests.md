# Concepts & Use Cases

---

## Key Concepts

1. **TCP/IP and Sockets:**  
   The server uses TCP sockets to communicate with clients over the network.

2. **Concurrency:**  
   Each client connection is handled in its own thread, allowing multiple clients to interact with the server at the same time.

3. **Mutex and Synchronization:**  
   A mutex ensures that only one thread can modify the database at a time, preventing data corruption.

4. **Data Structures:**  
   The server uses hash tables (unordered_map) for fast key lookups and vectors for lists.

5. **RESP Protocol:**  
   The server understands the Redis Serialization Protocol (RESP), which is how Redis clients and servers talk to each other.

6. **File Persistence:**  
   The database can be saved to and loaded from a file, so your data isn’t lost when the server restarts.

7. **Signal Handling:**  
   The server can handle signals (like Ctrl+C) to shut down gracefully and save data.

8. **Command Processing:**  
   Commands from clients are parsed, processed, and formatted before sending back a response.

9. **Singleton Pattern:**  
   Only one instance of the database exists in the program.

10. **Bitwise Operators:**  
    Used for combining results, for example when deleting keys from multiple data structures.

11. **Standard Libraries:**  
    The project uses C++ standard libraries for data structures, threading, and file I/O.

---

## Main Classes

- **RedisServer:** Handles network connections and client threads.
- **RedisDatabase:** Stores all the data and provides methods for commands.
- **RedisCommandHandler:** Parses and processes commands from clients.

---

## Commands & Use Cases

### Common Commands

- **PING**  
  _Check if the server is alive._  
  Example: Before doing anything, send `PING` to make sure the server is running.

- **ECHO**  
  _Test the connection or debug._  
  Example: Send `ECHO Hello` and get `Hello` back.

- **FLUSHALL**  
  _Clear all data._  
  Example: Use this to reset the database during development or testing.

---

### Key/Value Commands

- **SET**  
  _Store a value for a key._  
  Example: `SET user:1 "Alice"`

- **GET**  
  _Retrieve the value for a key._  
  Example: `GET user:1` returns `"Alice"`

- **KEYS**  
  _List all keys._  
  Example: `KEYS *` shows every key in the database.

- **TYPE**  
  _Find out what kind of value a key holds._  
  Example: `TYPE user:1` might return `string`, `list`, or `hash`.

- **DEL / UNLINK**  
  _Delete a key._  
  Example: `DEL user:1` removes the key and its value.

- **EXPIRE**  
  _Set a time-to-live for a key._  
  Example: `EXPIRE session:1 60` deletes the key after 60 seconds.

- **RENAME**  
  _Change a key’s name._  
  Example: `RENAME oldkey newkey`

---

### List Commands

- **LGET**  
  _Get all items in a list._  
  Example: `LGET mylist` returns all elements.

- **LLEN**  
  _Get the number of items in a list._  
  Example: `LLEN mylist` returns `3` if there are three items.

- **LPUSH / RPUSH**  
  _Add items to the start or end of a list._  
  Example: `LPUSH mylist a` adds `a` to the front; `RPUSH mylist b` adds `b` to the end.

- **LPOP / RPOP**  
  _Remove and return the first or last item in a list._  
  Example: `LPOP mylist` removes and returns the first item.

- **LREM**  
  _Remove items from a list by value._  
  Example: `LREM mylist 2 x` removes up to 2 occurrences of `x`.

- **LINDEX**  
  _Get an item by its position in the list._  
  Example: `LINDEX mylist 1` returns the second item.

- **LSET**  
  _Change the value at a specific position in the list._  
  Example: `LSET mylist 1 new_value` sets the second item to `new_value`.

---

### Hash Commands

- **HSET**  
  _Set fields in a hash (like a dictionary)._  
  Example: `HSET user:1 name Alice age 30`

- **HGET**  
  _Get a field’s value from a hash._  
  Example: `HGET user:1 name` returns `Alice`.

- **HEXISTS**  
  _Check if a field exists in a hash._  
  Example: `HEXISTS user:1 age` returns `1` if it exists.

- **HDEL**  
  _Delete a field from a hash._  
  Example: `HDEL user:1 age`

- **HGETALL**  
  _Get all fields and values from a hash._  
  Example: `HGETALL user:1` returns all data for that user.

- **HKEYS / HVALS**  
  _Get all field names or all values from a hash._  
  Example: `HKEYS user:1` returns all field names.

- **HLEN**  
  _Get the number of fields in a hash._  
  Example: `HLEN user:1` returns how many fields there are.

- **HMSET**  
  _Set multiple fields at once in a hash._  
  Example: `HMSET user:2 name Bob age 25 city Paris`

---

## How to Test

### 1. Start Your Server

```bash
./my_redis_server 6379
```

### 2. Connect with redis-cli

```bash
redis-cli -p 6379
```

### 3. Try These Commands

#### Common

| Command  | Example            | What You Get  |
| -------- | ------------------ | ------------- |
| PING     | `PING`             | `PONG`        |
| ECHO     | `ECHO Hello World` | `Hello World` |
| FLUSHALL | `FLUSHALL`         | `OK`          |

#### Key/Value

| Command   | Example                                      | What You Get      |
| --------- | -------------------------------------------- | ----------------- |
| SET / GET | `SET mykey myvalue`<br>`GET mykey`           | `OK`<br>`myvalue` |
| KEYS      | `KEYS *`                                     | List of keys      |
| TYPE      | `TYPE mykey`                                 | `string`          |
| DEL       | `DEL mykey`                                  | `1` (if deleted)  |
| EXPIRE    | `SET session:1 data`<br>`EXPIRE session:1 5` | `OK`              |
| RENAME    | `SET a x`<br>`RENAME a b`<br>`GET b`         | `OK`<br>`x`       |

#### Lists

| Command     | Example                                             | What You Get      |
| ----------- | --------------------------------------------------- | ----------------- |
| LGET        | `RPUSH L a b c`<br>`LGET L`                         | `a`, `b`, `c`     |
| LLEN        | `LLEN L`                                            | `3`               |
| LPUSH/RPUSH | `LPUSH L start`<br>`RPUSH L end`                    | `4`<br>`5`        |
| LPOP/RPOP   | `LPOP L`<br>`RPOP L`                                | `start`<br>`end`  |
| LREM        | `RPUSH L x y x z x`<br>`LREM L 2 x`<br>`LREM L 0 x` | `2`<br>`1`        |
| LINDEX      | `LINDEX L 1`<br>`LINDEX L -1`                       | `y`<br>`z`        |
| LSET        | `LSET L 1 new_val`<br>`LINDEX L 1`                  | `OK`<br>`new_val` |

#### Hashes

| Command     | Example                                                       | What You Get              |
| ----------- | ------------------------------------------------------------- | ------------------------- |
| HSET        | `HSET user:1 name Alice age 30`                               | `1` (per field)           |
| HGET        | `HGET user:1 name`                                            | `Alice`                   |
| HEXISTS     | `HEXISTS user:1 age`                                          | `1` or `0`                |
| HDEL        | `HDEL user:1 age`                                             | `1`                       |
| HGETALL     | `HGETALL user:1`                                              | All fields/values         |
| HKEYS/HVALS | `HKEYS user:1`<br>`HVALS user:1`                              | Field names<br>Values     |
| HLEN        | `HLEN user:1`                                                 | Number of fields          |
| HMSET       | `HMSET user:2 name Bob age 25 city Paris`<br>`HGETALL user:2` | `OK`<br>All fields/values |

---

**Tip:**  
After setting an expiry with `EXPIRE`, wait for the time to pass and then try `GET` to see that the key is gone.

---
