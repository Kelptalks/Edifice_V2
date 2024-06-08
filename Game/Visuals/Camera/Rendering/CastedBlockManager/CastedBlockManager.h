//
// Created by Spencer on 5/7/2024.
//

#ifndef EDIFICE_CASTEDBLOCKMANAGER_H
#define EDIFICE_CASTEDBLOCKMANAGER_H

#include "TextureList/TextureList.h"
#include "../../Rendering/TextureManager/IsoTextureManager.h"
#include "../../CameraData.h"

struct CastedBlock{
    struct TextureList* leftTextureList;
    struct TextureList* rightTextureList;
    enum Texture leftShader;
    enum Texture rightShader;
    unsigned long leftBlockKey;
    unsigned long rightBlockKey;
    unsigned long camKey;
};

struct CastedChunk{
    //Management
    bool busy;
    bool rayCast;
    bool textured;

    //Vars
    unsigned long worldKey;
    int scale;
    int isoX;
    int isoY;
    struct CastedBlock** castedBlocks;

    //Rendering
    SDL_Texture* chunkTexture;
};

struct CastedPool{
    struct CastedChunk** castedChunks;
};

struct CastedBlock* createCastedBlock();

struct CastedChunk* createCastedChunk(struct CameraData* cameraData, int isoX, int isoY);

struct CastedPool* createCastedPool(struct CameraData* cameraData);

#endif //EDIFICE_CASTEDBLOCKMANAGER_H
