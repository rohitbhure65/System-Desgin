#pragma once
#include "interfaces.hpp"
#include "concrete_products.hpp"

class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override { return std::make_unique<WindowsButton>(); }
    std::unique_ptr<Checkbox> createCheckbox() override { return std::make_unique<WindowsCheckbox>(); }
};

class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override { return std::make_unique<MacButton>(); }
    std::unique_ptr<Checkbox> createCheckbox() override { return std::make_unique<MacCheckbox>(); }
};

class MySQLFactory : public DatabaseFactory {
public:
    std::unique_ptr<DatabaseConnection> createConnection() override { return std::make_unique<MySQLConnection>(); }
    std::unique_ptr<DatabaseCommand> createCommand(const std::string& cmd) override { return std::make_unique<MySQLCommand>(cmd); }
};

class PostgreSQLFactory : public DatabaseFactory {
public:
    std::unique_ptr<DatabaseConnection> createConnection() override { return std::make_unique<PostgreSQLConnection>(); }
    std::unique_ptr<DatabaseCommand> createCommand(const std::string& cmd) override { return std::make_unique<PostgreSQLCommand>(cmd); }
};
