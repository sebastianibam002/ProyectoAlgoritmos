#ifndef _LAYERNODE_HPP
#define _LAYERNODE_HPP
#include <iostream>
#include <vector>
//es la estructura que contiene las direcciones a cad auno de sus elementos en las 3 estructuras que las van a estar almacenando













/*
 *
 *
 *ACA COMIENZA LA ESTRUCTURA QUE CONTIENE LA INFORMACION DE LA EDAD EN UN BINARY TREE
 *
 */

int NEXT = 10;

//nodo de localizacion para el arbol
struct nodeLoc
{
  int idUnico;
  int edad;
  //izquierda
  nodeLoc* left;
  //derecha que es mayor
  nodeLoc*  right;

  //el padrecito
  nodeLoc* parent;
  
};



int contadorId = 0;
class BinLoc
{

private:
  nodeLoc* root;
  void displayNode(nodeLoc* pNode, int count);
  //
  void insertNode(nodeLoc* &pNode, int pKey, nodeLoc* pParent);
  void destroyRecursive(nodeLoc* pNode);
  nodeLoc* maximum(nodeLoc *t);
  nodeLoc* minimum(nodeLoc *t);
  nodeLoc* findNode(nodeLoc* pNode, int pEdad);
public:
  BinLoc(){root = nullptr;}
  ~BinLoc(){destroyRecursive(root);}
  void insert(int pKey){insertNode(root, pKey, nullptr);}
  void display();
  nodeLoc* predecessor(nodeLoc *pNode);
  nodeLoc* successor(nodeLoc *pNode);
  nodeLoc* find(int pEdad){return findNode(root, pEdad);}
  bool contains(int pEdad);//este elemento existe en la estructura
  int searchNext(int pEdad);
  int searchLast(int pEdad);
  
  std::vector<int> rango(int pDesde, int pHasta);
  void test();
  
};

int BinLoc::searchNext(int pEdad)
{
  //in case the element doesn't exists this will be used in order to find the most look alike in an umbral of NEXT
  int tempEdad = pEdad;
  int contador = 0;
  while(contador < NEXT && !contains(tempEdad))
    {
      tempEdad++;
      contador++;
      
    }

  if(contains(tempEdad))
    return tempEdad;
  else
    return -1;
}

int BinLoc::searchLast(int pEdad)
{
  //in case the element doesn't exists this will be used in order to find the most look alike in an umbral of NEXT
  int tempEdad = pEdad;
  int contador = 0;
  while(contador < NEXT && !contains(tempEdad))
    {
      tempEdad--;
      contador++;
      
    }

  if(contains(tempEdad))
    return tempEdad;
  else
    return -1;
}


bool BinLoc::contains(int pEdad)
{
  if(find(pEdad) == nullptr)
    {
      return false;
    }
  return true;
}
std::vector<int> BinLoc::rango(int pDesde, int pHasta)
{

  if(pDesde != -1 && pHasta != -1)
    {
      std::vector<int> retorno;
      if(contains(pDesde) && contains(pHasta))
	{
	  nodeLoc* temp = find(pDesde);
	  std::cout<<"el hasta: "<<find(pHasta)->idUnico<<std::endl;
	  nodeLoc* tempDos = find(pHasta);
	  //los numeros mayores
	  while(temp != nullptr)
	    {
	      //std::cout<<"id unico: "<<temp->idUnico<<std::endl;
	      
	      
	      
	      retorno.push_back(temp->idUnico);
	      //std::cout<<"paso primer filtro"<<" temp "<<temp->right<<std::endl;
	      //std::cout<<"elemento introducido"<<std::endl;
	      temp = successor(temp);
	      //std::cout<<"llego"<<std::endl;
	      //std::cout<<"siguiente elemento "<< temp<<std::endl;
	      if(tempDos->idUnico == temp->idUnico)
		{
		  retorno.push_back(temp->idUnico);
		  break;
		}
	    }
	  return retorno;
	  
	}
      else
	{
	  //if(pDesde == -1 && !pHasta != -1)
	 return rango(searchNext(pDesde), searchLast(pHasta));
	   
	}
    }
  

}





void BinLoc::test()
{
  //std::cout<<"el predecessor de 5 es: "<< predecessor(find(5))->edad<<std::endl;
  //std::cout<<root->parent<<std::endl;

  
  std::vector<int> prueba= rango(0,10);

  for(unsigned int i =0; i < prueba.size(); i++)
    {
      std::cout<<prueba[i]<<" ";
    }
  std::cout<<std::endl;
  
}

  
  //std::cout<<searchLast(12)<<std::endl;

  //std::cout<<"sucesor del ultimo: "<<successor(find(6))->idUnico<<std::endl;


nodeLoc* BinLoc::minimum(nodeLoc *t)
{  

  if(t->left == nullptr)
    {
      return t;
    }
  else
    {
      minimum(t->left);
    }
}


nodeLoc* BinLoc::maximum(nodeLoc *t)
{

  if(t->right == nullptr)
    {
      return t;
    }
  else
    {
      maximum(t->right);
    }
}

void BinLoc::insertNode(nodeLoc *&pNode, int pKey, nodeLoc *pParent)
{

  if(pNode == nullptr)
    {
      
      pNode = new nodeLoc;
      pNode->edad = pKey;
      pNode->left = nullptr;
      pNode->right = nullptr;
      pNode->parent = pParent;
      pNode->idUnico = contadorId++;
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
      std::cout<< "("<<count -1<< ")"<<pNode->edad<<" id["<<pNode->idUnico <<"] " ;
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

nodeLoc* BinLoc::successor(nodeLoc *pNode)
{

  
  if(pNode->right != nullptr)
    {
      return minimum(pNode->right);
    }
  else
    {

      //std::cout<<"filtro dos"<<std::endl;
      //std::cout<<"padrecito: "<<pNode->parent<<std::endl;
      nodeLoc* tempB = new nodeLoc;
      while(((pNode->parent)->right == pNode) && (pNode->parent) != nullptr)
	{

	  //if(pNode->parent != nullptr)
	  pNode = pNode->parent;
	  if(root == pNode)
	    {
	      //std::cout<<"successor: "<<pNode->edad<<std::endl;
	      break;
	    }

	   
	  
	  
	}

      return pNode->parent;
    }

}

nodeLoc* BinLoc::predecessor(nodeLoc* pNode)
{
  //continua mientras siga siendo hijo izquierdo de su padre
  if(pNode->left != nullptr)
    {
      return maximum(pNode->left);
    }
  else
    {
      while(((pNode->parent)->left == pNode) && (pNode->parent) != nullptr)
	{
	  pNode = pNode->parent;
	}

      return pNode->parent;
    }
}

nodeLoc* BinLoc::findNode(nodeLoc *pNode, int pEdad)
{
  if(pNode == nullptr) return nullptr;
  if(pNode->edad == pEdad) return pNode;
  if(pNode->edad < pEdad)
    return findNode(pNode->right, pEdad);
  else
    return findNode(pNode->left, pEdad);
}
#endif
