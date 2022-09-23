#include <cmath>
#include "heur.h"
#include <vector>
#include <set>
using namespace std;

// Complete
size_t BFSHeuristic::compute(const Board& b)
{
    return 0U;
}


// To be completed
size_t DirectHeuristic::compute(const Board& b)
{
    const Vehicle& v = b.escapeVehicle();
    int row = v.startr;
    set<char> ids;
    int i;
    for(i =0; i< b.size(); i++)
    {
        if(b.at(row,i)=='a')
        {
            i+=2;
            break;
        }
    }
    for( ; i< b.size(); i++)
    {
        if(b.at(row, i)!='.')
            ids.insert(b.at(row, i));
    }

    // Avoid compiler warnings -- replace this
    return ids.size();
}

// To be completed
size_t IndirectHeuristic::compute(const Board& b)
{
    const Vehicle& v = b.escapeVehicle();
    int row = v.startr;
    set<char> ids;
    set<char> ids2;
    set<char>::iterator it;
    int i;
    int retval;
    for(i =0; i< b.size(); i++)
    {
        if(b.at(row,i)=='a')
        {
            i+=2;
            break;
        }
    }
    for( ; i< b.size(); i++)
    {
        if(b.at(row, i)!='.')
            ids.insert(b.at(row, i));
    }
    retval = ids.size();
    for(it = ids.begin(); it!=ids.end(); ++it)
    {
        const Vehicle& dbv = b.vehicle(*it);
        int up, down;
        up = -(dbv.startr+dbv.length-row);
        down = row - dbv.startr+1;
        if(b.isLegalMove(*it, down)&&b.isLegalMove(*it, up))
            continue;
        else if(dbv.startr+up<0&&!(dbv.startr+dbv.length+down>b.size()))
        {
            if(!b.isLegalMove(*it, down))
            {
                for(int i=(dbv.startr+dbv.length); i<b.size();i++)
                {
                    char x = b.at(i, dbv.startc);
                    if(x!='.')
                    {
                        ids2.insert(x);
                        break;
                    }
                }
            }
        }
        else if(dbv.startr+dbv.length+down>b.size()&&!(dbv.startr+up<0))
        {
            if(!b.isLegalMove(*it, up))
            {
                for(int i=dbv.startr-1; i>=0;i--)
                {
                    char x = b.at(i, dbv.startc);
                    if(x!='.')
                    {
                        ids2.insert(x);
                        break;
                    }
                }
            }
        }
    }
    retval+=ids2.size();
    // Avoid compiler warnings -- replace this
    return retval;
}

