# Linux System Monitor

A multithreaded Linux System Monitoring tool developed in **C** on **Ubuntu Linux**.

## Features

* Real-time CPU Usage Monitoring
* Real-time Memory Usage Monitoring
* Process Information Monitoring
* POSIX Threads (`pthread`) Implementation
* Mutex Synchronization

## Technologies Used

* C Programming
* Ubuntu Linux
* POSIX Threads (`pthread`)
* Linux `/proc` Filesystem

## Compilation

```bash
gcc main.c cpu.c memory.c process.c -o monitor -lpthread
```

## Run

```bash
./monitor
```

## Author

**Keerthana M L**

