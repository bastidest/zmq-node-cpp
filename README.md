#   node/cpp dealer/router with zmq

A simple demo implementation of a router / dealer pattern using c++11 and node

##  Requirements
- Debian
- g++
- package `libzmq3-dev`
- node

##  Usage

### Server
Compile and start the cpp server (router):
```shell
g++ server/main.cpp -o out/main -std=c++11 -lpthread -lzmq && ./out/main
```

### Client
```shell
cd client && npm run dev
```

## TODOs
- Request Timeout to prevent stacking of commands
- Removing disconnected clients