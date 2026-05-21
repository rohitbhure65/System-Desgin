#pragma once
#include <memory>
#include <map>
#include <string>

class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret() = 0;
};

class BooleanExpression {
public:
    virtual ~BooleanExpression() = default;
    virtual bool evaluate(Context& context) = 0;
};

class PatternExpression {
public:
    virtual ~PatternExpression() = default;
    virtual bool match(const std::string& text) = 0;
};

class Context {
private:
    std::map<std::string, int> variables;
    
public:
    void setVariable(const std::string& name, int value) {
        variables[name] = value;
    }
    
    int getVariable(const std::string& name) {
        return variables[name];
    }
};
