#ifndef __SIMPLE_VECTOR_HPP
#define __SIMPLE_VECTOR_HPP

#include <iostream>
using namespace std;

const int INITIAL_CAPACITY = 10;

// define a bidirectional iterator structure for doubles
// this class is basically a wrapper for a pointer ptr
class BidirIterator {
private:
    double *ptr;

public:
    // default constructor
    BidirIterator() { ptr = nullptr; }
    // constructor
    BidirIterator(double *beg);
    // copy constructor
    BidirIterator(const BidirIterator& it);
    // destructor
    ~BidirIterator() {}

    // dereference operator
    double & operator*();

    // prefix/postfix ++ operators
    BidirIterator & operator++();  // ++it
    BidirIterator operator++(int); // it++
    // prefix/postfix -- operators
    BidirIterator & operator--();  // --it
    BidirIterator operator--(int); // it--

    // assignment operator
    void operator=(const BidirIterator it);

    // comparison operators
    bool operator==(const BidirIterator it);
    bool operator!=(const BidirIterator it);
};


class SimpleVec {
private:
    double *array;
    int capacity, length;

    void expandCapacity();

public:
    // iterator and related methods
    typedef BidirIterator iterator;
    iterator begin();
    iterator end();

    // constructors
    SimpleVec();
    SimpleVec(const SimpleVec& rhs);
    // destructor
    ~SimpleVec();

    // assignment operator
    SimpleVec & operator=(const SimpleVec &rhs);

    // other SimpleVec methods
    void push(double value);
    void erase(int index);
    void insert(int index, double value);
    void modify(int index, double value);
    double retrieve(int index);

    void clear();
    bool empty();
    int size();
};

#endif
