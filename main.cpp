#include "simple_vector.hpp"
#include <iostream>
using namespace std;

int main() {
  
  SimpleVec myvec;
    
    // initialize the vector
    for(int i = 0; i < 20; i++)
        myvec.push(i);
    
    //iterate with index
    cout << "Going through the vector with the index:\n";
    for(int i = 0; i < 20; i++)
        cout << myvec.retrieve(i) << " ";
    cout << endl;
    
    // declare an iterator
    SimpleVec::iterator it = myvec.begin();
    
    // iterate with iterator
    cout << "Going through the vector with the iterator:\n";
    //it++;
    //cout<<*(++it)<<endl;
    
    cout<<((myvec.end()).getIt() -(myvec.begin()).getIt())/sizeof(int)<<endl;
    


    /*
    for(it = myvec.begin(); it != myvec.end(); it++)
        cout << *it << " ";
    cout << endl;
    
    // go to the 3rd element
    it = myvec.begin();
    for(int i = 0; i < 3; i++)
        ++it;
    // change the element
    *it = 300;
    // delete the last 3 elements
    for(int i = 0; i < 3; i++)
        myvec.erase(myvec.size()-1);
    
    
    // iterate with iterator
    cout << "Going through the vector with the iterator:\n";
    for(it = myvec.begin(); it != myvec.end(); it++)
        cout << *it << " ";
    cout << endl;
    
    // testing prefix/postfix operators
    SimpleVec::iterator it2 = myvec.begin();
    SimpleVec::iterator it3 = myvec.begin();
    
    cout << "*it++: " << *it2++
    << " *it: " << *it2 << endl;
    cout << "++*it: " << *++it3
    << " *it: " << *it3 << endl;
  

    
  double numero = 22.4;
  
  BidirIterator prueba(&numero);
  BidirIterator testII(prueba);
  cout<<(&testII)<<endl;
  */
  return 0;
}
