#include "interfaces.hpp"
#include "concrete_products.hpp"
#include "creators.hpp"

int main() {
    std::cout << "=== Factory Method Pattern Demo ===" << std::endl << std::endl;
    
    std::cout << "--- Inheritance-based Factory Method ---" << std::endl;
    
    std::unique_ptr<Application> textEditor = std::make_unique<TextEditor>();
    textEditor->newDocument();
    std::cout << std::endl;
    
    std::unique_ptr<Application> pdfViewer = std::make_unique<PDFViewer>();
    pdfViewer->newDocument();
    std::cout << std::endl;
    
    std::unique_ptr<Application> webBrowser = std::make_unique<WebBrowser>();
    webBrowser->newDocument();
    std::cout << std::endl;
    
    std::cout << "--- Parameterized Factory Method ---" << std::endl;
    
    auto textDoc = DocumentFactory::createDocument(DocumentFactory::DocumentType::TEXT);
    textDoc->open();
    std::cout << std::endl;
    
    auto pdfDoc = DocumentFactory::createDocument(DocumentFactory::DocumentType::PDF);
    pdfDoc->open();
    std::cout << std::endl;
    
    auto htmlDoc = DocumentFactory::createDocument(DocumentFactory::DocumentType::HTML);
    htmlDoc->open();
    
    return 0;
}
