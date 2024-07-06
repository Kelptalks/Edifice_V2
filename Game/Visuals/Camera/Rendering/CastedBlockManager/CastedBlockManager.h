//
// Created by Spencer on 5/7/2024.
//

#ifndef EDIFICE_CASTEDBLOCKMANAGER_H
#define EDIFICE_CASTEDBLOCKMANAGER_H

#include "TextureList/TextureList.h"
#include "../../Rendering/TextureManager/IsoTextureManager.h"
#include "../../CameraData.h"
#include "../../ChunkMap/ChunkMap.h"

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

    bool active;

    //Vars
    unsigned long worldKey;
    int scale;
    int isoX;
    int isoY;

    struct CastedBlock* castedBlocks;
    int castedBlockCount;

    //Rendering
    SDL_Texture* chunkTexture;
};

struct CastedPool{
    struct ChunkMap* chunkMap;
    int castedChunkArraySize;
};

struct CastedBlock* createCastedBlock();

void updateChunkCamCords(struct CameraData* cameraData, struct CastedChunk* castedChunk);

struct CastedChunk* createCastedChunk(struct CameraData* cameraData, struct SDL_Renderer* renderer, int isoX, int isoY);

void freeCastedChunk(struct CastedChunk* castedChunk);

struct CastedPool* createCastedPool(struct CameraData* cameraData, SDL_Renderer* renderer);

struct CastedChunk* getCastedChunkAtCords(struct CameraData* cameraData, int isoX, int isoY);

struct CastedBlock* getCastedBlockAtCords(struct CameraData* cameraData, int isoX, int isoY);

void updateChunksInBounds(struct GameData* gameData);

#endif //EDIFICE_CASTEDBLOCKMANAGER_H
