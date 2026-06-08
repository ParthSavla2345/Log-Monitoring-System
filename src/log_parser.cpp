#include "../include/log_parser.h"
#include "../include/file_utils.h"
#include <iostream>
#include <regex>
#include <algorithm>

void LogParser::readLogs(const std::string& filePath) {
    std::vector<std::string> lines = FileUtils::readFile(filePath);
    logs.clear();
    
    for (const auto& line : lines) {
        if (!line.empty()) {
            logs.push_back(parseLine(line));
        }
    }
    
    std::cout << "Loaded " << logs.size() << " log entries." << std::endl;
}

const std::vector<LogEntry>& LogParser::getLogs() const {
    return logs;
}

std::vector<LogEntry> LogParser::filterByLevel(const std::string& level) const {
    std::vector<LogEntry> filtered;
    
    for (const auto& log : logs) {
        if (log.level == level) {
            filtered.push_back(log);
        }
    }
    
    return filtered;
}

std::vector<LogEntry> LogParser::searchByKeyword(const std::string& keyword) const {
    std::vector<LogEntry> results;
    
    for (const auto& log : logs) {
        // Search in message and service name
        if (log.message.find(keyword) != std::string::npos ||
            log.service.find(keyword) != std::string::npos) {
            results.push_back(log);
        }
    }
    
    return results;
}

LogEntry LogParser::parseLine(const std::string& line) {
    LogEntry entry;
    
    // Parse format: [TIMESTAMP] [SERVICE] [LEVEL] MESSAGE
    // Example: [2026-06-08 18:30:20] [PaymentService] [ERROR] Payment gateway timeout
    
    size_t pos = 0;
    
    // Extract timestamp
    size_t start = line.find('[') + 1;
    size_t end = line.find(']', start);
    entry.timestamp = line.substr(start, end - start);
    
    // Extract service
    start = line.find('[', end) + 1;
    end = line.find(']', start);
    entry.service = line.substr(start, end - start);
    
    // Extract level
    start = line.find('[', end) + 1;
    end = line.find(']', start);
    entry.level = line.substr(start, end - start);
    
    // Extract message
    start = end + 2; // Skip "] "
    entry.message = line.substr(start);
    
    return entry;
}
