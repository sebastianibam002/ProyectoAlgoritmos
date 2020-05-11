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
  int length;
  
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
