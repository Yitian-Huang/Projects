#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include "solver.h"

using namespace std;

// To be completed
Solver::Solver(const Board& b, Heuristic *heur)
{
    b_=b;
    heur_=heur;
}

// To be completed
Solver::~Solver()
{
    MoveSet::iterator it;
    for(it=closelist.begin(); it!=closelist.end();++it)
    {
        delete *it;
    }
}

// To be completed
bool Solver::run()
{
    const Vehicle& ev = b_.escapeVehicle();
    int row = ev.startr;
    for(int i =ev.startc+ev.length; i<b_.size(); i++)
    {
        Vehicle::VID_T id = b_.at(row, i);
        if(id!='.')
        {
            const Vehicle& v = b_.vehicle(id);
            if(v.direction==Vehicle::HORIZONTAL)
                return false;
        }
    }
    Board* board = new Board(b_);
    Move* fmove = new Move(board);
    openlist.push(fmove);
    closelist.insert(fmove);
    while(!openlist.empty())
    {
        Move* mymove = openlist.top();
        openlist.pop();
        if(mymove->b->solved())
        {
            Move* temp = mymove;
            while(temp->prev!=nullptr)
            {
                solution_.push_back(temp->m);
                temp = temp->prev;
            }
            std::reverse(solution_.begin(), solution_.end());
            expansions_=closelist.size();
            return true;
        }
        else
        {
            Board::MovePairList potmoves = mymove->b->potentialMoves();
            for(unsigned int i=0; i< potmoves.size(); i++)
            {
                Board* nextboard = new Board(*(mymove->b));
                nextboard->move(potmoves[i].first,potmoves[i].second);
                Move* nextmove = new Move(potmoves[i], nextboard, mymove);
                nextmove->score(heur_);
                if(closelist.find(nextmove)==closelist.end())
                {
                    openlist.push(nextmove);
                    closelist.insert(nextmove);
                }
                else{
                    delete nextmove;
                }
            }
        }
    }
    // Avoid compiler warnings - replace this
    expansions_=closelist.size();
    return false;
}

// To be completed
Board::MovePairList Solver::solution() const
{
    // Avoid compiler warnings - replace this
    return solution_;
}

// Complete
size_t Solver::numExpansions() const
{
    return expansions_;
}
