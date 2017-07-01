//
//  ICurrency.hpp
//  Jumo
//
//  Created by Wesley Schrauwen on 2017/06/30.
//  Copyright © 2017 Wesley. All rights reserved.
//

#ifndef ICurrency_hpp
#define ICurrency_hpp

#include <iostream>

/*
 Currency interface.
 
 Provides future expansion of firm by allowing for different currencies
 */
class ICurrency {
public:
    virtual ~ICurrency(){};
    virtual float getRandAmount(float) = 0;
};


class ZARCurrency : public ICurrency {
public:
    ~ZARCurrency(){};
    float getRandAmount(float amount){
        return amount;
    }
};

#endif /* ICurrency_hpp */
