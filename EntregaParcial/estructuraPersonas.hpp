#ifndef _ESTRUCTURAPERSONAS_HPP
#define _ESTRUCTURAPERSONAS_HPP
#include <string>
//cajitas dentro de la estructura es decir la persona
struct person
{
  //edad
  int age;
  //genero
  bool gender;
  //locacion
  string location;
  // idUnico
  int id;
  //apuntador al siguiente por izquieda
  person* left;
  //apuntador al soguiente por derecha
  person* right;
  //apuntador al padre
  person* parent;
};


class EstructuraPersonas
{

private:
  //tenemos la raiz
  person *root;
  //para mostrar un nodo
  void display_node(person* p_node, int count);
  //insertar un nodo
  void insert_node(person *&node, T k, person*p);
  /*
  
  //no accedemos nunca desde afuera
  //node desde donde comenzamos a destruir recursivamente
  void destroy_recursive(BSTNode<T> *node);
  BSTNode<T>* find_node(BSTNode<T> *node, T k);
  //Minimo y maximo
  BSTNode<T>* minimum(BSTNode<T> *t);
  BSTNode<T>* maximum(BSTNode<T> *t);
  */
public:
  EstructuraPersonas(){root = nullptr;}
  //~EstructuraPersonas(){destroy_recursive(root);} //destructor 
  //crea un nodo, y derecho e izquiedo apunta a nullptr
  
  void display();
  bool empty();
  /*--------------*/
  void test(T val);
  void insert(T k){insert_node(root,k, nullptr);}
  //BSTNode<T>* find(T k){return find_node(root, k);}
  //Predecesor y sucesor
  //BSTNode<T> *predecessor(BSTNode<T> *pNode); //le doy un nodo y me deberia retorna el predecesor de este
  //BSTNode<T> *sucessor(BSTNode<T> *pNode);

  //Removiendo Nodos
  //BSTNode<T>* removeNode(BSTNode<T> *pNode, T k);

};
#endif
