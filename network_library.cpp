#include <iostream>
#include <unistd.h>
#include <utility>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SIZE 2048

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;

class INetworkSocket {
public:
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual string getSocketType() const = 0;
    virtual pair<bool, string> receive() = 0;
    virtual bool send(const string &data) = 0;
    virtual inline void setSocketType(const string& type) = 0;
    virtual bool connect(const string& address, int port) = 0;
    virtual bool bindAndListen(int port) = 0;
};

class NetworkSocket : public INetworkSocket {
protected:
    string socketType;
    bool isOpen {false};
public:
    inline string getSocketType() const override { return socketType; }
    inline void setSocketType(const string& type) override { socketType = type; }
};

// TCP Client Implementation
class TCPSocketClient : public NetworkSocket {
private:
    int server_fd {0};
public:
    TCPSocketClient() {
        setSocketType("TCP");
    }

    bool open() override {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            perror("socket");
            return false;
        }
        return true;
    }

    bool connect(const string& address, int port) override {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, address.c_str(), &addr.sin_addr);

        if (::connect(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            perror("connect");
            return false;
        }
        return true;
    }

    pair<bool, string> receive() override {
        char buff[SIZE] = {0};
        ssize_t bytes_received = recv(server_fd, buff, SIZE, 0);
        if (bytes_received <= 0) {
            return std::make_pair(false, "nullptr");
        }
        return std::make_pair(true, string(buff, bytes_received));
    }

    bool send(const string& data) override {
        if (::send(server_fd, data.c_str(), data.size(), 0) < 0) {
            perror("send");
            return false;
        }
        return true;
    }

    bool close() override {
        if (::close(server_fd) == 0) return true;
        return false;
    }

    bool bindAndListen(int) override {
        return false;  // Not applicable for client
    }
};

// TCP Server Implementation
class TCPSocketServer : public NetworkSocket {
private:
    int server_fd {0}, client_fd {0};
public:
    TCPSocketServer() {
        setSocketType("TCP");
    }

    bool open() override {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0) {
            perror("socket");
            return false;
        }
        return true;
    }

    bool bindAndListen(int port) override {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            perror("bind");
            return false;
        }
        if (listen(server_fd, 1) < 0) {
            perror("listen");
            return false;
        }
        cout << "Server listening on port: " << port << endl;
        client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            perror("accept");
            return false;
        }
        return true;
    }

    pair<bool, string> receive() override {
        char buff[SIZE] = {0};
        ssize_t bytes_received = recv(client_fd, buff, SIZE, 0);
        if (bytes_received <= 0) return std::make_pair(false, "nullptr");
        return std::make_pair(true, string(buff, bytes_received));
    }

    bool send(const string& data) override {
        if (::send(client_fd, data.c_str(), data.size(), 0) < 0) {
            perror("send");
            return false;
        }
        return true;
    }

    bool close() override {
        ::close(client_fd);
        if (::close(server_fd) == 0) return true;
        return false;
    }

    bool connect(const string&, int) override {
        return false;  // Not applicable for server
    }
};

// UDP Client Implementation
class UDPSocketClient : public NetworkSocket {
private:
    int sock_fd {0};
    struct sockaddr_in server_addr {};
    socklen_t addr_len = sizeof(server_addr);
public:
    UDPSocketClient() {
        setSocketType("UDP");
    }

    bool open() override {
        sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock_fd < 0) {
            perror("socket");
            return false;
        }
        return true;
    }

    bool connect(const string& address, int port) override {
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, address.c_str(), &server_addr.sin_addr);
        return true;
    }

    pair<bool, string> receive() override {
        char buff[SIZE] = {0};
        ssize_t bytes_received = recvfrom(sock_fd, buff, SIZE, 0, (struct sockaddr*)&server_addr, &addr_len);
        if (bytes_received <= 0) {
            perror("recvfrom");
            return std::make_pair(false, "nullptr");
        }
        return std::make_pair(true, string(buff, bytes_received));
    }

    bool send(const string& data) override {
        if (sendto(sock_fd, data.c_str(), data.size(), 0, (struct sockaddr*)&server_addr, addr_len) < 0) {
            perror("sendto");
            return false;
        }
        return true;
    }

    bool close() override {
        if (::close(sock_fd) == 0) return true;
        return false;
    }

    bool bindAndListen(int) override {
        return false;  // Not applicable for client
    }
};

// UDP Server Implementation
class UDPSocketServer : public NetworkSocket {
private:
    int sock_fd {0};
    struct sockaddr_in server_addr {}, client_addr {};
    socklen_t addr_len = sizeof(client_addr);
public:
    UDPSocketServer() {
        setSocketType("UDP");
    }

    bool open() override {
        sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock_fd < 0) {
            perror("socket");
            return false;
        }
        return true;
    }

    bool bindAndListen(int port) override {
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            perror("bind");
            return false;
        }
        cout << "Server listening on port: " << port << endl;
        return true;
    }

    pair<bool, string> receive() override {
        char buff[SIZE] = {0};
        ssize_t bytes_received = recvfrom(sock_fd, buff, SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (bytes_received <= 0) {
            perror("recvfrom");
            return std::make_pair(false, "nullptr");
        }
        return std::make_pair(true, string(buff, bytes_received));
    }

    bool send(const string& data) override {
        ssize_t bytes_sent = sendto(sock_fd, data.c_str(), data.size(), 0, (struct sockaddr*)&client_addr, addr_len);
        if (bytes_sent < 0) {
            perror("sendto");
            return false;
        }
        return true;
    }

    bool close() override {
        if (::close(sock_fd) == 0) return true;
        return false;
    }

    bool connect(const string&, int) override {
        return false;  // Not applicable for server
    }
};
