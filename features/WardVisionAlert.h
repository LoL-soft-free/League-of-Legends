#pragma once

#include <iostream>
#include <vector>
#include <string>

/**
 * WardVisionAlert - Provides alerts when enemy wards are placed nearby
 * 
 * This feature monitors ward placement activities and alerts the player
 * when enemy vision is established in the vicinity.
 */

struct WardInfo {
    int id;
    float x, y;
    std::string type; // "trinket", "control", "stealth", "zombie"
    std::string team; // "ally", "enemy"
    long long placementTime;
    int duration; // in seconds, -1 for permanent
    bool isActive;
};

class WardVisionAlert {
private:
    bool enabled;
    std::vector<WardInfo> detectedWards;
    float alertRadius;
    bool soundAlerts;
    bool visualAlerts;

public:
    WardVisionAlert();
    ~WardVisionAlert();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Ward detection
    void scanForWards();
    void detectWardPlacement(float x, float y, const std::string& type, const std::string& team);
    void removeExpiredWards();

    // Alert system
    void triggerAlert(const WardInfo& ward);
    void showVisualAlert(const WardInfo& ward);
    void playSoundAlert();

    // Configuration
    void setAlertRadius(float radius);
    void enableSoundAlerts(bool enable);
    void enableVisualAlerts(bool enable);

    // Information retrieval
    std::vector<WardInfo> getNearbyWards(float x, float y, float radius) const;
    std::vector<WardInfo> getEnemyWards() const;
    bool isAreaWarded(float x, float y, float radius) const;

    // Status and debugging
    std::string getStatus() const;
    void printWardInfo() const;
};