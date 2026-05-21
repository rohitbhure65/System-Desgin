#pragma once
#include <memory>

class State {
public:
    virtual ~State() = default;
    virtual void insertCoin() = 0;
    virtual void ejectCoin() = 0;
    virtual void pressButton() = 0;
    virtual void dispense() = 0;
};
