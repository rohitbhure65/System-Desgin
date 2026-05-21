#include "receivers.hpp"
#include "interfaces.hpp"
#include "concrete_commands.hpp"
#include "invoker.hpp"

int main() {
    std::cout << "=== Command Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Remote Control
    std::cout << "--- Remote Control Example ---" << std::endl;
    
    Light livingRoomLight;
    Stereo livingRoomStereo;
    
    auto lightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    auto lightOff = std::make_shared<LightOffCommand>(livingRoomLight);
    auto stereoOn = std::make_shared<StereoOnCommand>(livingRoomStereo);
    auto stereoOff = std::make_shared<StereoOffCommand>(livingRoomStereo);
    
    RemoteControl remote;
    remote.setCommand(lightOn);
    remote.setCommand(lightOff);
    remote.setCommand(stereoOn);
    remote.setCommand(stereoOff);
    
    std::cout << "\nTurning on light (slot 0):" << std::endl;
    remote.buttonPressed(0);
    
    std::cout << "\nTurning on stereo (slot 2):" << std::endl;
    remote.buttonPressed(2);
    
    std::cout << "\nUndo last action:" << std::endl;
    remote.undoButtonPressed();
    
    std::cout << "\nTurning off light (slot 1):" << std::endl;
    remote.buttonPressed(1);
    
    std::cout << "\nUndo last action:" << std::endl;
    remote.undoButtonPressed();
    
    std::cout << std::endl;
    
    // Example 2: Macro Command
    std::cout << "--- Macro Command Example ---" << std::endl;
    
    auto partyMode = std::make_shared<MacroCommand>();
    partyMode->addCommand(lightOn);
    partyMode->addCommand(stereoOn);
    
    auto shutdownMode = std::make_shared<MacroCommand>();
    shutdownMode->addCommand(stereoOff);
    shutdownMode->addCommand(lightOff);
    
    std::cout << "\nActivating party mode:" << std::endl;
    partyMode->execute();
    
    std::cout << "\nActivating shutdown mode:" << std::endl;
    shutdownMode->execute();
    
    std::cout << "\nUndo shutdown:" << std::endl;
    shutdownMode->undo();
    
    std::cout << std::endl;
    
    // Example 3: Transaction Command
    std::cout << "--- Transaction Command Example ---" << std::endl;
    
    BankAccount myAccount(1000);
    
    std::cout << "\nInitial balance: $" << myAccount.getBalance() << std::endl;
    
    auto deposit = std::make_shared<DepositCommand>(myAccount, 500);
    auto withdraw = std::make_shared<WithdrawCommand>(myAccount, 200);
    
    std::cout << "\nExecuting deposit:" << std::endl;
    deposit->execute();
    
    std::cout << "\nExecuting withdrawal:" << std::endl;
    withdraw->execute();
    
    std::cout << "\nUndo withdrawal:" << std::endl;
    withdraw->undo();
    
    std::cout << "\nFinal balance: $" << myAccount.getBalance() << std::endl;
    
    return 0;
}
