//
//  Food.cpp
//  PA4
//
//  Created by Joshua Brummet on 4/5/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "Food.h"
#include <iostream>
#include <string>

namespace Gaming
{
    const char Food::FOOD_ID ='F';
    
    Food::Food(const Game&g, const Position &p, double capacity) : Resource(g,p,capacity)
    {
        
        __capacity = capacity;
    }
    
    Food::~Food()
    {
        
        
    }
   
  void Food::print(std::ostream &os) const
    {
        
        os << FOOD_ID << __id;
        
    }
    
    
    
}