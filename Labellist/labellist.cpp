#include "labellist.h"
#include <cassert>

// Complete - Do not alter
LabelList::MsgNode::MsgNode(const MsgType& msg)
    : msg_(msg)
{
    // Every message is part of the "all" (index 0) label
    labelled_.push_back(true);
    next_.push_back(nullptr);
    prev_.push_back(nullptr);
}


// Complete - Do not alter
LabelList::MsgToken::MsgToken()
 : node_(nullptr), list_(nullptr)
{
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::MsgToken(MsgNode* node, LabelList* list)
// Add any initializers here
: node_(node), list_(list)
{

}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::MsgToken::operator==(const MsgToken& rhs) const
{
    if((list_==rhs.list_)&&(node_==rhs.node_))
    {
        return true;
    }
    else if(node_==rhs.node_&&node_==nullptr)
        return true;
    return false;
}


// Complete - Do not alter
bool LabelList::MsgToken::operator!=(const MsgToken& rhs) const
{
    return !operator==(rhs);
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::operator bool() const
{
    if(node_==nullptr)
        return false;
    return true;
}

// Complete - Do not alter
bool LabelList::MsgToken::isValid() const
{
    return this->node_ != nullptr;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::next(const LabelType& label)
{
    // Add your code here
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->next_[index];
    // Should return reference to self
    return *this;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::prev(const LabelType& label)
{
    // Add your code here
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->prev_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(const LabelType& label) const
{
    size_t index = this->list_->findLabelIndex(label);
    return isLabelMember(index);
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(size_t index) const
{
    return this->isValid() && 
            index != INVALID_LABEL &&
            index < this->node_->labelled_.size() &&
            this->node_->labelled_[index] ;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType const & LabelList::MsgToken::msg() const
{
    if(!this->isValid())
        throw std::logic_error("");
    return node_ -> msg_;
}
// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType& LabelList::MsgToken::msg() 
{
    if(!this->isValid())
        throw std::logic_error("");
    return node_ -> msg_;
}

// To be completed - must adhere to any requirements in the .h file
std::ostream& operator<<(std::ostream& ostr, const LabelList::MsgToken& token)
{
    if(token.isValid())
    {
        ostr << token.node_->msg_;
    }
    return ostr;
}

// Static constant 
const LabelList::MsgToken LabelList::end_(nullptr, nullptr);

// To be completed - must adhere to any requirements in the .h file
LabelList::LabelList() 
// Add any initializers here
{
    heads_.push_back(nullptr);
    labels_.push_back("all");
    tail_=nullptr;
    x=0;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::~LabelList()
{   
    while(tail_!= nullptr)
    {
        if(tail_->prev_[0]==nullptr)
        {
            delete tail_;
            break;
        }
        MsgNode* temp =tail_;
        tail_ = tail_->prev_[0];
        delete temp;
    }

}

// To be completed - must adhere to any requirements in the .h file
void LabelList::clear()
{
    while(tail_!= nullptr)
    {
        if(tail_->prev_[0]==nullptr)
        {
            delete tail_;
            break;
        }
        tail_ = tail_->prev_[0];
        delete tail_->next_[0];
    }
    tail_ = nullptr;
    for(unsigned int i=0; i<heads_.size();i++)
    {
        heads_[i] = nullptr;
    }


}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::empty() const
{
    if(heads_[0]==nullptr)
        return true;
    return false;

}

// Complete
size_t LabelList::size() const
{
    MsgNode* n = this->heads_[0];
    size_t cnt = 0;
    while(n != nullptr){
        cnt++;
        n = n->next_[0];
    }
    return cnt;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::add(const MsgType& msg)
{
    MsgNode* new_node = new MsgNode(msg);
    if(heads_[0]==nullptr)
    {
        heads_[0] = new_node;
        tail_ = new_node;
        new_node->num = x;
        x++;

    }
    else
    {
        new_node->prev_[0]=tail_;
        tail_->next_[0]= new_node;
        tail_ = new_node;
        new_node->num = x;
        x++;
    }
    MsgToken val(new_node ,this);
    return val;
}


// To be completed - must adhere to any requirements in the .h file
void LabelList::remove(const MsgToken& token)
{
    if(!token.isValid())
        return;

    for(unsigned int i =0; i< token.node_->labelled_.size(); i++)
    {
        if(token.node_->labelled_[i]==true)
        {
            if(token.node_->prev_[i]==nullptr&&token.node_->next_[i]==nullptr)
            {
                token.list_->heads_[i]=nullptr;
            }
            else if(token.node_->prev_[i]==nullptr)
            {
                token.node_->next_[i]->prev_[i]=nullptr;
                token.list_->heads_[i]=token.node_->next_[i];
            }
            else if(token.node_->next_[i]==nullptr)
            {
                token.node_->prev_[i]->next_[i]=nullptr;
            }
            else{
                token.node_->prev_[i]->next_[i]=token.node_->next_[i];
                token.node_->next_[i]->prev_[i]=token.node_->prev_[i];
            }
        }
    }
    if(token.node_->next_[0]==nullptr)
        tail_ = token.node_->prev_[0];
    delete token.node_;

}

// To be completed - must adhere to any requirements in the .h file
void LabelList::label(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }
    unsigned int i;
    bool found =false;
    for(i =0; i<token.list_->labels_.size();i++)
    {
        if(token.list_->labels_[i]==label)
        {
            found = true;
            if(token.node_->labelled_.size()<=i)
            {
                token.node_->labelled_.resize(i+1,false);
                token.node_->next_.resize(i+1);
                token.node_->prev_.resize(i+1);
                token.node_->labelled_[i]= true;
                
            }
            else
            {
                token.node_->labelled_[i] = true;

            }
            MsgNode* temp = heads_[i];
            while(temp!=nullptr&&temp->num<token.node_->num&&temp->next_[i]!=nullptr)
            {
                temp = temp->next_[i];
            }
            if(temp ==nullptr)
            {
                heads_[i]=token.node_;
                token.node_->prev_[i]=nullptr;
                token.node_->next_[i]=nullptr;
            }
            else if(temp->prev_[i]==nullptr&&temp->num>token.node_->num)
            {
                temp->prev_[i]= token.node_;
                token.node_->prev_[i] = nullptr;
                token.node_->next_[i] = temp;
                heads_[i] = token.node_;
            }
            else if(temp->next_[i]==nullptr&& temp->num<token.node_->num)
            {
                temp->next_[i] = token.node_;
                token.node_->prev_[i]= temp;
                token.node_->next_[i]=nullptr;
            }
            else
            {
                temp->prev_[i]->next_[i] = token.node_;
                token.node_->prev_[i] = temp->prev_[i];
                temp->prev_[i] = token.node_;
                token.node_->next_[i] = temp;               
            }
            break;
        }

    }
    if(found == false)
    {
        heads_.push_back(token.node_);
        labels_.push_back(label);
        token.node_->labelled_.resize(token.list_->labels_.size(),false);
        token.node_->next_.resize(token.list_->labels_.size());
        token.node_->prev_.resize(token.list_->labels_.size());
        token.node_->labelled_[token.list_->labels_.size()-1]= true;
        token.node_->next_[token.list_->labels_.size()-1]=nullptr;
        token.node_->prev_[token.list_->labels_.size()-1]=nullptr;

    }

}

// To be completed - must adhere to any requirements in the .h file
void LabelList::unlabel(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }
    if(findLabelIndex(label)==INVALID_LABEL)
    {
        throw std::out_of_range("not a member");
    }
    if(!token.isLabelMember(label))
    {
        return;
    }
    if(label == "all")
        return;

    for(unsigned int i = 0; i< labels_.size(); i++)
    {
        if(labels_[i]==label)
        {
            if(token.node_->prev_[i]==nullptr&&token.node_->next_[i]==nullptr)
            {
                token.list_->heads_[i]=nullptr;
            }
            else if(token.node_->prev_[i]==nullptr)
            {
                token.list_->heads_[i]=token.node_->next_[i];
                token.node_->next_[i]->prev_[i]=nullptr;
            }
            else if (token.node_->next_[i]==nullptr)
            {
                token.node_->prev_[i]->next_[i]=nullptr;
            }
            else
            {
                token.node_->prev_[i]->next_[i] = token.node_->next_[i];
                token.node_->next_[i]->prev_[i] = token.node_->prev_[i];
              
            }
            token.node_->labelled_[i] = false; 
            token.node_->prev_[i] = nullptr;
            token.node_->next_[i] = nullptr;
            return;
        }
    }
}

// Complete - Do not alter
LabelList::MsgToken LabelList::find(const MsgType& msg, const LabelType& label)
{
    // See if the label exists, will throw if not
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(n != nullptr)
    {
        if(n->msg_ == msg)
        {
            return MsgToken(n, this);
        }
        n = n->next_[level];
    }
    return end();
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::find(size_t index, const LabelType& label)
{

    int ind =-1;
    for(unsigned int x =0; x < labels_.size();x++)
    {
        if(labels_[x]==label)
        {
            ind  = x;
            break;
        }
    }
    if(ind ==-1)
    {
        throw std::out_of_range("No given label");
    }
    if(heads_[ind]==nullptr)
        return end();
    MsgNode* temp = heads_[ind];
    for(unsigned int i =0; i<index; i++)
    {
        if(temp->next_[ind]==nullptr&&i<index)
            return end();
        temp = temp->next_[ind];
    }
    MsgToken val(temp,this);
    return val;
}

// Complete - Do not alter
LabelList::MsgToken const & LabelList::end() const
{
    return end_;
}

// Complete - Do not alter
void LabelList::print(std::ostream& ostr, const LabelType& label, char separator) const
{
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(nullptr != n)
    {
        ostr << n->msg_ << separator;
        n = n->next_[level];
    }
    ostr << std::endl;
}

// To be completed - must adhere to any requirements in the .h file
size_t LabelList::findLabelIndex(const LabelType& label) const
{
    unsigned int i;
    for(i =0; i<labels_.size();i++)
    {
        if(labels_[i]==label)
        {
            size_t val = i;
            return val;
        }
    }
    return INVALID_LABEL;

}

// Complete - Do not alter
size_t LabelList::getLabelIndex(const LabelType& label) const
{
    size_t retval = this->findLabelIndex(label);
    if(INVALID_LABEL == retval)
    {
        throw std::out_of_range("Label doesn't exist");
    }
    return retval;
}


