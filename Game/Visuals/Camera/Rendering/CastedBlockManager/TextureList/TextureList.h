//
// Created by Spencer on 5/7/2024.
//

#ifndef EDIFICE_TEXTURELIST_H
#define EDIFICE_TEXTURELIST_H

#include <malloc.h>
#include "TextureList.h"
#include "../../TextureManager/IsoTextureManager.h"
#include "../../../../../Blocks/Blocks.h"

struct TextureNode{
    enum Texture texture;
    enum Block block;
};

struct TextureList{
    int length;
    int size;
    struct TextureNode* nodes;
};

struct TextureList* createTextureList();

void addTexture(struct TextureList* textureList, enum Block block, enum Texture texture);

void clearTextureList(struct TextureList* textureList);

void freeTextureList(struct TextureList* textureList);

#endif //EDIFICE_TEXTURELIST_H
