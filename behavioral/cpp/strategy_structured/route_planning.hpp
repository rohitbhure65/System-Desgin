#pragma once
#include <string>
#include <memory>

class RouteStrategy {
public:
    virtual ~RouteStrategy() = default;
    virtual void calculateRoute(const std::string& from, const std::string& to) = 0;
};

class FastestRoute : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating fastest route from " << from << " to " << to << std::endl;
        std::cout << "  Using highways and main roads to minimize time" << std::endl;
        std::cout << "  Estimated time: 25 minutes" << std::endl;
    }
};

class ShortestRoute : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating shortest route from " << from << " to " << to << std::endl;
        std::cout << "  Using direct path to minimize distance" << std::endl;
        std::cout << "  Estimated distance: 15 km" << std::endl;
    }
};

class ScenicRoute : public RouteStrategy {
public:
    void calculateRoute(const std::string& from, const std::string& to) override {
        std::cout << "Calculating scenic route from " << from << " to " << to << std::endl;
        std::cout << "  Using parks and landmarks for best views" << std::endl;
        std::cout << "  Estimated time: 45 minutes" << std::endl;
    }
};

class NavigationSystem {
private:
    std::unique_ptr<RouteStrategy> strategy;
    
public:
    void setRouteStrategy(std::unique_ptr<RouteStrategy> strat) {
        strategy = std::move(strat);
    }
    
    void navigate(const std::string& from, const std::string& to) {
        std::cout << "\n=== Navigation ===" << std::endl;
        std::cout << "From: " << from << std::endl;
        std::cout << "To: " << to << std::endl;
        
        if (strategy) {
            strategy->calculateRoute(from, to);
        } else {
            std::cout << "No route strategy selected" << std::endl;
        }
    }
};
