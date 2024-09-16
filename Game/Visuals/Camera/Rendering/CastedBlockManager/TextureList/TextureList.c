//
// Created by Spencer on 5/7/2024.
//

#include <malloc.h>
#include "TextureList.h"
#include "../../TextureManager/IsoTextureManager.h"
#include "../../../../../Blocks/Blocks.h"
#include "../../../../../Debuging/Test_Main.h"


void expandTextureList(struct TextureList* textureList){
    textureList->size += 5;
    //malloc new array with increased size
    struct TextureNode* newNodes = calloc(textureList->size, sizeof (struct TextureNode));
    //Copy nodes from old array
    for (int x = 0; x < textureList->length; x++){
        newNodes[0] = textureList->nodes[x];
    }
    //Clean up and set vars
    free(textureList->nodes);
    textureList->nodes = newNodes;
}

struct TextureList* createTextureList(){
    struct TextureList* textureList = calloc(1,sizeof(struct TextureList));
    textureList->length = 0;
    textureList->size = 5;
    textureList->nodes = calloc( textureList->size, sizeof(struct TextureNode));
    return textureList;
}

void addTexture(struct TextureList* textureList, enum Block block, enum Texture texture){
    if (textureList->length == textureList->size){
        return;
    }
    textureList->nodes[textureList->length].texture = texture;
    textureList->nodes[textureList->length].block = block;
    textureList->length++;
}

void clearTextureList(struct TextureList* textureList){
    textureList->length = 0;
}

void freeTextureList(struct TextureList* textureList){
    free(textureList->nodes);
    textureList->nodes = NULL;
    free(textureList);
    textureList = NULL;
}

