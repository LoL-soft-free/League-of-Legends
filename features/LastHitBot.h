#pragma once

#include <iostream>
#include <vector>
#include <string>

/**
 * LastHitBot - Optimizes gold farming by executing last-hits on minions automatically
 * 
 * This feature analyzes minion health and automatically executes last-hits
 * to maximize gold income and farming efficiency.
 */

struct MinionData {
    int id;
    float health;
    float maxHealth;
    float x, y;
    std::string type; // "melee", "caster", "cannon", "super"
    bool isLastHittable;
};

class LastHitBot {
private:
    bool enabled;
    std::vector<MinionData> nearbyMinions;
    float attackDamage;
    int lastHitThreshold;
    bool autoAttackOnly;

public:
    LastHitBot();
    ~LastHitBot();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Last-hit mechanics
    void scanMinions();
    void executeLastHit();
    bool shouldLastHit(const MinionData& minion) const;
    void calculateOptimalTiming();

    // Configuration
    void setAttackDamage(float damage);
    void setLastHitThreshold(int threshold);
    void setAutoAttackOnly(bool autoOnly);

    // Minion management
    void updateMinionData();
    std::vector<MinionData> getLastHittableMinions() const;

    // Status and debugging
    std::string getStatus() const;
    void printMinionInfo() const;
    int getGoldEarned() const;
};