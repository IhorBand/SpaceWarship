#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <list>

#include "SoundHandler.h"

class SoundManager
{
public:
    static void PlayInstanceOf(size_t soundID, float volume = 100, bool isLoop = false);
    static size_t RegisterSound(const std::string& filename, size_t maxSounds = 10);
    static sf::Sound GetInstanceOf(size_t soundID);

private:
    static std::vector<SoundHandler> _buffers;
};
