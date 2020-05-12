#include "nodeLayers.hpp"
//BAJO
int BAJAA = 0;
int BAJAB = 21;
//MEDIANA
int MEDIANAA = 22;
int MEDIANAB = 55;
//Alta
int ALTAA = 56;


bool firstTimeM = true;
bool firstTimeW = true;

bool firstB = true;
bool firstM = true;
bool firstA = true;

bool firstC = true;

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
  topG = nullptr;
  topG2 = nullptr;

  topB = nullptr;
  topM = nullptr;
  topA = nullptr;
  //topCity = new node;
  
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

  //primera vez que se inserta un genero
  if(firstTimeM && pGender == false)
    {
      //es el primer hombre que introduzco
      topG = nuevo;
      //firstTimeM = false;
    }
  
  else if(firstTimeW && pGender == true)
    {
      //el la primer mujer
      topG2 = nuevo;
      //firstTimeW = false;
    }
 
  //primera vez que se inserta cierta edad
  if(firstB && (pAge >= BAJAA && pAge <= BAJAB))
    {
      topB = nuevo;
      //firstB = false;
    }
  else if(firstM && (pAge >= MEDIANAA && pAge <= MEDIANAB))
    {
      topM = nuevo;
      //firstM = false;
    }
  else if(firstA && (pAge >= ALTAA))
    {
      topA = nuevo;
      //firstA = false;
    }
  //primera vez qu se inserta la ciudad
  if(firstC)
    {
      topCity = nuevo;
      //firstC = false;
    }
  

    
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

int LayerNode::countAge(int pGroup)
{
  int contador = 0;
 

  if(pGroup == 0)
    {
      //vamos a contar a los que son de edad baja
      node* temp = topB;
      
      while(temp != nullptr)
	{
	  contador++;
	  temp = temp->next;
	}
      
    }
  else if(pGroup == 1)
    {
      
      node* temp = topM;
      while(temp != nullptr)
	{
	  contador++;
	  temp = temp->next;
	}
    }
  else if(pGroup == 2)
    {
      
      node* temp = topA;
      while(temp != nullptr)
	{
	  contador++;
	  temp = temp->next;
	}
     
    }

  return contador;
}


int LayerNode::countGender(bool pSeleccion)
{
 
  int contador = 0;
  if(pSeleccion)
    {
      
      node* temp = topG2;
      while(temp != nullptr)
	{
	  contador++;
	  temp = temp->nextGender;
	}
    }
  else
    {
      node* temp = topG;
      while(temp != nullptr)
	{
	  contador++;
	  temp = temp->nextGender;
	} 
    }
    


  return contador;
}

void LayerNode::destroy(node* pNode)
{
  node* temp = pNode;
  //node* temp2 = new node;
  while(temp != nullptr)
    {

      //if(temp->next != nullptr)
      
      node* reTemp = temp->next;
      if(reTemp != nullptr)
	{
	  //std::cout<<"borrando: "<<temp->location<<" el siguiente es:"<<reTemp->location<<std::endl;
	  delete temp;
	  temp = reTemp;
	}
      else
	{
	  //std::cout<<"borrando: "<<temp->location<<std::endl;
	  delete temp;
	  break;
	}
      
    }
}

