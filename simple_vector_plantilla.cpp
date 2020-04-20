#include "simple_vector.hpp"
/*
 * CLASS BidirIterator METHODS ---------------------------------------------
 */

//**********************************************

double &BidirIterator::operator*(){
  //double value = *ptr;
  return *ptr;
}


BidirIterator &BidirIterator::operator++(){  // ++it
  ptr++;
  //return *this;
}

BidirIterator BidirIterator::operator++(int){  // it++
  ++ptr;
  //BidirIterator temporal = *this;
  //++*this;
  //return temporal;
} 



BidirIterator &BidirIterator::operator--(){
  ptr = ptr - sizeof(double);
  return *this;
}

//constructor con argumento de un apuntador a double
BidirIterator::BidirIterator(double *beg)
{
  ptr = beg;
  
}


BidirIterator::BidirIterator(const BidirIterator &it)
{
  //ptr= it.getIt();
  //ptr = &temp;
  //es un Copy constructor
  //double temp = *it;
  ptr = it.getIt();
  
}



void BidirIterator::operator=(BidirIterator it){ // REVIZAR!!!
  double temp = *it;
  ptr = &temp;
}


bool BidirIterator::operator==(const BidirIterator it)
{
  return it.getIt() == ptr;
}

double *BidirIterator::getIt()const
{
  return ptr;
}

bool BidirIterator::operator!=(const BidirIterator it)
{
  return it.getIt() != ptr;
}


//**********************************************


/*
 * CLASS SimpleVec METHODS -------------------------------------------------
 */

// Iterator-related methods
/**********************************************
 *
 *
 * Su
 * código
 * aquí
 *
 *
 **********************************************/

// Constructors
SimpleVec::SimpleVec() : capacity(INITIAL_CAPACITY), length(0) {
    array = new double[capacity];
}

SimpleVec::SimpleVec(const SimpleVec& rhs) {
    capacity = rhs.capacity;
    length = rhs.length;
    array = new double[capacity];
    for(int i = 0; i < length; ++i)
        array[i] = rhs.array[i];
}

// Destructor
SimpleVec::~SimpleVec() {
    delete[] array;
}

// Assignment operator
SimpleVec & SimpleVec::operator=(const SimpleVec& rhs) {
    delete[] array;
    capacity = rhs.capacity;
    length = rhs.length;
    array = new double[capacity];
    for(int i = 0; i < length; ++i)
        array[i] = rhs.array[i];

    return *this;
}


//iteraro andn related methods

SimpleVec::iterator SimpleVec::begin()
{
  BidirIterator begin(array);
  return begin;
}

SimpleVec::iterator SimpleVec::end()
{
  //BidirIterator end(array[length]);
  BidirIterator end(&(array[length -1]));
  return end;
}



// Other SimpleVec methods
void SimpleVec::push(double value) {
    if(length == capacity) expandCapacity();
    array[length++] = value;
}

void SimpleVec::erase(int index) {
    for(int i = index; i < length-1; ++i)
        array[i] = array[i+1];
    length--;
}

void SimpleVec::insert(int index, double value) {
    if(length == capacity) expandCapacity();
    for(int i = length-1; i > index; --i)
        array[i] = array[i-1];
    array[index] = value;
    length++;
}

void SimpleVec::modify(int index, double value) {
    array[index] = value;
}

double SimpleVec::retrieve(int index) {
    return array[index];
}

void SimpleVec::expandCapacity() {
    double *oldArray = array;
    capacity *= 2;
    array = new double[capacity];
    for(int i = 0; i < length; ++i)
        array[i] = oldArray[i];
    delete[] oldArray;
}

void SimpleVec::clear() {
    length = 0;
}

bool SimpleVec::empty() {
    return length == 0;
}

int SimpleVec::size() {
    return length;
}
