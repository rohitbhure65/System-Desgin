#pragma once
#include <iostream>
#include <string>
#include <memory>

class Button {
public:
    virtual ~Button() = default;
    virtual void click() = 0;
    virtual void render() = 0;
    virtual std::string getName() const = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void check() = 0;
    virtual void render() = 0;
    virtual std::string getName() const = 0;
};

class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
};

class DatabaseConnection {
public:
    virtual ~DatabaseConnection() = default;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void executeQuery(const std::string& query) = 0;
};

class DatabaseCommand {
public:
    virtual ~DatabaseCommand() = default;
    virtual void execute() = 0;
};

class DatabaseFactory {
public:
    virtual ~DatabaseFactory() = default;
    virtual std::unique_ptr<DatabaseConnection> createConnection() = 0;
    virtual std::unique_ptr<DatabaseCommand> createCommand(const std::string& cmd) = 0;
};
