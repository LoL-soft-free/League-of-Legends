#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

/**
 * HotkeyProfiles - Lets you save/configure multiple control profiles for different scenarios
 * 
 * This feature allows users to create and manage different hotkey configurations
 * for various gameplay scenarios and champion types.
 */

struct Hotkey {
    std::string action;
    std::string keyBinding;
    bool isModified;
    std::string modifiers; // "ctrl", "alt", "shift"
};

struct HotkeyProfile {
    std::string profileName;
    std::string description;
    std::vector<Hotkey> hotkeys;
    bool isActive;
    std::string championType; // "adc", "support", "mid", "jungle", "top", "any"
};

class HotkeyProfiles {
private:
    bool enabled;
    std::vector<HotkeyProfile> profiles;
    std::string activeProfileName;
    std::map<std::string, std::string> defaultBindings;

public:
    HotkeyProfiles();
    ~HotkeyProfiles();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Profile management
    void manageProfiles();
    void createProfile(const std::string& name, const std::string& description);
    void deleteProfile(const std::string& name);
    void switchProfile(const std::string& name);

    // Hotkey configuration
    void addHotkey(const std::string& profileName, const Hotkey& hotkey);
    void removeHotkey(const std::string& profileName, const std::string& action);
    void modifyHotkey(const std::string& profileName, const std::string& action, const std::string& newBinding);

    // Profile operations
    void saveProfile(const std::string& profileName);
    void loadProfile(const std::string& profileName);
    void exportProfile(const std::string& profileName, const std::string& filePath);
    void importProfile(const std::string& filePath);

    // Information retrieval
    std::vector<HotkeyProfile> getAllProfiles() const;
    HotkeyProfile* getProfile(const std::string& name);
    std::string getActiveProfileName() const;

    // Status and debugging
    std::string getStatus() const;
    void printProfileInfo() const;
    void printHotkeys(const std::string& profileName) const;
};