//
// Created by Spencer on 7/30/2024.
//

#include <SDL.h>
#include <stdio.h>
#include "../Debuging/Test_Main.h"
#include "SoundManager.h"
#include "../../Assets/AssetManager.h"

void resetSound(struct Sound* sound) {
    sound->buffer = sound->original_buffer;
    sound->length = sound->original_length;
    sound->is_playing = 0; // Set it as not playing
    SDL_CloseAudioDevice(sound->device_id);
}

void my_audio_callback(void *userdata, Uint8 *stream, int len) {
    struct Sound *sound = (struct Sound *)userdata;

    if (sound->length == 0 || !sound->is_playing) {
        SDL_memset(stream, 0, len); // Silence the output if no sound is left
        return;
    }

    len = (len > sound->length ? sound->length : len); // Clip length
    SDL_memcpy(stream, sound->buffer, len);            // Copy sound data to stream

    sound->buffer += len;
    sound->length -= len;

    // Check if the sound has finished playing
    if (sound->length == 0) {
        sound->is_playing = 0; // Stop playback
        // Do not close the device here to avoid potential issues
    }
}

void playSound(struct SoundManager *soundManager, int soundIndex) {
    if (soundIndex >= soundManager->soundCount) {
        reportBug("Invalid sound index\n");
        return;
    }

    struct Sound *sound = &soundManager->sounds[soundIndex];

    resetSound(sound);

    // Open a new audio device for this sound
    sound->device_id = SDL_OpenAudioDevice(NULL, 0, &sound->spec, NULL, 0);
    if (sound->device_id == 0) {
        reportBug("Failed to open audio device: %s\n", SDL_GetError());
        return;
    }

    sound->is_playing = 1;

    // Set the audio callback and userdata for this sound
    sound->spec.callback = my_audio_callback;
    sound->spec.userdata = sound;

    // Start playback
    SDL_PauseAudioDevice(sound->device_id, 0);
}

struct SoundManager* createSoundManager(int soundCount) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        reportBug("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    struct SoundManager* soundManager = malloc(sizeof(struct SoundManager));
    if (soundManager == NULL){
        reportBug("failed to malloc sound manager\n");
        return NULL;
    }

    soundManager->sounds = malloc(sizeof(struct Sound) * soundCount);
    if (soundManager->sounds == NULL){
        reportBug("failed to malloc sound array\n");
        free(soundManager);  // Free allocated memory to avoid a leak
        return NULL;
    }

    soundManager->soundCount = soundCount;

    // Load sounds into the manager
    loadSound("MusicSunn.WAV", &soundManager->sounds[MusicSunn]);
    loadSound("MenuClick.WAV", &soundManager->sounds[MenuClick]);
    loadSound("BlockPlaceSoundPlant.WAV", &soundManager->sounds[BlockPlaceSoundPlant]);
    loadSound("BlockRemoveSoundPlant.WAV", &soundManager->sounds[BlockRemoveSoundPlant]);
    loadSound("BlockPlaceSoundDirt.WAV", &soundManager->sounds[BlockPlaceSoundDirt]);
    loadSound("BlockRemoveSoundDirt.WAV", &soundManager->sounds[BlockRemoveSoundDirt]);
    loadSound("BlockPlaceSoundBrick.WAV", &soundManager->sounds[BlockPlaceSoundBrick]);
    loadSound("BlockRemoveSoundBrick.WAV", &soundManager->sounds[BlockRemoveSoundBrick]);
    loadSound("BlockPlaceSoundFactory.WAV", &soundManager->sounds[BlockPlaceSoundFactory]);
    loadSound("BlockRemoveSoundFactory.WAV", &soundManager->sounds[BlockRemoveSoundFactory]);
    loadSound("BlockRemoveSoundDefault.WAV", &soundManager->sounds[BlockRemoveSoundDefault]);
    loadSound("BlockPlaceSoundDefault.WAV", &soundManager->sounds[BlockPlaceSoundDefault]);

    //Play sounds to set them up


    for (int i = 0; i < soundCount; i++){
        playSound(soundManager, i);
    }


    return soundManager;
}