//
// Created by Spencer on 7/30/2024.
//

#ifndef EDIFICE_SOUNDMANAGER_H
#define EDIFICE_SOUNDMANAGER_H

#include <SDL2/SDL.h>
enum SoundType{
    MusicSunn,
    MusicEdifice,

    SoundMenuButtonClick,

    BlockPlaceSoundPlant,
    BlockRemoveSoundPlant,

    BlockPlaceSoundDirt,

    BlockPlaceSoundBrick,

    BlockPlaceSoundFactory,
    BlockRemoveSoundFactory,

    BlockRemoveSoundDefault,
    BlockPlaceSoundDefault,


};

struct Sound {
    Uint8 *buffer;     // current position in the audio buffer
    Uint32 length;     // length of the remaining audio buffer

    Uint8 *original_buffer; // pointer to the original audio buffer
    Uint32 original_length; // original length of the audio buffer

    SDL_AudioDeviceID device_id;

    SDL_AudioSpec spec;   // audio specification (format, frequency, channels, etc.)
    int is_playing;       // flag to check if the audio is currently playing
};

struct SoundManager{
    struct Sound *sounds;

    int count;
    int maxCount;

    int soundCount;
};

struct Sounds{
    struct BlockSound* blockSounds;
    int numOfBlockSounds;
};

struct SoundManager* createSoundManager(int soundCount);
void playSound(struct SoundManager *soundManager, enum SoundType soundIndex);

#endif //EDIFICE_SOUNDMANAGER_H
