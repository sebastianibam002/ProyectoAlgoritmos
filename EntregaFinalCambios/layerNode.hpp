#ifndef _LAYERNODE_HPP
#define _LAYERNODE_HPP
#include <iostream>

//nodo de localizacion para el arbol
struct nodeLoc
{
  int edad;
  //izquierda
  nodeLoc* left;
  //derecha que es mayor
  nodeLoc*  right;

  //el padrecito
  nodeLoc* parent;
  
};


class BinLoc
{

private:
  nodeLoc* root;
  void displayNode(nodeLoc* pNode, int count);
  //
  void insertNode(nodeLoc* &pNode, int pKey, nodeLoc* pParent);
  void destroyRecursive(nodeLoc* pNode);
public:
  BinLoc(){root = nullptr;}
  ~BinLoc(){destroyRecursive(root);}
  void insert(int pKey){insertNode(root, pKey, nullptr);}
  void display();
  
};

void BinLoc::insertNode(nodeLoc *&pNode, int pKey, nodeLoc *pParent)
{

  if(pNode == nullptr)
    {
      pNode = new nodeLoc;
      pNode->edad = pKey;
      pNode->left = nullptr;
      pNode->right = nullptr;
      pNode->parent = pParent;
    }
  else
    {
      if(pKey != pNode->edad)
	{
	  if(pKey < pNode->edad)
	    {
	      insertNode(pNode->left, pKey, pNode);
	    }
	  else
	    {
	      insertNode(pNode->right, pKey, pNode);
	    }
	}
    }

  

}

void BinLoc::destroyRecursive(nodeLoc *pNode)
{
  if(pNode != nullptr)
    {
      destroyRecursive(pNode->left);
      destroyRecursive(pNode->right);
      delete pNode;
    }
}


void BinLoc::displayNode(nodeLoc *pNode, int count)
{
  //recursion
  count++;
  if(pNode != nullptr)
    {

      displayNode(pNode->left, count);	
      std::cout<< "("<<count -1<< ")"<<pNode->edad<<" ";
      displayNode(pNode->right, count);
	
    }
}


void BinLoc::display()
{
  //wraper para no acceder al root desde afuera
  int contador = 0;
  displayNode(root, contador);
  std::cout<<std::endl;
}
#endif
