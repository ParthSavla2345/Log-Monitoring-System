#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <string>
#include <vector>
#include <map>
#include "log_parser.h"

class Analytics {
public:
    // Constructor that takes parsed logs
    Analytics(const std::vector<LogEntry>& logs);
    
    // Analytics methods
    int getTotalLogs() const;
    int getCountByLevel(const std::string& level) const;
    std::string getTopErrorService() const;
    std::string getMostCommonErrorMessage() const;
    
    // Generate and save analytics report
    void generateReport(const std::string& reportPath);
    
    // Display analytics to console
    void displaySummary() const;
    
private:
    const std::vector<LogEntry>& logs;
    std::map<std::string, int> levelCounts;
    std::map<std::string, int> serviceCounts;
    std::map<std::string, int> errorMessageCounts;
    
    // Helper method to calculate statistics
    void calculateStatistics();
};

#endif // ANALYTICS_H
