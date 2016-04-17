//
//  Simple.cpp
//  PA4
//
//  Created by Joshua Brummet on 4/5/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "Simple.h"

namespace Gaming
{
    
    const char Simple::SIMPLE_ID = 'S';
    
    Simple::Simple(const Game &g, const Position &p, double energy) :Agent(g,p,energy)
    {
        __energy = energy;
        
    }
    Simple::~Simple()
    {
        
        
    }
    
    void Simple::print(std::ostream &os) const
    {
        os << SIMPLE_ID << __id;
    }
    
    ActionType Simple::takeTurn(const Surroundings &s) const
    {
        std::vector<int> Resources, Empty;
     
        Position newPos;
        Position newPos1(1,1);
     
        
        for(int i=0; i < s.array.size(); ++i)
        {
            if (s.array[i] == FOOD || s.array[i] == ADVANTAGE)
                Resources.push_back(i);
            
            else if(s.array[i]==EMPTY)
                Empty.push_back(i);
            
        }
        
        if(Resources.size()>0)
        {
            newPos = Game::randomPosition(Resources);
            return __game.reachSurroundings(newPos1,newPos);
        }
        else if(Empty.size()>0)
        {
            newPos = Game::randomPosition(Empty);
            return __game.reachSurroundings(newPos1, newPos);
        }
        else
            return STAY;
    }
    
    
}