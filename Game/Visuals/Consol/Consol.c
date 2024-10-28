//
// Created by Spencer on 10/28/2024.
//

#include "Consol.h"
#include <stdlib.h>
#include <string.h>

#include "../../InGameTime/Drone/DroneData.h"
#include "../../InGameTime/Drone/DroneInventoryManager/DroneInventoryManager.h"

struct Console* CreateConsole() {
    struct Console* console = malloc(sizeof(struct Console));


    console->logHistoryLength = 5;
    console->currentLogIndex = 0;

    console->visible = true;
    console->clickedOn = false;
    console->renderScale = 0;
    console->textCursorIndex = 0;


    console->log = malloc((sizeof(char*) * console->logHistoryLength));

    for (int i = 0; i < console->logHistoryLength; i++) {
        console->log[i] = calloc(100, sizeof(char));
    }

    return console;
}


char keyToChar(SDL_Event event){
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            // Alphabet keys
            case SDLK_a: return 'a';
            case SDLK_b: return 'b';
            case SDLK_c: return 'c';
            case SDLK_d: return 'd';
            case SDLK_e: return 'e';
            case SDLK_f: return 'f';
            case SDLK_g: return 'g';
            case SDLK_h: return 'h';
            case SDLK_i: return 'i';
            case SDLK_j: return 'j';
            case SDLK_k: return 'k';
            case SDLK_l: return 'l';
            case SDLK_m: return 'm';
            case SDLK_n: return 'n';
            case SDLK_o: return 'o';
            case SDLK_p: return 'p';
            case SDLK_q: return 'q';
            case SDLK_r: return 'r';
            case SDLK_s: return 's';
            case SDLK_t: return 't';
            case SDLK_u: return 'u';
            case SDLK_v: return 'v';
            case SDLK_w: return 'w';
            case SDLK_x: return 'x';
            case SDLK_y: return 'y';
            case SDLK_z: return 'z';

            // Number keys
            case SDLK_0: return '0';
            case SDLK_1: return '1';
            case SDLK_2: return '2';
            case SDLK_3: return '3';
            case SDLK_4: return '4';
            case SDLK_5: return '5';
            case SDLK_6: return '6';
            case SDLK_7: return '7';
            case SDLK_8: return '8';
            case SDLK_9: return '9';
        }
    }
    return ' ';
}

void handleCommand(struct GameData* gameData, char* command) {
    reportBug("Execute Command : %s\n", command);

    if (strncmp(command, "dronegive", 9) == 0) {
        char *endPointer;
        int droneId = strtol(command + 10, &endPointer, 10);

        int currentIndex = endPointer - command;

        // Check for "item" after the Drone ID
        if (strncmp(command + currentIndex + 1, "item", 4) == 0) {
            currentIndex += 5; // Move past "item" (4 characters) and the space following it
            int item = strtol(command + currentIndex, &endPointer, 10);


            struct DroneData* droneData = gameData->world->droneData;
            if (droneId < droneData->droneCount && item < getTotalItemCount()) {
                addItemToInventory(droneData, droneData->drones[droneId], item, getItemMaxStackSize(droneData->droneItemData, item));
            }
            else {
                reportBug("Failed to Perform Command dronegive | item or drone id out of range\n");
            }
        }
    }
    else if (strncmp(command, "move", 4) == 0) {
        reportBug("moved\n");
    }

}

bool handleConsoleInputs(struct GameData* gameData, SDL_Event event) {
    struct Console* console = gameData->menuManger->console;

    int xMouseCor; int yMouseCor;
    SDL_GetMouseState(&xMouseCor, &yMouseCor);

    //Box Cords
    int xCor = 0;
    int yCor = gameData->screen->yRez - console->renderScale;

    //Box Scale
    int xScale = 24 * console->renderScale;
    int yScale = console->renderScale;

    //Check if mouse is in bounds of box
    bool inXBounds = xMouseCor > xCor && xMouseCor  < xCor + xScale;
    bool inYBounds = yMouseCor > yCor && yMouseCor  < yCor + yScale;

    if (inXBounds && inYBounds) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            console->clickedOn = !console->clickedOn;
            return true;
        }
    }
    if (console->clickedOn) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_SLASH :
                    console->clickedOn = true;
                    break;
                case SDLK_RETURN :
                    handleCommand(gameData, console->log[console->currentLogIndex]);

                    console->currentLogIndex++;
                    console->textCursorIndex = 0;

                    if (console->currentLogIndex >= console->logHistoryLength) {
                        console->currentLogIndex = 0;
                    }

                    //Clear the old text box
                    for (int i = 0; i < 100; i++) {
                        console->log[console->currentLogIndex][i] = ' ';
                    }
                    console->clickedOn = false;
                break;
                case SDLK_BACKSPACE :
                    console->textCursorIndex--;
                    console->log[console->currentLogIndex][console->textCursorIndex] = ' ';
                break;
                default:
                    console->log[console->currentLogIndex][console->textCursorIndex] = keyToChar(event);
                    console->textCursorIndex++;
                    if (console->textCursorIndex >= 100) {
                        console->textCursorIndex = 0;
                    }
                break;
            }
        }
        return true;
    }
}

void renderConsole(struct GameData* gameData) {
    struct Console* console = gameData->menuManger->console;

    //Setup Scales
    console->renderScale = gameData->screen->xRez/96;
    int xCor = 0;
    int yCor = gameData->screen->yRez - console->renderScale;


    if (console->clickedOn) {
        SDL_Rect srcSelectedTextBoxRect = {1040, 704, 240, 16};
        SDL_Rect drawSelectedTextBoxRect = {xCor, yCor, 32 * console->renderScale, console->renderScale};
        SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcSelectedTextBoxRect, &drawSelectedTextBoxRect);

        if (SDL_GetTicks() % 200 > 100) {
            SDL_Rect srcCorsorIndex = {1024, 688, 16, 16};
            SDL_Rect destCorsorIndex = {xCor + (console->renderScale * console->textCursorIndex), yCor, console->renderScale, console->renderScale};
            SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcCorsorIndex, &destCorsorIndex);
        }

    }
    else {
        SDL_Rect srcTextBoxRect = {1040, 688, 240, 16};
        SDL_Rect drawTextBoxRect = {xCor, yCor, 24 * console->renderScale, console->renderScale};
        SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcTextBoxRect, &drawTextBoxRect);
    }

    for (int i = 0; i < console->logHistoryLength; i++) {
        int consoleIndex = console->currentLogIndex + i;

        if (consoleIndex >= console->logHistoryLength) {
            consoleIndex = consoleIndex - console->logHistoryLength;
        }


        //reportBug( "%i, ", consoleIndex);
        if (consoleIndex == console->currentLogIndex) {
            renderString(gameData, console->log[consoleIndex], xCor, yCor, console->renderScale);
        }
        else {
            SDL_Rect srcTextBoxRect = {1040, 688, 240, 16};
            SDL_Rect drawTextBoxRect = {xCor, (yCor - console->renderScale * console->logHistoryLength) + (i * console->renderScale), 24 * console->renderScale, console->renderScale};
            SDL_RenderCopy(gameData->screen->renderer, gameData->textures->spriteSheet, &srcTextBoxRect, &drawTextBoxRect);
            renderString(gameData, console->log[consoleIndex], xCor, (yCor - console->renderScale * console->logHistoryLength) + (i * console->renderScale), console->renderScale);
        }
    }

}