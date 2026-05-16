/*
 * PROXY DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Proxy pattern provides a surrogate or placeholder object to control access to another object.
 * It acts as an intermediary between the client and the real object.
 * 
 * WHY DOES IT EXIST?
 * - When you need to control access to an object
 * - When you want to add additional functionality when accessing an object
 * - When you need to defer the creation or initialization of expensive objects
 * 
 * WHEN TO USE IT?
 * - When you want to add a layer of security to access an object
 * - When you need to cache results of expensive operations
 * - When you want to delay object creation until it's actually needed (lazy initialization)
 * - When you need to log or monitor access to an object
 * - Common use cases: remote objects, virtual proxies, protection proxies, smart references
 * 
 * PROS:
 * - Can control access to the real object
 * - Can add additional functionality without changing the real object
 * - Can optimize performance (lazy loading, caching)
 * - Can provide security by controlling access
 * 
 * CONS:
 * - Adds an extra layer of indirection
 * - Can increase response time due to proxy overhead
 * - Can make the code more complex
 * - May introduce bugs if the proxy doesn't perfectly mimic the real object
 * 
 * REAL-WORLD ANALOGY:
 * Think of a credit card. The credit card (proxy) represents your bank account (real object). You don't carry your actual bank account around - you use the card as a proxy. The card controls access to your money, adds security (PIN, chip), and logs transactions, all while giving you access to your funds.
 */

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

// Subject Interface - defines the common interface for RealSubject and Proxy
class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
};

// RealSubject - the actual object that the proxy represents
class RealImage : public Image {
private:
    std::string filename;
    
    // Helper method to load the image from disk
    void loadFromDisk() {
        std::cout << "Loading " << filename << " from disk..." << std::endl;
    }
    
public:
    RealImage(const std::string& filename) : filename(filename) {
        loadFromDisk();
    }
    
    void display() override {
        std::cout << "Displaying " << filename << std::endl;
    }
};

// Proxy - controls access to the RealSubject
class ProxyImage : public Image {
private:
    std::string filename;
    std::unique_ptr<RealImage> realImage;
    
public:
    ProxyImage(const std::string& filename) : filename(filename) {}
    
    void display() override {
        // Lazy initialization: only create the real image when needed
        if (!realImage) {
            std::cout << "Creating real image on first access..." << std::endl;
            realImage = std::make_unique<RealImage>(filename);
        }
        realImage->display();
    }
};

// Example 2: Protection Proxy
// Shows how Proxy can control access based on permissions

class Database {
public:
    virtual ~Database() = default;
    virtual void query(const std::string& sql) = 0;
};

class RealDatabase : public Database {
public:
    void query(const std::string& sql) override {
        std::cout << "Executing query: " << sql << std::endl;
    }
};

class DatabaseProxy : public Database {
private:
    std::unique_ptr<RealDatabase> realDatabase;
    std::string currentUser;
    std::unordered_map<std::string, bool> permissions;
    
    bool hasPermission() {
        return permissions[currentUser];
    }
    
public:
    DatabaseProxy(const std::string& user) : currentUser(user) {
        // Set up permissions (in real app, this would come from auth system)
        permissions["admin"] = true;
        permissions["user"] = false;
        permissions["guest"] = false;
    }
    
    void query(const std::string& sql) override {
        if (hasPermission()) {
            if (!realDatabase) {
                realDatabase = std::make_unique<RealDatabase>();
            }
            realDatabase->query(sql);
        } else {
            std::cout << "Access denied: User '" << currentUser 
                      << "' does not have permission to execute queries" << std::endl;
        }
    }
    
    void setUser(const std::string& user) {
        currentUser = user;
    }
};

// Example 3: Caching Proxy
// Shows how Proxy can cache expensive operations

class Video {
public:
    virtual ~Video() = default;
    virtual void play() = 0;
};

class RealVideo : public Video {
private:
    std::string filename;
    
    void loadVideo() {
        std::cout << "Loading video " << filename << " from server..." << std::endl;
    }
    
public:
    RealVideo(const std::string& filename) : filename(filename) {
        loadVideo();
    }
    
    void play() override {
        std::cout << "Playing video: " << filename << std::endl;
    }
};

class VideoProxy : public Video {
private:
    std::string filename;
    std::unique_ptr<RealVideo> realVideo;
    bool isLoaded = false;
    
public:
    VideoProxy(const std::string& filename) : filename(filename) {}
    
    void play() override {
        if (!isLoaded) {
            std::cout << "Loading video on first play..." << std::endl;
            realVideo = std::make_unique<RealVideo>(filename);
            isLoaded = true;
        } else {
            std::cout << "Using cached video..." << std::endl;
        }
        realVideo->play();
    }
};

// Example 4: Logging Proxy
// Shows how Proxy can add logging functionality

class Service {
public:
    virtual ~Service() = default;
    virtual void doWork() = 0;
};

class RealService : public Service {
public:
    void doWork() override {
        std::cout << "Service: Performing work..." << std::endl;
    }
};

class LoggingProxy : public Service {
private:
    std::unique_ptr<RealService> realService;
    
    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
    
public:
    LoggingProxy() : realService(std::make_unique<RealService>()) {}
    
    void doWork() override {
        log("Before doWork");
        realService->doWork();
        log("After doWork");
    }
};

// Example 5: Remote Proxy (simulated)
// Shows how Proxy can represent remote objects

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

int main() {
    std::cout << "=== Proxy Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Virtual Proxy (Lazy Loading)
    std::cout << "--- Virtual Proxy (Lazy Loading) Example ---" << std::endl;
    
    std::shared_ptr<Image> image1 = std::make_shared<ProxyImage>("photo1.jpg");
    std::shared_ptr<Image> image2 = std::make_shared<ProxyImage>("photo2.jpg");
    std::shared_ptr<Image> image3 = std::make_shared<ProxyImage>("photo1.jpg");  // Same as image1
    
    std::cout << "\nFirst display of image1:" << std::endl;
    image1->display();
    
    std::cout << "\nSecond display of image1 (should use cached):" << std::endl;
    image1->display();
    
    std::cout << "\nDisplay of image2:" << std::endl;
    image2->display();
    
    std::cout << "\nDisplay of image3 (same as image1, should use cached):" << std::endl;
    image3->display();
    
    std::cout << std::endl;
    
    // Example 2: Protection Proxy
    std::cout << "--- Protection Proxy Example ---" << std::endl;
    
    DatabaseProxy db("guest");
    std::cout << "\nGuest trying to execute query:" << std::endl;
    db.query("SELECT * FROM users");
    
    std::cout << "\nSwitching to admin user:" << std::endl;
    db.setUser("admin");
    db.query("SELECT * FROM users");
    
    std::cout << "\nSwitching back to regular user:" << std::endl;
    db.setUser("user");
    db.query("SELECT * FROM users");
    
    std::cout << std::endl;
    
    // Example 3: Caching Proxy
    std::cout << "--- Caching Proxy Example ---" << std::endl;
    
    VideoProxy video("movie.mp4");
    
    std::cout << "\nFirst play (will load):" << std::endl;
    video.play();
    
    std::cout << "\nSecond play (will use cache):" << std::endl;
    video.play();
    
    std::cout << "\nThird play (will use cache):" << std::endl;
    video.play();
    
    std::cout << std::endl;
    
    // Example 4: Logging Proxy
    std::cout << "--- Logging Proxy Example ---" << std::endl;
    
    LoggingProxy loggingService;
    loggingService.doWork();
    
    std::cout << std::endl;
    
    // Example 5: Remote Proxy
    std::cout << "--- Remote Proxy Example ---" << std::endl;
    
    RemoteServerProxy remoteProxy("192.168.1.100");
    
    std::cout << "\nFirst request (will connect):" << std::endl;
    remoteProxy.request("GET /api/data");
    
    std::cout << "\nSecond request (already connected):" << std::endl;
    remoteProxy.request("POST /api/data");
    
    return 0;
}
