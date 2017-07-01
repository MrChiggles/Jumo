//
//  ProcessArgs.hpp
//  Jumo
//
//  Created by Wesley Schrauwen on 2017/06/29.
//  Copyright © 2017 Wesley. All rights reserved.
//

#ifndef ProcessArgs_hpp
#define ProcessArgs_hpp

#include <iostream>
#include "Messages.hpp"

/*
 Args Processor
 
 Only run once on init to process all input args
 */

class ProcessArgs{
private:
    bool _shouldReturn;
    bool _shouldReinit;
public:
    
    ProcessArgs(int argc, const char *args[]){
        _shouldReinit = false;
        _shouldReturn = false;
        
        if (argc > 2){
            
            Messages::getInstance().printTooManyInputsMessage();
            setShouldReturn(true);
            return;
            
        } else if (argc == 1){
            
            return;
            
        }
        
        if (string(args[1]) == "-h" || string(args[1]) == "-help"){
            
            Messages::getInstance().printHelpMessage();
            
        } else if (string(args[1]) == "-init") {
            
            Messages::getInstance().printInitMessage();
            setReinit(true);
            
        } else {
            
            Messages::getInstance().printUnrecognizedInputMessage(string(args[1]));
            setShouldReturn(true);
            
        }
        
    }
    
    #pragma region Getters and Setters
    
    bool getShouldReturn(){
        return _shouldReturn;
    }
    
    void setShouldReturn(bool shouldReturn){
        _shouldReturn = shouldReturn;
    }
    
    bool getReinit(){
        return _shouldReinit;
    }
    
    void setReinit(bool shouldInit){
        _shouldReinit = shouldInit;
    }
    
    #pragma endregion
    
};

#endif /* ProcessArgs_hpp */
