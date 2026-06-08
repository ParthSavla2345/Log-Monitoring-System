cmake_minimum_required(VERSION 3.10)
project(cpp-log-monitoring-system)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/log_generator.cpp
    src/log_parser.cpp
    src/analytics.cpp
    src/file_utils.cpp
)

# Create executable
add_executable(log-monitor ${SOURCES})

# Set output directory for the executable
set_target_properties(log-monitor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Enable C++17 features for the target
target_compile_features(log-monitor PRIVATE cxx_std_17)

# Optional: Add compiler flags for warnings
if(MSVC)
    target_compile_options(log-monitor PRIVATE /W4)
else()
    target_compile_options(log-monitor PRIVATE -Wall -Wextra -Wpedantic)
endif()
