//
// Created by Spencer on 7/30/2024.
//

#ifndef EDIFICE_SOUNDMANAGER_H
#define EDIFICE_SOUNDMANAGER_H

struct BlockSound{
    SDL_AudioSpec wavSpec;
    Uint8* wavBuffer;
    Uint32 wavLength;
};

struct Sounds{
    struct BlockSound* blockSounds;
    int numOfBlockSounds;
};

struct Sounds* createSounds();

void playSound(struct Sounds* sounds, int index);

#endif //EDIFICE_SOUNDMANAGER_H
