Here's a sample `README.md` file for your GitHub repository, which explains the usage of the socket classes for both TCP and UDP communication:

```markdown
# Network Socket Library in C++

This project provides a simple C++ library for handling TCP and UDP socket communication. It includes both client and server implementations for each protocol, allowing for flexible network communication. The library supports basic operations such as connecting, sending, receiving, binding, and listening.

## Features
- **TCP Client and Server**
  - TCP socket creation, connection, sending, receiving, and closing.
  - Server can bind to a port, listen for connections, and accept clients.
  
- **UDP Client and Server**
  - UDP socket creation, sending, receiving, and closing.
  - Server can bind to a port and receive data from clients.

## Requirements
- C++11 or higher.
- POSIX-compliant system (Linux, macOS).
- Networking libraries (`<sys/socket.h>`, `<arpa/inet.h>`, etc.).

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/network-socket-cpp.git
    cd network-socket-cpp
    ```

2. Compile the code with a C++ compiler. For example:
    ```bash
    g++ -o tcp_client tcp_client.cpp -std=c++11
    g++ -o tcp_server tcp_server.cpp -std=c++11
    g++ -o udp_client udp_client.cpp -std=c++11
    g++ -o udp_server udp_server.cpp -std=c++11
    ```

## Usage

### TCP Client Example

```cpp
#include "network_socket.h"

int main() {
    TCPSocketClient client;
    
    if (client.open()) {
        if (client.connect("127.0.0.1", 8080)) {
            client.send("Hello, Server!");
            auto response = client.receive();
            if (response.first) {
                std::cout << "Server response: " << response.second << std::endl;
            }
        }
        client.close();
    }
    return 0;
}
```

### TCP Server Example

```cpp
#include "network_socket.h"

int main() {
    TCPSocketServer server;
    
    if (server.open()) {
        if (server.bindAndListen(8080)) {
            auto message = server.receive();
            if (message.first) {
                std::cout << "Received message: " << message.second << std::endl;
            }
            server.send("Hello, Client!");
        }
        server.close();
    }
    return 0;
}
```

### UDP Client Example

```cpp
#include "network_socket.h"

int main() {
    UDPSocketClient client;
    
    if (client.open()) {
        client.connect("127.0.0.1", 8080);
        client.send("Hello, UDP Server!");
        auto response = client.receive();
        if (response.first) {
            std::cout << "Server response: " << response.second << std::endl;
        }
        client.close();
    }
    return 0;
}
```

### UDP Server Example

```cpp
#include "network_socket.h"

int main() {
    UDPSocketServer server;
    
    if (server.open()) {
        if (server.bindAndListen(8080)) {
            auto message = server.receive();
            if (message.first) {
                std::cout << "Received message: " << message.second << std::endl;
            }
            server.send("Hello, UDP Client!");
        }
        server.close();
    }
    return 0;
}
```

## Class Overview

### `INetworkSocket`
An abstract interface that defines the essential socket operations:
- `open()` – Opens the socket.
- `close()` – Closes the socket.
- `send()` – Sends data over the socket.
- `receive()` – Receives data from the socket.
- `connect()` – Connects to a remote server (TCP clients).
- `bindAndListen()` – Binds to a port and listens for incoming connections (TCP/UDP servers).

### TCP Classes
- **`TCPSocketClient`** – Implements a TCP client.
- **`TCPSocketServer`** – Implements a TCP server.

### UDP Classes
- **`UDPSocketClient`** – Implements a UDP client.
- **`UDPSocketServer`** – Implements a UDP server.

## Contribution
Feel free to fork this repository and submit pull requests if you have improvements or suggestions.

## License
This project is licensed under the MIT License.
```

### Instructions:
- Replace the repository link `https://github.com/yourusername/network-socket-cpp.git` with your actual GitHub repository URL.
- Add any additional sections like "Tests" or "Future Improvements" as needed.
