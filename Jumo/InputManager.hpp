//
//  InputManager.hpp
//  Jumo
//
//  Created by Wesley Schrauwen on 2017/06/30.
//  Copyright © 2017 Wesley. All rights reserved.
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include <iostream>
#include <dirent.h>
#include "ConfigManager.hpp"
#include "ICurrency.hpp"
#include "CommandProcessor.hpp"
#include <vector>
#include <regex>

class InputManager {
private:
    
    vector<string> fileList;
    ConfigManager *configManager;
    bool *shouldContinue;
    ICurrency *currency;
    CommandProcessor *commandProcessor;
    
    // lists all input files for a particular directory
    void listInputFiles(){
        DIR *dir = opendir(configManager->getInputDirectory().c_str());
        struct dirent *dp;
        
        while ((dp = readdir(dir)) != NULL){
            
            if (string(dp->d_name).find(".csv") != string::npos){
                fileList.push_back(dp->d_name);
            }
            
        }
        
        closedir(dir);
        
    }
    
    /* 
     Removes any non alphanumeric, period or underscore input parameters
     Eg: removes arrow_up, $, #.
     */
    void parseInput(string *input){
        regex expression("[^a-zA-Z0-9_.-]+");
        stringstream ss;
        
        regex_replace(ostream_iterator<char>(ss), input->begin(), input->end(), expression, "");
        
        *input =  ss.str();
    }
    
    /*
     Sets the parameter to the file name
     Searches between the first dash and last period of a string for the file name
     */
    void getFileName(string *input){
        // Add one so that first dash is non-inclusive        
        uint firstDash = uint(input->find_first_of('-'))+1;
        uint lastPeriod = uint(input->find_last_of('.'));
        
        *input = input->substr(firstDash, lastPeriod-firstDash) + ".csv";
    }
    
public:
    
    InputManager(ConfigManager *manager, bool *shouldContinue): configManager(manager), shouldContinue(shouldContinue){
        
        *shouldContinue = true;
        currency = new ZARCurrency();
        commandProcessor = new CommandProcessor(manager, currency);
        
        listInputFiles();
        
    }
    
    ~InputManager(){
        delete currency;
        delete commandProcessor;
    };
    
    void processInput(string *input){
        
            // exits the program
        if (*input == "-q" || *input == "-quit"){
            
            *shouldContinue = false;
            Messages::getInstance().printExiting();
            
            // processes all input files in a directory
        } else if (*input == "*") {
            
            Messages::getInstance().printProcessingAllFiles(configManager->getInputDirectory(), configManager->getOutputDirectory());
            commandProcessor->outputFile(&fileList);

            // prints the average size of all loans
        } else if(*input == "*average"){
            
            Messages::getInstance().printGettingAverageOfAllFiles();
            commandProcessor->printLoanAverage(&fileList);
            
            // prints the total of all loans
        } else if(*input == "*total"){
            
            Messages::getInstance().printGettingTotalOfAllFiles();
            commandProcessor->printLoanTotals(&fileList);
            
            // prints the loan count across all files
        } else if(*input == "*count"){
            
            Messages::getInstance().printGettingLoanCountOfAllFiles();
            commandProcessor->printLoanCount(&fileList);
        
            // prints the average size of loans in a file
        } else if(input->find("average-") != string::npos && input->find(".csv") != string::npos){
            
            
            getFileName(input);
            parseInput(input);
            
            cout << *input << endl;
        
            Messages::getInstance().printGettingAverageOfFile();
            commandProcessor->printLoanAverage(input);
            
            // prints the total of loans in a file
        } else if(input->find("total-") != string::npos && input->find(".csv") != string::npos){
            
            getFileName(input);
            parseInput(input);
            
            Messages::getInstance().printGettingTotalOfFile();
            commandProcessor->printLoanTotals(input);
            
            // prints the number of loans in a file
        } else if(input->find("count-") != string::npos && input->find(".csv") != string::npos){
            
            getFileName(input);
            parseInput(input);
            
            Messages::getInstance().printGettingLoanCountOfFile();
            commandProcessor->printLoanCount(input);
            
            // process a single input file
        } else if (input->find(".csv") != string::npos){
            
            parseInput(input);
            Messages::getInstance().printProcessingFile(*input, configManager->getOutputDirectory());
            commandProcessor->outputFile(input);
        
            // prints the current input directory
        } else if (*input == "-input"){
            
            Messages::getInstance().printCurrentInputDirectory(configManager->getInputDirectory());
            
            // prints the current output directory
        } else if (*input == "-output"){
            
            Messages::getInstance().printCurrentOutputDirectory(configManager->getOutputDirectory());
            
        } else if (*input == "-list") {
            
            Messages::getInstance().printListOfFiles(&fileList);
        
            // prints command list
        } else if (*input == "-h") {
        
            Messages::getInstance().printListOfCommands();
        
            // prints input error
        } else {
            
            Messages::getInstance().printUnrecognizedInputMessage();
            
        }
        
    }
    
    string getUserInput(){
        string temp;
        cin >> temp;
        return temp;
    }
    
    void setCurrency(ICurrency *currency){
        this->currency = currency;
    }
    
};

#endif /* InputManager_hpp */
