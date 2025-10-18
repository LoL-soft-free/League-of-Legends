#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
 * AutoUpdateLoader - Ensures the loader gets the latest secure modules and security patches
 * 
 * This feature handles automatic updates, security patches, and module management
 * to keep the application current and secure.
 */

struct UpdateInfo {
    std::string version;
    std::string description;
    std::string downloadUrl;
    std::string checksum;
    bool isSecurityUpdate;
    bool isRequired;
    long long releaseDate;
    std::vector<std::string> changedFiles;
};

struct ModuleInfo {
    std::string moduleName;
    std::string currentVersion;
    std::string latestVersion;
    bool needsUpdate;
    std::string moduleFile;
};

class AutoUpdateLoader {
private:
    bool enabled;
    std::string updateServerUrl;
    std::string currentVersion;
    bool autoUpdateEnabled;
    std::vector<ModuleInfo> modules;

public:
    AutoUpdateLoader();
    ~AutoUpdateLoader();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Update management
    void checkForUpdates();
    void downloadUpdate(const UpdateInfo& updateInfo);
    void installUpdate(const UpdateInfo& updateInfo);
    void rollbackUpdate();

    // Module management
    void loadModules();
    void updateModule(const std::string& moduleName);
    void validateModuleIntegrity(const std::string& moduleName);

    // Security features
    void verifyUpdateSignature(const UpdateInfo& updateInfo);
    void downloadSecurityPatches();
    void performSecurityCheck();

    // Configuration
    void setUpdateServer(const std::string& serverUrl);
    void enableAutoUpdate(bool enable);
    void setUpdateInterval(int hours);

    // Information retrieval
    std::vector<UpdateInfo> getAvailableUpdates();
    std::vector<ModuleInfo> getOutdatedModules();
    std::string getCurrentVersion() const;

    // Status and debugging
    std::string getStatus() const;
    void printUpdateInfo() const;
    void printModuleStatus() const;
};