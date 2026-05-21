#pragma once
#include "arithmetic_expressions.hpp"
#include <string>
#include <cctype>

class ExpressionParser {
private:
    std::string expression;
    size_t pos;
    
    char peek() {
        return pos < expression.length() ? expression[pos] : '\0';
    }
    
    char next() {
        return expression[pos++];
    }
    
    void skipWhitespace() {
        while (pos < expression.length() && std::isspace(expression[pos])) {
            pos++;
        }
    }
    
    std::unique_ptr<Expression> parseExpression() {
        auto left = parseTerm();
        
        while (peek() == '+' || peek() == '-') {
            char op = next();
            auto right = parseTerm();
            
            if (op == '+') {
                left = std::make_unique<AddExpression>(std::move(left), std::move(right));
            } else {
                left = std::make_unique<SubtractExpression>(std::move(left), std::move(right));
            }
        }
        
        return left;
    }
    
    std::unique_ptr<Expression> parseTerm() {
        auto left = parseFactor();
        
        while (peek() == '*' || peek() == '/') {
            char op = next();
            auto right = parseFactor();
            
            if (op == '*') {
                left = std::make_unique<MultiplyExpression>(std::move(left), std::move(right));
            }
        }
        
        return left;
    }
    
    std::unique_ptr<Expression> parseFactor() {
        skipWhitespace();
        
        if (peek() == '(') {
            next();
            auto expr = parseExpression();
            next();
            return expr;
        }
        
        skipWhitespace();
        int value = 0;
        while (pos < expression.length() && std::isdigit(expression[pos])) {
            value = value * 10 + (expression[pos] - '0');
            pos++;
        }
        
        return std::make_unique<NumberExpression>(value);
    }
    
public:
    ExpressionParser(const std::string& expr) : expression(expr), pos(0) {}
    
    std::unique_ptr<Expression> parse() {
        return parseExpression();
    }
};
