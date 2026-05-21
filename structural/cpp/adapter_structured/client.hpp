#pragma once
#include "interfaces.hpp"
#include "adapters.hpp"
#include <memory>
#include <iostream>

class AudioPlayer : public MediaPlayer {
private:
    std::unique_ptr<MediaAdapter> mediaAdapter;
public:
    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp3") {
            std::cout << "Playing mp3 file: " << fileName << std::endl;
        } else if (audioType == "vlc" || audioType == "mp4") {
            mediaAdapter = std::make_unique<MediaAdapter>();
            mediaAdapter->play(audioType, fileName);
        } else {
            std::cout << "Invalid media. " << audioType << " format not supported" << std::endl;
        }
    }
};
