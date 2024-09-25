//
// Created by Spencer on 6/7/2024.
//

#include "SDL.h"
#include "TextManager.h"
#include "../../../Debuging/Test_Main.h"
#include "../../Camera/Rendering/TextureManager/IsoTextureManager.h"
#include "../../../../Assets/AssetManager.h"

struct TextTextures* createTextTextures(SDL_Renderer* renderer){
    //Number of chars in enum for splicing
    int numOfChars = 47;
    int scale = 6;
    //Cords on the sprite sheet were the text is to be cropped from
    int spriteSheetTextYCords = 1274;

    //Setup textTextures struct
    struct TextTextures* textTextures = malloc(sizeof (struct TextTextures));
    if (textTextures == NULL){
        reportBug("Failed to malloc text textures struct \n");
        return NULL;
    }

    //Load spriteSheet
    SDL_Surface* spriteSheet = loadSpriteSheet();
    //Get the pixel data from spritesheet
    uint32_t *spriteSheetPixels = spriteSheet->pixels;

    //Setup texture array
    SDL_Texture** chars = malloc(sizeof (SDL_Texture*) * numOfChars);
    if (chars == NULL){
        reportBug("Failed to malloc char textures array\n");
        return NULL;
    }

    //Create the text surfaces
    for (int s = 0; s < numOfChars; s++) {
        SDL_Surface* charSurface = SDL_CreateRGBSurfaceWithFormat(0, scale, scale, 32, SDL_PIXELFORMAT_RGBA32);
        //Get pixels of new char surface
        uint32_t *charSurfacePixels = charSurface->pixels;

        //Copy pixels from spreadsheet to surface
        int startingX = s * scale;
        for (int y = 0; y < scale; y++){
            for (int x = 0; x < scale; x++){
                charSurfacePixels[x + (y * scale)] = spriteSheetPixels[(x + startingX) + ((y + spriteSheetTextYCords) * spriteSheet->w)];
            }
        }

        //Convert surface into texture and save to the charTextureArray;
        chars[s] = SDL_CreateTextureFromSurface(renderer, charSurface);

        SDL_FreeSurface(charSurface);
    }

    SDL_FreeSurface(spriteSheet);
    textTextures->chars = chars;
    return textTextures;
}

SDL_Texture* getCharTexture(struct GameData* gameData, char character){
    SDL_Texture** charTextures = gameData->textTextures->chars;

    switch (character) {
        //Letters
        case 'a' :
        case 'A' : return charTextures[CharA];

        case 'b' :
        case 'B' : return charTextures[CharB];

        case 'c' :
        case 'C' : return charTextures[CharC];

        case 'd' :
        case 'D' : return charTextures[CharD];

        case 'e' :
        case 'E' : return charTextures[CharE];

        case 'f' :
        case 'F' : return charTextures[CharF];

        case 'g' :
        case 'G' : return charTextures[CharG];

        case 'h' :
        case 'H' : return charTextures[CharH];

        case 'i' :
        case 'I' : return charTextures[CharI];

        case 'j' :
        case 'J' : return charTextures[CharJ];

        case 'k' :
        case 'K' : return charTextures[CharK];

        case 'l' :
        case 'L' : return charTextures[CharL];

        case 'm' :
        case 'M' : return charTextures[CharM];

        case 'n' :
        case 'N' : return charTextures[CharN];

        case 'o' :
        case 'O' : return charTextures[CharO];

        case 'p' :
        case 'P' : return charTextures[CharP];

        case 'q' :
        case 'Q' : return charTextures[CharQ];

        case 'r' :
        case 'R' : return charTextures[CharR];

        case 's' :
        case 'S' : return charTextures[CharS];

        case 't' :
        case 'T' : return charTextures[CharT];

        case 'u' :
        case 'U' : return charTextures[CharU];

        case 'v' :
        case 'V' : return charTextures[CharV];

        case 'w' :
        case 'W' : return charTextures[CharW];

        case 'x' :
        case 'X' : return charTextures[CharX];

        case 'y' :
        case 'Y' : return charTextures[CharY];

        case 'z' :
        case 'Z' : return charTextures[CharZ];

        //Numbers
        case '0' : return charTextures[Char0];
        case '1' : return charTextures[Char1];
        case '2' : return charTextures[Char2];
        case '3' : return charTextures[Char3];
        case '4' : return charTextures[Char4];
        case '5' : return charTextures[Char5];
        case '6' : return charTextures[Char6];
        case '7' : return charTextures[Char7];
        case '8' : return charTextures[Char8];
        case '9' : return charTextures[Char9];

        //Punctuation
        case '.' : return charTextures[CharPeriod];
        case '?' : return charTextures[CharQuestion];
        case '!' : return charTextures[CharExclamation];
        case ';' : return charTextures[CharLineDot];
        case ':' : return charTextures[CharDots];
        case '#' : return charTextures[CharHashtag];
        case '%' : return charTextures[CharPresent];
        case ')' : return charTextures[CharClose];
        case '(' : return charTextures[CharOpen];
        case '/' : return charTextures[CharSlash];
        case '-' : return charTextures[CharMinus];

        default:
            return NULL;
    }
}

int getStringLength(char *str){
    int length = 0;

    // Loop till the NULL character is found
    while (*str != '\0')
    {
        length++;

        // Move to the next character
        str++;
    }
    return length;
}

void renderStringCentered(struct GameData* gameData, char string[], int xCor, int yCor, int scale){
    int stringLen = getStringLength(string);
    xCor -= (stringLen/2) * scale;
    drawString(gameData, string, stringLen, xCor, yCor, scale);
}

void renderString(struct GameData* gameData, char string[], int xCor, int yCor, int scale){
    int stringLen = getStringLength(string);
    drawString(gameData, string, stringLen, xCor, yCor, scale);
}

void drawString(struct GameData* gameData, char string[], int stringLength, int xCor, int yCor, int scale){
    //Frame rate
    for (int x = 0; x < stringLength; x++) {
        SDL_Rect rect = {xCor + (x * scale), yCor, scale, scale};
        SDL_RenderCopy(gameData->screen->renderer, getCharTexture(gameData, string[x]), NULL, &rect);
    }
}