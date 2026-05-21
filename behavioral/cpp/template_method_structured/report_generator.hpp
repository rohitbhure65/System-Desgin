#pragma once
#include <iostream>

class ReportGenerator {
public:
    virtual ~ReportGenerator() = default;
    
    void generateReport() {
        std::cout << "\n=== Generating Report ===" << std::endl;
        collectData();
        analyzeData();
        formatReport();
        exportReport();
        std::cout << "=== Report Generated ===" << std::endl;
    }
    
protected:
    virtual void collectData() = 0;
    virtual void analyzeData() = 0;
    virtual void formatReport() = 0;
    virtual void exportReport() = 0;
};

class SalesReport : public ReportGenerator {
protected:
    void collectData() override {
        std::cout << "Collecting sales data from database..." << std::endl;
    }
    
    void analyzeData() override {
        std::cout << "Analyzing sales trends..." << std::endl;
        std::cout << "Sales increased by 15% this quarter" << std::endl;
    }
    
    void formatReport() override {
        std::cout << "Formatting sales report with charts..." << std::endl;
    }
    
    void exportReport() override {
        std::cout << "Exporting to PDF..." << std::endl;
    }
};

class InventoryReport : public ReportGenerator {
protected:
    void collectData() override {
        std::cout << "Collecting inventory data..." << std::endl;
    }
    
    void analyzeData() override {
        std::cout << "Analyzing stock levels..." << std::endl;
        std::cout << "3 items need restocking" << std::endl;
    }
    
    void formatReport() override {
        std::cout << "Formatting inventory report with tables..." << std::endl;
    }
    
    void exportReport() override {
        std::cout << "Exporting to Excel..." << std::endl;
    }
};
