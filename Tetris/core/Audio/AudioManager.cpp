#include "AudioManager.h"

AudioManager::AudioManager() {
    if (!rotateBuffer.loadFromFile("Assets/Audio/JDSherbert - Pixel UI SFX Pack - Cursor 1 (Sine).wav") ||
        !blockPlacementBuffer.loadFromFile("Assets/Audio/JDSherbert - Pixel UI SFX Pack - Error 1 (Square).wav") ||
        !lineClearBuffer.loadFromFile("Assets/Audio/JDSherbert - Pixel UI SFX Pack - Error 2 (Sine).wav")) {
        // Handle error loading sounds
    }

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