#include "SoundManager.h"

std::vector<SoundHandler> SoundManager::_buffers;

size_t SoundManager::RegisterSound(const std::string& filename, size_t maxSounds)
{
    _buffers.push_back(SoundHandler());
    SoundHandler& handler = _buffers.back();
    handler.soundBuffer.loadFromFile(filename);
    handler.maxLivingSounds = maxSounds;

    return _buffers.size() - 1;
}

void SoundManager::PlayInstanceOf(size_t soundID, float volume, bool isLoop)
{
    SoundHandler& handler = _buffers[soundID];
    std::list<sf::Sound>& soundList(handler.livingSounds);

    soundList.push_back(sf::Sound());
    sf::Sound& newSound = soundList.back();
    newSound.setBuffer(_buffers[soundID].soundBuffer);
    newSound.setVolume(volume);
    newSound.setLoop(isLoop);
    newSound.play();

    if (soundList.size() > handler.maxLivingSounds)
    {
        soundList.front().stop();
        soundList.pop_front();
    }

    handler.Update();
}

sf::Sound SoundManager::GetInstanceOf(size_t soundID)
{
    sf::Sound sound(_buffers[soundID].soundBuffer);
    return sound;
}
