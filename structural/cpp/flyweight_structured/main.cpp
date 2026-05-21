#include "forest.hpp"
#include "text_editor.hpp"
#include "game_soldiers.hpp"
#include <iostream>

int main() {
    std::cout << "=== Flyweight Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Forest Trees
    std::cout << "--- Forest Trees Example ---" << std::endl;
    
    TreeFactory treeFactory;
    
    std::vector<Tree> forest;
    
    forest.emplace_back(10, 20, treeFactory.getTreeType("Oak", "Green", "Rough"));
    forest.emplace_back(30, 40, treeFactory.getTreeType("Oak", "Green", "Rough"));
    forest.emplace_back(50, 60, treeFactory.getTreeType("Oak", "Green", "Rough"));
    
    forest.emplace_back(15, 25, treeFactory.getTreeType("Pine", "Dark Green", "Smooth"));
    forest.emplace_back(35, 45, treeFactory.getTreeType("Pine", "Dark Green", "Smooth"));
    
    forest.emplace_back(20, 30, treeFactory.getTreeType("Oak", "Green", "Rough"));
    
    std::cout << "\nDrawing forest:" << std::endl;
    for (const auto& tree : forest) {
        tree.draw();
    }
    
    std::cout << "\nTotal unique tree types: " << treeFactory.getTotalTreeTypes() << std::endl;
    std::cout << "Total trees in forest: " << forest.size() << std::endl;
    
    std::cout << std::endl;
    
    // Example 2: Text Editor Characters
    std::cout << "--- Text Editor Characters Example ---" << std::endl;
    
    CharacterFormatFactory formatFactory;
    
    std::vector<Character> document;
    
    document.emplace_back('H', formatFactory.getFormat("Arial", 12, "Black", true, false));
    document.emplace_back('e', formatFactory.getFormat("Arial", 12, "Black", false, false));
    document.emplace_back('l', formatFactory.getFormat("Arial", 12, "Black", false, false));
    document.emplace_back('l', formatFactory.getFormat("Arial", 12, "Black", false, false));
    document.emplace_back('o', formatFactory.getFormat("Arial", 12, "Black", false, false));
    
    document.emplace_back(' ', formatFactory.getFormat("Arial", 12, "Black", false, false));
    
    document.emplace_back('W', formatFactory.getFormat("Times New Roman", 14, "Blue", true, true));
    document.emplace_back('o', formatFactory.getFormat("Times New Roman", 14, "Blue", false, true));
    document.emplace_back('r', formatFactory.getFormat("Times New Roman", 14, "Blue", false, true));
    document.emplace_back('l', formatFactory.getFormat("Times New Roman", 14, "Blue", false, true));
    document.emplace_back('d', formatFactory.getFormat("Times New Roman", 14, "Blue", false, true));
    
    std::cout << "\nRendering document:" << std::endl;
    for (const auto& character : document) {
        character.render();
    }
    
    std::cout << "\nTotal unique formats: " << formatFactory.getTotalFormats() << std::endl;
    std::cout << "Total characters: " << document.size() << std::endl;
    
    std::cout << std::endl;
    
    // Example 3: Game Soldiers
    std::cout << "--- Game Soldiers Example ---" << std::endl;
    
    SoldierTypeFactory soldierFactory;
    
    std::vector<Soldier> army;
    
    army.emplace_back(10, 10, "Rifle", soldierFactory.getSoldierType("Camouflage", 5, "Private"));
    army.emplace_back(20, 20, "Rifle", soldierFactory.getSoldierType("Camouflage", 5, "Private"));
    army.emplace_back(30, 30, "Rifle", soldierFactory.getSoldierType("Camouflage", 5, "Private"));
    
    army.emplace_back(15, 15, "Sniper", soldierFactory.getSoldierType("Desert", 4, "Sergeant"));
    army.emplace_back(25, 25, "Sniper", soldierFactory.getSoldierType("Desert", 4, "Sergeant"));
    
    army.emplace_back(40, 40, "Machine Gun", soldierFactory.getSoldierType("Camouflage", 5, "Private"));
    
    std::cout << "\nRendering army:" << std::endl;
    for (const auto& soldier : army) {
        soldier.render();
    }
    
    std::cout << "\nTotal unique soldier types: " << soldierFactory.getTotalSoldierTypes() << std::endl;
    std::cout << "Total soldiers: " << army.size() << std::endl;
    
    return 0;
}
