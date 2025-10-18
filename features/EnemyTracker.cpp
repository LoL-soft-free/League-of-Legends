#include "EnemyTracker.h"
#include <chrono>
#include <algorithm>

EnemyTracker::EnemyTracker() : enabled(false), trackingRadius(1500), predictionEnabled(true) {
    std::cout << "[EnemyTracker] Module initialized" << std::endl;
}

EnemyTracker::~EnemyTracker() {
    std::cout << "[EnemyTracker] Module destroyed" << std::endl;
}

void EnemyTracker::toggle() {
    enabled = !enabled;
    std::cout << "[EnemyTracker] " << (enabled ? "Enabled" : "Disabled") << std::endl;
}

void EnemyTracker::enable() {
    enabled = true;
    std::cout << "[EnemyTracker] Feature enabled" << std::endl;
}

void EnemyTracker::disable() {
    enabled = false;
    std::cout << "[EnemyTracker] Feature disabled" << std::endl;
}

bool EnemyTracker::isEnabled() const {
    return enabled;
}

void EnemyTracker::updateEnemyPosition(const std::string& championName, float x, float y) {
    if (!enabled) return;
    
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    
    // Find existing enemy or create new entry
    EnemyPosition* enemy = findEnemy(championName);
    if (enemy) {
        enemy->x = x;
        enemy->y = y;
        enemy->lastSeen = now;
        enemy->isVisible = true;
    } else {
        EnemyPosition newEnemy;
        newEnemy.championName = championName;
        newEnemy.x = x;
        newEnemy.y = y;
        newEnemy.lastSeen = now;
        newEnemy.isVisible = true;
        newEnemy.predictedX = x;
        newEnemy.predictedY = y;
        trackedEnemies.push_back(newEnemy);
    }
    
    std::cout << "[EnemyTracker] Updated position for " << championName << 
                 " at (" << x << ", " << y << ")" << std::endl;
}

void EnemyTracker::scanForEnemies() {
    if (!enabled) return;
    
    std::cout << "[EnemyTracker] Scanning for enemies..." << std::endl;
    // Stub: In real implementation, this would scan game memory for enemy positions
}

void EnemyTracker::predictMovement() {
    if (!enabled || !predictionEnabled) return;
    
    std::cout << "[EnemyTracker] Predicting enemy movements..." << std::endl;
    // Stub: Implement movement prediction algorithms
    for (auto& enemy : trackedEnemies) {
        // Simple prediction: assume enemy continues in same direction
        enemy.predictedX = enemy.x + 50.0f; // Placeholder prediction
        enemy.predictedY = enemy.y + 50.0f; // Placeholder prediction
    }
}

std::vector<EnemyPosition> EnemyTracker::getTrackedEnemies() const {
    return trackedEnemies;
}

EnemyPosition* EnemyTracker::findEnemy(const std::string& championName) {
    auto it = std::find_if(trackedEnemies.begin(), trackedEnemies.end(),
        [&championName](const EnemyPosition& enemy) {
            return enemy.championName == championName;
        });
    
    return (it != trackedEnemies.end()) ? &(*it) : nullptr;
}

bool EnemyTracker::isEnemyInRange(const std::string& championName, float range) const {
    const EnemyPosition* enemy = const_cast<EnemyTracker*>(this)->findEnemy(championName);
    if (!enemy || !enemy->isVisible) return false;
    
    // Stub: Calculate distance to player position (assuming player at 0,0 for demo)
    float distance = std::sqrt(enemy->x * enemy->x + enemy->y * enemy->y);
    return distance <= range;
}

void EnemyTracker::setTrackingRadius(int radius) {
    trackingRadius = radius;
    std::cout << "[EnemyTracker] Tracking radius set to: " << radius << std::endl;
}

void EnemyTracker::enablePrediction(bool enable) {
    predictionEnabled = enable;
    std::cout << "[EnemyTracker] Movement prediction " << 
                 (enable ? "enabled" : "disabled") << std::endl;
}

std::string EnemyTracker::getStatus() const {
    return enabled ? "Active - Tracking " + std::to_string(trackedEnemies.size()) + " enemies" : "Inactive";
}

void EnemyTracker::printTrackedEnemies() const {
    std::cout << "=== Tracked Enemies ===" << std::endl;
    for (const auto& enemy : trackedEnemies) {
        std::cout << enemy.championName << " at (" << enemy.x << ", " << enemy.y << ") " 
                  << (enemy.isVisible ? "[VISIBLE]" : "[HIDDEN]") << std::endl;
    }
    std::cout << "======================" << std::endl;
}