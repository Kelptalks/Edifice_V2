//
// Created by Spencer on 5/7/2024.
//

#ifndef EDIFICE_CASTEDBLOCKMANAGER_H
#define EDIFICE_CASTEDBLOCKMANAGER_H

#include <pthread.h>
#include "TextureList/TextureList.h"
#include "../../Rendering/TextureManager/IsoTextureManager.h"
#include "ChunkMap/ChunkMap.h"
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

    int worldLeftBlockX;
    int worldLeftBlockY;
    int worldLeftBlockZ;

    int worldRightBlockX;
    int worldRightBlockY;
    int worldRightBlockZ;

    //World cords
    int worldX;
    int worldY;
    int worldZ;
};

struct CastedChunk{
    //Management
    bool rayCast;
    bool textured;

    //Vars
    int worldX;
    int worldY;
    int worldZ;


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



    //All chunks
    int totalChunksCreated;
    int maxChunks;
    struct CastedChunk** allChunks;


    //Free Chunks
    int freeChunkCount;
    struct CastedChunk** freeChunks;

    //Chunks in use
    int totalChunksInUse;
    struct CastedChunk** chunksInUse;

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

void unloadChunk(struct GameData* gameData, struct CastedChunk* castedChunk);
struct CastedChunk* loadChunk(struct GameData* gameData, int isoX, int isoY);



#endif //EDIFICE_CASTEDBLOCKMANAGER_H
