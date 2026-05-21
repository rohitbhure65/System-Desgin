#pragma once
#include <string>
#include <vector>
#include <memory>

class File;
class Directory;

class FileSystemVisitor {
public:
    virtual ~FileSystemVisitor() = default;
    virtual void visit(File* file) = 0;
    virtual void visit(Directory* directory) = 0;
};

class FileSystemNode {
public:
    virtual ~FileSystemNode() = default;
    virtual void accept(FileSystemVisitor* visitor) = 0;
    virtual std::string getName() const = 0;
    virtual int getSize() const = 0;
};

class File : public FileSystemNode {
private:
    std::string name;
    int size;
    
public:
    File(const std::string& name, int size) : name(name), size(size) {}
    
    void accept(FileSystemVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name; }
    int getSize() const override { return size; }
};

class Directory : public FileSystemNode {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemNode>> children;
    
public:
    Directory(const std::string& name) : name(name) {}
    
    void addChild(std::shared_ptr<FileSystemNode> child) {
        children.push_back(child);
    }
    
    void accept(FileSystemVisitor* visitor) override {
        visitor->visit(this);
    }
    
    std::string getName() const override { return name; }
    int getSize() const override {
        int total = 0;
        for (const auto& child : children) {
            total += child->getSize();
        }
        return total;
    }
};

class SizeCalculator : public FileSystemVisitor {
private:
    int totalSize;
    
public:
    SizeCalculator() : totalSize(0) {}
    
    void visit(File* file) override {
        totalSize += file->getSize();
        std::cout << "File: " << file->getName() << " - " << file->getSize() << " bytes" << std::endl;
    }
    
    void visit(Directory* directory) override {
        std::cout << "Directory: " << directory->getName() << " - " << directory->getSize() << " bytes" << std::endl;
        totalSize += directory->getSize();
    }
    
    int getTotalSize() const {
        return totalSize;
    }
};

class XMLExporter : public FileSystemVisitor {
public:
    void visit(File* file) override {
        std::cout << "  <file name=\"" << file->getName() << "\" size=\"" << file->getSize() << "\"/>" << std::endl;
    }
    
    void visit(Directory* directory) override {
        std::cout << "  <directory name=\"" << directory->getName() << "\" size=\"" << directory->getSize() << "\">" << std::endl;
    }
};
