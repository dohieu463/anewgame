#pragma once
#include "../TrainingFramework/stdafx.h"
#include "Sound.h"
/*
Sound::Sound() : m_deviceId(0), m_audioBuffer(nullptr), m_audioLength(0), m_isPlaying(false) {
    m_wantedSpec.freq = 44100;
    m_wantedSpec.format = AUDIO_S16SYS;
    m_wantedSpec.channels = 2;
    m_wantedSpec.samples = 4096;
    m_wantedSpec.callback = nullptr;
}

Sound::~Sound() {
    if (m_deviceId) {
        SDL_CloseAudioDevice(m_deviceId);
    }
    if (m_audioBuffer) {
        SDL_FreeWAV(m_audioBuffer);
    }
}

bool Sound::Load(const std::string& filePath) {
    SDL_LoadWAV(filePath.c_str(), &m_wantedSpec, &m_audioBuffer, &m_audioLength);
    if (m_audioBuffer) {
        m_deviceId = SDL_OpenAudioDevice(nullptr, 0, &m_wantedSpec, nullptr, 0);
        return true;
    }
    return false;
}

void Sound::Play() {
    if (m_deviceId) {
        SDL_QueueAudio(m_deviceId, m_audioBuffer, m_audioLength);
        SDL_PauseAudioDevice(m_deviceId, 0);
        m_isPlaying = true;
    }
}

void Sound::Pause() {
    if (m_deviceId && m_isPlaying) {
        SDL_PauseAudioDevice(m_deviceId, 1);
        m_isPlaying = false;
    }
}

void Sound::Resume() {
    if (m_deviceId && !m_isPlaying) {
        SDL_PauseAudioDevice(m_deviceId, 0);
        m_isPlaying = true;
    }
}

void Sound::Stop() {
    if (m_deviceId) {
        SDL_PauseAudioDevice(m_deviceId, 1);
        SDL_ClearQueuedAudio(m_deviceId);
        m_isPlaying = false;
    }
}

bool Sound::IsPlaying() {
    return m_isPlaying;
}
*/