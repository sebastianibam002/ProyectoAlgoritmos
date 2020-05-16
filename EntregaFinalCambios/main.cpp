#include "layerNode.hpp"
using namespace std;
int main()
{



  BDCovid prueba;
  vector<int> test =prueba.busqueda(false,0,100,"Bogota");
  
  for(int i = 0; i < test.size(); i++)
    {
      cout<<test[i]<<" ";
    }
  cout<<endl;
  
  
  
  

  

  return 0;
}
