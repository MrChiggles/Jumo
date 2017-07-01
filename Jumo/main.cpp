//
//  main.cpp
//  Jumo
//
//  Created by Wesley Schrauwen on 2017/06/29.
//  Copyright © 2017 Wesley. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "ConfigManager.hpp"
#include "InputManager.hpp"

int main(int argc, const char * argv[]) {
    
    bool configSuccessful;
    bool shouldContinue;
    
    ConfigManager *configManager = new ConfigManager(argc, argv, &configSuccessful);
    InputManager *inputManager = new InputManager(configManager, &shouldContinue);
    
    if (!configSuccessful){
        Messages::getInstance().printFailedToStartProgram();
        return 1;
    }
    
    Messages::getInstance().printSetupSuccessful();
    
    string input;
    
    do {
        
        Messages::getInstance().printCommandRequest();
        input = inputManager->getUserInput();
        inputManager->processInput(&input);
        
    } while (shouldContinue);
    
    delete inputManager;
    delete configManager;
    
    return 0;
    
}
