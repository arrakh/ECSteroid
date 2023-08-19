//
// Created by Arya Rakha on 8/1/2023.
//

#ifndef ECSTEROID_SFMLAUDIOSERVICE_H
#define ECSTEROID_SFMLAUDIOSERVICE_H


#include "core/ILocatableService.h"
#include "core/ILoadableService.h"
#include <string>
#include <unordered_map>
#include <SFML/Audio.hpp>

typedef struct{
    float volume;
    float pitch;
} SFXPlayParameter;

const SFXPlayParameter DEFAULT = {100.f, 1.f};

class SFMLAudioService : public ILocatableService, public ILoadableService {
public:
    void Load() override;

    void Unload() override;

    void PlaySFX(std::string fileName, SFXPlayParameter parameter = DEFAULT);

    void PlayBGM(std::string fileName, float volume = 100.f);

    void StopBGM();

private:
    static const int MAX_CONCURRENT_SFX = 24;
    const std::string SFX_PATH = "assets/sfx";
    const std::string BGM_PATH = "assets/bgm";

    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> loadedSounds;

    sf::Sound soundPool[MAX_CONCURRENT_SFX];

    sf::Music musicPlayer;

    void PlaySFXOneShot(SFXPlayParameter parameter, sf::Sound &sound, sf::SoundBuffer &buffer) const;
};


#endif //ECSTEROID_SFMLAUDIOSERVICE_H
