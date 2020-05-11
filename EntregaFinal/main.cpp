#include "nodeLayers.hpp"
using namespace std;
int main()
{
  LayerNode prueba;
  prueba.insertNode("Bogota", 15, false);
  prueba.insertNode("Islandia", 16, false);
  prueba.insertNode("Brkinafaso", 19, true);
  //prueba.display();
  prueba.test();
  return 0;
}
   
