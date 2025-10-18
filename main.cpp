#include <iostream>
#include <string>
#include <memory>

// Include headers for all features
#include "features/AutoSkillCast.h"
#include "features/EnemyTracker.h"
#include "features/LastHitBot.h"
#include "features/WardVisionAlert.h"
#include "features/SkinCustomizer.h"
#include "features/HotkeyProfiles.h"
#include "features/InGameOverlay.h"
#include "features/SafeModeToggle.h"
#include "features/AutoUpdateLoader.h"
#include "features/LogFileOutput.h"

class LeagueOfLegendsTrainer {
private:
    std::unique_ptr<AutoSkillCast> autoSkillCast;
    std::unique_ptr<EnemyTracker> enemyTracker;
    std::unique_ptr<LastHitBot> lastHitBot;
    std::unique_ptr<WardVisionAlert> wardVisionAlert;
    std::unique_ptr<SkinCustomizer> skinCustomizer;
    std::unique_ptr<HotkeyProfiles> hotkeyProfiles;
    std::unique_ptr<InGameOverlay> inGameOverlay;
    std::unique_ptr<SafeModeToggle> safeModeToggle;
    std::unique_ptr<AutoUpdateLoader> autoUpdateLoader;
    std::unique_ptr<LogFileOutput> logFileOutput;

public:
    LeagueOfLegendsTrainer() {
        initializeFeatures();
    }

    void initializeFeatures() {
        std::cout << "Initializing League of Legends Trainer..." << std::endl;
        
        // Initialize all features
        autoSkillCast = std::make_unique<AutoSkillCast>();
        enemyTracker = std::make_unique<EnemyTracker>();
        lastHitBot = std::make_unique<LastHitBot>();
        wardVisionAlert = std::make_unique<WardVisionAlert>();
        skinCustomizer = std::make_unique<SkinCustomizer>();
        hotkeyProfiles = std::make_unique<HotkeyProfiles>();
        inGameOverlay = std::make_unique<InGameOverlay>();
        safeModeToggle = std::make_unique<SafeModeToggle>();
        autoUpdateLoader = std::make_unique<AutoUpdateLoader>();
        logFileOutput = std::make_unique<LogFileOutput>();

        std::cout << "All features initialized successfully!" << std::endl;
    }

    void showMenu() {
        std::cout << "\n=== League of Legends Trainer ===" << std::endl;
        std::cout << "1. Toggle Auto Skill Cast" << std::endl;
        std::cout << "2. Toggle Enemy Tracker" << std::endl;
        std::cout << "3. Toggle Last Hit Bot" << std::endl;
        std::cout << "4. Toggle Ward Vision Alert" << std::endl;
        std::cout << "5. Open Skin Customizer" << std::endl;
        std::cout << "6. Manage Hotkey Profiles" << std::endl;
        std::cout << "7. Toggle In-Game Overlay" << std::endl;
        std::cout << "8. Safe Mode Toggle" << std::endl;
        std::cout << "9. Check for Updates" << std::endl;
        std::cout << "10. View Log Files" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose an option: ";
    }

    void run() {
        int choice;
        bool running = true;

        while (running) {
            showMenu();
            std::cin >> choice;

            switch (choice) {
                case 1:
                    autoSkillCast->toggle();
                    break;
                case 2:
                    enemyTracker->toggle();
                    break;
                case 3:
                    lastHitBot->toggle();
                    break;
                case 4:
                    wardVisionAlert->toggle();
                    break;
                case 5:
                    skinCustomizer->openCustomizer();
                    break;
                case 6:
                    hotkeyProfiles->manageProfiles();
                    break;
                case 7:
                    inGameOverlay->toggle();
                    break;
                case 8:
                    safeModeToggle->toggle();
                    break;
                case 9:
                    autoUpdateLoader->checkForUpdates();
                    break;
                case 10:
                    logFileOutput->viewLogs();
                    break;
                case 0:
                    std::cout << "Exiting League of Legends Trainer..." << std::endl;
                    running = false;
                    break;
                default:
                    std::cout << "Invalid option. Please try again." << std::endl;
                    break;
            }
        }
    }
};

int main() {
    std::cout << "Welcome to League of Legends Trainer!" << std::endl;
    std::cout << "Built in C++, designed to assist with gameplay mechanics." << std::endl;
    std::cout << "DISCLAIMER: This software is for research and educational purposes only." << std::endl;
    std::cout << "It must not be used to cheat in live online games.\n" << std::endl;

    try {
        LeagueOfLegendsTrainer trainer;
        trainer.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}