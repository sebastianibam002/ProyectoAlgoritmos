#ifndef _LAYERNODE_HPP
#define _LAYERNODE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <set>
//libreria para poder trabajar con el archivo de tipo texto
#include <fstream>
//es la estructura que contiene las direcciones a cad auno de sus elementos en las 3 estructuras que las van a estar almacenando

//ahora bien toca hacer la parte que divide los generos en dos mapas



/*
ESTRUCTURA GENERAL QUE CONTIENE A TODOS LOS ELEMENTOS
*/

/*

struct nodeMaster
{
  int idUnico;
  int age;
  bool gender;
  std::string location;
};


class BDCovid
{
private:
  vector<nodeMaster*> tabla ;//es la general
  GenderMap genderMap;//contine los generos
  BinLoc binaryTree;//contirne las edades
  //colocar set
public:
  BDCovid();
  ~BDCovid();
};

BDCovid::BDCovid()
{
  
  
  
  
}



*/



/*

  ACA COMIENZA EL MAPA QUE SE USA PARA EL GENERO

 */



const int INITIAL_SIZE = 5;

struct nodeGender
{
  bool value;
  int key;
  nodeGender* next;
};

class GenderMap
{
private:
  nodeGender** table;
  int table_size;
  int count;

  void reHash();
  int hash_fun(int key);
  nodeGender* search_bucket(int i, int key);
public:
  GenderMap();
  ~GenderMap();

  int size();
  bool empty();

  void insert(int pKey, bool value);
  void display();
  void clear();
  std::vector<int> generarLista(bool pGenero);//genera un vector que contiene los nombres que contienen cierta propiedad
  void test();
  
};


void GenderMap::test()
{
    //inicializar los atributos
  std::ifstream ifs("dataset.txt");
  std::string line = "";
  
  if(ifs.good())
    {
      while(!ifs.eof())
	{
	  std::getline(ifs, line);
	  std::cout<<line<<std::endl;
	  //se extrae linea y se guarda en line
	  
	  int cont1 = 0;
	  //bool para cada uno de los atributos
	  bool id = true;
	  bool gender = true;
	  bool age = true;
	  bool loc = true;
	  for(int i = 0; i < line.length(); i++)
	    {

	      nodeMaster* temp = new nodeMaster;
	      //recorro la linea
	      if(line[i] == ',')
		{
		  
		  //separo el espacio en memoria
		  if(id)
		    {
		      temp->idUnico = int(line[i:cont1]);
		      id = false;
		      cont1 = i;
		      std::cout<<temp->idUnico<<std::endl;
		    }

		  
		}
	      delete temp;
	      //tabla.push_back(temp);
	    }
	}
    }

  ifs.close();

}


std::vector<int> GenderMap::generarLista(bool pGenero)
{
  //recordar si es true es mujer si es hombre es false


  /*
   *
   *  std::cout<<count<<" elements:\n";
  nodeGender* cursor;
  for(int i = 0; i <table_size; ++i)
    {
      cursor = table[i];
      while(cursor != nullptr)








	{
	  std::cout<<"("<<cursor->key<< ","<<cursor->value<<")";
	  cursor =cursor->next;
	}
      std::cout<<std::endl;
    }
   *
   *
   */

  std::vector<int> retorno;
  nodeGender* cursor;
  
  for(int i = 0; i <table_size; i++)
    {
      cursor = table[i];
      while(cursor != nullptr)
	{
	  if(cursor->value == pGenero)
	    {
	      retorno.push_back(cursor->key);
	    }
	}
    }
  
}


void GenderMap::reHash()
{

  int old_table_size = table_size;
  nodeGender **old_table = table;
  table_size = 2*table_size;
  table = new nodeGender*[table_size];
  for(int i = 0; i < table_size;++i) table[i] = nullptr;
  count = 0;
  //un cursor para ir recorriendolo
  nodeGender *cursor;
  //creo la nueva tabla
  
  
  for(int i = 0; i < old_table_size; ++i)
    {
      cursor = old_table[i];
      while(old_table[i] != nullptr)
	{
	  insert(cursor->key, cursor->value);
	  cursor = cursor->next;
	  delete old_table[i];
	  old_table[i] = cursor;
	}
    }
  delete[] old_table;

}

GenderMap::~GenderMap()
{
  clear();
  delete[] table;
}


void clear_bucket(nodeGender* pNodo)
{
  nodeGender* temp;
  
  if(pNodo != nullptr)
    {
      // std::cout<<pNodo->key<<std::
      temp = pNodo->next;
      delete pNodo;
      
      clear_bucket(temp);
    }
  
}

void GenderMap::clear()
{

  
  for(int i = 0; i < table_size; ++i)
    {
      clear_bucket(table[i]);
      table[i] = nullptr;
      //std::cout<<table[i]<<std::endl;
      
    }

}




GenderMap::GenderMap()
{
  
  table_size = INITIAL_SIZE;
  table = new nodeGender*[INITIAL_SIZE];
  for(int i = 0; i < table_size; i++)
    { 
      table[i] = nullptr;
    }
  count = 0;
}

int GenderMap::size()
{
  return count;
}

bool GenderMap::empty()
{
  return count == 0;
}

int GenderMap::hash_fun(int key)
{

  return key%table_size;
  
}

void GenderMap::insert(int pKey, bool value)
{
  int entra = hash_fun(pKey);
  nodeGender* esta = search_bucket(entra, pKey);
  //
  //std::cout<<"es nullptr: "<< esta<<std::endl;
  
  if(esta == nullptr && count < (2*table_size))
    {
      nodeGender*temporal = new nodeGender;
      temporal->value = value;
      temporal->key = pKey;
      //el next ahora es el primero del tabl
      temporal->next = table[entra];
      //lo introduzco al inicio del bucket
      table[entra]= temporal;
      count++;
    }
  else if(esta == nullptr && count == (2* table_size))
    {
      //hay que hacer el rehash
      reHash();
      insert(pKey, value);
    }
  else
    {
      //remplaza
      
      esta->value=value;
    }
  //table[entra] = temp;
  
  
  
}

nodeGender* GenderMap::search_bucket(int i, int key)
{

  nodeGender* elemento = new nodeGender;
  if(table[i] != nullptr)
    {
      
      elemento->key = table[i]->key;
      elemento->value = table[i]->value;
      elemento->next = table[i]->next;
      
      while(elemento != nullptr)
	{
	  
	  if(elemento->key == key)
	    return elemento;
	  elemento = elemento->next;
	  
	}
    }


  return nullptr;
}

void GenderMap::display()
{
  std::cout<<count<<" elements:\n";
  nodeGender* cursor;
  for(int i = 0; i <table_size; ++i)
    {
      cursor = table[i];
      while(cursor != nullptr)
	{
	  std::cout<<"("<<cursor->key<< ","<<cursor->value<<")";
	  cursor =cursor->next;
	}
      std::cout<<std::endl;
    }
}


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



/* CLASE QUE CREA UN SET PARA CADA DEPARTAMENTO */

class DptoSet{
private:
  std::set<int> antioquia; // 05
  std::set<int> atlantico; // 08
  std::set<int> bogota; // 11
  std::set<int> bolivar; // 13
  std::set<int> boyaca; // 15
  std::set<int> caldas; // 17
  std::set<int> caqueta; // 18
  std::set<int> cauca; // 19
  std::set<int> cesar; // 20
  std::set<int> cordova; // 23
  std::set<int> cundinamarca; // 25
  std::set<int> choco; // 27
  std::set<int> huila; // 41
  std::set<int> la_guajira; // 44
  std::set<int> magdalena; //47
  std::set<int> meta; // 50
  std::set<int> narino; // 52
  std::set<int> norte_de_santander; // 54
  std::set<int> quindio; // 63
  std::set<int> risaralda; // 66
  std::set<int> santander; // 68
  std::set<int> sucre; // 70
  std::set<int> tolima; // 73
  std::set<int> valle_del_cauca; // 76
  std::set<int> arauca; // 81
  std::set<int> casanare; // 85
  std::set<int> putumayo; // 86
  std::set<int> san_andres; // 88
  std::set<int> amazonas; // 91
  std::set<int> guainia; // 94
  std::set<int> guaviare; // 95
  std::set<int> vaupes; //  97
  std::set<int> vichada; //  99
  std::vector<int> interseccion;

public:
  DptoSet();
  ~DptoSet();

  void insert(int pKey, bool value);
  void display();

};


DptoSet::~DptoSet(){
  antioquia.clear(); // 05
  atlantico.clear(); // 08
  bogota.clear(); // 11
  bolivar.clear(); // 13
  boyaca.clear(); // 15
  caldas.clear(); // 17
  caqueta.clear(); // 18
  cauca.clear(); // 19
  cesar.clear(); // 20
  cordova.clear(); // 23
  cundinamarca.clear(); // 25
  choco.clear(); // 27
  huila.clear(); // 41
  la_guajira.clear(); // 44
  magdalena.clear(); //47
  meta.clear(); // 50
  narino.clear(); // 52
  norte_de_santander.clear(); // 54
  quindio.clear(); // 63
  risaralda.clear(); // 66
  santander.clear(); // 68
  sucre.clear(); // 70
  tolima.clear(); // 73
  valle_del_cauca.clear(); // 76
  arauca.clear(); // 81
  casanare.clear(); // 85
  putumayo.clear(); // 86
  san_andres.clear(); // 88
  amazonas.clear(); // 91
  guainia.clear(); // 94
  guaviare.clear(); // 95
  vaupes.clear(); //  97
  vichada.clear(); //  99
  interseccion.clear();
  //delete[] table;
}

DptoSet::DptoSet(){
  std::set<int> antioquia {}; // 05
  std::set<int> atlantico {}; // 08
  std::set<int> bogota {}; // 11
  std::set<int> bolivar {}; // 13
  std::set<int> boyaca {}; // 15
  std::set<int> caldas {}; // 17
  std::set<int> caqueta {}; // 18
  std::set<int> cauca {}; // 19
  std::set<int> cesar {}; // 20
  std::set<int> cordova {}; // 23
  std::set<int> cundinamarca {}; // 25
  std::set<int> choco {}; // 27
  std::set<int> huila {}; // 41
  std::set<int> la_guajira {}; // 44
  std::set<int> magdalena {}; //47
  std::set<int> meta {}; // 50
  std::set<int> narino {}; // 52
  std::set<int> norte_de_santander {}; // 54
  std::set<int> quindio {}; // 63
  std::set<int> risaralda {}; // 66
  std::set<int> santander {}; // 68
  std::set<int> sucre {}; // 70
  std::set<int> tolima {}; // 73
  std::set<int> valle_del_cauca {}; // 76
  std::set<int> arauca {}; // 81
  std::set<int> casanare {}; // 85
  std::set<int> putumayo {}; // 86
  std::set<int> san_andres {}; // 88
  std::set<int> amazonas {}; // 91
  std::set<int> guainia {}; // 94
  std::set<int> guaviare {}; // 95
  std::set<int> vaupes {}; //  97
  std::set<int> vichada {}; //  99
  std::vector<int> interseccion; ///////////////////////////////////////////

}


void DptoSet::insert(){

}


void DptoSet::display(){

}



#endif
