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
  node* next;
};


class LayerNode
{
private:
  node* back;
  node* root;
  //son unos apuntadores que estan a los segmentos en cuano a la edad
  node* baja;
  node* mediana;
  node* alta;
  //apuntador a mujeres
  node* wom;
  node* men;
  //para recorrer las locaciones se va a hacer uso de mas o menos un binary tree
  //para eso necesito organizarlos
  node* city;

  //el simplement next
  int length;
  void findNodeAge(node* &pNodo);
  void findNodeGender(node* &pNodo);
  void findNodeCity(node* &pNode);
public:
  LayerNode();
  //~LayerNode();
  bool empty();
  int size();//retorna el numero de elementos que hay en las layers
  void insertNode(std::string pLocation, int pAge, bool pGender);
  void display();
  //test para ir probando
  void test();
  //node* find();
  //metodos para comenzar a contar elmentos
  int countGender(bool pSeleccion);//verdadero para mujeres, falso para hombres
 
};

#endif
