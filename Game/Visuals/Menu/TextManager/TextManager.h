//
// Created by Spencer on 6/7/2024.
//

//
// Created by Spencer on 6/7/2024.
//

#ifndef EDIFICE_TEXTMANAGER_H
#define EDIFICE_TEXTMANAGER_H

#include "SDL.h"
#include "../../../../Game/GameData.h"

struct TextTextures{
    //Array of char textures
    SDL_Texture** chars;
    SDL_Texture** highRezChars;
};

//Chars for indexing the texture array
enum CharTexture{
    CharA,
    CharB,
    CharC,
    CharD,
    CharE,
    CharF,
    CharG,
    CharH,
    CharI,
    CharJ,
    CharK,
    CharL,
    CharM,
    CharN,
    CharO,
    CharP,
    CharQ,
    CharR,
    CharS,
    CharT,
    CharU,
    CharV,
    CharW,
    CharX,
    CharY,
    CharZ,
    Char0,
    Char1,
    Char2,
    Char3,
    Char4,
    Char5,
    Char6,
    Char7,
    Char8,
    Char9,
    CharPeriod,
    CharQuestion,
    CharExclamation,
    CharLineDot,
    CharDots,
    CharHashtag,
    CharPresent,
    CharClose,
    CharOpen,
    CharSlash,
    CharMinus,
};

struct TextTextures* createTextTextures(SDL_Renderer* renderer);

SDL_Texture* getCharTexture(struct GameData* gameData, char character, int scale);

void renderStringCentered(struct GameData* gameData, char string[], int xCor, int yCor, int scale);

void renderString(struct GameData* gameData, char string[], int xCor, int yCor, int scale);

void drawString(struct GameData* gameData, char string[], int stringLength, int xCor, int yCor, int scale);

#endif //EDIFICE_TEXTMANAGER_H
