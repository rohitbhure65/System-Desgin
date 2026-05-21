#pragma once
#include "interfaces.hpp"
#include <vector>
#include <memory>

class LiteralPattern : public PatternExpression {
private:
    std::string literal;
    
public:
    LiteralPattern(const std::string& lit) : literal(lit) {}
    
    bool match(const std::string& text) override {
        return text.find(literal) != std::string::npos;
    }
};

class WildcardPattern : public PatternExpression {
private:
    std::string pattern;
    
public:
    WildcardPattern(const std::string& pat) : pattern(pat) {}
    
    bool match(const std::string& text) override {
        size_t patternPos = 0;
        size_t textPos = 0;
        
        while (patternPos < pattern.length() && textPos < text.length()) {
            if (pattern[patternPos] == '*') {
                patternPos++;
                if (patternPos == pattern.length()) {
                    return true;
                }
                char nextChar = pattern[patternPos];
                while (textPos < text.length() && text[textPos] != nextChar) {
                    textPos++;
                }
            } else if (pattern[patternPos] == text[textPos]) {
                patternPos++;
                textPos++;
            } else {
                return false;
            }
        }
        
        return patternPos == pattern.length();
    }
};

class OrPattern : public PatternExpression {
private:
    std::vector<std::unique_ptr<PatternExpression>> patterns;
    
public:
    void addPattern(std::unique_ptr<PatternExpression> pattern) {
        patterns.push_back(std::move(pattern));
    }
    
    bool match(const std::string& text) override {
        for (const auto& pattern : patterns) {
            if (pattern->match(text)) {
                return true;
            }
        }
        return false;
    }
};
