#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

class FileUtils {
public:
    // Read all lines from a file
    static std::vector<std::string> readFile(const std::string& filePath);
    
    // Write lines to a file (overwrites existing)
    static bool writeFile(const std::string& filePath, const std::vector<std::string>& lines);
    
    // Append a line to a file
    static bool appendToFile(const std::string& filePath, const std::string& line);
    
    // Check if file exists
    static bool fileExists(const std::string& filePath);
    
    // Create directories if they don't exist
    static bool createDirectory(const std::string& dirPath);
};

#endif // FILE_UTILS_H
