//
// Created by Spencer on 7/30/2024.
//

#include <SDL.h>
#include <stdio.h>
#include "../Debuging/Test_Main.h"
#include "SoundManager.h"
#include "../../Assets/AssetManager.h"

struct Sounds* createSounds(){
    struct Sounds* sounds = malloc(sizeof (struct Sounds));
    if (sounds == NULL){
        reportBug("failed to create sounds");
        return NULL;
    }

    sounds->numOfBlockSounds = 5;
    sounds->blockSounds = malloc(sizeof (struct BlockSound) * sounds->numOfBlockSounds);


    // Load the WAV files
    for (int i = 0; i < sounds->numOfBlockSounds; i++) {
        char pathBuffer[1024];
        getExecutablePath(pathBuffer, sizeof(pathBuffer));
        char wavPath[1024];
        sprintf(wavPath, "%s\\..\\Assets\\Sounds\\Dirt.wav", pathBuffer, i + 1); // Construct the full path for each sound

        if (SDL_LoadWAV(wavPath, &sounds->blockSounds[i].wavSpec, &sounds->blockSounds[i].wavBuffer, &sounds->blockSounds[i].wavLength) == NULL) {
            reportBug(stderr, "Could not load %s: %s\n", wavPath, SDL_GetError());
            // Free previously loaded sounds
            for (int j = 0; j < i; j++) {
                SDL_FreeWAV(sounds->blockSounds[j].wavBuffer);
            }
            free(sounds->blockSounds);
            free(sounds);
            return NULL;
        }
    }

    return sounds;
}

// Global variables to hold the current sound data
Uint8* currentSoundBuffer = NULL;
Uint32 currentSoundLength = 0;
Uint32 currentSoundPosition = 0;

// Audio callback function
void audioCallback(void* userdata, Uint8* stream, int len) {
    if (currentSoundPosition >= currentSoundLength) {
        return; // No more data to play
    }

    Uint32 remaining = currentSoundLength - currentSoundPosition;
    Uint32 length = (Uint32)len;
    if (length > remaining) {
        length = remaining;
    }

    SDL_memcpy(stream, currentSoundBuffer + currentSoundPosition, length);
    currentSoundPosition += length;

    if (length < (Uint32)len) {
        SDL_memset(stream + length, 0, (Uint32)len - length); // Clear the remaining buffer
    }
}

// Function to play a sound from the sounds array
void playSound(struct Sounds* sounds, int index) {
    if (index < 0 || index >= sounds->numOfBlockSounds) {
        reportBug("Invalid sound index");
        return;
    }

    SDL_CloseAudio(); // Close the audio device if it was previously opened

    currentSoundBuffer = sounds->blockSounds[index].wavBuffer;
    currentSoundLength = sounds->blockSounds[index].wavLength;
    currentSoundPosition = 0;

    SDL_AudioSpec wavSpec = sounds->blockSounds[index].wavSpec;
    wavSpec.callback = audioCallback;

    if (SDL_OpenAudio(&wavSpec, NULL) < 0) {
        fprintf(stderr, "Could not open audio: %s\n", SDL_GetError());
        return;
    }

    SDL_PauseAudio(0); // Start playing audio

    SDL_PauseAudio(1); // Stop the audio

}