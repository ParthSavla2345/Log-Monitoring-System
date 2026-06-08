#include "../include/analytics.h"
#include "../include/file_utils.h"
#include <iostream>
#include <iomanip>

Analytics::Analytics(const std::vector<LogEntry>& logs) : logs(logs) {
    calculateStatistics();
}

void Analytics::calculateStatistics() {
    levelCounts.clear();
    serviceCounts.clear();
    errorMessageCounts.clear();
    
    for (const auto& log : logs) {
        // Count by level
        levelCounts[log.level]++;
        
        // Count services that produce errors
        if (log.level == "ERROR" || log.level == "CRITICAL") {
            serviceCounts[log.service]++;
            errorMessageCounts[log.message]++;
        }
    }
}

int Analytics::getTotalLogs() const {
    return logs.size();
}

int Analytics::getCountByLevel(const std::string& level) const {
    auto it = levelCounts.find(level);
    return (it != levelCounts.end()) ? it->second : 0;
}

std::string Analytics::getTopErrorService() const {
    std::string topService = "None";
    int maxCount = 0;
    
    for (const auto& pair : serviceCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            topService = pair.first;
        }
    }
    
    return topService;
}

std::string Analytics::getMostCommonErrorMessage() const {
    std::string commonMessage = "None";
    int maxCount = 0;
    
    for (const auto& pair : errorMessageCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            commonMessage = pair.first;
        }
    }
    
    return commonMessage;
}

void Analytics::displaySummary() const {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "LOG ANALYTICS SUMMARY" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    std::cout << "\nTotal Logs: " << getTotalLogs() << std::endl;
    std::cout << "\nLog Level Distribution:" << std::endl;
    std::cout << "  INFO:     " << getCountByLevel("INFO") << std::endl;
    std::cout << "  WARN:     " << getCountByLevel("WARN") << std::endl;
    std::cout << "  ERROR:    " << getCountByLevel("ERROR") << std::endl;
    std::cout << "  CRITICAL: " << getCountByLevel("CRITICAL") << std::endl;
    
    std::cout << "\nTop Error-Producing Service: " << getTopErrorService() << std::endl;
    std::cout << "Most Common Error Message: " << getMostCommonErrorMessage() << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;
}

void Analytics::generateReport(const std::string& reportPath) {
    std::vector<std::string> report;
    
    report.push_back(std::string(50, '='));
    report.push_back("LOG ANALYTICS REPORT");
    report.push_back(std::string(50, '='));
    report.push_back("");
    
    report.push_back("Total Logs: " + std::to_string(getTotalLogs()));
    report.push_back("");
    
    report.push_back("Log Level Distribution:");
    report.push_back("  INFO:     " + std::to_string(getCountByLevel("INFO")));
    report.push_back("  WARN:     " + std::to_string(getCountByLevel("WARN")));
    report.push_back("  ERROR:    " + std::to_string(getCountByLevel("ERROR")));
    report.push_back("  CRITICAL: " + std::to_string(getCountByLevel("CRITICAL")));
    report.push_back("");
    
    report.push_back("Top Error-Producing Service: " + getTopErrorService());
    report.push_back("Most Common Error Message: " + getMostCommonErrorMessage());
    report.push_back("");
    
    report.push_back(std::string(50, '='));
    
    if (FileUtils::writeFile(reportPath, report)) {
        std::cout << "Report generated successfully at: " << reportPath << std::endl;
    } else {
        std::cerr << "Error generating report at: " << reportPath << std::endl;
    }
}
