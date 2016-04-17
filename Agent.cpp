//
//  Agent.cpp
//  PA4
//
//  Created by Joshua Brummet on 4/5/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "Agent.h"
#include "Piece.h"
#include "Game.h"
#include "Resource.h"
#include <iostream>
#include <string>

namespace Gaming
{

    const double Agent::AGENT_FATIGUE_RATE = 0.3;
    
    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g,p)
    {
        
        __energy = energy;
        
        
    }
    
    void Agent::age()
    {
        __energy -= AGENT_FATIGUE_RATE;
        
    }
    
    Agent::~Agent()
    {
        
        
    }
    Piece &Agent::operator*(Piece &other)
    {
        return other.interact(this);
    }
    
    Piece &Agent::interact(Agent *other)
    {
        
        if(__energy >= other->__energy)
            other->finish();
        
        if (__energy <= other->__energy)
            finish();
        
        return *this;
        
        
    }
    Piece &Agent::interact(Resource *R)
    {
        
        __energy += R->consume();
    
        return *this;
        
    }
    
    
}