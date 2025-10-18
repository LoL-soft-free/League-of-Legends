#pragma once

#include <iostream>
#include <string>

/**
 * SafeModeToggle - Instantly disables advanced/risky features to enhance security
 * 
 * This feature provides a quick way to disable all potentially risky functionalities
 * and switch to a safer operational mode when needed.
 */

class SafeModeToggle {
private:
    bool enabled;
    bool safeModeActive;
    std::string previousState;

public:
    SafeModeToggle();
    ~SafeModeToggle();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Safe mode operations
    void activateSafeMode();
    void deactivateSafeMode();
    bool isSafeModeActive() const;
    void emergencyShutdown();

    // Feature management
    void disableAllRiskyFeatures();
    void restorePreviousState();
    void saveCurrentState();

    // Security checks
    bool isFeatureSafe(const std::string& featureName) const;
    void validateSystemSecurity();
    void performSecurityScan();

    // Configuration
    void setEmergencyHotkey(const std::string& hotkey);
    void addRiskyFeature(const std::string& featureName);
    void removeRiskyFeature(const std::string& featureName);

    // Status and debugging
    std::string getStatus() const;
    void printSecurityStatus() const;
    std::string getLastSecurityCheck() const;
};