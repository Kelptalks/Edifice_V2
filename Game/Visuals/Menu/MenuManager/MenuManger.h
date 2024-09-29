//
// Created by Spencer on 8/7/2024.
//

#ifndef EDIFICE_MENUMANGER_H
#define EDIFICE_MENUMANGER_H

#include "../../../GameData.h"
#include "Menus/SettingsMenu/SettingsMenu.h"
#include " UIManager/UIManger.h"
#include "Menus/WorldSelectMenu/WorldSelectMenu.h"

enum MenuType{
    MainMenu,
    CameraMenu,
    SettingsMenu,
    WorldSelectMenu
};

struct MenuManager{
    enum MenuType currentMenuType;
    struct MainMenu* mainMenu;
    struct SettingsMenu* settingsMenu;
    struct WorldSelectMenu* worldSelectMenu;

    struct OnScreenUI* onScreenUi;

};

struct MenuManager* createMenuManager();

void renderCurrentMenu(struct GameData* gameData);

void handleCurrentMenuInputs(struct GameData* gameData, SDL_Event event);

#endif //EDIFICE_MENUMANGER_H
