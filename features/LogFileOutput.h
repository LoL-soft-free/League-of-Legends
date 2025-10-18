#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/**
 * LogFileOutput - Records all activity for audit, debugging, or analysis
 * 
 * This feature provides comprehensive logging capabilities for tracking
 * all application activities, errors, and user actions.
 */

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
};

struct LogEntry {
    long long timestamp;
    LogLevel level;
    std::string category;
    std::string message;
    std::string source;
};

class LogFileOutput {
private:
    bool enabled;
    std::string logDirectory;
    std::string currentLogFile;
    LogLevel minimumLogLevel;
    bool rotateDaily;
    int maxLogFileSize; // in MB
    std::vector<LogEntry> logBuffer;
    std::ofstream logFileStream;

public:
    LogFileOutput();
    ~LogFileOutput();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Logging methods
    void log(LogLevel level, const std::string& message, const std::string& category = "GENERAL");
    void logDebug(const std::string& message, const std::string& category = "DEBUG");
    void logInfo(const std::string& message, const std::string& category = "INFO");
    void logWarning(const std::string& message, const std::string& category = "WARNING");
    void logError(const std::string& message, const std::string& category = "ERROR");
    void logCritical(const std::string& message, const std::string& category = "CRITICAL");

    // File management
    void createNewLogFile();
    void rotateLogFile();
    void archiveOldLogs();
    void flushLogBuffer();

    // Log viewing and analysis
    void viewLogs();
    void searchLogs(const std::string& searchTerm);
    std::vector<LogEntry> getLogsForCategory(const std::string& category);
    std::vector<LogEntry> getLogsForLevel(LogLevel level);

    // Configuration
    void setLogDirectory(const std::string& directory);
    void setMinimumLogLevel(LogLevel level);
    void setMaxLogFileSize(int sizeMB);
    void enableDailyRotation(bool enable);

    // Utility methods
    std::string logLevelToString(LogLevel level) const;
    LogLevel stringToLogLevel(const std::string& levelStr) const;
    std::string formatTimestamp(long long timestamp) const;

    // Status and debugging
    std::string getStatus() const;
    void printLogStats() const;
    std::string getCurrentLogFile() const;
};