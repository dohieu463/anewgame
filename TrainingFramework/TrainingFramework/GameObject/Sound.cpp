#pragma once
#include "../GameObject/Sound.h"
#include <string>

Sound::Sound()
{
    music = nullptr;
    isPaused = false;
}

Sound::Sound(const char* soundPath)
{
    music = nullptr;
    Load(soundPath);
}

Sound::~Sound()
{
    Stop();
    Mix_FreeMusic(music);
}

bool Sound::Load(const char* soundName)
{
    std::string path = "../Resources/Sounds/" + std::string(soundName) + ".mp3";
    
    if (Mix_Init(MIX_INIT_MP3) == -1) {
        // Xử lý lỗi
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        // Xử lý lỗi
        return false;
    }

    music = Mix_LoadMUS(path.c_str());
    if (music == NULL) {
        // Xử lý lỗi
        return false;
    }

    return true;
}

void Sound::Play()
{
    if (music != nullptr) {
        Mix_PlayMusic(music, -1);
    }
}

void Sound::Stop()
{
    if (music != nullptr && Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}

void Sound::Pause()
{
    if (music != nullptr && Mix_PlayingMusic()) {
        Mix_PauseMusic();
        isPaused = true;
    }
}

void Sound::Resume()
{
    if (music != nullptr && isPaused) {
        Mix_ResumeMusic();
        isPaused = false;
    }
}
