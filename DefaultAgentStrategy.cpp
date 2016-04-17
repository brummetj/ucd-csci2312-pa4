//
//  DefaultAgentStrategy.cpp
//  PA4
//
//  Created by Joshua Brummet on 4/5/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "DefaultAgentStrategy.h"
#include "Strategic.h"
#include <vector>
namespace Gaming
{
    
    DefaultAgentStrategy::DefaultAgentStrategy() : Strategy()
    {
        
    
    }
    DefaultAgentStrategy::~DefaultAgentStrategy()
    {
        
        
    }
    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
         //Vectors to hold number ActionTypes to insert into surroundings for gameplay
        std::vector<int> Advantages , Food, Empty, simple;

        Position agentPos(1,1);

        PositionRandomizer Pos;
        Position newPos;
        
        //Adding the Number of Action types in the surroundings Array 
        for(int i=0;i < s.array.size();i++)
        {
            switch (s.array[i])
            {
                case SIMPLE: simple.push_back(i);
                    break;
                case ADVANTAGE: Advantages.push_back(i);
                    break;
                case EMPTY: Empty.push_back(i);
                    break;
                case FOOD: Food.push_back(i);
                    break;
                    
            }
        
            
        }
    
         //Inserting Action types with their Position.
        if(simple.size() > 0)
        {
            newPos = Game::randomPosition(simple);
            return Game::reachSurroundings(agentPos,newPos);
        }
        else if(Advantages.size() > 0)
        {
            newPos = Game::randomPosition(Advantages);
            return Game::reachSurroundings(agentPos,newPos);
        }
        else if(Food.size() > 0)
        {
            newPos = Game::randomPosition(Food);
            return Game::reachSurroundings(agentPos,newPos);
        }
        
        else
            return STAY;
    }
    
    
    
}

