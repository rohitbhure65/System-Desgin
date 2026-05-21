#pragma once
#include "interfaces.hpp"

class ConstructionDirector {
private:
    HouseBuilder* builder;
    
public:
    void setBuilder(HouseBuilder* b) {
        builder = b;
    }
    
    void buildBasicHouse() {
        builder->buildFoundation();
        builder->buildStructure();
        builder->buildRoof();
        builder->buildInterior();
    }
    
    void buildFullHouse() {
        builder->buildFoundation();
        builder->buildStructure();
        builder->buildRoof();
        builder->buildInterior();
        builder->buildGarage();
        builder->buildGarden();
        builder->buildSwimmingPool();
    }
    
    void buildCustomHouse(bool withGarage, bool withGarden, bool withPool) {
        builder->buildFoundation();
        builder->buildStructure();
        builder->buildRoof();
        builder->buildInterior();
        if (withGarage) builder->buildGarage();
        if (withGarden) builder->buildGarden();
        if (withPool) builder->buildSwimmingPool();
    }
};
