#include "text_editor.hpp"
#include "game_state.hpp"
#include "configuration.hpp"
#include <iostream>

int main() {
    std::cout << "=== Memento Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Text Editor with Undo
    std::cout << "--- Text Editor with Undo ---" << std::endl;
    
    TextEditor editor;
    History history;
    
    editor.write("Hello ");
    history.push(editor.save());
    
    editor.write("World ");
    history.push(editor.save());
    
    editor.write("!");
    history.push(editor.save());
    
    std::cout << "\nCurrent content: \"" << editor.getContent() << "\"" << std::endl;
    std::cout << "History size: " << history.size() << std::endl;
    
    std::cout << "\nPerforming undo..." << std::endl;
    if (auto memento = history.pop()) {
        editor.restore(*memento);
    }
    
    std::cout << "\nPerforming undo..." << std::endl;
    if (auto memento = history.pop()) {
        editor.restore(*memento);
    }
    
    std::cout << std::endl;
    
    // Example 2: Game Save System
    std::cout << "--- Game Save System ---" << std::endl;
    
    GameCharacter player;
    GameSaveManager saveManager;
    
    std::cout << "\nInitial state:" << std::endl;
    player.displayStatus();
    
    std::cout << "\nPlaying game..." << std::endl;
    player.moveTo("Forest");
    player.gainScore(100);
    player.takeDamage(10);
    
    std::cout << "\nCreating save 1..." << std::endl;
    saveManager.createSave(player.saveState());
    
    std::cout << "\nContinuing game..." << std::endl;
    player.moveTo("Castle");
    player.levelUp();
    player.gainScore(500);
    player.takeDamage(30);
    
    std::cout << "\nCreating save 2..." << std::endl;
    saveManager.createSave(player.saveState());
    
    std::cout << "\nCurrent state:" << std::endl;
    player.displayStatus();
    
    std::cout << "\nLoading save 1..." << std::endl;
    if (auto save = saveManager.loadSave(0)) {
        player.restoreState(*save);
    }
    
    std::cout << std::endl;
    
    // Example 3: Configuration Management
    std::cout << "--- Configuration Management ---" << std::endl;
    
    ApplicationSettings settings;
    
    std::cout << "\nDefault settings:" << std::endl;
    settings.displaySettings();
    
    auto originalConfig = settings.saveConfiguration();
    
    std::cout << "\nChanging settings..." << std::endl;
    settings.setTheme("dark");
    settings.setFontSize(14);
    settings.setNotificationsEnabled(false);
    
    std::cout << "\nNew settings:" << std::endl;
    settings.displaySettings();
    
    std::cout << "\nRestoring original settings..." << std::endl;
    settings.restoreConfiguration(*originalConfig);
    
    return 0;
}
