#pragma once
#include "products.hpp"

class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
    
    virtual void buildFoundation() = 0;
    virtual void buildStructure() = 0;
    virtual void buildRoof() = 0;
    virtual void buildInterior() = 0;
    virtual void buildGarage() = 0;
    virtual void buildGarden() = 0;
    virtual void buildSwimmingPool() = 0;
    
    virtual House getResult() = 0;
};
