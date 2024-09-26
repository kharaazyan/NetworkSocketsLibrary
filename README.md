Here's a README file for your code with an explanation of the main classes, methods, and instructions for running it.

---

# Network Sockets in C++

This application implements a client-server architecture using TCP and UDP sockets in C++. It provides the ability to work with both TCP and UDP protocols, facilitating the creation of client-server applications. The code is structured into different classes to handle network communication for both server and client sides.

## Classes Overview

### 1. `INetworkSocket_server`
This interface defines the basic methods for a server socket:
- `open()` - Opens the socket.
- `close()` - Closes the socket.
- `getSocketType()` - Returns the type of socket (TCP or UDP).
- `receive()` - Receives data from a client.
- `send(const string& data)` - Sends data to a client.
- `connect(int port)` - Binds and connects the server to a specified port.

### 2. `INetworkSocket_client`
This interface defines the basic methods for a client socket:
- `open()` - Opens the socket.
- `close()` - Closes the socket.
- `getSocketType()` - Returns the type of socket.
- `receive()` - Receives data from the server.
- `send(const string& data)` - Sends data to the server.
- `connect(const string& address, int port)` - Connects to the server using the specified address and port.

### 3. `TCPSocket_server` and `TCPSocket_client`
These classes implement the server and client functionality for TCP sockets.
- The server listens on a specific port and accepts incoming client connections.
- The client connects to the server using the specified IP address and port.
- Both classes support sending and receiving messages.

### 4. `UDPSocket_server` and `UDPSocket_client`
These classes implement the server and client functionality for UDP sockets.
- The server listens on a specified port for incoming UDP packets.
- The client sends UDP packets to the server.
- Both classes support sending and receiving datagrams (messages).

## Key Methods

### Common Methods
- `open()`: Opens the socket.
- `close()`: Closes the socket.
- `receive()`: Receives data. Returns a `pair<bool, string>` where `bool` indicates success and `string` contains the data.
- `send(const string& data)`: Sends data.

### TCP-Specific Methods
- `connect(int port)` (server): Binds the server to the given port and starts listening for incoming connections.
- `connect(const string& address, int port)` (client): Connects the client to the specified address and port.

### UDP-Specific Methods
- `connect(int port)` (server): Binds the server to the given port to receive UDP datagrams.
- `connect(const string& address, int port)` (client): Specifies the server address and port to send UDP datagrams.

## How to Run

### TCP Server
1. Create an instance of `TCPSocket_server`.
2. Call the `open()` method to initialize the server.
3. Use `connect(port)` to bind the server to the desired port.
4. Use `receive()` to get data from the client.
5. Use `send(data)` to send data to the client.

### TCP Client
1. Create an instance of `TCPSocket_client`.
2. Call the `open()` method to initialize the client.
3. Use `connect(address, port)` to connect to the server.
4. Use `send(data)` to send data to the server.
5. Use `receive()` to get data from the server.

### UDP Server
1. Create an instance of `UDPSocket_server`.
2. Call the `open()` method to initialize the server.
3. Use `connect(port)` to bind the server to the desired port.
4. Use `receive()` to get data from the client.
5. Use `send(data)` to send data to the client.

### UDP Client
1. Create an instance of `UDPSocket_client`.
2. Call the `open()` method to initialize the client.
3. Use `connect(address, port)` to set the server address and port.
4. Use `send(data)` to send data to the server.
5. Use `receive()` to get data from the server.

## Example Usage

### TCP Example
```cpp
TCPSocket_server tcp_server;
tcp_server.open();
tcp_server.connect(8080);
auto received_data = tcp_server.receive();
tcp_server.send("Response from server");
tcp_server.close();
```

```cpp
TCPSocket_client tcp_client;
tcp_client.open();
tcp_client.connect("127.0.0.1", 8080);
tcp_client.send("Hello from client");
auto response = tcp_client.receive();
tcp_client.close();
```

### UDP Example
```cpp
UDPSocket_server udp_server;
udp_server.open();
udp_server.connect(8081);
auto received_data = udp_server.receive();
udp_server.send("Response from server");
udp_server.close();
```

```cpp
UDPSocket_client udp_client;
udp_client.open();
udp_client.connect("127.0.0.1", 8081);
udp_client.send("Hello from client");
auto response = udp_client.receive();
udp_client.close();
```

## Dependencies
- C++ Standard Library
- POSIX-compliant operating system (for socket and networking functions)

## Compilation

To compile the code, use `g++` or any other C++ compiler:

```bash
g++ -o network_app main.cpp -std=c++11
```

## License
This project is licensed under the MIT License.

---

This README explains the purpose of each class and how to use the TCP/UDP client-server communication model in your application.
