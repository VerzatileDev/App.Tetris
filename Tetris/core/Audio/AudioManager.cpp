#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager() {
    if (!rotateBuffer.loadFromFile("Assets/Audio/JDSherbert - Pixel UI SFX Pack - Cursor 1 (Sine).wav"))
        std::cerr << "Failed to load Cursor 1 sound\n";

    if (!blockPlacementBuffer.loadFromFile("Assets/Audio/JDSherbert - Pixel UI SFX Pack - Error 1 (Square).wav"))
        std::cerr << "Failed to load Error 1 sound\n";

    if (!lineClearBuffer.loadFromFile("Assets/Audio/JDSherbert - Pixel UI SFX Pack - Error 2 (Sine).wav"))
        std::cerr << "Failed to load Error 2 sound\n";

    rotateSound.setBuffer(rotateBuffer);
    blockPlacementSound.setBuffer(blockPlacementBuffer);
    lineClearSound.setBuffer(lineClearBuffer);
}

AudioManager::~AudioManager() {
    // Cleanup if needed
}

void AudioManager::playRotateSound() {
    rotateSound.play();
}

void AudioManager::playBlockPlacementSound() {
    blockPlacementSound.play();
}

void AudioManager::playLineClearSound() {
    lineClearSound.play();
}