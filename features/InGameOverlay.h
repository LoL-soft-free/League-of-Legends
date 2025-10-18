#pragma once

#include <iostream>
#include <vector>
#include <string>

/**
 * InGameOverlay - Adds a transparent overlay that displays computed data and timers
 * 
 * This feature creates a visual overlay that shows real-time game information,
 * statistics, and timers without interfering with normal gameplay.
 */

struct OverlayElement {
    std::string id;
    std::string type; // "text", "timer", "progress_bar", "image", "graph"
    std::string content;
    float x, y; // position on screen (0-1 normalized)
    float width, height;
    bool isVisible;
    std::string color;
    float opacity;
};

struct GameTimer {
    std::string name;
    long long startTime;
    long long duration; // in milliseconds, -1 for infinite
    bool isActive;
    std::string displayFormat;
};

class InGameOverlay {
private:
    bool enabled;
    std::vector<OverlayElement> overlayElements;
    std::vector<GameTimer> timers;
    bool isOverlayVisible;
    float globalOpacity;

public:
    InGameOverlay();
    ~InGameOverlay();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Overlay management
    void showOverlay();
    void hideOverlay();
    void renderOverlay();
    void updateOverlay();

    // Element management
    void addElement(const OverlayElement& element);
    void removeElement(const std::string& id);
    void updateElement(const std::string& id, const std::string& content);
    void setElementPosition(const std::string& id, float x, float y);

    // Timer functionality
    void addTimer(const std::string& name, long long duration);
    void removeTimer(const std::string& name);
    void startTimer(const std::string& name);
    void stopTimer(const std::string& name);
    void resetTimer(const std::string& name);

    // Configuration
    void setGlobalOpacity(float opacity);
    void setOverlayVisible(bool visible);

    // Information display
    void displayGameStats();
    void displayKDA();
    void displayGameTime();
    void displayFPS();

    // Status and debugging
    std::string getStatus() const;
    void printOverlayInfo() const;
};