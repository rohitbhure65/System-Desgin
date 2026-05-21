#pragma once
#include "interfaces.hpp"

class WindowsButton : public Button {
public:
    void click() override { std::cout << "Windows button clicked!" << std::endl; }
    void render() override { std::cout << "Rendering Windows-style button..." << std::endl; }
    std::string getName() const override { return "Windows Button"; }
};

class WindowsCheckbox : public Checkbox {
public:
    void check() override { std::cout << "Windows checkbox checked!" << std::endl; }
    void render() override { std::cout << "Rendering Windows-style checkbox..." << std::endl; }
    std::string getName() const override { return "Windows Checkbox"; }
};

class MacButton : public Button {
public:
    void click() override { std::cout << "Mac button clicked!" << std::endl; }
    void render() override { std::cout << "Rendering Mac-style button..." << std::endl; }
    std::string getName() const override { return "Mac Button"; }
};

class MacCheckbox : public Checkbox {
public:
    void check() override { std::cout << "Mac checkbox checked!" << std::endl; }
    void render() override { std::cout << "Rendering Mac-style checkbox..." << std::endl; }
    std::string getName() const override { return "Mac Checkbox"; }
};

class MySQLConnection : public DatabaseConnection {
public:
    void connect() override { std::cout << "Connecting to MySQL database..." << std::endl; }
    void disconnect() override { std::cout << "Disconnecting from MySQL database..." << std::endl; }
    void executeQuery(const std::string& query) override { std::cout << "Executing MySQL query: " << query << std::endl; }
};

class MySQLCommand : public DatabaseCommand {
private:
    std::string command;
public:
    MySQLCommand(const std::string& cmd) : command(cmd) {}
    void execute() override { std::cout << "Executing MySQL command: " << command << std::endl; }
};

class PostgreSQLConnection : public DatabaseConnection {
public:
    void connect() override { std::cout << "Connecting to PostgreSQL database..." << std::endl; }
    void disconnect() override { std::cout << "Disconnecting from PostgreSQL database..." << std::endl; }
    void executeQuery(const std::string& query) override { std::cout << "Executing PostgreSQL query: " << query << std::endl; }
};

class PostgreSQLCommand : public DatabaseCommand {
private:
    std::string command;
public:
    PostgreSQLCommand(const std::string& cmd) : command(cmd) {}
    void execute() override { std::cout << "Executing PostgreSQL command: " << command << std::endl; }
};
