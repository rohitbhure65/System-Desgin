#pragma once
#include "interfaces.hpp"
#include <unordered_map>

class PrototypeRegistry {
private:
    std::unordered_map<std::string, std::unique_ptr<Prototype>> prototypes;
    
public:
    void registerPrototype(const std::string& key, std::unique_ptr<Prototype> prototype) {
        prototypes[key] = std::move(prototype);
    }
    
    std::unique_ptr<Prototype> clone(const std::string& key) {
        auto it = prototypes.find(key);
        if (it != prototypes.end()) {
            return it->second->clone();
        }
        return nullptr;
    }
};
