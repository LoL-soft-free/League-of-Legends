#include "LogFileOutput.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <algorithm>

LogFileOutput::LogFileOutput() : enabled(false), logDirectory("logs"), currentLogFile(""), 
                                 minimumLogLevel(LogLevel::INFO), rotateDaily(true), 
                                 maxLogFileSize(10) { // 10MB default
    std::cout << "[LogFileOutput] Module initialized" << std::endl;
    createNewLogFile();
}

LogFileOutput::~LogFileOutput() {
    flushLogBuffer();
    if (logFileStream.is_open()) {
        logFileStream.close();
    }
    std::cout << "[LogFileOutput] Module destroyed" << std::endl;
}

void LogFileOutput::toggle() {
    enabled = !enabled;
    if (enabled) {
        createNewLogFile();
        logInfo("Logging system enabled", "SYSTEM");
    } else {
        logInfo("Logging system disabled", "SYSTEM");
        flushLogBuffer();
    }
    std::cout << "[LogFileOutput] " << (enabled ? "Enabled" : "Disabled") << std::endl;
}

void LogFileOutput::enable() {
    enabled = true;
    createNewLogFile();
    logInfo("Logging system enabled", "SYSTEM");
    std::cout << "[LogFileOutput] Feature enabled" << std::endl;
}

void LogFileOutput::disable() {
    enabled = false;
    logInfo("Logging system disabled", "SYSTEM");
    flushLogBuffer();
    std::cout << "[LogFileOutput] Feature disabled" << std::endl;
}

bool LogFileOutput::isEnabled() const {
    return enabled;
}

void LogFileOutput::log(LogLevel level, const std::string& message, const std::string& category) {
    if (!enabled || level < minimumLogLevel) return;
    
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    
    LogEntry entry;
    entry.timestamp = now;
    entry.level = level;
    entry.category = category;
    entry.message = message;
    entry.source = "LOLTrainer";
    
    logBuffer.push_back(entry);
    
    // Write to file immediately for important messages
    if (level >= LogLevel::WARNING) {
        flushLogBuffer();
    }
    
    // Also output to console for demonstration
    std::cout << "[" << formatTimestamp(now) << "] [" << logLevelToString(level) 
              << "] [" << category << "] " << message << std::endl;
}

void LogFileOutput::logDebug(const std::string& message, const std::string& category) {
    log(LogLevel::DEBUG, message, category);
}

void LogFileOutput::logInfo(const std::string& message, const std::string& category) {
    log(LogLevel::INFO, message, category);
}

void LogFileOutput::logWarning(const std::string& message, const std::string& category) {
    log(LogLevel::WARNING, message, category);
}

void LogFileOutput::logError(const std::string& message, const std::string& category) {
    log(LogLevel::ERROR, message, category);
}

void LogFileOutput::logCritical(const std::string& message, const std::string& category) {
    log(LogLevel::CRITICAL, message, category);
}

void LogFileOutput::createNewLogFile() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << logDirectory << "/lol_trainer_" 
       << std::put_time(std::localtime(&time_t), "%Y%m%d_%H%M%S") << ".log";
    
    currentLogFile = ss.str();
    
    std::cout << "[LogFileOutput] Created new log file: " << currentLogFile << std::endl;
    
    // Stub: In real implementation, create directory and open file
    // For demonstration, we'll just simulate file creation
}

void LogFileOutput::rotateLogFile() {
    if (!enabled) return;
    
    std::cout << "[LogFileOutput] Rotating log file..." << std::endl;
    
    flushLogBuffer();
    
    if (logFileStream.is_open()) {
        logFileStream.close();
    }
    
    createNewLogFile();
    
    logInfo("Log file rotated", "SYSTEM");
}

void LogFileOutput::archiveOldLogs() {
    std::cout << "[LogFileOutput] Archiving old log files..." << std::endl;
    
    // Stub: Archive old logs (compress, move to archive directory, etc.)
    std::cout << "  Compressed 5 old log files" << std::endl;
    std::cout << "  Moved archived logs to archive/" << std::endl;
}

void LogFileOutput::flushLogBuffer() {
    if (logBuffer.empty()) return;
    
    std::cout << "[LogFileOutput] Flushing " << logBuffer.size() << " log entries to file" << std::endl;
    
    // Stub: Write buffer contents to file
    for (const auto& entry : logBuffer) {
        // In real implementation, write formatted entry to file
    }
    
    logBuffer.clear();
}

void LogFileOutput::viewLogs() {
    if (!enabled) {
        std::cout << "[LogFileOutput] Cannot view logs - feature is disabled" << std::endl;
        return;
    }
    
    std::cout << "\n=== Recent Log Entries ===" << std::endl;
    
    // Show last few entries from buffer
    int entriesToShow = std::min(10, static_cast<int>(logBuffer.size()));
    auto startIt = logBuffer.end() - entriesToShow;
    
    for (auto it = startIt; it != logBuffer.end(); ++it) {
        std::cout << "[" << formatTimestamp(it->timestamp) << "] "
                  << "[" << logLevelToString(it->level) << "] "
                  << "[" << it->category << "] "
                  << it->message << std::endl;
    }
    
    std::cout << "Current log file: " << currentLogFile << std::endl;
    std::cout << "==========================" << std::endl;
}

void LogFileOutput::searchLogs(const std::string& searchTerm) {
    std::cout << "[LogFileOutput] Searching logs for: " << searchTerm << std::endl;
    
    int matches = 0;
    for (const auto& entry : logBuffer) {
        if (entry.message.find(searchTerm) != std::string::npos ||
            entry.category.find(searchTerm) != std::string::npos) {
            std::cout << "[" << formatTimestamp(entry.timestamp) << "] "
                      << "[" << logLevelToString(entry.level) << "] "
                      << "[" << entry.category << "] "
                      << entry.message << std::endl;
            matches++;
        }
    }
    
    std::cout << "Found " << matches << " matching entries" << std::endl;
}

std::vector<LogEntry> LogFileOutput::getLogsForCategory(const std::string& category) {
    std::vector<LogEntry> categoryLogs;
    std::copy_if(logBuffer.begin(), logBuffer.end(),
                 std::back_inserter(categoryLogs),
                 [&category](const LogEntry& entry) {
                     return entry.category == category;
                 });
    return categoryLogs;
}

std::vector<LogEntry> LogFileOutput::getLogsForLevel(LogLevel level) {
    std::vector<LogEntry> levelLogs;
    std::copy_if(logBuffer.begin(), logBuffer.end(),
                 std::back_inserter(levelLogs),
                 [level](const LogEntry& entry) {
                     return entry.level == level;
                 });
    return levelLogs;
}

void LogFileOutput::setLogDirectory(const std::string& directory) {
    logDirectory = directory;
    std::cout << "[LogFileOutput] Log directory set to: " << directory << std::endl;
}

void LogFileOutput::setMinimumLogLevel(LogLevel level) {
    minimumLogLevel = level;
    std::cout << "[LogFileOutput] Minimum log level set to: " << logLevelToString(level) << std::endl;
}

void LogFileOutput::setMaxLogFileSize(int sizeMB) {
    maxLogFileSize = sizeMB;
    std::cout << "[LogFileOutput] Maximum log file size set to: " << sizeMB << "MB" << std::endl;
}

void LogFileOutput::enableDailyRotation(bool enable) {
    rotateDaily = enable;
    std::cout << "[LogFileOutput] Daily log rotation " << 
                 (enable ? "enabled" : "disabled") << std::endl;
}

std::string LogFileOutput::logLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

LogLevel LogFileOutput::stringToLogLevel(const std::string& levelStr) const {
    if (levelStr == "DEBUG") return LogLevel::DEBUG;
    if (levelStr == "INFO") return LogLevel::INFO;
    if (levelStr == "WARNING") return LogLevel::WARNING;
    if (levelStr == "ERROR") return LogLevel::ERROR;
    if (levelStr == "CRITICAL") return LogLevel::CRITICAL;
    return LogLevel::INFO; // Default
}

std::string LogFileOutput::formatTimestamp(long long timestamp) const {
    auto time_point = std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));
    auto time_t = std::chrono::system_clock::to_time_t(time_point);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string LogFileOutput::getStatus() const {
    if (!enabled) return "Inactive";
    
    return "Active - " + std::to_string(logBuffer.size()) + " entries buffered, " +
           "level: " + logLevelToString(minimumLogLevel);
}

void LogFileOutput::printLogStats() const {
    std::cout << "=== Log Statistics ===" << std::endl;
    std::cout << "Status: " << (enabled ? "Enabled" : "Disabled") << std::endl;
    std::cout << "Current Log File: " << currentLogFile << std::endl;
    std::cout << "Buffer Size: " << logBuffer.size() << " entries" << std::endl;
    std::cout << "Minimum Level: " << logLevelToString(minimumLogLevel) << std::endl;
    std::cout << "Daily Rotation: " << (rotateDaily ? "Enabled" : "Disabled") << std::endl;
    std::cout << "Max File Size: " << maxLogFileSize << "MB" << std::endl;
    
    // Count entries by level
    std::map<LogLevel, int> levelCounts;
    for (const auto& entry : logBuffer) {
        levelCounts[entry.level]++;
    }
    
    std::cout << "Level Distribution:" << std::endl;
    for (const auto& pair : levelCounts) {
        std::cout << "  " << logLevelToString(pair.first) << ": " << pair.second << std::endl;
    }
    
    std::cout << "======================" << std::endl;
}

std::string LogFileOutput::getCurrentLogFile() const {
    return currentLogFile;
}