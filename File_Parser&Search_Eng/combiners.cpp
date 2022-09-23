#include "searcheng.h"
#include "combiners.h"

// Complete the necessary code
WebPageSet AndWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet retval;
    std::set<WebPage*>::iterator itA;
    std::set<WebPage*>::iterator itB;
    for(itA=setA.begin(); itA!=setA.end();++itA)
    {
        itB=setB.find(*itA);
        if(itB!=setB.end())
            retval.insert(*itB);
    }
    return retval;
}

WebPageSet OrWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet retval;
    std::set<WebPage*>::iterator it;
    for(it=setA.begin(); it!=setA.end();++it)
    {
        retval.insert(*it);
    }
    for(it = setB.begin(); it!=setB.end();++it)
    {
        retval.insert(*it);
    }
    return retval;
}

WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet retval = setA;
    std::set<WebPage*>::iterator itA;
    std::set<WebPage*>::iterator itB;
    for(itA=setA.begin(); itA!=setA.end();++itA)
    {
        itB=setB.find(*itA);
        if(itB!=setB.end())
            retval.erase(*itA);
    }
    return retval;


}
