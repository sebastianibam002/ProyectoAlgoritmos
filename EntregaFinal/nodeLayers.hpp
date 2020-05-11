#ifndef _NODELAYERS_HPP
#define _NODELAYERS_HPP
#include <string>
#include <iostream>

struct node
{

  std::string location;
  int age;
  bool gender;
  node* nextGender;
  node* nextAge;
  node* nextLocation;
};


class LayerNode
{
private:
  node* root;
  //son unos apuntadores que estan a los segmentos en cuano a la edad
  node* baja;
  node* mediana;
  node* alta;
  
  int length;
  void findNodeAge(node* pNodo);
  
public:
  LayerNode();
  //~LayerNode();
  bool empty();
  int size();//retorna el numero de elementos que hay en las layers
  void insertNode(std::string pLocation, int pAge, bool pGender);
  void display();
  //node* find();
};

#endif
