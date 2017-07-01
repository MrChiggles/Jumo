//
//  Messages.hpp
//  Jumo
//
//  Created by Wesley Schrauwen on 2017/06/29.
//  Copyright © 2017 Wesley. All rights reserved.
//

#ifndef Messages_hpp
#define Messages_hpp

#include <iostream>
#include <vector>

using namespace std;

/*
 The messages class.
 
 Contains all console printed messages and globally accessible singleton.
 */
class Messages{
private:
    
    Messages(){};
    
public:
    
    // The Messages Class Singleton    
    static Messages& getInstance(){
        static Messages instance;
        return instance;
    }
    
    #pragma region UX - No Parameters messages
    
    void printInitMessage(){
        cout << "Resetting config file..." << endl;
    }
    
    void printInitConfigMessage(){
        cout << "Preparing to search for config file..." << endl;
    }
    
    void printReinitMessage(){
        cout << "Preparing to reinitialise config..." << endl;
    }
    
    void printConfigFileFoundMessage(){
        cout << "Config file found!" << endl;
    }
    
    void printNewConfigFileMessage(){
        cout    << "Could not find existing config file." << endl
                << "Setting up new config file..." << endl;
    }
    
    void printSetupSuccessful(){
        cout    << "Setup successful" << endl
                << "Tip: Enter -h for a list of commands" << endl;
    }
    
    void printListOfCommands(){
        cout    << "* - processes all files found in the input directory and outputs them to the output directory" <<   endl
                << "'filename' - processes the specified file into the output directory" << endl
                << "*average - prints the average sized loan based on all files found in the input directory" << endl
                << "average-'filename' - prints the average sized load for a particular file" << endl
                << "*total - prints the total of all loans found in the input directory" << endl
                << "total-'filename' - prints the total loans for a particular file" << endl
                << "*count - counts all loans in the input directory" << endl
                << "count-'filename - counts all the loans in a particular file" << endl
                << "-input - prints the current input directory" << endl
                << "-output - prints the current output directory" << endl
                << "-quit - exits the program" << endl
                << endl << "ALL Filename operations only accept .csv extensions" << endl;
    }
    
    void printFailedToStartProgram(){
        cout << "Failed to initialise program." << endl;
    }
    
    void printExiting(){
        cout << "Exiting..." << endl;
    }
    
    // Prints information about the program and its possible inputs
    void printHelpMessage(){
        cout    << "First time execution" << endl
        << "\tOn first time execution some setup will be required. " << endl
        << "\tYou will be required to set the:" << endl
        << "\t\t-- input directory (where input files are stored)" << endl
        << "\t\t-- output directory (where output files will be saved)" << endl
        << "'tThis process will create a jumo_accountancy_config.txt file where directory information will be   saved for future use" << endl
        << "\tTo reset the directory settings pass -init as a command line parameter." << endl
        << endl
        << "Required Inputs:" << endl
        << "\t--input file name" << endl
        << endl
        << "General:" << endl
        << "\tThe output file will always be named <input>_out" << endl
        << "\tTo exit: -q or -quit" << endl;
    }
    
    void printGettingAverageOfAllFiles(){
        cout << endl << "Getting average loan size from all files" << endl;
    }
    
    void printGettingAverageOfFile(){
        cout << endl << "Getting average loan size of file" << endl;
    }
    
    void printGettingTotalOfAllFiles(){
        cout << endl << "Getting loan total of all files" << endl;
    }
    
    void printGettingTotalOfFile(){
        cout << endl << "Getting loan total of file" << endl;
    }
    
    void printGettingLoanCountOfAllFiles(){
        cout << endl << "Getting loan count for all files" << endl;
    }
    
    void printGettingLoanCountOfFile(){
        cout << endl << "Getting loan count for file" << endl;
    }

    
    #pragma endregion
    
    #pragma region UX - Parameters
    
    void printProcessingAllFiles(string inputDir, string outputDir){
        cout    << endl << "Processing all files in: " << inputDir << endl
                << "Outputting to: " << outputDir << endl << endl;
    }
    
    void printProcessingFile(string file, string outputDir){
        cout    << endl << "Processing: " << file << endl
                << "Outputting to: " << outputDir << endl << endl;
    }
    
    void printCurrentOutputDirectory(string outputDir){
        cout << "Current output dir: " << outputDir << endl;
    }
    
    void printCurrentInputDirectory(string inputDir){
        cout << "Current input dir: " << inputDir << endl;
    }
    
    void printLoanTotal(float total){
        cout << "Loan total: " << total << endl;
    }
    
    void printLoanCount(int count){
        cout << "Loans counted: " << count << endl;
    }
    
    void printAverageLoanSize(float average){
        cout << "Average loan size: " << average << endl;
    }
    
    void printListOfFiles(vector<string> *fList){
        cout << endl << "Printing file list: " << endl;
        
        for (auto i : *fList){
            cout << "\t" << i << endl;
        }
        
    }
    
    #pragma endregion
    
    #pragma user input messages
    
    void printUserNameMessage(){
        cout << "Please enter your username:" << endl;
    }
    
    void printInputDirMessage(){
        cout << "Please enter the input file path directory:" << endl;
    }
    
    void printOutputDirMessage(){
        cout << "Please enter the output file path directory:" << endl;
    }
    
    void printCommandRequest(){
        cout << endl << "Please Enter Next Command.." << endl;
    }
    
    #pragma endregion
    
    #pragma region Error Messages
    
    // Prints arg error message
    void printUnrecognizedInputMessage(string arg){
        cout    << "Error - Unrecognized input arguement: " << arg << endl
                << "\tEnter -h for help" << endl;
    }
    
    void printUnrecognizedInputMessage(){
        cout << "Error - Unrecognized input" << endl;
    }
    
    void printTooManyInputsMessage(){
        cout    << "Error - Too Many Inputs" << endl;
    }
    
    #pragma endregion
    
};

#endif /* Messages_hpp */
