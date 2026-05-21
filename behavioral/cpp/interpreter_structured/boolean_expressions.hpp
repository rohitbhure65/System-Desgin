#pragma once
#include "interfaces.hpp"
#include <memory>

class VariableExpression : public BooleanExpression {
private:
    std::string variableName;
    
public:
    VariableExpression(const std::string& name) : variableName(name) {}
    
    bool evaluate(Context& context) override {
        return context.getVariable(variableName) != 0;
    }
};

class ConstantExpression : public BooleanExpression {
private:
    bool value;
    
public:
    ConstantExpression(bool value) : value(value) {}
    
    bool evaluate(Context& context) override {
        return value;
    }
};

class AndExpression : public BooleanExpression {
private:
    std::unique_ptr<BooleanExpression> left;
    std::unique_ptr<BooleanExpression> right;
    
public:
    AndExpression(std::unique_ptr<BooleanExpression> left, std::unique_ptr<BooleanExpression> right)
        : left(std::move(left)), right(std::move(right)) {}
    
    bool evaluate(Context& context) override {
        return left->evaluate(context) && right->evaluate(context);
    }
};

class OrExpression : public BooleanExpression {
private:
    std::unique_ptr<BooleanExpression> left;
    std::unique_ptr<BooleanExpression> right;
    
public:
    OrExpression(std::unique_ptr<BooleanExpression> left, std::unique_ptr<BooleanExpression> right)
        : left(std::move(left)), right(std::move(right)) {}
    
    bool evaluate(Context& context) override {
        return left->evaluate(context) || right->evaluate(context);
    }
};

class NotExpression : public BooleanExpression {
private:
    std::unique_ptr<BooleanExpression> expression;
    
public:
    NotExpression(std::unique_ptr<BooleanExpression> expr)
        : expression(std::move(expr)) {}
    
    bool evaluate(Context& context) override {
        return !expression->evaluate(context);
    }
};
