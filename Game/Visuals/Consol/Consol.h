//
// Created by Spencer on 10/28/2024.
//

#ifndef CONSOL_H
#define CONSOL_H
#include <SDL_events.h>
#include <stdbool.h>
#include "../Menu/MenuManager/MenuManger.h"


struct Console {
    char** log;
    int logHistoryLength;

    int currentLogIndex;
    bool visible;
    bool clickedOn;

    int textCursorIndex;

    int renderScale;
};

struct Console* CreateConsole();

bool handleConsoleInputs(struct GameData* gameData, SDL_Event event);

void renderConsole(struct GameData* gameData);

#endif //CONSOL_H
