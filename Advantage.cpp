//
//  Advantage.cpp
//  PA4
//
//  Created by Joshua Brummet on 4/5/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "Advantage.h"
#include <iostream>
#include <string>
namespace Gaming
{

    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;
    const char Advantage::ADVANTAGE_ID = 'D';
    
    Advantage::Advantage(const Game &g, const Position &p,double capacity) : Resource(g,p,capacity)
    {
        __capacity = capacity *ADVANTAGE_MULT_FACTOR;
        
    }
    Advantage::~Advantage()
    {
        
        
    }
    void Advantage::print(std::ostream &os) const
    {
        os << ADVANTAGE_ID << __id;
    }
    double Advantage::getCapacity() const
    {
        
        return __capacity;
        
    }
    
    double Advantage::consume()
    {

        finish();
        return __capacity;
        
    }
    
}