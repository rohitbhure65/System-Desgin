#pragma once
#include <string>
#include <memory>

class RemoteServer {
public:
    virtual ~RemoteServer() = default;
    virtual void request(const std::string& data) = 0;
};

class RealRemoteServer : public RemoteServer {
public:
    void request(const std::string& data) override {
        std::cout << "Remote server processing request: " << data << std::endl;
    }
};

class RemoteServerProxy : public RemoteServer {
private:
    std::unique_ptr<RealRemoteServer> remoteServer;
    std::string serverAddress;
    
    void connectToServer() {
        std::cout << "Connecting to remote server at " << serverAddress << "..." << std::endl;
    }
    
public:
    RemoteServerProxy(const std::string& address) : serverAddress(address) {}
    
    void request(const std::string& data) override {
        if (!remoteServer) {
            connectToServer();
            remoteServer = std::make_unique<RealRemoteServer>();
        }
        std::cout << "Proxy forwarding request to remote server..." << std::endl;
        remoteServer->request(data);
    }
};
