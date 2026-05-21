#include "virtual_proxy.hpp"
#include "protection_proxy.hpp"
#include "caching_proxy.hpp"
#include "logging_proxy.hpp"
#include "remote_proxy.hpp"
#include <iostream>
#include <memory>

int main() {
    std::cout << "=== Proxy Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Virtual Proxy (Lazy Loading)
    std::cout << "--- Virtual Proxy (Lazy Loading) Example ---" << std::endl;
    
    std::shared_ptr<Image> image1 = std::make_shared<ProxyImage>("photo1.jpg");
    std::shared_ptr<Image> image2 = std::make_shared<ProxyImage>("photo2.jpg");
    std::shared_ptr<Image> image3 = std::make_shared<ProxyImage>("photo1.jpg");
    
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
