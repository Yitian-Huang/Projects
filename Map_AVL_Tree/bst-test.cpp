#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    // AVL Tree Tests
    AVLTree<int,int> at;
    at.insert(std::make_pair(30,1));
    at.insert(std::make_pair(20,2));
    at.insert(std::make_pair(40,3));
    at.insert(std::make_pair(10,3));
    at.insert(std::make_pair(35,3));
    at.insert(std::make_pair(45,3));
    at.insert(std::make_pair(5,3));
    at.insert(std::make_pair(43,3));
    at.insert(std::make_pair(46,3));
    at.insert(std::make_pair(1,3));
    at.print();
    std::cout<<"End of a insert-------------------------------------------------------"<<std::endl;
    at.insert(std::make_pair(-47,3));
    at.print();
    std::cout<<"End of a insert-------------------------------------------------------"<<std::endl;
    at.insert(std::make_pair(-74,3));
    at.print();
    std::cout<<"End of a insert-------------------------------------------------------"<<std::endl;
    at.insert(std::make_pair(133,3));
    at.print();
    std::cout<<"End of a insert-------------------------------------------------------"<<std::endl;
    at.insert(std::make_pair(-115,3));
    at.print();
    std::cout<<"End of a insert-------------------------------------------------------"<<std::endl;
    at.insert(std::make_pair(141,3));
    at.insert(std::make_pair(-38,3));
    at.insert(std::make_pair(-12,3));
    at.insert(std::make_pair(48,3));
    at.insert(std::make_pair(-89,3));
    at.insert(std::make_pair(61,3));
    at.insert(std::make_pair(87,3));
    at.insert(std::make_pair(11,3));
    at.insert(std::make_pair(-35,3));
    at.insert(std::make_pair(-87,3));
    at.insert(std::make_pair(130,3));
    at.insert(std::make_pair(72,3));
    at.insert(std::make_pair(76,3));
    std::cout<<at.isBalanced()<<std::endl;
    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<int,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('c') != at.end()) {
        cout << "Found c" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove(35);
    at.print();

    return 0;
}
