#include "../include/file_utils.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::string> FileUtils::readFile(const std::string& filePath) {
    std::vector<std::string> lines;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for reading: " << filePath << std::endl;
        return lines;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    return lines;
}

bool FileUtils::writeFile(const std::string& filePath, const std::vector<std::string>& lines) {
    // Create directory if it doesn't exist
    fs::path path(filePath);
    if (!path.parent_path().empty() && !fs::exists(path.parent_path())) {
        try {
            fs::create_directories(path.parent_path());
        } catch (const std::exception& e) {
            std::cerr << "Error creating directory: " << e.what() << std::endl;
            return false;
        }
    }
    
    std::ofstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
        return false;
    }
    
    for (const auto& line : lines) {
        file << line << "\n";
    }
    
    file.close();
    return true;
}

bool FileUtils::appendToFile(const std::string& filePath, const std::string& line) {
    // Create directory if it doesn't exist
    fs::path path(filePath);
    if (!path.parent_path().empty() && !fs::exists(path.parent_path())) {
        try {
            fs::create_directories(path.parent_path());
        } catch (const std::exception& e) {
            std::cerr << "Error creating directory: " << e.what() << std::endl;
            return false;
        }
    }
    
    std::ofstream file(filePath, std::ios::app);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for appending: " << filePath << std::endl;
        return false;
    }
    
    file << line << "\n";
    file.close();
    return true;
}

bool FileUtils::fileExists(const std::string& filePath) {
    return fs::exists(filePath);
}

bool FileUtils::createDirectory(const std::string& dirPath) {
    try {
        fs::create_directories(dirPath);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
        return false;
    }
}
