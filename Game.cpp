//
//  Game.cpp
//  PA4
//
//  Created by Joshua Brummet on 4/5/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "Game.h"
#include "Gaming.h"
#include "Piece.h"
#include "Simple.h"
#include "Agent.h"
#include "Resource.h"
#include "Strategic.h"
#include "Advantage.h"
#include "Food.h"

#include <iomanip>

namespace Gaming
{
    const unsigned int Game::NUM_INIT_AGENT_FACTOR =4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR =2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;
    PositionRandomizer Game::__posRandomizer = PositionRandomizer();
    
void Game::populate()
    {
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);
        
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;
        
        
        while (numStrategic > 0)
        {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr)
            { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }
        
        while (numSimple > 0)
        {
            int i = d(gen); 
            if (__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple --;
            }
        }

        while (numAdvantages > 0)
        {
            int i = d(gen); 
            if (__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages --;
            }
        }
        
        while (numFoods > 0)
        {
            int i = d(gen);
            if (__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods --;
            }
        }
        
        
        
    }
    
//constructor,copy constucter, overloaded constucter
Game::Game() : Game(3,3)
    {
        
    }
    
Game::Game(unsigned width, unsigned height, bool manual) :
    __grid(width*height,nullptr),
    __round(0),
    __status(NOT_STARTED)
    {
        
        __width = width;
        __height = height;
        __numInitAgents = (__width * __height) /NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) /NUM_INIT_RESOURCE_FACTOR;
        __verbose = false;
        
        if (width < MIN_WIDTH || height < MIN_HEIGHT)
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
       
        
        if (! manual) void populate();
        
    }
Game::~Game()
    {
      
        
    }
//getters
unsigned int Game::getNumPieces() const
    {
        unsigned int numPieces = 0;
        
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            if (*it != nullptr)
                numPieces++;
            
        }
        
        return numPieces;
    }
    
unsigned int Game::getNumAgents() const
    {
        unsigned int numAgents = 0;
        
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Agent *agent = dynamic_cast<Agent*>(*it);
            if (agent) numAgents ++;
        }
        
        return numAgents;
    }
    
    
unsigned int Game::getNumSimple() const
    {
        unsigned int numAgents = 0;
        
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Simple *simple = dynamic_cast<Simple*>(*it);
            if (simple) numAgents ++;
        }
        return numAgents;
    }
    
    
unsigned int Game::getNumStrategic() const
    {
        unsigned int numAgents = 0;
        
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Strategic *strategic = dynamic_cast<Strategic*>(*it);
            if (strategic) numAgents ++;
        }
        
        return numAgents;
    }
    
unsigned int Game::getNumResources() const
    {
        unsigned int numResources = 0;
        
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            Resource *resource = dynamic_cast<Resource*>(*it);
            if (resource) numResources ++;
        }
        
        return numResources;
    }
    
const Piece *Game::getPiece(unsigned int x, unsigned int y) const
    {
        
        int place = x *__width +y;
        
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);
        
        if (__grid[place] == nullptr)
            throw PositionEmptyEx(x, y);
        
        return __grid[place];
        
        
    }
//grid population methods
void Game::addSimple(const Position &position)
    {
        int place = position.y + position.x * __width;
        
        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        
        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);
        
        __grid[place] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }
    
void Game::addSimple(const Position &position, double energy)
    {
        
        int place = position.y + position.x * __width;
        
        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        
        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);
        
        __grid[place] = new Simple(*this, position, energy);
    }
    
void Game::addSimple(unsigned x, unsigned y)
    {
        int place = y + x * __width;
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);
        
        if (__grid[place])
            throw PositionNonemptyEx(x, y);
        
        __grid[place] = new Simple(*this, Position(x, y), STARTING_AGENT_ENERGY);
    }
    
void Game::addSimple(unsigned y, unsigned x, double energy)
    {
        int place = y + x * __width;
        
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);
        
        if (__grid[place])
            throw PositionNonemptyEx(x, y);
        
        __grid[place] = new Simple(*this, Position(x, y), energy);
    }
    
void Game::addStrategic(const Position &position, Strategy *s)
    {
        int place = position.y + position.x * __width;
        
        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        
        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);
        
        __grid[place] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }
    
void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        int place = y + x * __width;
        
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);
        
        if (__grid[place])
            throw PositionNonemptyEx(x, y);
        
        __grid[place] = new Strategic(*this, Position(x, y), STARTING_AGENT_ENERGY, s);
    }
    
void Game::addFood(const Position &position)
    {
        int place = position.y + position.x * __width;
        
        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        
        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);
        
        __grid[place] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    
void Game::addFood(unsigned x, unsigned y)
    {
        int place = y + x * __width;
        
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);
        
        if (__grid[place])
            throw PositionNonemptyEx(x, y);
        
        __grid[place] = new Food(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
    }
    
void Game::addAdvantage(const Position &position)
    {
        int place = position.y + position.x * __width;
        
        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        
        if (__grid[place])
            throw PositionNonemptyEx(position.x, position.y);
        
        __grid[place] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    
void Game::addAdvantage(unsigned x, unsigned y)
    {
        int place = y + (x * __width);
        
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);
        
        if (__grid[place])
            throw PositionNonemptyEx(x, y);
        
        __grid[place] = new Advantage(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings Sur;
        unsigned int x,y;
        unsigned int i = 0;
        
        // Checks surrounding from a piece using grid from -1 -> 1. returns the surroundings of a peice.
        for (int row =-1; row <=1; ++row)
        {
            x = pos.x+row;
            for (int col =-1; col <=1; ++col)
            {
                y=pos.y+col;
                
                if( x>=__height || y >=__width)
                {
                    Sur.array[i] = INACCESSIBLE;
                    i++;
                }
                else if(__grid[x*__width+y]== nullptr)
                {
                    Sur.array[i] = EMPTY;
                    i++;
                }
                else
                {
                    Sur.array[i]=getPiece(x,y)->getType();
                    i++;
                }
            }
        }
        Sur.array[4]=SELF;
        return Sur;
    }
    
    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {
        ActionType Move = STAY;
        unsigned int x,y;
        
        
        //Moving the piece a certain surrounding depending on position, returing the actiontype.
        x = (from.x - to.x);
        y = (from.y - to.y);
        
        if(x ==1 && y ==1)
            return Move = NW;
        
        else if(x ==1 && y ==0)
            return Move = N;
        
        else if(x ==1 && y ==-1)
            return Move = NE;
        
        else if(x ==0 && y ==-1)
            return Move = E;
        
        else if(x ==-1 && y ==-1)
            return Move = SE;
        
        else if(x ==-1 && y ==0)
            return Move = S;
        
        else if(x ==-1 && y ==1)
            return Move = SW;
        
        else if(x ==0 && y ==1)
            return Move = W;
        
        return Move;
    }
    
    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        int x = pos.x, y = pos.y;
        
        switch(ac)
        { //each case makes sure your move stays legal.
            case NW: x--; y--;
                break;
            case N: x--;
                break;
            case NE: x--; y++;
                break;
            case W: y--;
                break;
            case STAY:
                return true;
            case E: y++;
                break;
            case SW: x++; y--;
                break;
            case S: x++;
                break;
            case SE: x++; y++;
                break;
        }
        return (x >= 0 && x < __height && y >= 0 && y < __width);
    }
const Position Game::move(const Position &pos, const ActionType &ac) const
    {
            //make sure its a legal action.
        if(!isLegal(ac, pos))
            return pos;
        int x = pos.x, y = pos.y;
        switch(ac)
        { //each case is the position in the surroundings array.
            case NW: x--; y--;
                break;
            case N: x--;
                break;
            case NE: x--; y++;
                break;
            case W: y--;
                break;
            case STAY:
                return pos; //don't change the position
            case E: y++;
                break;
            case SW: x++; y--;
                break;
            case S: x++;
                break;
            case SE: x++; y++;
                break;
        }
        return Position(x,y);
        
    }
void Game::round()
    {
       
        __status = PLAYING;
        ActionType ac;
        Position pos;
        
        for(int i =0; i<__grid.size(); ++i)
        {
            
            if(__grid[i]!= nullptr && ! __grid[i]->getTurned())
            {
                __grid[i]->setTurned(true);
                
                //Moving pieces and getting the surroundings during each round.
                ac = __grid[i]->takeTurn(getSurroundings(__grid[i]->getPosition()));
                
                pos = move(__grid[i]->getPosition(), ac);
                int place = pos.x * __width + pos.y;
            
                //If theres a piece on the grid check to see if its a valid piece, then move te piece to the correct pos.
                // If piece is valid, delete it then replace it with the other piece.
                if (__grid[place] != nullptr)
                {
                    __grid[i]->operator*(*(__grid[place]));
                    
                    if (__grid[i]->isViable())
                    {

                        delete __grid[place];
                        __grid[place] = __grid[i];
                        __grid[i]->setPosition(pos);
                        __grid[i] = nullptr;
                    }
                    else if (__grid[place]->isViable())
                    {
        
                        delete __grid[i];
                        __grid[i] = nullptr;
                     
                    }
                    else
                    {
                        delete __grid[place];
                        delete __grid[i];
                        __grid[place]=nullptr;
                        __grid[i]=nullptr;
                    }
                }
                
            else
                {
                __grid[i]->setPosition(pos);
                __grid[place] = __grid[i];
                __grid[i] = nullptr;
                    
                }
            }
        }
        
        //Aging pieces and deleting pieces on the grid for end of round.
        for(int i = 0; i < __grid.size(); ++i)
            if(__grid[i] != NULL)
            {
                __grid[i]->setTurned(false);
                __grid[i]->age();
                
                if(!__grid[i]->isViable())
                {
                    delete __grid[i];
                    __grid[i] = NULL;
                }
            }
        __round++;
   
    }
void Game::play(bool verbose)
    {
        
        while(getNumResources() > 0 && getNumPieces() > 1)
            round();
        
    }
std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        
        os  << "Round " << game.getRound() << std::endl;
        
        for (int i = 0; i < game.__height; ++i)
        {
            for (int j = 0; j < game.__width; ++j)
            {
                if (game.__grid[j + (i * (game.__width - 1))] == nullptr)
                    
                    os << "[     ]";
                
                else
                    os << std::setw(5) << game.__grid[j + (i * (game.__width - 1))] << "]";
            }
            os << std::endl;
        }
        os << "Status: " << game.getStatus() << std::endl;
   
        switch(game.__status) {
            case (0):
                os << "Not Started";
                break;
            case (1):
                os << "Playing...";
                break;
            case (2):
                os << "Over!";
                break;
        }
        os<<std::endl<<std::endl;
        
        
        return os;
    }
    
}