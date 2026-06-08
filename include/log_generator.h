#ifndef LOG_GENERATOR_H
#define LOG_GENERATOR_H

#include <string>
#include <vector>

class LogGenerator {
public:
    // Generate sample logs and write to file
    void generateSampleLogs(const std::string& filePath, int count = 20);
    
private:
    // Helper methods
    std::string getCurrentTimestamp();
    std::string getRandomService();
    std::string getRandomLogLevel();
    std::string getRandomMessage();
};

#endif // LOG_GENERATOR_H
