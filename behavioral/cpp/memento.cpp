/*
 * MEMENTO DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Memento pattern lets you save and restore the previous state of an object without revealing the details of its implementation.
 * It provides the ability to restore an object to its previous state (undo).
 * 
 * WHY DOES IT EXIST?
 * - When you need to implement undo/redo functionality
 * - When you want to create snapshots of an object's state
 * - When direct access to the object's internal representation would violate encapsulation
 * 
 * WHEN TO USE IT?
 * - When you need to save and restore the state of an object without exposing its internal structure
 * - When you want to implement undo/redo operations
 * - When you need to maintain a history of states
 * - Common use cases: text editors (undo/redo), game states, database transactions, configuration management
 * 
 * PROS:
 * - Preserves encapsulation (doesn't expose internal state)
 * - Simplifies the originator (doesn't need to manage state history)
 * - Can provide snapshots at different times
 * - Supports undo/redo functionality
 * 
 * CONS:
 * - Can be expensive if the originator has large state
 * - May consume significant memory if many mementos are stored
 * - Caretaker must track the originator's lifecycle
 * - Can be complex to implement for complex objects
 * 
 * REAL-WORLD ANALOGY:
 * Think of a game save system. When you save a game, the game creates a snapshot of your current state (position, health, inventory). This snapshot (memento) is stored separately. Later, you can restore the game to that exact state by loading the snapshot. The game doesn't need to know how the snapshot is stored, just that it can be restored.
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <ctime>

// Memento - stores the internal state of the Originator
class TextEditorMemento {
private:
    std::string content;
    std::string timestamp;
    
public:
    TextEditorMemento(const std::string& content) 
        : content(content), timestamp(getCurrentTime()) {}
    
    std::string getContent() const {
        return content;
    }
    
    std::string getTimestamp() const {
        return timestamp;
    }
    
private:
    static std::string getCurrentTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        std::string timeStr(dt);
        timeStr.pop_back(); // Remove newline
        return timeStr;
    }
};

// Originator - creates a memento containing a snapshot of its current state
class TextEditor {
private:
    std::string content;
    
public:
    TextEditor() : content("") {}
    
    void write(const std::string& text) {
        content += text;
        std::cout << "Text: \"" << text << "\" added" << std::endl;
    }
    
    void setContent(const std::string& newContent) {
        content = newContent;
    }
    
    std::string getContent() const {
        return content;
    }
    
    std::unique_ptr<TextEditorMemento> save() {
        std::cout << "Saving current state..." << std::endl;
        return std::make_unique<TextEditorMemento>(content);
    }
    
    void restore(const TextEditorMemento& memento) {
        content = memento.getContent();
        std::cout << "Restored state from " << memento.getTimestamp() << std::endl;
        std::cout << "Current content: \"" << content << "\"" << std::endl;
    }
};

// Caretaker - manages mementos, never operates on their contents
class History {
private:
    std::vector<std::unique_ptr<TextEditorMemento>> mementos;
    
public:
    void push(std::unique_ptr<TextEditorMemento> memento) {
        mementos.push_back(std::move(memento));
    }
    
    std::unique_ptr<TextEditorMemento> pop() {
        if (mementos.empty()) {
            return nullptr;
        }
        auto memento = std::move(mementos.back());
        mementos.pop_back();
        return memento;
    }
    
    size_t size() const {
        return mementos.size();
    }
};

// Example 2: Game State Memento
// Shows how Memento can be used for game saves

class GameStateMemento {
private:
    int level;
    int health;
    int score;
    std::string position;
    
public:
    GameStateMemento(int level, int health, int score, const std::string& position)
        : level(level), health(health), score(score), position(position) {}
    
    int getLevel() const { return level; }
    int getHealth() const { return health; }
    int getScore() const { return score; }
    std::string getPosition() const { return position; }
};

class GameCharacter {
private:
    int level;
    int health;
    int score;
    std::string position;
    
public:
    GameCharacter() : level(1), health(100), score(0), position("Start") {}
    
    void moveTo(const std::string& newPosition) {
        position = newPosition;
        std::cout << "Moved to " << position << std::endl;
    }
    
    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << "Took " << damage << " damage. Health: " << health << std::endl;
    }
    
    void gainScore(int points) {
        score += points;
        std::cout << "Gained " << points << " points. Score: " << score << std::endl;
    }
    
    void levelUp() {
        level++;
        health = 100;
        std::cout << "Level up! Now at level " << level << std::endl;
    }
    
    void displayStatus() const {
        std::cout << "=== Character Status ===" << std::endl;
        std::cout << "Level: " << level << std::endl;
        std::cout << "Health: " << health << std::endl;
        std::cout << "Score: " << score << std::endl;
        std::cout << "Position: " << position << std::endl;
        std::cout << "=====================" << std::endl;
    }
    
    std::unique_ptr<GameStateMemento> saveState() {
        std::cout << "Saving game state..." << std::endl;
        return std::make_unique<GameStateMemento>(level, health, score, position);
    }
    
    void restoreState(const GameStateMemento& memento) {
        level = memento.getLevel();
        health = memento.getHealth();
        score = memento.getScore();
        position = memento.getPosition();
        std::cout << "Game state restored!" << std::endl;
        displayStatus();
    }
};

class GameSaveManager {
private:
    std::vector<std::unique_ptr<GameStateMemento>> saves;
    
public:
    void createSave(std::unique_ptr<GameStateMemento> save) {
        saves.push_back(std::move(save));
        std::cout << "Save created. Total saves: " << saves.size() << std::endl;
    }
    
    std::unique_ptr<GameStateMemento> loadSave(int index) {
        if (index >= 0 && index < saves.size()) {
            std::cout << "Loading save " << (index + 1) << "..." << std::endl;
            return std::move(saves[index]);
        }
        return nullptr;
    }
    
    int getSaveCount() const {
        return saves.size();
    }
};

// Example 3: Configuration Memento
// Shows how Memento can be used for configuration management

class ConfigurationMemento {
private:
    std::string theme;
    int fontSize;
    bool notificationsEnabled;
    
public:
    ConfigurationMemento(const std::string& theme, int fontSize, bool notifications)
        : theme(theme), fontSize(fontSize), notificationsEnabled(notifications) {}
    
    std::string getTheme() const { return theme; }
    int getFontSize() const { return fontSize; }
    bool getNotificationsEnabled() const { return notificationsEnabled; }
};

class ApplicationSettings {
private:
    std::string theme;
    int fontSize;
    bool notificationsEnabled;
    
public:
    ApplicationSettings() : theme("light"), fontSize(12), notificationsEnabled(true) {}
    
    void setTheme(const std::string& newTheme) {
        theme = newTheme;
        std::cout << "Theme changed to " << theme << std::endl;
    }
    
    void setFontSize(int size) {
        fontSize = size;
        std::cout << "Font size set to " << fontSize << std::endl;
    }
    
    void setNotificationsEnabled(bool enabled) {
        notificationsEnabled = enabled;
        std::cout << "Notifications " << (enabled ? "enabled" : "disabled") << std::endl;
    }
    
    void displaySettings() const {
        std::cout << "=== Current Settings ===" << std::endl;
        std::cout << "Theme: " << theme << std::endl;
        std::cout << "Font Size: " << fontSize << std::endl;
        std::cout << "Notifications: " << (notificationsEnabled ? "Enabled" : "Disabled") << std::endl;
        std::cout << "=====================" << std::endl;
    }
    
    std::unique_ptr<ConfigurationMemento> saveConfiguration() {
        return std::make_unique<ConfigurationMemento>(theme, fontSize, notificationsEnabled);
    }
    
    void restoreConfiguration(const ConfigurationMemento& memento) {
        theme = memento.getTheme();
        fontSize = memento.getFontSize();
        notificationsEnabled = memento.getNotificationsEnabled();
        std::cout << "Configuration restored!" << std::endl;
        displaySettings();
    }
};

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
