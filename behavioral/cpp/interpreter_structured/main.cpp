#include "interfaces.hpp"
#include "arithmetic_expressions.hpp"
#include "parser.hpp"
#include "boolean_expressions.hpp"
#include "pattern_expressions.hpp"
#include <iostream>
#include <vector>

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
    
    auto expr1 = std::make_unique<AndExpression>(
        std::make_unique<VariableExpression>("A"),
        std::make_unique<OrExpression>(
            std::make_unique<VariableExpression>("B"),
            std::make_unique<VariableExpression>("C")
        )
    );
    std::cout << "\nA AND (B OR C): " << (expr1->evaluate(context) ? "true" : "false") << std::endl;
    
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
