#include "main.hpp"
#include "UI/Settings/CmSettingsViewController.hpp"
#include "TextHandler.hpp"

#include "custom-types/shared/register.hpp"
#include "beatsaber-hook/shared/utils/utils-functions.h"

#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
using namespace QuestUI;

#include "GlobalNamespace/MainMenuViewController.hpp"
using namespace GlobalNamespace;

#include "config-utils/shared/config-utils.hpp"
#include "ModConfig.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup
DEFINE_CONFIG(ModConfig);

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

MAKE_HOOK_MATCH(
    MainMenuViewController_DidActivate,
    &MainMenuViewController::DidActivate,
    void,
    MainMenuViewController* self,
    bool firstActivation,
    bool addedToHierarchy,
    bool screenSystemEnabling
) {
    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    cm::updateMenuText(self);
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    getModConfig().Init(modInfo);
    QuestUI::Init();

    QuestUI::Register::RegisterMainMenuModSettingsViewController<cm::CmSettingsViewController*>({ID, VERSION});

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), MainMenuViewController_DidActivate);
    getLogger().info("Installed all hooks!");
}