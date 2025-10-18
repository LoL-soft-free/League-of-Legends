#include "LastHitBot.h"
#include <algorithm>
#include <cmath>

LastHitBot::LastHitBot() : enabled(false), attackDamage(50.0f), lastHitThreshold(10), autoAttackOnly(true) {
    std::cout << "[LastHitBot] Module initialized" << std::endl;
}

LastHitBot::~LastHitBot() {
    std::cout << "[LastHitBot] Module destroyed" << std::endl;
}

void LastHitBot::toggle() {
    enabled = !enabled;
    std::cout << "[LastHitBot] " << (enabled ? "Enabled" : "Disabled") << std::endl;
}

void LastHitBot::enable() {
    enabled = true;
    std::cout << "[LastHitBot] Feature enabled" << std::endl;
}

void LastHitBot::disable() {
    enabled = false;
    std::cout << "[LastHitBot] Feature disabled" << std::endl;
}

bool LastHitBot::isEnabled() const {
    return enabled;
}

void LastHitBot::scanMinions() {
    if (!enabled) return;
    
    std::cout << "[LastHitBot] Scanning for minions..." << std::endl;
    
    // Stub: Clear existing data and populate with sample minions
    nearbyMinions.clear();
    
    // Sample minions for demonstration
    MinionData minion1 = {1, 45.0f, 100.0f, 100.0f, 200.0f, "melee", false};
    MinionData minion2 = {2, 25.0f, 80.0f, 150.0f, 250.0f, "caster", false};
    MinionData minion3 = {3, 55.0f, 60.0f, 200.0f, 300.0f, "caster", false};
    
    nearbyMinions.push_back(minion1);
    nearbyMinions.push_back(minion2);
    nearbyMinions.push_back(minion3);
    
    // Update last-hittable status
    for (auto& minion : nearbyMinions) {
        minion.isLastHittable = shouldLastHit(minion);
    }
}

void LastHitBot::executeLastHit() {
    if (!enabled) return;
    
    scanMinions();
    
    // Find the best minion to last-hit
    MinionData* bestTarget = nullptr;
    for (auto& minion : nearbyMinions) {
        if (minion.isLastHittable) {
            if (!bestTarget || minion.health < bestTarget->health) {
                bestTarget = &minion;
            }
        }
    }
    
    if (bestTarget) {
        std::cout << "[LastHitBot] Executing last-hit on " << bestTarget->type 
                  << " minion (ID: " << bestTarget->id << ")" << std::endl;
        // Stub: Execute attack command
    } else {
        std::cout << "[LastHitBot] No minions available for last-hitting" << std::endl;
    }
}

bool LastHitBot::shouldLastHit(const MinionData& minion) const {
    // Simple logic: minion health is less than our attack damage + threshold
    return minion.health <= (attackDamage + lastHitThreshold);
}

void LastHitBot::calculateOptimalTiming() {
    if (!enabled) return;
    
    std::cout << "[LastHitBot] Calculating optimal timing for last-hits..." << std::endl;
    // Stub: Calculate attack timing based on animation speeds, projectile travel time, etc.
}

void LastHitBot::setAttackDamage(float damage) {
    attackDamage = damage;
    std::cout << "[LastHitBot] Attack damage set to: " << damage << std::endl;
}

void LastHitBot::setLastHitThreshold(int threshold) {
    lastHitThreshold = threshold;
    std::cout << "[LastHitBot] Last-hit threshold set to: " << threshold << std::endl;
}

void LastHitBot::setAutoAttackOnly(bool autoOnly) {
    autoAttackOnly = autoOnly;
    std::cout << "[LastHitBot] Auto-attack only mode " << 
                 (autoOnly ? "enabled" : "disabled") << std::endl;
}

void LastHitBot::updateMinionData() {
    if (!enabled) return;
    
    std::cout << "[LastHitBot] Updating minion data..." << std::endl;
    // Stub: Refresh minion health and positions from game memory
    for (auto& minion : nearbyMinions) {
        // Simulate minion health decay
        minion.health = std::max(0.0f, minion.health - 2.0f);
        minion.isLastHittable = shouldLastHit(minion);
    }
}

std::vector<MinionData> LastHitBot::getLastHittableMinions() const {
    std::vector<MinionData> lastHittable;
    std::copy_if(nearbyMinions.begin(), nearbyMinions.end(), 
                 std::back_inserter(lastHittable),
                 [](const MinionData& minion) { return minion.isLastHittable; });
    return lastHittable;
}

std::string LastHitBot::getStatus() const {
    if (!enabled) return "Inactive";
    
    int lastHittableCount = getLastHittableMinions().size();
    return "Active - " + std::to_string(nearbyMinions.size()) + " minions detected, " +
           std::to_string(lastHittableCount) + " last-hittable";
}

void LastHitBot::printMinionInfo() const {
    std::cout << "=== Minion Information ===" << std::endl;
    for (const auto& minion : nearbyMinions) {
        std::cout << "ID: " << minion.id << " | Type: " << minion.type 
                  << " | Health: " << minion.health << "/" << minion.maxHealth
                  << " | Last-hittable: " << (minion.isLastHittable ? "YES" : "NO") << std::endl;
    }
    std::cout << "==========================" << std::endl;
}

int LastHitBot::getGoldEarned() const {
    // Stub: Return accumulated gold from successful last-hits
    return 0; // Placeholder
}