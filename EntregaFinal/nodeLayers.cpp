#include "nodeLayers.hpp"
//BAJO
int BAJOA = 0;
int BAJOB = 21;
//MEDIANA
int MEDIANAA = 22;
int MEDIANAB = 55;
//Alta
int ALTAA = 56;


LayerNode::LayerNode()
{
  length = 0;
  root = nullptr;
  //edad
  //corresponde al ultimo nodo ue quedo en la parte de baja
  baja = nullptr; 
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
  else
    {
      //primero lo relacionamos en cuanto a la edad en baja, mediana o alta
      findNodeAge(nuevo);
    }
  
 
      //en el caso de que ya exista un elemento tenemos que volver a organizadorlos haciendo una comparación
      
    
}

void LayerNode::display()
{
  std::cout<<"genero: "<<root->gender<<"edad"<<root->age<<"locacion: "<<root->location<<std::endl;
}




void LayerNode::findNodeAge(node* pNode)
{
  //tiene como parametro un nodo y va a buscar asociar de la mejor manera
  //comienzo con la edad
  //tengo asi que dividir por tres edades: menores, mediana y alta
  //baja(0-21) media(22-55), alta(56 en adelante)

  if(pNode->age >= BAJAA && pNode->age <= BAJAB)
    {
      //entra al primer rango
      pNode->next = baja;
      baja = pNode;
      
    }
  else if(pNode->age >= MEDIANAA && pNode->age <= MEDIANAB)
    {
      pNode->next = mediana;
      mediana = pNode;
    }
  else if(pNode->age > ALTAA)
    {
      pNode->next = alta;
      alta = pNode;
    }
  
}

