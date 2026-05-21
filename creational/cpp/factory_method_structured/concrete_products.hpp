#pragma once
#include "interfaces.hpp"

class TextDocument : public Document {
public:
    void open() override { std::cout << "Opening Text Document in text editor..." << std::endl; }
    void close() override { std::cout << "Closing Text Document..." << std::endl; }
    void save() override { std::cout << "Saving Text Document as .txt file..." << std::endl; }
    std::string getType() const override { return "Text Document"; }
};

class PDFDocument : public Document {
public:
    void open() override { std::cout << "Opening PDF Document in PDF viewer..." << std::endl; }
    void close() override { std::cout << "Closing PDF Document..." << std::endl; }
    void save() override { std::cout << "Saving PDF Document as .pdf file..." << std::endl; }
    std::string getType() const override { return "PDF Document"; }
};

class HTMLDocument : public Document {
public:
    void open() override { std::cout << "Opening HTML Document in web browser..." << std::endl; }
    void close() override { std::cout << "Closing HTML Document..." << std::endl; }
    void save() override { std::cout << "Saving HTML Document as .html file..." << std::endl; }
    std::string getType() const override { return "HTML Document"; }
};
