#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

/**
 * SkinCustomizer - Allows live skin changes right inside your current game session
 * 
 * This feature enables real-time customization of champion skins and visual effects
 * during active gameplay sessions.
 */

struct SkinData {
    int skinId;
    std::string skinName;
    std::string championName;
    bool isOwned;
    bool isActive;
    std::string previewImage;
};

class SkinCustomizer {
private:
    bool enabled;
    std::map<std::string, std::vector<SkinData>> availableSkins;
    std::string currentChampion;
    int activeSkinId;

public:
    SkinCustomizer();
    ~SkinCustomizer();

    // Core functionality
    void toggle();
    void enable();
    void disable();
    bool isEnabled() const;

    // Skin management
    void openCustomizer();
    void loadAvailableSkins();
    void applySkin(int skinId);
    void resetToDefaultSkin();

    // Skin browsing
    std::vector<SkinData> getSkinsForChampion(const std::string& championName) const;
    void previewSkin(int skinId);
    void showSkinGallery();

    // Configuration
    void setCurrentChampion(const std::string& championName);
    void addCustomSkin(const SkinData& skin);

    // Information retrieval
    SkinData getCurrentSkin() const;
    std::string getSkinName(int skinId) const;
    bool isSkinOwned(int skinId) const;

    // Status and debugging
    std::string getStatus() const;
    void printAvailableSkins() const;
};