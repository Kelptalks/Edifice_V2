//
// Created by Spencer on 10/21/2024.
//

#ifndef DEBUGCONSOL_H
#define DEBUGCONSOL_H
#include <stdbool.h>

struct DebugConsole {
    bool visible;
};

struct DebugConsol* createDebugConsole();

void renderConsole(struct GameData* gameData);



#endif //DEBUGCONSOL_H
