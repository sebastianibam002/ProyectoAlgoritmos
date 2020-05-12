#include "nodeLayers.hpp"
using namespace std;
int main()
{
  LayerNode prueba;
  prueba.insertNode("Bogota", 15, true);
  prueba.insertNode("Islandia", 45, false);
  prueba.insertNode("Brkinafaso", 19, false);
  prueba.insertNode("ipiales", 12, true);
  prueba.insertNode("calarca", 25, false);
  prueba.display();
  //prueba.test();
  cout<<"hay: "<<prueba.size() <<" personitas"<<endl;
  cout<<"de esas: "<<prueba.countGender(true)<<" son mujeres"<<endl;
  //cout<<"hay: "<<prueba.countAge(0)<<" de baja edad"<<endl;
  cout<<"hay: "<<prueba.countAge(0)<<" de edad baja"<<endl;
  //cout<<"hay: "<<prueba.countAge(2)<<" de alta edad"<<endl;
  return 0;
}
   
