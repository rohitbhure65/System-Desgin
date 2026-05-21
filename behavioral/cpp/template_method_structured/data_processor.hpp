#pragma once
#include <iostream>
#include <string>

class DataProcessor {
public:
    virtual ~DataProcessor() = default;
    
    void processData() {
        std::cout << "\n=== Starting Data Processing ===" << std::endl;
        readData();
        validateData();
        transformData();
        saveData();
        std::cout << "=== Data Processing Complete ===" << std::endl;
    }
    
protected:
    virtual void readData() = 0;
    virtual void validateData() = 0;
    virtual void transformData() = 0;
    virtual void saveData() = 0;
    
    virtual void logProcessing() {
        std::cout << "Processing logged" << std::endl;
    }
};

class CSVDataProcessor : public DataProcessor {
private:
    std::string data;
    
protected:
    void readData() override {
        std::cout << "Reading CSV file..." << std::endl;
        data = "name,age,city\nJohn,30,NYC\nJane,25,LA";
    }
    
    void validateData() override {
        std::cout << "Validating CSV format..." << std::endl;
        std::cout << "CSV format is valid" << std::endl;
    }
    
    void transformData() override {
        std::cout << "Transforming CSV to JSON..." << std::endl;
        data = "[{\"name\":\"John\",\"age\":30,\"city\":\"NYC\"},{\"name\":\"Jane\",\"age\":25,\"city\":\"LA\"}]";
    }
    
    void saveData() override {
        std::cout << "Saving JSON file..." << std::endl;
        std::cout << "Data saved: " << data << std::endl;
    }
};

class XMLDataProcessor : public DataProcessor {
private:
    std::string data;
    
protected:
    void readData() override {
        std::cout << "Reading XML file..." << std::endl;
        data = "<users><user><name>John</name><age>30</age></user></users>";
    }
    
    void validateData() override {
        std::cout << "Validating XML structure..." << std::endl;
        std::cout << "XML structure is valid" << std::endl;
    }
    
    void transformData() override {
        std::cout << "Transforming XML to CSV..." << std::endl;
        data = "name,age\nJohn,30";
    }
    
    void saveData() override {
        std::cout << "Saving CSV file..." << std::endl;
        std::cout << "Data saved: " << data << std::endl;
    }
};
