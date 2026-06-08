#ifndef LOG_PARSER_H
#define LOG_PARSER_H

#include <string>
#include <vector>

// Struct to represent a parsed log entry
struct LogEntry {
    std::string timestamp;
    std::string service;
    std::string level;      // INFO, WARN, ERROR, CRITICAL
    std::string message;
};

class LogParser {
public:
    // Read and parse logs from file
    void readLogs(const std::string& filePath);
    
    // Get all parsed logs
    const std::vector<LogEntry>& getLogs() const;
    
    // Filter logs by level
    std::vector<LogEntry> filterByLevel(const std::string& level) const;
    
    // Search logs by keyword
    std::vector<LogEntry> searchByKeyword(const std::string& keyword) const;
    
private:
    std::vector<LogEntry> logs;
    
    // Helper method to parse a single log line
    LogEntry parseLine(const std::string& line);
};

#endif // LOG_PARSER_H
