#include "nodeLayers.hpp"




LayerNode::LayerNode()
{
  length = 0;
  root = nullptr;
}


bool LayerNode::empty()
{
  return root == nullptr;
}

int LayerNode::size()
{
  return length;
}

void LayerNode::insertNode(std::string pLocation, int pAge, bool pGender)
{
  //creo primero el objeto que pienso intrudcir

  node* nuevo = new node;
  nuevo->location = pLocation;
  nuevo->age = pAge;
  nuevo->gender = pGender;


  if(empty())
    {
      nuevo->nextGender = nullptr;
      nuevo->nextAge = nullptr;
      nuevo->nextLocation = nullptr;
      //en el caso de que root este apuntando a nullptr
      root = nuevo;
    }
 
      //en el caso de que ya exista un elemento tenemos que volver a organizadorlos haciendo una comparación
      
    
}

void LayerNode::display()
{
  std::cout<<"genero: "<<root->gender<<"edad"<<root->age<<"locacion: "<<root->location<<std::endl;
}



/*
node* LayerNode::find()
*/
