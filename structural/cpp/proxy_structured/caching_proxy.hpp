#pragma once
#include <string>
#include <memory>

class Video {
public:
    virtual ~Video() = default;
    virtual void play() = 0;
};

class RealVideo : public Video {
private:
    std::string filename;
    
    void loadVideo() {
        std::cout << "Loading video " << filename << " from server..." << std::endl;
    }
    
public:
    RealVideo(const std::string& filename) : filename(filename) {
        loadVideo();
    }
    
    void play() override {
        std::cout << "Playing video: " << filename << std::endl;
    }
};

class VideoProxy : public Video {
private:
    std::string filename;
    std::unique_ptr<RealVideo> realVideo;
    bool isLoaded = false;
    
public:
    VideoProxy(const std::string& filename) : filename(filename) {}
    
    void play() override {
        if (!isLoaded) {
            std::cout << "Loading video on first play..." << std::endl;
            realVideo = std::make_unique<RealVideo>(filename);
            isLoaded = true;
        } else {
            std::cout << "Using cached video..." << std::endl;
        }
        realVideo->play();
    }
};
