//
//  Piece.cpp
//  PA4
//
//  Created by Joshua Brummet on 4/5/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include <iostream>
#include <string>
#include "Piece.h"



namespace Gaming
{
    
    unsigned int Piece::__idGen = 1000;

    
    Piece::Piece(const Game&g, const Position &p) : __game(g), __position(p)
    {
        __id = __idGen++;
        __finished = false;
        __turned = false;
        
    }
    Piece::~Piece()
    {
        
        
    }
    
    std::ostream &operator <<(std::ostream &os, const Piece &piece)
    {
        
        piece.print(os);
        return os;
        
    }



}
