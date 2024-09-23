//
// Created by Spencer on 9/23/2024.
//

#ifndef EDIFICE_CASTEDBLOCKRENDERING_H
#define EDIFICE_CASTEDBLOCKRENDERING_H

#endif //EDIFICE_CASTEDBLOCKRENDERING_H

void renderChunkOutLine(struct GameData* gameData, int isoX, int isoY, int color[3]);

void renderCastedBlock(struct GameData* gameData, struct CastedBlock* castedBlock, int x, int y, int side);
//Render a chunks texture
void renderChunkTexture(struct GameData* gameData, struct CastedChunk* castedChunk);

void clearChunkTexture(struct GameData* gameData, struct CastedChunk* castedChunk);
//Draw a chunk in the correct location
void DrawChunk(struct GameData* gameData, struct CastedChunk* castedChunk);