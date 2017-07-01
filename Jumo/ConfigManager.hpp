//
//  ConfigManager.hpp
//  Jumo
//
//  Created by Wesley Schrauwen on 2017/07/01.
//  Copyright © 2017 Wesley. All rights reserved.
//

#ifndef ConfigManager_hpp
#define ConfigManager_hpp

#include <iostream>
#include <fstream>
#include "ProcessArgs.hpp"

/*
 Manages the Config file.
 */
class ConfigManager {
private:
    string _inputDir;
    string _outputDir;
    string _fileName;
    string _username;
    
    ProcessArgs *_processArgs;;
    fstream _configFile;
    
#pragma region configHelpers
    
    void saveConfigDirectories(){
        _configFile << _inputDir << "\n";
        _configFile << _outputDir << "\n";
    }
    
    bool configExists(){
        _configFile.open(_fileName);
        return _configFile.good();
    }
    
    void loadConfig(){
        getline(_configFile, _inputDir);
        getline(_configFile, _outputDir);
    }
    
    void createConfigFile(){
        if (!_configFile.is_open()){
            ofstream f(_fileName);
            f.close();
        }
        
        _configFile.open(_fileName);
        
    }
    
    void getConfigDirectories(){
        Messages::getInstance().printInputDirMessage();
        setInputDirectory(getUserInput());
        
        Messages::getInstance().printOutputDirMessage();
        setOutputDirectory(getUserInput());
    }
    
    bool removeConfig(){
        return remove(_fileName.c_str()) == 0;
    }
    
    void closeConfigFile(){
        _configFile.close();
    }
    
    
#pragma endregion
    
#pragma region getters and setters
    
    string getUserInput(){
        string _temp;
        cin >> _temp;
        return _temp;
    }
    
    void setUserName(string name){
        _username = name;
    }
    
    void getUserName(){
        Messages::getInstance().printUserNameMessage();
        setUserName(getUserInput());
    }
    
    void setInputDirectory(string dir){
        _inputDir = dir;
    }
    
    void setOutputDirectory(string dir){
        _outputDir = dir;
    }
    
    void setFilePath(){
        _fileName = "/Users/" + _username + "/Desktop/jumo_accountancy_config.txt";
    }
    
#pragma endregion
    
    
public:
    
    /*
     
     Handles the execution of process args and searching / CRUD of the config file.
     
     */
    
    ConfigManager(int argc, const char * args[], bool *configSuccessful){
        
        _processArgs = new ProcessArgs(argc, args);
        
        if (_processArgs->getShouldReturn()){
            *configSuccessful = false;
            return;
        }
        
        Messages::getInstance().printInitConfigMessage();
        
        getUserName();
        setFilePath();
        
        if (configExists()){
            
            Messages::getInstance().printConfigFileFoundMessage();
            
            if (_processArgs->getReinit()){
                
                Messages::getInstance().printReinitMessage();
                closeConfigFile();
                
                if (removeConfig()){
                    
                    createConfigFile();
                    getConfigDirectories();
                    saveConfigDirectories();
                    
                } else {
                    
                    closeConfigFile();
                    *configSuccessful = false;
                    return;
                    
                }
                
            } else {
                
                loadConfig();
                
            }
            
        } else {
            
            Messages::getInstance().printNewConfigFileMessage();
            createConfigFile();
            getConfigDirectories();
            saveConfigDirectories();
            
        }
        
        delete _processArgs;
        *configSuccessful = true;
        closeConfigFile();
        
    }
    
#pragma region getters
    
    string getInputDirectory(){
        return _inputDir;
    }
    
    string getOutputDirectory(){
        return _outputDir;
    }
    
#pragma endregion
    
};


#endif /* ConfigManager_hpp */
