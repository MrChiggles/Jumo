//
//  CommandProcessor.hpp
//  Jumo
//
//  Created by Wesley Schrauwen on 2017/07/01.
//  Copyright © 2017 Wesley. All rights reserved.
//

#ifndef CommandProcessor_hpp
#define CommandProcessor_hpp

#include <iostream>
#include <map>
#include <vector>
#include "ConfigManager.hpp"
#include <sstream>
#include "ICurrency.hpp"

class CommandProcessor {
private:
    
    ICurrency *currency;
    ConfigManager *configManager;
    vector<string> fileKeys;
    map<string, int> loanCount;
    map<string, float> loanTotal;
    
    // string splitter
    vector<string> split(string s, char delim){
        
        stringstream ss(s);
        string temp;
        vector<string> dVector;
        
        while(getline(ss, temp, delim)){
            dVector.push_back(temp);
        }
        
        return dVector;
        
    };
    
#pragma region getters and setters
    
    void getFileContents(vector<string> *fList){
        for (auto i : *fList){
            getFileContents(&i);
        }
    }
    
    /*
     Puts all file contents into their respective variables
     */
    void getFileContents(string *f){
        
        ifstream file(configManager->getInputDirectory() + *f);
        string line;
        vector<string> csv;
        
        while(getline(file, line)){
            
            csv = split(line, ',');
            string key = createFileKey(csv);
            setFileKey(key);
            increaseLoanCount(key);
            increaseLoanTotal(key, getLoanAmount(csv));
            
        }
        
        file.close();
        
    }
    
    void setFileKey(string key){
        
        for (auto i : fileKeys){
            if (key == i) return;
        }
        
        fileKeys.push_back(key);
        
    }
    
    string createFileKey(vector<string> csv){
        return csv[1] + "," + csv[3] + "," + getMonth(csv[2]);
    }
    
    string getMonth(string date){
        return split(date, '-')[1];
    }
    
    float getLoanAmount(vector<string> csv){
        return stof(csv[4]);
    }
    
    float getLoanCount(){
        
        int sum = 0;
        
        for (auto i : loanCount){
            sum += i.second;
        }
        
        return sum;
        
    }
    
    float getLoanTotal(){
        
        float sum = 0;
        
        for (auto i : loanTotal){
            sum += i.second;
        }
        
        return sum;
        
    }
    
#pragma endregion
    
    void increaseLoanCount(string key){
        loanCount[key]++;
    }
    
    void increaseLoanTotal(string key, float amount){
        loanTotal[key]+=currency->getRandAmount(amount);
    }
    
    void clearContent(){
        loanCount.clear();
        loanTotal.clear();
        fileKeys.clear();
    }
    
    void writeContentToFile(string *f){
        ofstream file(configManager->getOutputDirectory() + *f);
        
        for (auto i : fileKeys){
            
            stringstream ss;
            
            ss << i << ", Loan Count " << loanCount[i] << ", Total " << loanTotal[i] << "\n";
            
            file << ss.str();
            
        }
        
        file.close();
        
    }
    
    void _printLoanTotals(){
        float total = getLoanTotal();
        Messages::getInstance().printLoanTotal(total);
        clearContent();
    }
    
    void _printLoanCount(){
        float total = getLoanCount();
        Messages::getInstance().printLoanCount(total);
        clearContent();
    }
    
    void _printLoanAverage(){
        float loanTotal = getLoanTotal();
        float loanCount = float(getLoanCount());
        
        Messages::getInstance().printAverageLoanSize(loanTotal / loanCount);
        clearContent();
    }
    
public:
    
    CommandProcessor(ConfigManager *configManager, ICurrency *currency): configManager(configManager), currency(currency){};
    
    void outputFile(vector<string> *fList){
        
        for (auto f : *fList){
            outputFile(&f);
        }
        
    }
    
    void outputFile(string *file){
        
        getFileContents(file);
        writeContentToFile(file);
        clearContent();
        
    }
    
    void printLoanTotals(vector<string> *fList){
        
        getFileContents(fList);
        _printLoanTotals();
        
    }
    
    void printLoanTotals(string *file){
        
        getFileContents(file);
        _printLoanTotals();
        
    }
    
    void printLoanCount(vector<string> *fList){
        
        getFileContents(fList);
        _printLoanCount();
        
    }
    
    void printLoanCount(string *file){
        
        
        getFileContents(file);
        _printLoanCount();
        
    }
    
    void printLoanAverage(vector<string> *fList){
        
        getFileContents(fList);
        _printLoanAverage();
        
    }
    
    void printLoanAverage(string *file){
        
        getFileContents(file);
        _printLoanAverage();
        
    }
    
};

#endif /* CommandProcessor_hpp */
