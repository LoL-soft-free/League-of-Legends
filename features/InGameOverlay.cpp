#include "InGameOverlay.h"
#include <chrono>
#include <algorithm>

InGameOverlay::InGameOverlay() : enabled(false), isOverlayVisible(false), globalOpacity(0.8f) {
    std::cout << "[InGameOverlay] Module initialized" << std::endl;
}

InGameOverlay::~InGameOverlay() {
    std::cout << "[InGameOverlay] Module destroyed" << std::endl;
}

void InGameOverlay::toggle() {
    enabled = !enabled;
    if (enabled) {
        showOverlay();
    } else {
        hideOverlay();
    }
    std::cout << "[InGameOverlay] " << (enabled ? "Enabled" : "Disabled") << std::endl;
}

void InGameOverlay::enable() {
    enabled = true;
    showOverlay();
    std::cout << "[InGameOverlay] Feature enabled" << std::endl;
}

void InGameOverlay::disable() {
    enabled = false;
    hideOverlay();
    std::cout << "[InGameOverlay] Feature disabled" << std::endl;
}

bool InGameOverlay::isEnabled() const {
    return enabled;
}

void InGameOverlay::showOverlay() {
    if (!enabled) return;
    
    isOverlayVisible = true;
    std::cout << "[InGameOverlay] Overlay is now visible" << std::endl;
    
    // Initialize default overlay elements
    if (overlayElements.empty()) {
        // Add default elements
        OverlayElement fpsCounter = {"fps", "text", "FPS: 60", 0.02f, 0.02f, 0.1f, 0.05f, true, "white", 1.0f};
        OverlayElement gameTimer = {"timer", "text", "Game Time: 00:00", 0.02f, 0.08f, 0.15f, 0.05f, true, "yellow", 1.0f};
        OverlayElement kdaDisplay = {"kda", "text", "KDA: 0/0/0", 0.02f, 0.14f, 0.12f, 0.05f, true, "green", 1.0f};
        
        addElement(fpsCounter);
        addElement(gameTimer);
        addElement(kdaDisplay);
    }
    
    renderOverlay();
}

void InGameOverlay::hideOverlay() {
    isOverlayVisible = false;
    std::cout << "[InGameOverlay] Overlay is now hidden" << std::endl;
}

void InGameOverlay::renderOverlay() {
    if (!enabled || !isOverlayVisible) return;
    
    std::cout << "[InGameOverlay] Rendering overlay with " << overlayElements.size() << " elements" << std::endl;
    
    // Stub: Render each overlay element
    for (const auto& element : overlayElements) {
        if (element.isVisible) {
            // Simulate rendering
            std::cout << "  Rendering " << element.type << " at (" 
                      << element.x << ", " << element.y << "): " << element.content << std::endl;
        }
    }
}

void InGameOverlay::updateOverlay() {
    if (!enabled) return;
    
    // Update dynamic content
    updateElement("fps", "FPS: " + std::to_string(60)); // Placeholder FPS
    
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    updateElement("timer", "Game Time: 15:30"); // Placeholder game time
    
    updateElement("kda", "KDA: 3/1/5"); // Placeholder KDA
    
    if (isOverlayVisible) {
        renderOverlay();
    }
}

void InGameOverlay::addElement(const OverlayElement& element) {
    // Remove existing element with same ID
    removeElement(element.id);
    
    overlayElements.push_back(element);
    std::cout << "[InGameOverlay] Added overlay element: " << element.id << std::endl;
}

void InGameOverlay::removeElement(const std::string& id) {
    auto it = std::remove_if(overlayElements.begin(), overlayElements.end(),
        [&id](const OverlayElement& element) {
            return element.id == id;
        });
    
    if (it != overlayElements.end()) {
        overlayElements.erase(it, overlayElements.end());
        std::cout << "[InGameOverlay] Removed overlay element: " << id << std::endl;
    }
}

void InGameOverlay::updateElement(const std::string& id, const std::string& content) {
    auto it = std::find_if(overlayElements.begin(), overlayElements.end(),
        [&id](const OverlayElement& element) {
            return element.id == id;
        });
    
    if (it != overlayElements.end()) {
        it->content = content;
    }
}

void InGameOverlay::setElementPosition(const std::string& id, float x, float y) {
    auto it = std::find_if(overlayElements.begin(), overlayElements.end(),
        [&id](const OverlayElement& element) {
            return element.id == id;
        });
    
    if (it != overlayElements.end()) {
        it->x = x;
        it->y = y;
        std::cout << "[InGameOverlay] Moved element " << id << " to (" << x << ", " << y << ")" << std::endl;
    }
}

void InGameOverlay::addTimer(const std::string& name, long long duration) {
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    
    GameTimer timer;
    timer.name = name;
    timer.startTime = now;
    timer.duration = duration;
    timer.isActive = false;
    timer.displayFormat = "mm:ss";
    
    timers.push_back(timer);
    std::cout << "[InGameOverlay] Added timer: " << name << std::endl;
}

void InGameOverlay::removeTimer(const std::string& name) {
    auto it = std::remove_if(timers.begin(), timers.end(),
        [&name](const GameTimer& timer) {
            return timer.name == name;
        });
    
    if (it != timers.end()) {
        timers.erase(it, timers.end());
        std::cout << "[InGameOverlay] Removed timer: " << name << std::endl;
    }
}

void InGameOverlay::startTimer(const std::string& name) {
    auto it = std::find_if(timers.begin(), timers.end(),
        [&name](const GameTimer& timer) {
            return timer.name == name;
        });
    
    if (it != timers.end()) {
        it->isActive = true;
        it->startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        std::cout << "[InGameOverlay] Started timer: " << name << std::endl;
    }
}

void InGameOverlay::stopTimer(const std::string& name) {
    auto it = std::find_if(timers.begin(), timers.end(),
        [&name](const GameTimer& timer) {
            return timer.name == name;
        });
    
    if (it != timers.end()) {
        it->isActive = false;
        std::cout << "[InGameOverlay] Stopped timer: " << name << std::endl;
    }
}

void InGameOverlay::resetTimer(const std::string& name) {
    auto it = std::find_if(timers.begin(), timers.end(),
        [&name](const GameTimer& timer) {
            return timer.name == name;
        });
    
    if (it != timers.end()) {
        it->startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        std::cout << "[InGameOverlay] Reset timer: " << name << std::endl;
    }
}

void InGameOverlay::setGlobalOpacity(float opacity) {
    globalOpacity = std::max(0.0f, std::min(1.0f, opacity));
    std::cout << "[InGameOverlay] Global opacity set to: " << globalOpacity << std::endl;
}

void InGameOverlay::setOverlayVisible(bool visible) {
    if (visible) {
        showOverlay();
    } else {
        hideOverlay();
    }
}

void InGameOverlay::displayGameStats() {
    std::cout << "[InGameOverlay] Displaying game statistics" << std::endl;
    // Stub: Display comprehensive game stats
}

void InGameOverlay::displayKDA() {
    std::cout << "[InGameOverlay] Displaying KDA information" << std::endl;
    // Stub: Display kills/deaths/assists
}

void InGameOverlay::displayGameTime() {
    std::cout << "[InGameOverlay] Displaying game time" << std::endl;
    // Stub: Display current game time
}

void InGameOverlay::displayFPS() {
    std::cout << "[InGameOverlay] Displaying FPS counter" << std::endl;
    // Stub: Display frames per second
}

std::string InGameOverlay::getStatus() const {
    if (!enabled) return "Inactive";
    
    return "Active - " + std::to_string(overlayElements.size()) + " elements, " +
           std::to_string(timers.size()) + " timers, " +
           (isOverlayVisible ? "Visible" : "Hidden");
}

void InGameOverlay::printOverlayInfo() const {
    std::cout << "=== Overlay Information ===" << std::endl;
    std::cout << "Status: " << (enabled ? "Enabled" : "Disabled") << std::endl;
    std::cout << "Visibility: " << (isOverlayVisible ? "Visible" : "Hidden") << std::endl;
    std::cout << "Elements: " << overlayElements.size() << std::endl;
    std::cout << "Timers: " << timers.size() << std::endl;
    std::cout << "Global Opacity: " << globalOpacity << std::endl;
    std::cout << "===========================" << std::endl;
}