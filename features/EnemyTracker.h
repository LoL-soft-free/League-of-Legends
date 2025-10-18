#pragma once

#include <iostream>
#include <vector>
#include <string>

/**
 * EnemyTracker - Tracks the location of enemy players and predicts movement for map awareness
 * 
 * This feature monitors enemy positions and provides predictive analysis
 * to enhance map awareness and strategic decision making.
 */

struct EnemyPosition {
    std::string championName;
    float x, y;
    long long lastSeen;
    bool isVisible;
    float predictedX, predictedY;
};

class EnemyTracker {
private:
    bool enabled;
    std::vector<EnemyPosition> trackedEnemies;
    int trackingRadius;
    bool predictionEnabled;

public:
    EnemyTracker();
    ~EnemyTracker();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Tracking methods
    void updateEnemyPosition(const std::string& championName, float x, float y);
    void scanForEnemies();
    void predictMovement();

    // Information retrieval
    std::vector<EnemyPosition> getTrackedEnemies() const;
    EnemyPosition* findEnemy(const std::string& championName);
    bool isEnemyInRange(const std::string& championName, float range) const;

    // Configuration
    void setTrackingRadius(int radius);
    void enablePrediction(bool enable);

    // Status and debugging
    std::string getStatus() const;
    void printTrackedEnemies() const;
};