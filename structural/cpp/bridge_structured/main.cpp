#include "implementations.hpp"
#include "abstractions.hpp"

int main() {
    std::cout << "=== Bridge Pattern Demo ===" << std::endl << std::endl;
    
    std::cout << "--- Shape Drawing Bridge ---" << std::endl;
    auto redCircle = std::make_unique<Circle>(100, 100, 10, std::make_unique<RedCircleAPI>());
    auto greenCircle = std::make_unique<Circle>(100, 100, 10, std::make_unique<GreenCircleAPI>());
    redCircle->draw();
    greenCircle->draw();
    
    auto redRectangle = std::make_unique<Rectangle>(50, 50, 20, 30, std::make_unique<RedCircleAPI>());
    auto greenRectangle = std::make_unique<Rectangle>(50, 50, 20, 30, std::make_unique<GreenCircleAPI>());
    redRectangle->draw();
    greenRectangle->draw();
    
    std::cout << "\nResizing shapes:" << std::endl;
    redCircle->resize(150);
    redCircle->draw();
    std::cout << std::endl;
    
    std::cout << "--- Device and Remote Control Bridge ---" << std::endl;
    auto tv = std::make_unique<Television>();
    auto tvRemote = std::make_unique<RemoteControl>(std::move(tv));
    
    std::cout << "\nControlling TV with basic remote:" << std::endl;
    tvRemote->togglePower();
    tvRemote->volumeUp();
    tvRemote->volumeUp();
    tvRemote->volumeDown();
    tvRemote->togglePower();
    
    auto radio = std::make_unique<Radio>();
    auto advancedRemote = std::make_unique<AdvancedRemoteControl>(std::move(radio));
    
    std::cout << "\nControlling Radio with advanced remote:" << std::endl;
    advancedRemote->togglePower();
    advancedRemote->volumeUp();
    advancedRemote->mute();
    advancedRemote->togglePower();
    
    return 0;
}
