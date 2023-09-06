/*
#pragma once

#include <SDL.h>
#include <string>

class Sound {
public:
    Sound();
    ~Sound();

    bool Load(const std::string& filePath);
    void Play();
    void Pause();
    void Resume();
    void Stop();
    bool IsPlaying();

private:
    SDL_AudioSpec m_wantedSpec;
    Uint32 m_deviceId;
    Uint8* m_audioBuffer;
    Uint32 m_audioLength;
    bool m_isPlaying;
};
*/