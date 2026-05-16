/*
 * INTERPRETER DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Interpreter pattern defines a grammar for a language and interprets sentences in that language.
 * It's used to evaluate sentences in a language and can be extended with new grammar rules.
 * 
 * WHY DOES IT EXIST?
 * - When you need to interpret a language or expression
 * - When you want to parse and evaluate expressions according to a grammar
 * - When you have a simple grammar that can be represented as a tree structure
 * 
 * WHEN TO USE IT?
 * - When the grammar of the language is relatively simple
 * - When efficiency is not a critical concern
 * - When you want to parse and evaluate expressions dynamically
 * - Common use cases: SQL parsers, regular expression engines, formula evaluators, configuration file parsers
 * 
 * PROS:
 * - Can easily change and extend the grammar
 * - Separates grammar from the interpretation logic
 * - Can be combined with Composite pattern to build parse trees
 * - Makes adding new expressions easy
 * 
 * CONS:
 * - Can become complex for large grammars
 * - Can be less efficient than other parsing approaches
 * - Can lead to many small classes
 * - May be overkill for simple expressions
 * 
 * REAL-WORLD ANALOGY:
 * Think of a calculator. When you type "2 + 3 * 4", the calculator (interpreter) parses the expression according to arithmetic grammar rules. It interprets the multiplication first (operator precedence), then addition, and returns the result. The calculator doesn't need to know the specific numbers in advance - it interprets any valid expression.
 */

#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <memory>
#include <sstream>
#include <vector>
#include <cctype>

// Expression interface - declares the interpret method
class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret() = 0;
};

// Terminal Expression - implements interpret for terminal symbols
class NumberExpression : public Expression {
private:
    int value;
    
public:
    NumberExpression(int value) : value(value) {}
    
    int interpret() override {
        return value;
    }
};

// Non-terminal Expression - implements interpret for operators
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

// Parser - parses the expression and builds the syntax tree
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
            // Division not implemented for simplicity
        }
        
        return left;
    }
    
    std::unique_ptr<Expression> parseFactor() {
        skipWhitespace();
        
        if (peek() == '(') {
            next();  // consume '('
            auto expr = parseExpression();
            next();  // consume ')'
            return expr;
        }
        
        // Parse number
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

// Context - provides information to the interpreter
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

// Example 2: Boolean Expression Interpreter
// Shows how Interpreter can be used for boolean logic

class BooleanExpression {
public:
    virtual ~BooleanExpression() = default;
    virtual bool evaluate(Context& context) = 0;
};

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

// Example 3: String Pattern Matcher
// Shows how Interpreter can be used for pattern matching

class PatternExpression {
public:
    virtual ~PatternExpression() = default;
    virtual bool match(const std::string& text) = 0;
};

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
        // Simple wildcard matching: * matches any sequence
        size_t patternPos = 0;
        size_t textPos = 0;
        
        while (patternPos < pattern.length() && textPos < text.length()) {
            if (pattern[patternPos] == '*') {
                // Skip wildcard
                patternPos++;
                if (patternPos == pattern.length()) {
                    return true;  // Wildcard at end matches rest
                }
                // Find next character in pattern after wildcard
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

int main() {
    std::cout << "=== Interpreter Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Arithmetic Expression
    std::cout << "--- Arithmetic Expression Example ---" << std::endl;
    
    std::vector<std::string> expressions = {
        "2 + 3 * 4",
        "10 - 5 + 3",
        "2 * 3 + 4 * 5"
    };
    
    for (const auto& expr : expressions) {
        std::cout << "\nExpression: " << expr << std::endl;
        ExpressionParser parser(expr);
        auto parsedExpr = parser.parse();
        std::cout << "Result: " << parsedExpr->interpret() << std::endl;
    }
    
    // Example 2: Boolean Expression
    std::cout << "\n--- Boolean Expression Example ---" << std::endl;
    
    Context context;
    context.setVariable("A", 1);
    context.setVariable("B", 0);
    context.setVariable("C", 1);
    
    std::cout << "\nVariables: A=1, B=0, C=1" << std::endl;
    
    // A AND (B OR C)
    auto expr1 = std::make_unique<AndExpression>(
        std::make_unique<VariableExpression>("A"),
        std::make_unique<OrExpression>(
            std::make_unique<VariableExpression>("B"),
            std::make_unique<VariableExpression>("C")
        )
    );
    std::cout << "\nA AND (B OR C): " << (expr1->evaluate(context) ? "true" : "false") << std::endl;
    
    // NOT (A AND B)
    auto expr2 = std::make_unique<NotExpression>(
        std::make_unique<AndExpression>(
            std::make_unique<VariableExpression>("A"),
            std::make_unique<VariableExpression>("B")
        )
    );
    std::cout << "NOT (A AND B): " << (expr2->evaluate(context) ? "true" : "false") << std::endl;
    
    // Example 3: Pattern Matching
    std::cout << "\n--- Pattern Matching Example ---" << std::endl;
    
    std::vector<std::string> texts = {
        "Hello World",
        "Design Patterns",
        "Hello Design Patterns",
        "World of Patterns"
    };
    
    std::cout << "\nMatching 'Hello':" << std::endl;
    LiteralPattern helloPattern("Hello");
    for (const auto& text : texts) {
        std::cout << "  \"" << text << "\": " << (helloPattern.match(text) ? "Match" : "No match") << std::endl;
    }
    
    std::cout << "\nMatching 'Design*':" << std::endl;
    WildcardPattern designPattern("Design*");
    for (const auto& text : texts) {
        std::cout << "  \"" << text << "\": " << (designPattern.match(text) ? "Match" : "No match") << std::endl;
    }
    
    std::cout << "\nMatching 'Hello' OR 'World':" << std::endl;
    OrPattern orPattern;
    orPattern.addPattern(std::make_unique<LiteralPattern>("Hello"));
    orPattern.addPattern(std::make_unique<LiteralPattern>("World"));
    for (const auto& text : texts) {
        std::cout << "  \"" << text << "\": " << (orPattern.match(text) ? "Match" : "No match") << std::endl;
    }
    
    return 0;
}
