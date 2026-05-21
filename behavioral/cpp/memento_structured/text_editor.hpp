#pragma once
#include <string>
#include <memory>
#include <ctime>

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
        timeStr.pop_back();
        return timeStr;
    }
};

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
