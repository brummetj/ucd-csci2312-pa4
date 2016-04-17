//
//  AggressiveAgentStrategy.cpp
//  PA4
//
//  Created by Joshua Brummet on 4/5/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "AggressiveAgentStrategy.h"
#include "Game.h"
#include <vector>
#include "DefaultAgentStrategy.h"

namespace Gaming
{
    
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;
    
    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
    {
        __agentEnergy = agentEnergy;
        
    }
    AggressiveAgentStrategy::~AggressiveAgentStrategy()
    {
        
        
    }
    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const
    {
        //Vectors to hold number ActionTypes to insert into surroundings for gameplay
        std::vector<int> Advantages, Food, Emptyspot, simple, strategy;
        
        //Giving starting position of agent.
        Position agentPos(1,1);
        
        Position newPos;
       
        //Adding the Number of Action types in the surroundings Array
        for(int i=0;i < s.array.size();i++)
        {
            switch (s.array[i])
            {
                case SIMPLE: simple.push_back(i);
                    break;
                case STRATEGIC: strategy.push_back(i);
                    break;
                case ADVANTAGE: Advantages.push_back(i);
                    break;
                case EMPTY: Emptyspot.push_back(i);
                    break;
                case FOOD: Food.push_back(i);
                    break;
                    
            }
            
        }
        
        //Inserting Action types with their Position.
        if(simple.size() > 0 && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)
        {
            newPos=Game::randomPosition(simple);
            return Game::reachSurroundings(agentPos,newPos);
        }
        else if(Advantages.size() > 0)
        {
            newPos=Game::randomPosition(Advantages);
            return Game::reachSurroundings(agentPos,newPos);
        }
        else if(Food.size() > 0)
        {
            newPos=Game::randomPosition(Food);
            return Game::reachSurroundings(agentPos,newPos);
        }

        else
            return STAY;
    }
    
    
}