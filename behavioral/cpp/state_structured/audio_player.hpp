#pragma once
#include <memory>
#include <iostream>

class AudioPlayerState {
public:
    virtual ~AudioPlayerState() = default;
    virtual void clickPlay() = 0;
    virtual void clickStop() = 0;
    virtual void clickNext() = 0;
    virtual void clickPrevious() = 0;
};

class AudioPlayer {
private:
    std::unique_ptr<AudioPlayerState> currentState;
    bool isPlaying;
    int currentTrack;
    int totalTracks;
    
public:
    AudioPlayer(int tracks) : isPlaying(false), currentTrack(1), totalTracks(tracks) {
        currentState = std::make_unique<StoppedState>(this);
    }
    
    void setState(std::unique_ptr<AudioPlayerState> state) {
        currentState = std::move(state);
    }
    
    void clickPlay() {
        currentState->clickPlay();
    }
    
    void clickStop() {
        currentState->clickStop();
    }
    
    void clickNext() {
        currentState->clickNext();
    }
    
    void clickPrevious() {
        currentState->clickPrevious();
    }
    
    void startPlaying() {
        isPlaying = true;
        std::cout << "Started playing track " << currentTrack << std::endl;
    }
    
    void stopPlaying() {
        isPlaying = false;
        std::cout << "Stopped playing" << std::endl;
    }
    
    void nextTrack() {
        currentTrack = (currentTrack % totalTracks) + 1;
        std::cout << "Moved to track " << currentTrack << std::endl;
    }
    
    void previousTrack() {
        currentTrack = (currentTrack == 1) ? totalTracks : currentTrack - 1;
        std::cout << "Moved to track " << currentTrack << std::endl;
    }
    
    bool getIsPlaying() const {
        return isPlaying;
    }
};

class PlayingState : public AudioPlayerState {
private:
    AudioPlayer* player;
    
public:
    PlayingState(AudioPlayer* player) : player(player) {}
    
    void clickPlay() override {
        std::cout << "Already playing" << std::endl;
    }
    
    void clickStop() override {
        std::cout << "Stopping playback..." << std::endl;
        player->stopPlaying();
        player->setState(std::make_unique<StoppedState>(player));
    }
    
    void clickNext() override {
        std::cout << "Skipping to next track..." << std::endl;
        player->nextTrack();
    }
    
    void clickPrevious() override {
        std::cout << "Going to previous track..." << std::endl;
        player->previousTrack();
    }
};

class StoppedState : public AudioPlayerState {
private:
    AudioPlayer* player;
    
public:
    StoppedState(AudioPlayer* player) : player(player) {}
    
    void clickPlay() override {
        std::cout << "Starting playback..." << std::endl;
        player->startPlaying();
        player->setState(std::make_unique<PlayingState>(player));
    }
    
    void clickStop() override {
        std::cout << "Already stopped" << std::endl;
    }
    
    void clickNext() override {
        std::cout << "Skipping to next track..." << std::endl;
        player->nextTrack();
    }
    
    void clickPrevious() override {
        std::cout << "Going to previous track..." << std::endl;
        player->previousTrack();
    }
};
