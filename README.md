The server and the clients are sadly not working. We got problems with the socket connection and didn't have the time to solve everything.

# How to build

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Run the game server

```shell
$ ./server --port <port_number>
```

# Run the client

```shell
$ ./ai_client --port <port_number>
```