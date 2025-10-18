#include "HotkeyProfiles.h"
#include <algorithm>
#include <fstream>

HotkeyProfiles::HotkeyProfiles() : enabled(false), activeProfileName("") {
    std::cout << "[HotkeyProfiles] Module initialized" << std::endl;
    
    // Initialize default bindings
    defaultBindings["move"] = "RightClick";
    defaultBindings["attack"] = "A";
    defaultBindings["stop"] = "S";
    defaultBindings["hold"] = "H";
    defaultBindings["skill_q"] = "Q";
    defaultBindings["skill_w"] = "W";
    defaultBindings["skill_e"] = "E";
    defaultBindings["skill_r"] = "R";
    defaultBindings["summ1"] = "D";
    defaultBindings["summ2"] = "F";
    
    // Create a default profile
    createProfile("Default", "Standard League of Legends keybindings");
    createProfile("ADC", "Optimized for ADC gameplay");
    createProfile("Support", "Optimized for Support gameplay");
}

HotkeyProfiles::~HotkeyProfiles() {
    std::cout << "[HotkeyProfiles] Module destroyed" << std::endl;
}

void HotkeyProfiles::toggle() {
    enabled = !enabled;
    std::cout << "[HotkeyProfiles] " << (enabled ? "Enabled" : "Disabled") << std::endl;
}

void HotkeyProfiles::enable() {
    enabled = true;
    std::cout << "[HotkeyProfiles] Feature enabled" << std::endl;
}

void HotkeyProfiles::disable() {
    enabled = false;
    std::cout << "[HotkeyProfiles] Feature disabled" << std::endl;
}

bool HotkeyProfiles::isEnabled() const {
    return enabled;
}

void HotkeyProfiles::manageProfiles() {
    if (!enabled) {
        std::cout << "[HotkeyProfiles] Cannot manage profiles - feature is disabled" << std::endl;
        return;
    }
    
    std::cout << "\n=== Hotkey Profile Manager ===" << std::endl;
    std::cout << "Available profiles:" << std::endl;
    
    for (const auto& profile : profiles) {
        std::cout << "- " << profile.profileName 
                  << (profile.isActive ? " (ACTIVE)" : "")
                  << " [" << profile.championType << "]" << std::endl;
        std::cout << "  Description: " << profile.description << std::endl;
    }
    
    std::cout << "\nActive profile: " << activeProfileName << std::endl;
    std::cout << "=============================" << std::endl;
}

void HotkeyProfiles::createProfile(const std::string& name, const std::string& description) {
    HotkeyProfile newProfile;
    newProfile.profileName = name;
    newProfile.description = description;
    newProfile.isActive = false;
    newProfile.championType = "any";
    
    // Initialize with default hotkeys
    for (const auto& pair : defaultBindings) {
        Hotkey hotkey;
        hotkey.action = pair.first;
        hotkey.keyBinding = pair.second;
        hotkey.isModified = false;
        hotkey.modifiers = "";
        newProfile.hotkeys.push_back(hotkey);
    }
    
    profiles.push_back(newProfile);
    
    std::cout << "[HotkeyProfiles] Created profile: " << name << std::endl;
}

void HotkeyProfiles::deleteProfile(const std::string& name) {
    auto it = std::remove_if(profiles.begin(), profiles.end(),
        [&name](const HotkeyProfile& profile) {
            return profile.profileName == name;
        });
    
    if (it != profiles.end()) {
        profiles.erase(it, profiles.end());
        std::cout << "[HotkeyProfiles] Deleted profile: " << name << std::endl;
        
        if (activeProfileName == name) {
            activeProfileName = "";
        }
    } else {
        std::cout << "[HotkeyProfiles] Profile not found: " << name << std::endl;
    }
}

void HotkeyProfiles::switchProfile(const std::string& name) {
    if (!enabled) return;
    
    HotkeyProfile* profile = getProfile(name);
    if (profile) {
        // Deactivate current profile
        for (auto& p : profiles) {
            p.isActive = false;
        }
        
        profile->isActive = true;
        activeProfileName = name;
        
        std::cout << "[HotkeyProfiles] Switched to profile: " << name << std::endl;
        loadProfile(name);
    } else {
        std::cout << "[HotkeyProfiles] Profile not found: " << name << std::endl;
    }
}

void HotkeyProfiles::addHotkey(const std::string& profileName, const Hotkey& hotkey) {
    HotkeyProfile* profile = getProfile(profileName);
    if (profile) {
        profile->hotkeys.push_back(hotkey);
        std::cout << "[HotkeyProfiles] Added hotkey " << hotkey.action 
                  << " -> " << hotkey.keyBinding << " to profile " << profileName << std::endl;
    }
}

void HotkeyProfiles::removeHotkey(const std::string& profileName, const std::string& action) {
    HotkeyProfile* profile = getProfile(profileName);
    if (profile) {
        auto it = std::remove_if(profile->hotkeys.begin(), profile->hotkeys.end(),
            [&action](const Hotkey& hotkey) {
                return hotkey.action == action;
            });
        
        if (it != profile->hotkeys.end()) {
            profile->hotkeys.erase(it, profile->hotkeys.end());
            std::cout << "[HotkeyProfiles] Removed hotkey " << action 
                      << " from profile " << profileName << std::endl;
        }
    }
}

void HotkeyProfiles::modifyHotkey(const std::string& profileName, const std::string& action, const std::string& newBinding) {
    HotkeyProfile* profile = getProfile(profileName);
    if (profile) {
        auto it = std::find_if(profile->hotkeys.begin(), profile->hotkeys.end(),
            [&action](const Hotkey& hotkey) {
                return hotkey.action == action;
            });
        
        if (it != profile->hotkeys.end()) {
            it->keyBinding = newBinding;
            it->isModified = true;
            std::cout << "[HotkeyProfiles] Modified " << action 
                      << " -> " << newBinding << " in profile " << profileName << std::endl;
        }
    }
}

void HotkeyProfiles::saveProfile(const std::string& profileName) {
    std::cout << "[HotkeyProfiles] Saving profile: " << profileName << std::endl;
    // Stub: Save profile to file
}

void HotkeyProfiles::loadProfile(const std::string& profileName) {
    std::cout << "[HotkeyProfiles] Loading profile: " << profileName << std::endl;
    // Stub: Apply hotkey bindings to game
}

void HotkeyProfiles::exportProfile(const std::string& profileName, const std::string& filePath) {
    std::cout << "[HotkeyProfiles] Exporting profile " << profileName 
              << " to " << filePath << std::endl;
    // Stub: Export profile to file
}

void HotkeyProfiles::importProfile(const std::string& filePath) {
    std::cout << "[HotkeyProfiles] Importing profile from " << filePath << std::endl;
    // Stub: Import profile from file
}

std::vector<HotkeyProfile> HotkeyProfiles::getAllProfiles() const {
    return profiles;
}

HotkeyProfile* HotkeyProfiles::getProfile(const std::string& name) {
    auto it = std::find_if(profiles.begin(), profiles.end(),
        [&name](const HotkeyProfile& profile) {
            return profile.profileName == name;
        });
    
    return (it != profiles.end()) ? &(*it) : nullptr;
}

std::string HotkeyProfiles::getActiveProfileName() const {
    return activeProfileName;
}

std::string HotkeyProfiles::getStatus() const {
    if (!enabled) return "Inactive";
    
    return "Active - " + std::to_string(profiles.size()) + " profiles, using: " + 
           (activeProfileName.empty() ? "None" : activeProfileName);
}

void HotkeyProfiles::printProfileInfo() const {
    std::cout << "=== Profile Information ===" << std::endl;
    std::cout << "Total profiles: " << profiles.size() << std::endl;
    std::cout << "Active profile: " << activeProfileName << std::endl;
    std::cout << "===========================" << std::endl;
}

void HotkeyProfiles::printHotkeys(const std::string& profileName) const {
    const HotkeyProfile* profile = const_cast<HotkeyProfiles*>(this)->getProfile(profileName);
    if (profile) {
        std::cout << "=== Hotkeys for " << profileName << " ===" << std::endl;
        for (const auto& hotkey : profile->hotkeys) {
            std::cout << hotkey.action << " -> " << hotkey.keyBinding;
            if (!hotkey.modifiers.empty()) {
                std::cout << " (+" << hotkey.modifiers << ")";
            }
            if (hotkey.isModified) {
                std::cout << " [MODIFIED]";
            }
            std::cout << std::endl;
        }
        std::cout << "================================" << std::endl;
    }
}