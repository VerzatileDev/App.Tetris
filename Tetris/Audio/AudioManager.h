#pragma once

#include <SFML/Audio.hpp>

class AudioManager
{
public: 
public:
    AudioManager();
    ~AudioManager();

    void playRotateSound();
    void playBlockPlacementSound();
    void playLineClearSound();

private:
    sf::SoundBuffer rotateBuffer;
    sf::SoundBuffer blockPlacementBuffer;
    sf::SoundBuffer lineClearBuffer;

    sf::Sound rotateSound;
    sf::Sound blockPlacementSound;
    sf::Sound lineClearSound;
};