# Sample daemon

Logs `Test` to syslog every 3 seconds.
To view test logs, use `journalctl` and
scroll to the bottom.

# Compiling

```
gcc hello.c -o hello
```

# Running

```
./hello
```

# Exiting

```
pkill hello
```
