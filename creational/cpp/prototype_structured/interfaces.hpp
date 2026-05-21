#pragma once
#include <iostream>
#include <string>
#include <memory>

class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void display() const = 0;
    virtual std::string getType() const = 0;
};
