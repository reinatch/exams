# mini_serv Study Memo (Compact)

## What to memorize
- Globals: `g_sock`, `g_max`, `g_id`, `g_ids[fd]`, `g_bufs[fd]`, `g_all/g_rd/g_wr`.
- 2 helper funcs from exam `main.c`: `extract_message`, `str_join`.
- 3 runtime actions:
1. `add_client`: `accept` -> assign id -> `FD_SET` -> broadcast arrived.
2. `del_client`: broadcast left -> `FD_CLR` -> `free(buf)` -> `close`.
3. `read_client`: `recv` -> append with `str_join` -> while `extract_message` -> broadcast `"client %d: %s"`.

## Globals explained (brief)
- `g_sock`: server listening socket (`socket`/`bind`/`listen`).
- `g_max`: highest fd currently used; needed for `select(g_max + 1, ...)`.
- `g_id`: next id to assign to a new client (0, 1, 2, ...).
- `g_ids[fd]`: map from socket fd to stable client id.
- `g_bufs[fd]`: per-client pending text (keeps partial line until `\n` arrives).
- `g_all`: master fd set (server fd + all connected client fds).
- `g_rd`: read-ready copy of `g_all` filled by `select`.
- `g_wr`: write-ready copy of `g_all` filled by `select` (used before `send`).

`g_id` is used at connect time: `g_ids[fd] = g_id++;`
- `g_id` generates ids.
- `g_ids[fd]` stores the assigned id for later messages (`arrived`, `left`, `client %d:`).

Why global:
- `add_client`, `read_client`, `del_client`, `notify_all` all need shared state.
- Globals avoid passing a large context struct through every call (exam style / compact code).

## Event loop
1. `rd = wr = all`
2. `select(g_max + 1, &g_rd, &g_wr, 0, 0)`
3. iterate `fd = 0..g_max`
4. if `fd == g_sock` -> `add_client()`, else `read_client(fd)`

## Exact strings (must match)
- `Wrong number of arguments\n`
- `Fatal error\n`
- `server: client %d just arrived\n`
- `server: client %d just left\n`
- `client %d: ` (prefix for each line)

## Quick compile
```bash
cc -Wall -Wextra -Werror mini_serv_compact.c -o mini_serv
```

## Quick local check
```bash
./mini_serv 4242
nc 127.0.0.1 4242
```
