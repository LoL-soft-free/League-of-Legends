#include "WardVisionAlert.h"
#include <chrono>
#include <algorithm>
#include <cmath>

WardVisionAlert::WardVisionAlert() : enabled(false), alertRadius(800.0f), soundAlerts(true), visualAlerts(true) {
    std::cout << "[WardVisionAlert] Module initialized" << std::endl;
}

WardVisionAlert::~WardVisionAlert() {
    std::cout << "[WardVisionAlert] Module destroyed" << std::endl;
}

void WardVisionAlert::toggle() {
    enabled = !enabled;
    std::cout << "[WardVisionAlert] " << (enabled ? "Enabled" : "Disabled") << std::endl;
}

void WardVisionAlert::enable() {
    enabled = true;
    std::cout << "[WardVisionAlert] Feature enabled" << std::endl;
}

void WardVisionAlert::disable() {
    enabled = false;
    std::cout << "[WardVisionAlert] Feature disabled" << std::endl;
}

bool WardVisionAlert::isEnabled() const {
    return enabled;
}

void WardVisionAlert::scanForWards() {
    if (!enabled) return;
    
    std::cout << "[WardVisionAlert] Scanning for wards..." << std::endl;
    // Stub: In real implementation, scan game memory for ward objects
    removeExpiredWards();
}

void WardVisionAlert::detectWardPlacement(float x, float y, const std::string& type, const std::string& team) {
    if (!enabled) return;
    
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    
    WardInfo newWard;
    newWard.id = detectedWards.size() + 1; // Simple ID assignment
    newWard.x = x;
    newWard.y = y;
    newWard.type = type;
    newWard.team = team;
    newWard.placementTime = now;
    newWard.duration = (type == "control") ? -1 : 180000; // 3 minutes for most wards, permanent for control
    newWard.isActive = true;
    
    detectedWards.push_back(newWard);
    
    std::cout << "[WardVisionAlert] Detected " << team << " " << type 
              << " ward at (" << x << ", " << y << ")" << std::endl;
    
    if (team == "enemy") {
        triggerAlert(newWard);
    }
}

void WardVisionAlert::removeExpiredWards() {
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    
    detectedWards.erase(
        std::remove_if(detectedWards.begin(), detectedWards.end(),
            [now](const WardInfo& ward) {
                return ward.duration != -1 && (now - ward.placementTime) > ward.duration;
            }),
        detectedWards.end()
    );
}

void WardVisionAlert::triggerAlert(const WardInfo& ward) {
    std::cout << "[WardVisionAlert] ALERT: Enemy ward detected!" << std::endl;
    
    if (visualAlerts) {
        showVisualAlert(ward);
    }
    
    if (soundAlerts) {
        playSoundAlert();
    }
}

void WardVisionAlert::showVisualAlert(const WardInfo& ward) {
    std::cout << "[WardVisionAlert] Visual Alert: " << ward.type 
              << " ward at (" << ward.x << ", " << ward.y << ")" << std::endl;
    // Stub: Display visual alert on overlay
}

void WardVisionAlert::playSoundAlert() {
    std::cout << "[WardVisionAlert] *BEEP* Sound alert played!" << std::endl;
    // Stub: Play audio alert
}

void WardVisionAlert::setAlertRadius(float radius) {
    alertRadius = radius;
    std::cout << "[WardVisionAlert] Alert radius set to: " << radius << std::endl;
}

void WardVisionAlert::enableSoundAlerts(bool enable) {
    soundAlerts = enable;
    std::cout << "[WardVisionAlert] Sound alerts " << 
                 (enable ? "enabled" : "disabled") << std::endl;
}

void WardVisionAlert::enableVisualAlerts(bool enable) {
    visualAlerts = enable;
    std::cout << "[WardVisionAlert] Visual alerts " << 
                 (enable ? "enabled" : "disabled") << std::endl;
}

std::vector<WardInfo> WardVisionAlert::getNearbyWards(float x, float y, float radius) const {
    std::vector<WardInfo> nearbyWards;
    
    for (const auto& ward : detectedWards) {
        if (!ward.isActive) continue;
        
        float distance = std::sqrt(std::pow(ward.x - x, 2) + std::pow(ward.y - y, 2));
        if (distance <= radius) {
            nearbyWards.push_back(ward);
        }
    }
    
    return nearbyWards;
}

std::vector<WardInfo> WardVisionAlert::getEnemyWards() const {
    std::vector<WardInfo> enemyWards;
    std::copy_if(detectedWards.begin(), detectedWards.end(),
                 std::back_inserter(enemyWards),
                 [](const WardInfo& ward) { 
                     return ward.team == "enemy" && ward.isActive; 
                 });
    return enemyWards;
}

bool WardVisionAlert::isAreaWarded(float x, float y, float radius) const {
    return !getNearbyWards(x, y, radius).empty();
}

std::string WardVisionAlert::getStatus() const {
    if (!enabled) return "Inactive";
    
    int activeWards = 0;
    for (const auto& ward : detectedWards) {
        if (ward.isActive) activeWards++;
    }
    
    return "Active - " + std::to_string(activeWards) + " wards tracked";
}

void WardVisionAlert::printWardInfo() const {
    std::cout << "=== Ward Information ===" << std::endl;
    for (const auto& ward : detectedWards) {
        if (!ward.isActive) continue;
        std::cout << "ID: " << ward.id << " | Type: " << ward.type 
                  << " | Team: " << ward.team << " | Position: (" 
                  << ward.x << ", " << ward.y << ")" << std::endl;
    }
    std::cout << "========================" << std::endl;
}