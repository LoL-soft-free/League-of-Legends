#include "SkinCustomizer.h"
#include <algorithm>

SkinCustomizer::SkinCustomizer() : enabled(false), currentChampion(""), activeSkinId(0) {
    std::cout << "[SkinCustomizer] Module initialized" << std::endl;
    loadAvailableSkins();
}

SkinCustomizer::~SkinCustomizer() {
    std::cout << "[SkinCustomizer] Module destroyed" << std::endl;
}

void SkinCustomizer::toggle() {
    enabled = !enabled;
    std::cout << "[SkinCustomizer] " << (enabled ? "Enabled" : "Disabled") << std::endl;
}

void SkinCustomizer::enable() {
    enabled = true;
    std::cout << "[SkinCustomizer] Feature enabled" << std::endl;
}

void SkinCustomizer::disable() {
    enabled = false;
    std::cout << "[SkinCustomizer] Feature disabled" << std::endl;
}

bool SkinCustomizer::isEnabled() const {
    return enabled;
}

void SkinCustomizer::openCustomizer() {
    if (!enabled) {
        std::cout << "[SkinCustomizer] Cannot open customizer - feature is disabled" << std::endl;
        return;
    }
    
    std::cout << "[SkinCustomizer] Opening skin customizer interface..." << std::endl;
    showSkinGallery();
}

void SkinCustomizer::loadAvailableSkins() {
    std::cout << "[SkinCustomizer] Loading available skins..." << std::endl;
    
    // Stub: Load sample skins for demonstration
    std::vector<SkinData> jinxSkins = {
        {0, "Classic Jinx", "Jinx", true, false, "jinx_classic.jpg"},
        {1, "Mafia Jinx", "Jinx", false, false, "jinx_mafia.jpg"},
        {2, "Firecracker Jinx", "Jinx", true, false, "jinx_firecracker.jpg"}
    };
    
    std::vector<SkinData> yasuoSkins = {
        {0, "Classic Yasuo", "Yasuo", true, false, "yasuo_classic.jpg"},
        {1, "High Noon Yasuo", "Yasuo", true, false, "yasuo_highnoon.jpg"},
        {2, "PROJECT: Yasuo", "Yasuo", false, false, "yasuo_project.jpg"}
    };
    
    availableSkins["Jinx"] = jinxSkins;
    availableSkins["Yasuo"] = yasuoSkins;
    
    std::cout << "[SkinCustomizer] Loaded skins for " << availableSkins.size() << " champions" << std::endl;
}

void SkinCustomizer::applySkin(int skinId) {
    if (!enabled) {
        std::cout << "[SkinCustomizer] Cannot apply skin - feature is disabled" << std::endl;
        return;
    }
    
    if (currentChampion.empty()) {
        std::cout << "[SkinCustomizer] No champion selected" << std::endl;
        return;
    }
    
    auto it = availableSkins.find(currentChampion);
    if (it != availableSkins.end()) {
        auto& skins = it->second;
        auto skinIt = std::find_if(skins.begin(), skins.end(),
            [skinId](const SkinData& skin) { return skin.skinId == skinId; });
        
        if (skinIt != skins.end()) {
            // Reset previous active skin
            for (auto& skin : skins) {
                skin.isActive = false;
            }
            
            skinIt->isActive = true;
            activeSkinId = skinId;
            
            std::cout << "[SkinCustomizer] Applied skin: " << skinIt->skinName << std::endl;
            // Stub: Apply skin in game memory
        } else {
            std::cout << "[SkinCustomizer] Skin ID " << skinId << " not found" << std::endl;
        }
    }
}

void SkinCustomizer::resetToDefaultSkin() {
    if (!enabled) return;
    
    applySkin(0); // Skin ID 0 is typically the default/classic skin
    std::cout << "[SkinCustomizer] Reset to default skin" << std::endl;
}

std::vector<SkinData> SkinCustomizer::getSkinsForChampion(const std::string& championName) const {
    auto it = availableSkins.find(championName);
    return (it != availableSkins.end()) ? it->second : std::vector<SkinData>();
}

void SkinCustomizer::previewSkin(int skinId) {
    if (!enabled) return;
    
    std::cout << "[SkinCustomizer] Previewing skin ID: " << skinId << std::endl;
    // Stub: Show skin preview without applying
}

void SkinCustomizer::showSkinGallery() {
    std::cout << "\n=== Skin Gallery ===" << std::endl;
    if (currentChampion.empty()) {
        std::cout << "No champion selected. Available champions:" << std::endl;
        for (const auto& pair : availableSkins) {
            std::cout << "- " << pair.first << " (" << pair.second.size() << " skins)" << std::endl;
        }
    } else {
        auto skins = getSkinsForChampion(currentChampion);
        std::cout << "Skins for " << currentChampion << ":" << std::endl;
        for (const auto& skin : skins) {
            std::cout << "[" << skin.skinId << "] " << skin.skinName 
                      << (skin.isOwned ? "" : " (NOT OWNED)")
                      << (skin.isActive ? " (ACTIVE)" : "") << std::endl;
        }
    }
    std::cout << "===================" << std::endl;
}

void SkinCustomizer::setCurrentChampion(const std::string& championName) {
    currentChampion = championName;
    std::cout << "[SkinCustomizer] Current champion set to: " << championName << std::endl;
}

void SkinCustomizer::addCustomSkin(const SkinData& skin) {
    availableSkins[skin.championName].push_back(skin);
    std::cout << "[SkinCustomizer] Added custom skin: " << skin.skinName << std::endl;
}

SkinData SkinCustomizer::getCurrentSkin() const {
    if (currentChampion.empty()) {
        return SkinData{0, "None", "", false, false, ""};
    }
    
    auto skins = getSkinsForChampion(currentChampion);
    auto it = std::find_if(skins.begin(), skins.end(),
        [](const SkinData& skin) { return skin.isActive; });
    
    return (it != skins.end()) ? *it : SkinData{0, "Classic", currentChampion, true, true, ""};
}

std::string SkinCustomizer::getSkinName(int skinId) const {
    if (currentChampion.empty()) return "Unknown";
    
    auto skins = getSkinsForChampion(currentChampion);
    auto it = std::find_if(skins.begin(), skins.end(),
        [skinId](const SkinData& skin) { return skin.skinId == skinId; });
    
    return (it != skins.end()) ? it->skinName : "Unknown";
}

bool SkinCustomizer::isSkinOwned(int skinId) const {
    if (currentChampion.empty()) return false;
    
    auto skins = getSkinsForChampion(currentChampion);
    auto it = std::find_if(skins.begin(), skins.end(),
        [skinId](const SkinData& skin) { return skin.skinId == skinId; });
    
    return (it != skins.end()) ? it->isOwned : false;
}

std::string SkinCustomizer::getStatus() const {
    if (!enabled) return "Inactive";
    
    if (currentChampion.empty()) {
        return "Active - No champion selected";
    }
    
    auto currentSkin = getCurrentSkin();
    return "Active - " + currentChampion + " using " + currentSkin.skinName;
}

void SkinCustomizer::printAvailableSkins() const {
    std::cout << "=== Available Skins ===" << std::endl;
    for (const auto& pair : availableSkins) {
        std::cout << pair.first << ":" << std::endl;
        for (const auto& skin : pair.second) {
            std::cout << "  [" << skin.skinId << "] " << skin.skinName 
                      << (skin.isOwned ? " (Owned)" : " (Not Owned)") << std::endl;
        }
    }
    std::cout << "======================" << std::endl;
}