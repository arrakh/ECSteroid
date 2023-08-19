//
// Created by Arya Rakha on 8/1/2023.
//

#include <filesystem>
#include <iostream>
#include "SFMLAudioService.h"
namespace fs = std::filesystem;

void SFMLAudioService::Load() {

    //Load SFX
    for (const auto& entry : fs::directory_iterator(SFX_PATH)) {
        if (!entry.is_regular_file()) continue;

        auto path = entry.path().string();

        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(path))
            throw std::invalid_argument("Trying to load SFX but could not load " + path);

        auto id = entry.path().stem().string();
        loadedSounds[id] = std::make_unique<sf::SoundBuffer>(buffer);
    }
}

void SFMLAudioService::Unload() {

}

void SFMLAudioService::PlaySFX(std::string fileName, const SFXPlayParameter param) {
    auto it = loadedSounds.find(fileName);
    if (it == loadedSounds.end()) throw std::invalid_argument("Could not find sfx with name " + fileName);

    for (int i = 0; i < MAX_CONCURRENT_SFX; ++i) {
        sf::Sound& sound = soundPool[i];
        auto status = sound.getStatus();

        if (status != sf::Sound::Status::Stopped) continue;
        PlaySFXOneShot(param, sound, *it->second);
        return;
    }

    PlaySFXOneShot(param, soundPool[0], *it->second);
}

void SFMLAudioService::PlaySFXOneShot(const SFXPlayParameter param, sf::Sound &sound, sf::SoundBuffer &buffer) const {
    sound.stop();
    sound.setVolume(param.volume);
    sound.setPitch(param.pitch);
    sound.setBuffer(buffer);
    sound.play();
}

void SFMLAudioService::PlayBGM(std::string fileNameWithExtension, const float volume) {
    musicPlayer.stop();
    if (!musicPlayer.openFromFile(BGM_PATH + '/' + fileNameWithExtension))
        throw std::invalid_argument("Trying to load BGM but could not load " + fileNameWithExtension);
    musicPlayer.setVolume(volume);
    musicPlayer.play();
}

void SFMLAudioService::StopBGM() {
    musicPlayer.stop();
}
