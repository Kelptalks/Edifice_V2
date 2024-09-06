//
// Created by Spencer on 5/7/2024.
//

#ifndef EDIFICE_CASTEDBLOCKMANAGER_H
#define EDIFICE_CASTEDBLOCKMANAGER_H

#include <pthread.h>
#include "TextureList/TextureList.h"
#include "../../Rendering/TextureManager/IsoTextureManager.h"
#include "../../ChunkMap/ChunkMap.h"
#include "../../CameraData.h"


struct CastedBlock{
    //Textures
    struct TextureList* leftTextureList;
    struct TextureList* rightTextureList;

    //ExtraLair
    bool hasLeftTextureList;
    bool hasRightTextureList;
    struct TextureList* leftTempTextureList;
    struct TextureList* rightTemptTextureList;

    //Shaders
    enum Texture leftShader;
    enum Texture rightShader;

    unsigned long leftBlockKey;
    unsigned long rightBlockKey;
    unsigned long camKey;
};

struct CastedChunk{
    //Management
    bool rayCast;
    bool textured;

    //Vars
    unsigned long worldKey;
    int scale;
    int isoX;
    int isoY;

    struct CastedBlock* castedBlocks;
    int castedBlockCount;

    enum Direction direction;

    //Rendering
    SDL_Texture* chunkTexture;

    pthread_mutex_t lock;
};

struct CastedPool{
    struct ChunkMap* chunkMap;


    int totalChunksCreated;
    int maxChunks;
    struct CastedChunk** allChunks;


    //Chunks that are available for use
    int freeChunkCount;
    struct CastedChunk** freeChunks;
};

//Casted area Creating/Freeing
struct CastedBlock* createCastedBlock();
void updateChunkCamCords(struct CameraData* cameraData, struct CastedChunk* castedChunk);
struct CastedChunk* createCastedChunk(struct CameraData* cameraData, struct SDL_Renderer* renderer, int isoX, int isoY);
void freeCastedChunk(struct CastedChunk* castedChunk);
struct CastedPool* createCastedPool(struct CameraData* cameraData, SDL_Renderer* renderer);

//Pool management
struct CastedChunk* getCastedChunkAtCords(struct CameraData* cameraData, int isoX, int isoY);
struct CastedBlock* getCastedBlockAtCords(struct CameraData* cameraData, int isoX, int isoY);

void unloadChunk(struct CastedPool* castedPool, struct CastedChunk* castedChunk);
struct CastedChunk* loadChunk(struct GameData* gameData, int isoX, int isoY);



#endif //EDIFICE_CASTEDBLOCKMANAGER_H
