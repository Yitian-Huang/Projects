#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

private:
  /// Add whatever helper functions and data members you need below
  void trickleup(int loc);
  void heapify(int loc);
  std::vector<T> myvec;
  int dary;
  PComparator comp;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  :dary(m), comp(c)
{

}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleup(int loc)//Referenced from lecture slide Heaps but is modified to fit 0-based indexing
{
  int parent =(loc-1)/dary;
  while(parent!=loc&&comp(myvec[loc], myvec[parent]))
  {
    std::swap(myvec[loc], myvec[parent]);
    loc = parent;
    parent = (loc-1)/dary;
  }
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)//Referenced from lecture slide Heaps but is modified to fit 0-based indexing
{
  myvec.push_back(item);
  trickleup(myvec.size()-1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("There's no top element because the heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return myvec[0];
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int loc)//Referenced from lecture slide Heaps but is modified to fit 0-based indexing
{
  int size=myvec.size();
  if(loc*dary>=size-1)
    return;
  int smallerchild = loc*dary+1;
  if(smallerchild<size-1)
  {
    int temp = smallerchild;
    for(int i=1; i<dary; i++)
    {
      if(temp==size-1)
        break;
      int rchild = temp+1;
      if(comp(myvec[rchild], myvec[smallerchild]))
        smallerchild=rchild;
      temp++;
    }
  }
  if(comp(myvec[smallerchild],myvec[loc]))
  {
    std::swap(myvec[smallerchild],myvec[loc]);
    heapify(smallerchild);
  }
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()//Referenced from lecture slide Heaps but is modified to fit 0-based indexing
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Can't pop because the heap is empty");
  }
  myvec[0]=myvec.back();
  myvec.pop_back();
  heapify(0);
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return myvec.empty();
}



#endif

