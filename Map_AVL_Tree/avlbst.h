#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    // Add helper functions here
    void insert_fix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);
    void remove_fix(AVLNode<Key,Value>* node,const char diff);
    void right_zig(AVLNode<Key,Value>* gp);
    void left_zig(AVLNode<Key,Value>* gp);
    void left_zag(AVLNode<Key,Value>* parent);
    void right_zag(AVLNode<Key,Value>* parent);
    bool isLeftChild(AVLNode<Key,Value>* node);
    bool isRightChild(AVLNode<Key,Value>* node);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if(this->root_==nullptr)
    {
        this->root_= new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        static_cast<AVLNode<Key,Value>*>(this->root_)->setBalance(0);
    }
    else
    {
        AVLNode<Key,Value>* temp = static_cast<AVLNode<Key,Value>*>(this->root_);
        
        while(temp!=nullptr)
        {
            if(temp->getKey()==new_item.first)
            {
                temp->setValue(new_item.second);
                return;
            }
            else if(temp->getKey()<new_item.first)
            {
                if(temp->getRight()!=nullptr)
                    temp = temp->getRight();
                else
                {
                    temp->setRight(new AVLNode<Key,Value>(new_item.first,new_item.second, temp));
                    if(temp->getBalance()==1||temp->getBalance()==-1)
                        temp->setBalance(0);
                    else
                    {
                        temp->updateBalance(1);
                        insert_fix(temp, temp->getRight());
                    }
                    return;
                }
            }
            else
            {
                if(temp->getLeft()!=nullptr)
                    temp = temp->getLeft();
                else
                {
                    temp->setLeft(new AVLNode<Key,Value>(new_item.first,new_item.second, temp));
                    if(temp->getBalance()==1||temp->getBalance()==-1)
                        temp->setBalance(0);
                    else
                    {
                        temp->updateBalance(-1);
                        insert_fix(temp, temp->getLeft());
                    }
                    return;
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert_fix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node)
{
    if(parent==nullptr||parent->getParent()==nullptr)
        return;
    AVLNode<Key,Value>* gp = parent->getParent();
    if(isLeftChild(parent))
    {
        gp->updateBalance(-1);
        char temp = gp->getBalance();
        if(temp==0)
            return;
        else if(temp==-1)
            insert_fix(gp,parent);
        else
        {
            if(isLeftChild(node))
            {
                right_zig(gp);
                gp->setBalance(0);
                parent->setBalance(0);
            }
            else
            {
                left_zag(parent);
                right_zig(gp);
                if(node->getBalance()==-1)
                {
                    parent->setBalance(0);
                    gp->setBalance(1);
                    node->setBalance(0);
                }
                else if(node->getBalance()==0)
                {
                    parent->setBalance(0);
                    gp->setBalance(0);
                }
                else
                {
                    parent->setBalance(-1);
                    gp->setBalance(0);
                    node->setBalance(0);
                }
            }
        }
    }
    else
    {
        gp->updateBalance(1);
        char temp = gp->getBalance();
        if(temp==0)
            return;
        else if(temp==1)
            insert_fix(gp,parent);
        else
        {
            if(isRightChild(node))
            {
                left_zig(gp);
                gp->setBalance(0);
                parent->setBalance(0);
            }
            else
            {
                right_zag(parent);
                left_zig(gp);
                if(node->getBalance()==1)
                {
                    parent->setBalance(0);
                    gp->setBalance(-1);
                    node->setBalance(0);
                }
                else if(node->getBalance()==0)
                {
                    parent->setBalance(0);
                    gp->setBalance(0);
                }
                else
                {
                    parent->setBalance(1);
                    gp->setBalance(0);
                    node->setBalance(0);
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::right_zig(AVLNode<Key,Value>* gp)
{
    AVLNode<Key,Value>* parent = gp->getLeft();
    AVLNode<Key,Value>* ggp = gp->getParent();
    AVLNode<Key,Value>* parent_right = parent->getRight();
    if(ggp!=nullptr)
    {
        if(isLeftChild(gp))
            ggp->setLeft(parent);
        else
            ggp->setRight(parent);
    }
    else
        this->root_=parent;
    if(parent_right!=nullptr)
        parent_right->setParent(gp);
    gp->setLeft(parent_right);
    parent->setRight(gp);
    gp->setParent(parent);
    parent->setParent(ggp);
}

template<class Key, class Value>
void AVLTree<Key, Value>::left_zig(AVLNode<Key,Value>* gp)
{
    AVLNode<Key,Value>* parent = gp->getRight();
    AVLNode<Key,Value>* ggp = gp->getParent();
    AVLNode<Key,Value>* parent_left = parent->getLeft();
    if(ggp!=nullptr)
    {
        if(isLeftChild(gp))
            ggp->setLeft(parent);
        else
            ggp->setRight(parent);
    }
    else
        this->root_=parent;
    if(parent_left!=nullptr)
        parent_left->setParent(gp);
    gp->setRight(parent_left);
    parent->setLeft(gp);
    gp->setParent(parent);
    parent->setParent(ggp);
}

template<class Key, class Value>
void AVLTree<Key, Value>::right_zag(AVLNode<Key,Value>* parent)
{
    AVLNode<Key,Value>* gp = parent->getParent();
    AVLNode<Key,Value>* node = parent->getLeft();
    AVLNode<Key,Value>* node_right = node->getRight();
    gp->setRight(node);
    node->setParent(gp);
    node->setRight(parent);
    parent->setParent(node);
    parent->setLeft(node_right);
    if(node_right!=nullptr)
        node_right->setParent(parent);
}

template<class Key, class Value>
void AVLTree<Key, Value>::left_zag(AVLNode<Key,Value>* parent)
{
    AVLNode<Key,Value>* gp = parent->getParent();
    AVLNode<Key,Value>* node = parent->getRight();
    AVLNode<Key,Value>* node_left = node->getLeft();
    gp->setLeft(node);
    node->setParent(gp);
    node->setLeft(parent);
    parent->setParent(node);
    parent->setRight(node_left);
    if(node_left!=nullptr)
        node_left->setParent(parent);
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftChild(AVLNode<Key,Value>* node)
{
    if(node->getParent()->getLeft()==node)
        return true;
    return false;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isRightChild(AVLNode<Key,Value>* node)
{
    if(node->getParent()->getRight()==node)
        return true;
    return false;
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    AVLNode<Key,Value>* node = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    if(node==nullptr)
        return;
    if(node->getLeft()!=nullptr&&node->getRight()!=nullptr)
        nodeSwap(node,static_cast<AVLNode<Key,Value>*>(this->predecessor(node)));
    AVLNode<Key,Value>* parent = node->getParent();
    char diff;
    if(parent != nullptr)
    {
        if(isLeftChild(node))
            diff=1;
        else
            diff=-1;    
    }
    if(node->getLeft()==nullptr&&node->getRight()==nullptr)
        this->removeNoChild(node);
    else
        this->removeOneChild(node);
    remove_fix(parent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove_fix(AVLNode<Key,Value>* node,const char diff)
{
    if(node==nullptr)
        return;
    AVLNode<Key,Value>* parent = node->getParent();
    char ndiff = 0;
    if(parent!=nullptr)
    {
        if(isLeftChild(node))
            ndiff=1;
        else 
            ndiff=-1;
    }
    if(diff==-1)
    {
        if((node->getBalance()+diff)==-2)
        {  
            AVLNode<Key,Value>* tallerchild = node->getLeft();
            if(tallerchild->getBalance()==-1)
            {
                right_zig(node);
                node->setBalance(0);
                tallerchild->setBalance(0);
                remove_fix(parent,ndiff);
            }
            else if(tallerchild->getBalance()==0)
            {
                right_zig(node);
                node->setBalance(-1);
                tallerchild->setBalance(1);
            }
            else
            {
                AVLNode<Key,Value>* grandchild = tallerchild->getRight();
                left_zag(tallerchild);
                right_zig(node);
                if(grandchild->getBalance()==1)
                {
                    node->setBalance(0);
                    tallerchild->setBalance(-1);
                    grandchild->setBalance(0);
                }
                else if(grandchild->getBalance()==0)
                {
                    node->setBalance(0);
                    tallerchild->setBalance(0);
                }
                else
                {
                    node->setBalance(1);
                    tallerchild->setBalance(0);
                    grandchild->setBalance(0);
                }
                remove_fix(parent, ndiff);
            }
        }
        else if((node->getBalance()+diff)==-1)
            node->setBalance(-1);
        else
        {
            node->setBalance(0);
            remove_fix(parent, ndiff);
        }
    }
    else
    {
        if((node->getBalance()+diff)==2)
        {
            AVLNode<Key,Value>* tallerchild = node->getRight();
            if(tallerchild->getBalance()==1)
            {
                left_zig(node);
                node->setBalance(0);
                tallerchild->setBalance(0);
                remove_fix(parent,ndiff);
            }
            else if(tallerchild->getBalance()==0)
            {
                left_zig(node);
                node->setBalance(1);
                tallerchild->setBalance(-1);
            }
            else
            {
                AVLNode<Key,Value>* grandchild = tallerchild->getLeft();
                right_zag(tallerchild);
                left_zig(node);
                if(grandchild->getBalance()==-1)
                {
                    node->setBalance(0);
                    tallerchild->setBalance(1);
                    grandchild->setBalance(0);
                }
                else if(grandchild->getBalance()==0)
                {
                    node->setBalance(0);
                    tallerchild->setBalance(0);
                }
                else
                {
                    node->setBalance(-1);
                    tallerchild->setBalance(0);
                    grandchild->setBalance(0);
                }
                remove_fix(parent, ndiff);
            }
        }
        else if((node->getBalance()+diff)==1)
            node->setBalance(1);
        else
        {
            node->setBalance(0);
            remove_fix(parent, ndiff);
        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
