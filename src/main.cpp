#include <iostream>
#include <string>
#include <iomanip>
#include "../include/log_generator.h"
#include "../include/log_parser.h"
#include "../include/analytics.h"
#include "../include/file_utils.h"

// Constants
const std::string LOGS_DIR = "logs";
const std::string LOGS_FILE = "logs/system.log";
const std::string REPORTS_DIR = "reports";
const std::string REPORT_FILE = "reports/summary.txt";

// Function declarations
void displayMenu();
void handleGenerateLogs();
void handleViewAllLogs(LogParser& parser);
void handleFilterByLevel(LogParser& parser);
void handleSearchByKeyword(LogParser& parser);
void handleGenerateReport(LogParser& parser);
void displayLogEntry(const LogEntry& entry);

int main() {
    std::cout << "=== C++ LOG MONITORING SYSTEM ===" << std::endl;
    std::cout << "Initializing system..." << std::endl;
    
    // Ensure directories exist
    FileUtils::createDirectory(LOGS_DIR);
    FileUtils::createDirectory(REPORTS_DIR);
    
    LogParser parser;
    int choice = 0;
    
    // Load existing logs if they exist
    if (FileUtils::fileExists(LOGS_FILE)) {
        parser.readLogs(LOGS_FILE);
    } else {
        std::cout << "No existing logs found. Create some logs to get started." << std::endl;
    }
    
    while (true) {
        displayMenu();
        std::cout << "\nEnter your choice (1-6): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear the newline from input buffer
        
        switch (choice) {
            case 1:
                handleGenerateLogs();
                // Reload logs after generation
                parser.readLogs(LOGS_FILE);
                break;
            
            case 2:
                handleViewAllLogs(parser);
                break;
            
            case 3:
                handleFilterByLevel(parser);
                break;
            
            case 4:
                handleSearchByKeyword(parser);
                break;
            
            case 5:
                handleGenerateReport(parser);
                break;
            
            case 6:
                std::cout << "Exiting... Goodbye!" << std::endl;
                return 0;
            
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    
    return 0;
}

void displayMenu() {
    std::cout << "\n" << std::string(40, '-') << std::endl;
    std::cout << "LOG MONITORING SYSTEM MENU" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    std::cout << "1. Generate sample logs" << std::endl;
    std::cout << "2. View all logs" << std::endl;
    std::cout << "3. Filter logs by level" << std::endl;
    std::cout << "4. Search logs by keyword" << std::endl;
    std::cout << "5. Generate analytics report" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
}

void handleGenerateLogs() {
    std::cout << "\nHow many logs do you want to generate? (default 20): ";
    std::string input;
    std::getline(std::cin, input);
    
    int count = 20;
    if (!input.empty()) {
        try {
            count = std::stoi(input);
        } catch (...) {
            std::cout << "Invalid input. Using default 20 logs." << std::endl;
        }
    }
    
    LogGenerator generator;
    generator.generateSampleLogs(LOGS_FILE, count);
}

void handleViewAllLogs(LogParser& parser) {
    const auto& logs = parser.getLogs();
    
    if (logs.empty()) {
        std::cout << "\nNo logs found. Generate some logs first." << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "ALL LOGS" << std::endl;
    std::cout << std::string(100, '=') << std::endl;
    std::cout << std::left 
              << std::setw(20) << "TIMESTAMP"
              << std::setw(20) << "SERVICE"
              << std::setw(12) << "LEVEL"
              << "MESSAGE" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    
    for (const auto& log : logs) {
        displayLogEntry(log);
    }
    
    std::cout << std::string(100, '=') << std::endl;
    std::cout << "Total: " << logs.size() << " logs" << std::endl;
}

void handleFilterByLevel(LogParser& parser) {
    std::cout << "\nFilter by log level:" << std::endl;
    std::cout << "1. INFO" << std::endl;
    std::cout << "2. WARN" << std::endl;
    std::cout << "3. ERROR" << std::endl;
    std::cout << "4. CRITICAL" << std::endl;
    std::cout << "Enter choice (1-4): ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    
    std::string level;
    switch (choice) {
        case 1: level = "INFO"; break;
        case 2: level = "WARN"; break;
        case 3: level = "ERROR"; break;
        case 4: level = "CRITICAL"; break;
        default:
            std::cout << "Invalid choice." << std::endl;
            return;
    }
    
    auto filtered = parser.filterByLevel(level);
    
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "LOGS FILTERED BY LEVEL: " << level << std::endl;
    std::cout << std::string(100, '=') << std::endl;
    std::cout << std::left 
              << std::setw(20) << "TIMESTAMP"
              << std::setw(20) << "SERVICE"
              << std::setw(12) << "LEVEL"
              << "MESSAGE" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    
    for (const auto& log : filtered) {
        displayLogEntry(log);
    }
    
    std::cout << std::string(100, '=') << std::endl;
    std::cout << "Found: " << filtered.size() << " logs" << std::endl;
}

void handleSearchByKeyword(LogParser& parser) {
    std::cout << "\nEnter keyword to search: ";
    std::string keyword;
    std::getline(std::cin, keyword);
    
    if (keyword.empty()) {
        std::cout << "Keyword cannot be empty." << std::endl;
        return;
    }
    
    auto results = parser.searchByKeyword(keyword);
    
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << "SEARCH RESULTS FOR: \"" << keyword << "\"" << std::endl;
    std::cout << std::string(100, '=') << std::endl;
    std::cout << std::left 
              << std::setw(20) << "TIMESTAMP"
              << std::setw(20) << "SERVICE"
              << std::setw(12) << "LEVEL"
              << "MESSAGE" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    
    for (const auto& log : results) {
        displayLogEntry(log);
    }
    
    std::cout << std::string(100, '=') << std::endl;
    std::cout << "Found: " << results.size() << " logs" << std::endl;
}

void handleGenerateReport(LogParser& parser) {
    const auto& logs = parser.getLogs();
    
    if (logs.empty()) {
        std::cout << "\nNo logs available to generate report." << std::endl;
        return;
    }
    
    Analytics analytics(logs);
    analytics.displaySummary();
    analytics.generateReport(REPORT_FILE);
}

void displayLogEntry(const LogEntry& entry) {
    std::cout << std::left 
              << std::setw(20) << entry.timestamp
              << std::setw(20) << entry.service
              << std::setw(12) << entry.level
              << entry.message << std::endl;
}
