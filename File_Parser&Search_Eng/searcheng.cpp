#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;

// Helper function that will extract the extension of a filename
std::string extract_extension(const std::string& filename);

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}


// To be updated as needed 
SearchEng::SearchEng()
{

}

// To be completed
SearchEng::~SearchEng()
{
    std::map<std::string, WebPage*>::iterator it1;
    std::map<std::string, PageParser*>::iterator it2;
    for(it1 = pages_.begin(); it1!= pages_.end();++it1)
    {
        delete it1->second;
    }
    for(it2 = parsers_.begin(); it2!= parsers_.end();++it2)
    {
        delete it2->second;
    }

}

// Complete
void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
    if (parsers_.find(extension) != parsers_.end())
    {
        throw std::invalid_argument("parser for provided extension already exists");
    }
    parsers_.insert(make_pair(extension, parser));
}

// Complete
void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

// To be completed
void SearchEng::read_page(const string& filename)
{
    string ext = extract_extension(filename);
    if (parsers_.find(ext) == parsers_.end())
    {
        throw std::logic_error("No parser registered for given file");
    }
    ifstream ifile(filename);
    if(ifile.fail())
    {
        throw std::invalid_argument("Can't open the file");
    }
    WebPage* page ;
    if(pages_.find(filename)==pages_.end())
    {
        pages_.insert(make_pair(filename, new WebPage(filename)));
    }
    page = pages_.find(filename)->second;

    StringSet searchableterm;
    StringSet outlink;
    parsers_.find(ext)->second->parse(ifile, searchableterm, outlink);
    page->all_terms(searchableterm);
    StringSet::iterator string_set_it;
    std::map<std::string, WebPage*>::iterator it;
    for(string_set_it=outlink.begin(); string_set_it!=outlink.end(); ++string_set_it)
    {
        it = pages_.find(*string_set_it);
        if(it==pages_.end())
        {
            pages_.insert(make_pair(*string_set_it, new WebPage(*string_set_it)));
            it = pages_.find(*string_set_it);
        }
        it->second->add_incoming_link(page);
        page->add_outgoing_link(it->second);
    }
    WebPageSet pages;
    for(string_set_it = searchableterm.begin(); string_set_it != searchableterm.end(); ++string_set_it)
    {
        if(terms_.find(*string_set_it)==terms_.end())
        {
            terms_.insert(make_pair(*string_set_it, pages));
        }
        terms_.find(*string_set_it)->second.insert(page);
    }
    
}

// To be completed
WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
    if(pages_.find(page_name)==pages_.end())
        return nullptr;
    return pages_.find(page_name)->second;
}

// To be completed
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
    string ext = extract_extension(page_name);
    if (parsers_.find(ext) == parsers_.end())
    {
        throw std::logic_error("No parser registered for given file");
    }
    ifstream ifile(page_name);
    if(ifile.fail())
    {
        throw std::invalid_argument("Can't open the file");
    }
    ostr<<parsers_.find(ext)->second->display_text(ifile);

}

// To be completed
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
    WebPageSet retval;
    int index = 0;
    std::map<std::string, WebPageSet>::const_iterator it;
    unsigned int i;
    for(i=0; i<terms.size();++i)
    {
        it = terms_.find(terms[i]);
        if(it!=terms_.end()&&index==0)
        {
            retval = it->second;
            index++;
        }
        else if(it!=terms_.end()&&index==1)
        {
            retval = combiner->combine(retval,it->second );
            index++;
            break;
        }
    }
    if(index<=1)
        return retval;
    for(; i<terms.size();++i)
    {
        it = terms_.find(terms[i]);
        if(it!=terms_.end())
        {
            retval = combiner->combine(retval, it->second);
        }
        
    }
    return retval;
}

// Add private helper function implementations here

