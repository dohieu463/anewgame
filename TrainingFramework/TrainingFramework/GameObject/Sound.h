#pragma once
#include "../TrainingFramework/stdafx.h"
#include "SDL.h"
#include "SDL_mixer.h"

class Sound
{
public:
    Sound();
    Sound(const char* soundPath);
    ~Sound();

    bool Load(const char* soundPath);
    void Play();
    void PlaySingle();
    void Pause();
    void Resume();
    void Stop();
    bool isPaused;
private:
    Mix_Music* music;
};


