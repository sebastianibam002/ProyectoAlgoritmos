#include "nodeLayers.hpp"
using namespace std;
int main()
{
  LayerNode prueba;
  prueba.insertNode("Bogota", 15, false);
  prueba.insertNode("Islandia", 16, false);
  prueba.insertNode("Brkinafaso", 19, false);
  prueba.insertNode("ipiales", 45, true);
  prueba.insertNode("calarca", 66, false);
  prueba.display();
  prueba.test();
  cout<<"hay: "<<prueba.size() <<" personitas"<<endl;
  cout<<"de esas: "<<prueba.countGender(false)<<" son hombres"<<endl;
  return 0;
}
   
