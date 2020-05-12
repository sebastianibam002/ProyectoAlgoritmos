#include "nodeLayers.hpp"
//BAJO
int BAJAA = 0;
int BAJAB = 21;
//MEDIANA
int MEDIANAA = 22;
int MEDIANAB = 55;
//Alta
int ALTAA = 56;


LayerNode::LayerNode()
{
  length = 0;
  //back = nullptr;
  root = nullptr;
  baja = root;
  mediana = root;
  alta = root;
  city = root;
  wom = nullptr;
  men = nullptr;
  
  //edad
  //corresponde al ultimo nodo ue quedo en la parte de baja
  //baja = nullptr; 
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
  node* temp = root;
  length++;
  

  if(empty())
    {
      nuevo->nextGender = nullptr;
      nuevo->nextAge = nullptr;
      nuevo->nextLocation = nullptr;
      //en el caso de que root este apuntando a nullptr
      findNodeAge(nuevo);
      findNodeGender(nuevo);
      findNodeCity(nuevo);
      root = nuevo;
      
    }
  else
    {

      //en el caso que sea el primer elemento en anadirse
      nuevo->next = root;
      root = nuevo;
      findNodeAge(nuevo);
      findNodeGender(nuevo);
      findNodeCity(nuevo);

	
      
    }
  
 
      //en el caso de que ya exista un elemento tenemos que volver a organizadorlos haciendo una comparación
      
    
}



void LayerNode::display()
{
  node* temp = root;
  while(temp != nullptr)
    {
      std::cout<<"Genero: "<<temp->gender<<" Edad: "<<temp->age<<" Locacion: "<<temp->location<<std::endl;
      //std::cout<<"quien es baja: "<<temp->nextAge<<std::endl;
      temp = temp->next;
 
    }
  
}

void LayerNode::test()
{
  node* temp = root;
  while(temp != nullptr)
    {
      std::cout<<temp->location<<" ";
      temp = temp->nextLocation;

    }
  std::cout<<std::endl;
}

void LayerNode::findNodeCity(node* &pNode)
{
  pNode->nextLocation = city;
  city = pNode;
}


void LayerNode::findNodeGender(node *&pNode)
{
  if(pNode->gender == true)
    {
      //es mujer
      pNode->nextGender = wom;
      wom = pNode;
    }
  else
    {
      //es hombre
      pNode->nextGender = men;
      men = pNode;
    }
}


void LayerNode::findNodeAge(node* &pNode)
{
  
  //tiene como parametro un nodo y va a buscar asociar de la mejor manera
  //comienzo con la edad
  //tengo asi que dividir por tres edades: menores, mediana y alta
  //baja(0-21) media(22-55), alta(56 en adelante)

  if(pNode->age >= BAJAA && pNode->age <= BAJAB)
    {
      //entra al primer rango
      pNode->nextAge = baja;
      baja = pNode;
    }
  else if(pNode->age >= MEDIANAA && pNode->age <= MEDIANAB)
    {
      pNode->nextAge = mediana;
      mediana = pNode;
    }
  else if(pNode->age > ALTAA)
    {
      pNode->nextAge = alta;
      alta = pNode;
    }
  
}

