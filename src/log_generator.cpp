#include "../include/log_generator.h"
#include "../include/file_utils.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <random>
#include <iostream>

void LogGenerator::generateSampleLogs(const std::string& filePath, int count) {
    std::vector<std::string> logs;
    
    // Generate 'count' random log entries
    for (int i = 0; i < count; ++i) {
        std::string logLine = "[" + getCurrentTimestamp() + "] [" + getRandomService() + 
                             "] [" + getRandomLogLevel() + "] " + getRandomMessage();
        logs.push_back(logLine);
    }
    
    // Write logs to file
    if (FileUtils::writeFile(filePath, logs)) {
        std::cout << "Generated " << count << " sample logs in " << filePath << std::endl;
    } else {
        std::cerr << "Error writing logs to file: " << filePath << std::endl;
    }
}

std::string LogGenerator::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string LogGenerator::getRandomService() {
    static const std::vector<std::string> services = {
        "PaymentService", "AuthService", "DatabaseService", 
        "CacheService", "NotificationService", "LoggingService"
    };
    
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, services.size() - 1);
    return services[dis(gen)];
}

std::string LogGenerator::getRandomLogLevel() {
    static const std::vector<std::string> levels = {"INFO", "WARN", "ERROR", "CRITICAL"};
    
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, levels.size() - 1);
    return levels[dis(gen)];
}

std::string LogGenerator::getRandomMessage() {
    static const std::vector<std::string> messages = {
        "Request processed successfully",
        "High memory usage detected",
        "Database connection timeout",
        "Invalid user credentials",
        "API rate limit exceeded",
        "File not found",
        "Service unavailable",
        "Permission denied",
        "Unexpected error occurred",
        "Connection reset by peer"
    };
    
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, messages.size() - 1);
    return messages[dis(gen)];
}
