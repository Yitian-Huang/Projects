#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;

// To be completed
void MDParser::parse(std::istream& istr, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // Complete your code below
    string term ="";
    string link ="";
    char c = istr.get();
    while(!istr.fail())
    {
        if(!isalnum(c))
        {
            insert_(allSearchableTerms, term);
            if(c=='[')//LINKTEXT
            {
                c = istr.get();
                while(!istr.fail()&&c!=']')
                {
                    if(!isalnum(c))
                    {
                        insert_(allSearchableTerms, term);
                    }
                    else
                        term +=c;

                    c = istr.get();
                }
                c = istr.get();//ISLINK
                if(c=='[')
                    continue;
                else if(c=='(')//LINKURL
                {
                    link = "";
                    c = istr.get();
                    while(!istr.fail()&&c!=')')
                    {
                        link+=c;
                        c = istr.get();
                    }
                    insert_(allOutgoingLinks, link);
                    continue;
                }
            }
        }
        else{
            term+=c;
        }
        c = istr.get();
    }
    insert_(allSearchableTerms, term);
}

// To be completed
std::string MDParser::display_text(std::istream& istr)
{
    string retval;
    char c = istr.get();
    while(!istr.fail())
    {
        if(c=='[')
        {
            retval+=c;
            c = istr.get();
            while(!istr.fail()&&c!=']')
            {
                retval+=c;
                c = istr.get();
            }
            retval+=c;
            c = istr.get();
            if(c == '(')
            {
                while(!istr.fail()&&c!=')')
                {
                    c = istr.get();
                }
                c = istr.get();
            }
        }
        else
        {
            retval+=c;
            c = istr.get();
        }
    }

    return retval;
}
void  MDParser::insert_(std::set<std::string>& SearchableTerms, std::string& term_)
{
    if(term_!= "")
    {
        term_ = conv_to_lower(term_);
        SearchableTerms.insert(term_);
        term_ = "";
    }

}



