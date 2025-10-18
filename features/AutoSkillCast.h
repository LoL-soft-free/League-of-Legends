#pragma once

#include <iostream>
#include <string>

/**
 * AutoSkillCast - Automatically selects and casts abilities as required during play
 * 
 * This feature analyzes the current game state and automatically casts abilities
 * based on optimal scenarios and user-defined preferences.
 */
class AutoSkillCast {
private:
    bool enabled;
    std::string lastSkillCast;
    int castDelay;

public:
    AutoSkillCast();
    ~AutoSkillCast();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Skill casting methods
    void castSkill(const std::string& skillKey);
    void analyzeGameState();
    void executeOptimalCast();

    // Configuration
    void setCastDelay(int delay);
    void setSkillPriority(const std::string& priorities);

    // Status and debugging
    std::string getStatus() const;
    void printDebugInfo() const;
};