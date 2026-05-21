#pragma once
#include "interfaces.hpp"
#include <memory>

class NumberExpression : public Expression {
private:
    int value;
    
public:
    NumberExpression(int value) : value(value) {}
    
    int interpret() override {
        return value;
    }
};

class AddExpression : public Expression {
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    
public:
    AddExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}
    
    int interpret() override {
        return left->interpret() + right->interpret();
    }
};

class SubtractExpression : public Expression {
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    
public:
    SubtractExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}
    
    int interpret() override {
        return left->interpret() - right->interpret();
    }
};

class MultiplyExpression : public Expression {
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    
public:
    MultiplyExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}
    
    int interpret() override {
        return left->interpret() * right->interpret();
    }
};
