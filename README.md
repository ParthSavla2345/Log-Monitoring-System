# C++ Log Monitoring System

A professional, console-based log monitoring system built with modern C++17. This project demonstrates clean architecture, modular design, and file handling best practices.

## Project Structure

```
cpp-log-monitoring-system/
├── src/
│   ├── main.cpp              # CLI menu and main application logic
│   ├── log_generator.cpp     # Generate sample logs
│   ├── log_parser.cpp        # Parse and filter logs
│   ├── analytics.cpp         # Analytics and reporting
│   └── file_utils.cpp        # File I/O utilities
│
├── include/
│   ├── log_generator.h
│   ├── log_parser.h
│   ├── analytics.h
│   └── file_utils.h
│
├── logs/                     # Directory for log files
├── reports/                  # Directory for generated reports
├── CMakeLists.txt            # CMake build configuration
└── README.md                 # This file
```

## Features

### 1. Log Generation
- Generates sample logs with realistic data
- Includes timestamps, service names, log levels, and messages
- Configurable log count

### 2. Log Parsing
- Parses logs from file in standard format
- Supports INFO, WARN, ERROR, and CRITICAL levels
- Extracts timestamp, service, level, and message components

### 3. Filtering & Search
- Filter logs by severity level
- Keyword-based search across service names and messages
- Efficient vector-based operations

### 4. Analytics & Reporting
- Count total logs by level
- Identify top error-producing services
- Track most common error messages
- Generate formatted reports saved to file

### 5. File Management
- Safe file I/O with error handling
- Automatic directory creation
- Append and overwrite operations

## Log Format

```
[TIMESTAMP] [SERVICE] [LEVEL] MESSAGE

Example:
[2026-06-08 18:30:20] [PaymentService] [ERROR] Payment gateway timeout
[2026-06-08 18:35:45] [AuthService] [INFO] User login successful
```

## Build Instructions

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler (GCC, Clang, MSVC)
- On Linux/macOS: g++ or clang++
- On Windows: Visual Studio with CMake support or MinGW

### Building on Linux/macOS

```bash
# Navigate to project directory
cd cpp-log-monitoring-system

# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
make

# Run the application
./bin/log-monitor
```

### Building on Windows (Command Prompt)

```bash
# Navigate to project directory
cd cpp-log-monitoring-system

# Create build directory
mkdir build
cd build

# Generate build files for Visual Studio
cmake -G "Visual Studio 17 2022" ..

# Build the project
cmake --build . --config Release

# Run the application
.\bin\Release\log-monitor.exe
```

### Building in VS Code (All Platforms)

1. Install the "CMake Tools" extension in VS Code
2. Open the project folder in VS Code
3. Select a kit (compiler) when prompted
4. Click "Build" in the CMake toolbar
5. Press Ctrl+Shift+` to open terminal and run: `./build/bin/log-monitor`

## Usage

After building and running the application:

```
=== C++ LOG MONITORING SYSTEM ===
Initializing system...

----------------------------------------
LOG MONITORING SYSTEM MENU
----------------------------------------
1. Generate sample logs
2. View all logs
3. Filter logs by level
4. Search logs by keyword
5. Generate analytics report
6. Exit
----------------------------------------

Enter your choice (1-6):
```

### Menu Options

1. **Generate Sample Logs**: Create new log entries with random data
2. **View All Logs**: Display all logs in a formatted table
3. **Filter by Level**: Show only logs of a specific severity level
4. **Search by Keyword**: Find logs matching a keyword
5. **Generate Report**: Create analytics summary and save to file
6. **Exit**: Quit the application

## Output Directories

- **logs/system.log** - Stores all generated and parsed logs
- **reports/summary.txt** - Contains generated analytics reports

## Code Architecture

### Classes

#### LogGenerator
- Generates realistic sample log entries
- Uses random service names, levels, and messages
- Includes timestamp generation

#### LogParser
- Reads and parses log files
- Provides filtering and search capabilities
- Maintains vector of LogEntry structures

#### Analytics
- Calculates statistics from parsed logs
- Generates formatted reports
- Displays summary to console and file

#### FileUtils (Static Utilities)
- Safe file reading and writing
- Directory creation with error handling
- File existence checking

## Design Principles

- **Modular Design**: Each component has a single responsibility
- **C++17 Features**: Modern STL containers (vector, map, string)
- **Error Handling**: Graceful error messages and validation
- **Extensibility**: Easy to add new features and integrations

## Future Enhancements

- Kafka integration for streaming logs
- Docker containerization
- AWS deployment support
- Database backend (PostgreSQL, MongoDB)
- Real-time log monitoring with websockets
- Advanced filtering with regex patterns
- Log rotation and archiving
- Performance metrics and benchmarking

## Compilation Notes

- Uses `<filesystem>` library (C++17 feature)
- Requires compiler with C++17 support
- All dependencies are from C++ standard library
- No external library dependencies required

## Testing

To test the application:

1. Generate 20 sample logs
2. View all logs to verify format
3. Filter by ERROR level
4. Search for "timeout"
5. Generate analytics report
6. Check `reports/summary.txt` for output

## Author

C++ Log Monitoring System - Educational Project

## License

Open source project for learning and development purposes.
