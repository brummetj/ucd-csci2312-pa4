//
//  Resource.cpp
//  PA4
//
//  Created by Joshua Brummet on 4/5/16.
//  Copyright © 2016 C++. All rights reserved.
//
#include <string>
#include <iostream>
#include "Resource.h"
#include "Piece.h"
#include "Game.h"
#include "Agent.h"

namespace Gaming{
    
    
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;
    
    
    Resource::Resource(const Game&g, const Position&p, double capacity) : Piece(g,p), __capacity(capacity)
    {
        

        
    }
    
    Resource::~Resource()
    {
        
        
    }
    
    
    double Resource::consume()
    {
        finish();
        return __capacity;
    }
    
    void Resource::age()
    {
        
        __capacity -= RESOURCE_SPOIL_FACTOR;
        if (__capacity <= 0) finish();
        
        
    }
    ActionType Resource::takeTurn(const Surroundings &s) const
    {
        return STAY;
        
    }
    
    Piece &Resource::operator*(Piece &other )
    {
       
        return other.interact(this);
    }
    
    
    Piece &Resource::interact(Agent *other)
    {
        other->addEnergy(consume());
        return *this;
    }
    Piece &Resource::interact(Resource *p)
    {
        
        return *this;
    }
    
    
}























