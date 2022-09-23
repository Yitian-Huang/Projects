#include "move.h"


// Complete
Move::Move(Board* board)
{
    m.first = Vehicle::INVALID_ID;
    m.second = 0;
    b = board;
    g = 0;
    h = 0;
    prev = NULL;
}

// To be completed
Move::Move(const Board::MovePair& move, Board* board,  Move *parent)
{
    m=move;
    b=board;
    prev=parent;
    g=(parent->g)+1;
    h=0;

}

// To be completed
Move::~Move()
{
    delete b;
}

// To be completed
bool Move::operator<(const Move& rhs) const
{
    if((g+h)<(rhs.g+rhs.h))
        return true;
    else if(((g+h)==(rhs.g+rhs.h))&&(h<rhs.h))
        return true;
    else if(((g+h)==(rhs.g+rhs.h))&&(h<rhs.h)&&*this<rhs)
        return true;
    else 
        return false;
    // Replace this
    
}

// To be completed
void Move::score(Heuristic *heur) 
{
    h = heur->compute(*b);

}
