#include <iostream>
using namespace std;


int main()
{
  int *a = nullptr;
  
  int b = 44;
  int &c = b;
  b= 33;
  a = &b;
  cout<<c<<endl;
  return 0;
}
