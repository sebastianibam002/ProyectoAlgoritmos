#ifndef _LAYERNODE_HPP
#define _LAYERNODE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <set>
//para ponerlas todas en  mayusculas
#include <cctype>

//libreria para poder trabajar con el archivo de tipo texto
#include <fstream>
//es la estructura que contiene las direcciones a cad auno de sus elementos en las 3 estructuras que las van a estar almacenando

//ahora bien toca hacer la parte que divide los generos en dos mapas




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
  std::cout<<"e¡test"<<std::endl;
}


std::vector<int> GenderMap::generarLista(bool pGenero)
{
  //recordar si es true es mujer si es hombre es false



  std::vector<int> retorno;
  nodeGender* cursor = new nodeGender;
  std::cout<<"generando lista generos.."<<std::endl;
  for(int i = 0; i <table_size; i++)
    {
      cursor = table[i];
      while(cursor != nullptr)
	{
	  //std::cout<<"cursor->key: "<<cursor->key<<"cursor->value: "<<cursor->value<<std::endl;
	  if(cursor->value == pGenero)
	    {
	      
	      retorno.push_back(cursor->key);
	    }
	  cursor = cursor->next;
	}
    }

  return retorno;
  
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

int NEXT = 20;

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



//int contadorId = 0;
class BinLoc
{

private:
  nodeLoc* root;
  void displayNode(nodeLoc* pNode, int count);
  //
  void insertNode(nodeLoc* &pNode, int pKey, int pIdUnico, nodeLoc* pParent);
  void destroyRecursive(nodeLoc* pNode);
  nodeLoc* maximum(nodeLoc *t);
  nodeLoc* minimum(nodeLoc *t);
  nodeLoc* findNode(nodeLoc* pNode, int pEdad);
  int size;
public:
  BinLoc(){root = nullptr;}
  ~BinLoc(){destroyRecursive(root);}
  void insert(int pKey, int pIdUnico){insertNode(root, pKey, pIdUnico, nullptr);}
  void display();
  nodeLoc* predecessor(nodeLoc *pNode);
  nodeLoc* successor(nodeLoc *pNode);
  nodeLoc* find(int pEdad){return findNode(root, pEdad);}
  bool contains(int pEdad);//este elemento existe en la estructura
  int searchNext(int pEdad);
  int searchLast(int pEdad);
  int tamano();
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
  //std::cout<<"tamano: "<<tamano()<<std::endl;
  if(pDesde != -1 && pHasta != -1)
    {
      std::vector<int> retorno;
      if(contains(pDesde) && contains(pHasta))
	{
	  nodeLoc* temp = find(pDesde);
	  
	  nodeLoc* tempDos = find(pHasta);
	  //los numeros mayores
	  // std::cout<<"El desde: "<<find(pDesde)->edad<<" el phasta: "<<find(pHasta)->edad<<std::endl;
	  while(temp != nullptr)
	    {
	      if(temp->idUnico == tempDos->idUnico)
		{
		  //aca es donde deja de ver si hay mas con el mismo valor del predecesor
		  
		  retorno.push_back(temp->idUnico);
		  break;
		}
	      else
		{

		  
		  //std::cout<<"id unico: "<<temp->idUnico<<std::endl;
		  retorno.push_back(temp->idUnico);
		  //retorno.push_back(tempDos->idUnico);
		  //std::cout<<"paso primer filtro"<<" temp "<<temp->right<<std::endl;
		  
		  //std::cout<<"elemento introducido"<<std::endl;
		  temp = successor(temp);
		  //tempDos = predecessor(tempDos);
		  //std::cout<<"llego"<<std::endl;
		  //std::cout<<"siguiente elemento "<< temp->edad<<std::endl;
		  if(tempDos->idUnico == temp->idUnico)
		    {
		      while(temp->edad == tempDos->edad)
			{
			  retorno.push_back(temp->idUnico);
			  temp = successor(temp);
			}
		      break;
		    }

		  
		}
	    }


	  return retorno;
	  
	}
      else
	{

	  //std::cout<<"caso del else rango: "<<searchNext(pDesde) <<" hasta: "<< searchLast(pHasta)<<std::endl;
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

int BinLoc::tamano()
{
  return size;
}

void BinLoc::insertNode(nodeLoc *&pNode, int pKey, int pIdUnico, nodeLoc *pParent)
{
  
  if(pNode == nullptr)
    {
      
      pNode = new nodeLoc;
      pNode->edad = pKey;
      pNode->left = nullptr;
      pNode->right = nullptr;
      pNode->parent = pParent;
      pNode->idUnico = pIdUnico;
      size++;
    }
  else
    {
     
	  if(pKey < pNode->edad)
	    {
	      insertNode(pNode->left, pKey, pIdUnico , pNode);
	    }
	  else
	    {
	      insertNode(pNode->right, pKey, pIdUnico, pNode);
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

  //contiene cada uno de los sets que se crearon
  std::vector<std::set<int>> elementos;


  //metodo que hace toda la parte de la busqueda que necesitamos


public:
  DptoSet();
  //~DptoSet();

  //le introduzco una llave que es el idUnico y el departametno en formato "amazonas"
  void insert(int pKey, std::string value);
  void displaySet(int pNumero);
  void display();
  std::vector<int> generarLista(int valor);
  std::vector<int> unionDepto(std::string pString); ///////////////////////////////////////////
  void test();
};

/*
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
  
  }*/



DptoSet::DptoSet()
{
  std::set<int> antioquia; // 05 == 0
  std::set<int> atlantico {}; // 08 ==1
  std::set<int> bogota {}; // 11 == 2
  std::set<int> bolivar {}; // 13 == 3
  std::set<int> boyaca {}; // 15 == 4
  std::set<int> caldas {}; // 17 == 5
  std::set<int> caqueta {}; // 18 == 6
  std::set<int> cauca {}; // 19 == 7 
  std::set<int> cesar {}; // 20== 8
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
  std::set<int> vichada; //  99
  
  std::vector<std::set<int>> prueba{antioquia, atlantico, bogota, bolivar, boyaca, caldas, caqueta, cauca, cesar, cordova, cundinamarca, choco, huila, la_guajira, magdalena, meta, narino, norte_de_santander, quindio, risaralda, santander, sucre, tolima, valle_del_cauca, arauca, casanare, putumayo, san_andres, amazonas, guainia, vaupes, vichada};
  elementos = prueba;
  //std::vector<std::set<int>> elementos;
 
}


void DptoSet::test()
{
  std::vector<int> prueba = generarLista(8);
  for(unsigned int i = 0; i < prueba.size(); i++)
    {
      std::cout<<prueba[i]<<" ";
    }
  std::cout<<std::endl;


  unionDepto("Amazonas,Putumayo");
}


std::vector<int> DptoSet::generarLista(int numero)
{

  std::vector<int> retorno{};
  int contador = 0;
  
  int lista[34] = {5,8,11,13,15,17,18,19,20,23,25,27,41,44,47,50,52,54,63,66,68,70,73,76,81,85,86,88,91,94,95,97,99};
  //std::cout<<"el valor que entro: "<<numero <<std::endl;
  for(int i = 0; i < 34; i++)
    {
      
      if(numero == lista[i])
	{
	  //si numero es igual al de la lista

	  if(elementos[i].size() != 0)
	    {
	      std::set<int>::iterator it;
	      //std::cout<<"cantidad de elementps

	      for(it = elementos[i].begin(); it !=  elementos[i].end(); it++)
		{
		  //std::cout<<"el *it: "<<(*it)<<std::endl;
		  retorno.push_back(*it);
		  
		}
	    }

	  break;
	}

    }

  return retorno;

  
}


std::string mayus(std::string pCadena)
{

  std::string retorno = "";
  for(int i = 0; i < pCadena.length(); i++)
    {
      retorno += std::toupper(pCadena[i]);
    }

  return retorno;
}
std::vector<int> DptoSet::unionDepto(std::string pString)
{
  //dada una string hace una interseccion entre los departamentos dados
  std::vector<std::string> numeros;
  int count1 = 0;
  int count2 = 0;
  pString+= ",";
  for(int i = 0; i < pString.length(); i++)
    {
      
      if(pString.substr(i,1) == ",")
	{
	  //encontre una separacion
	  int count2 = pString.find(",", count1);
	  //std::cout<<"count2: "<<count2<<std::endl;
	  //pString.replace(count2,1,"");
	  numeros.push_back(mayus(pString.substr(count1,(count2-count1))));
	  //std::cout<<"Word: "<<mayus(pString.substr(count1,(count2-count1)))<<std::endl;
	  count1 = count2+1;
	  
	}
      
      
    }
  
  if(numeros.size() == 0)
    {
      numeros.push_back(pString);
    }
  
  /*
  std::cout<<"Lugares: ";
  for(unsigned int i = 0; i < numeros.size();i++)
    {
      std::cout<<numeros[i] <<" ";
    }
  std::cout<<std::endl;
  */
  


  //por cada uno de los elemntos que se tiene hay que adignarle primero que todo un numero y hay que generar una lista para asi

  std::vector<std::vector<int>> vectorPadre;
  //std::cout<<"Tengo estos("<<numeros.size()<<"): ";
  for (unsigned int i = 0; i < numeros.size(); i++)
    {
      //se recorre todos los elementos
      if(numeros[i] == "ANTIOQUIA")
	{
	  //std::cout<<"entre a antioquia"<<std::endl;
	  vectorPadre.push_back(generarLista(5));
	}
      else if(numeros[i] == "ATLANTICO")
	{
	  vectorPadre.push_back(generarLista(8));
	}
      else if(numeros[i] == "BOGOTA")
	{
	  //std::cout<<"entre a Bopgpta"<<std::endl;
	  vectorPadre.push_back(generarLista(11));
	}
      else if(numeros[i] == "BOLIVAR")
	{
	  vectorPadre.push_back(generarLista(13));
	}
      else if(numeros[i] == "BOYACA")
	{
	  vectorPadre.push_back(generarLista(15));
	}
      else if(numeros[i] == "CALDAS")
	{
	  vectorPadre.push_back(generarLista(17));
	}
      else if(numeros[i] == "CAQUETA")
	{
	  vectorPadre.push_back(generarLista(18));
	}
      else if(numeros[i] == "CAUCA")
	{
	  vectorPadre.push_back(generarLista(19));
	}
      else if(numeros[i] == "CESAR")
	{
	  vectorPadre.push_back(generarLista(20));
	}
      else if(numeros[i] == "CORDOVA")
	{
	  vectorPadre.push_back(generarLista(23));
	}
      else if(numeros[i] == "CUNDINAMARCA")
	{
	  vectorPadre.push_back(generarLista(25));
	}
      else if(numeros[i] == "CHOCO")
	{
	  vectorPadre.push_back(generarLista(27));
	}
      else if(numeros[i] == "HUILA")
	{
	  vectorPadre.push_back(generarLista(41));
	}
      else if(numeros[i] == "LA GUAJIRA")
	{
	  vectorPadre.push_back(generarLista(44));
	}
      else if(numeros[i] == "MAGDALENA")
	{
	  vectorPadre.push_back(generarLista(47));
	}
      else if(numeros[i] == "META")
	{
	  vectorPadre.push_back(generarLista(50));
	}
      else if(numeros[i] == "NARINO")
	{
	  vectorPadre.push_back(generarLista(52));
	}
      else if(numeros[i] == "NORTE DE SANTANDER")
	{
	  vectorPadre.push_back(generarLista(54));
	}
      else if(numeros[i] == "QUINDIO")
	{
	  vectorPadre.push_back(generarLista(63));
	}
      else if(numeros[i] == "RISARALDA")
	{
	  vectorPadre.push_back(generarLista(66));
	}
      else if(numeros[i] == "SANTANDER")
	{
	  vectorPadre.push_back(generarLista(68));
	}
      else if(numeros[i] == "SUCRE")
	{
	  vectorPadre.push_back(generarLista(70));
	}
      else if(numeros[i] == "TOLIMA")
	{
	  vectorPadre.push_back(generarLista(73));
	}
      else if(numeros[i] == "VALLE DEL CAUCA")
	{
	  vectorPadre.push_back(generarLista(76));
	}
      else if(numeros[i] == "ARAUCA")
	{
	  vectorPadre.push_back(generarLista(81));
	}
      else if(numeros[i] == "CASANARE")
	{
	  vectorPadre.push_back(generarLista(85));
	}
      else if(numeros[i] == "PUTUMAYO")
	{
	  vectorPadre.push_back(generarLista(86));
	}
      else if(numeros[i] == "SAN ANDRES")
	{
	  vectorPadre.push_back(generarLista(88));
	}
      else if(numeros[i] == "AMAZONAS")
	{
	  vectorPadre.push_back(generarLista(91));
	}
      else if(numeros[i] == "GUAINIA")
	{
	  vectorPadre.push_back(generarLista(94));
	}
      else if(numeros[i] == "GUAVIARE")
	{
	  vectorPadre.push_back(generarLista(95));
	}
      else if(numeros[i] == "VAUPES")
	{
	  vectorPadre.push_back(generarLista(97));
	}
      else if(numeros[i] == "VICHADA")
	{
	  vectorPadre.push_back(generarLista(99));
	}
      else
	{
	  std::cout<<"Error: "<<numeros[i]<<" no existe"<<std::endl;
	}
    }

  //std::cout<<std::endl;

  //ahora si voy a crear el vector que contenga todos los ids
  //std::cout<<"el size de vector padre: "<<vectorPadre.size()<<std::endl;
  std::vector<int> retorno{};
  
  for(int i =0; i< vectorPadre.size();i++)
    {
      for(int e = 0; e<vectorPadre[i].size();e++)
	{
	  //std::cout<<"el tamano del vector hijo("<<i<<"): "<<vectorPadre[i].size()<<std::endl;
	  retorno.push_back((vectorPadre[i])[e]);
	}
    }
  

  
  return retorno;
}

void DptoSet::insert(int pKey, std::string value)
{
  //debe bucar que value corresponde para esto hay que compararlos con las que existan
  
  //5,8,11,13,15,17,18,19,20,23,25,27,41,44,47,50,52,54,63,66,68,70,73,76,81,85,86,88,91,94,95,97,99
  //std::cout<<"casos: "<<value<<std::endl;
  int casos = std::stoi(value);
  
  int lista[34] = {5,8,11,13,15,17,18,19,20,23,25,27,41,44,47,50,52,54,63,66,68,70,73,76,81,85,86,88,91,94,95,97,99};
    
  for(int i = 0; i < 34;i++)
    {

      //std::cout<<"casos: "<<casos<<"lista[i]: "<<lista[i]<<std::endl;
      if(casos == lista[i])
	{
	  
	  (elementos[i]).insert(pKey);
	  
	}
      
    }
  

  //elementos[0].insert(2);
 
}

void DptoSet::displaySet(int pNumero)
{

  std::set<int>::iterator it;
  //std::cout<<"este tiene: "<<elementos[pNumero].size();
  for(it = (elementos[pNumero]).begin(); it != elementos[pNumero].end(); it++)
    {
      std::cout<<*it<<" ";
    }

  std::cout<<std::endl;
}

void DptoSet::display()
{
  //std::cout<<"elementos size: "<<elementos.size()<<std::endl;
  for(int i = 0; i < elementos.size();i++)
    {
      if(elementos[i].size() != 0)
	{
	  std::cout<<"Elementos("<<i<<"): ";
	  displaySet(i);
	}
    }
}

/*
ESTRUCTURA GENERAL QUE CONTIENE A TODOS LOS ELEMENTOS
*/



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
  std::vector<nodeMaster*> tabla ;//es la general
  
  GenderMap genderMap;//contine los generos
  BinLoc binaryTree;//contirne las edades
  DptoSet depSet;
  //colocar set
public:
  BDCovid();
  //~BDCovid();
  std::vector<int> busqueda(bool pGenero,int pDesde, int pHasta, std::string pLocation);
  void generarArchivoVis(bool pGenero,int pDesde, int pHasta, std::string pLocation);
};

BDCovid::BDCovid()
{
  //inicializar los atributos
  std::ifstream ifs("datasetFinal.txt");
  std::string line = "";

  
  if(ifs.good())
    {
      //int contadorBorrar = 0;
      while(!ifs.eof())
	{
	  std::getline(ifs, line);


	  if(line != "")
	    {
	      //std::cout<<line<<std::endl;
	      //se extrae linea y se guarda en line
	      int cont1 = 0;
	      //bool para cada uno de los atributos
	      bool id = true;
	      bool gender = true;
	      bool age = true;
	      bool loc = true;
	      nodeMaster* temp = new nodeMaster;
	      
	      //contadorBorrar++;
	      for(int i = 0; i < line.length(); i++)
		{
		  
		  //recorro la linea
		  if(line[i] == ',')
		    {
		      
		      //separo el espacio en memoria
		      if(id)
			{
			  
			  int tempCont = line.find(",");
  
			  temp->idUnico = std::stoi(line.substr(cont1,tempCont));
			  id = false;
			  cont1 = i;
			  //std::cout<<temp->idUnico<<std::endl;
			}
		      else if(age)
			{
			  int tam = line.find(",", cont1+1);
			  //std::cout<<"tam: "<<tam<<" i: "<<cont1<<"substr"<< line.substr(cont1, tam)<<std::endl;
			  int pAge = std::stoi(line.substr(cont1+1, tam-1));
			  temp->age = pAge;
			  //lo introduzco al arbol
			  //BinLoc::insertNode(nodeLoc *&pNode, int pKey, int pIdUnico, nodeLoc *pParent)
			  binaryTree.insert(pAge, temp->idUnico);
			  //std::cout<<"prorblm bro? "<<pAge<<std::endl;
			  //std::cout<<"edad: "<<pAge<<"id: "<<temp->idUnico<<std::endl;
			  age = false;
			  cont1 = i;
			  
			  
			}
		      else if(gender)
			{
			  
			  //std::cout<<line.substr(cont1+1,1)<<std::endl;
			  if(line.substr(cont1+1,1) == "F")
			    {
			      //std::cout<<"mujer"<<std::endl;
			      temp->gender = true;
			      
			      
			    }
			  else if(line.substr(cont1+1,1) == "M")
			    {
			      //std::cout<<"hombre"<<std::endl;
			      temp->gender = false;
			    }

			  genderMap.insert(temp->idUnico, temp->gender);
			  gender = false;
			  cont1 = i;
			}
		      else if(loc)
			{
			  int tam = line.find(",",cont1+1);
			  //el menos siete es importante aunque no se exactamente por que
			  //tam -= 7;
			  //std::cout<<"la segunda coma esa en: "<<tam<<std::endl;
			  int tam2 = line.find(",", tam);
			  
			  temp->location = line.substr(tam2+1, 2);
			  //std::cout<<"numero de departamento: "<<temp->location<<std::endl;
			  loc = false;
			  depSet.insert(temp->idUnico, temp->location);
			
			}
		    }
		
		}
	      tabla.push_back(temp);
	    }
	      
	  //std::cout<<"contador: "<<contadorBorrar<<" ifs: " <<!ifs.eof()<<std::endl;
	  //std::cout<<"Id("<<temp->idUnico<<") "<<"Age("<<temp->age<<") "<<"Gender("<<temp->gender<<") "<<"Location("<<temp->location<<") "<<std::endl;
	  //delete temp;
	  
	  
	}
      //std::cout<<"contadorb orrar: "<<contadorBorrar<<std::endl;
    }
  
  ifs.close();

  //binaryTree.display();
  /*
  //ahora para ver que esta todo
  for(unsigned int i = 0; i < tabla.size(); i++)
    {
      std::cout<<"Id("<<tabla[i]->idUnico<<") "<<"Age("<<tabla[i]->age<<") "<<"Gender("<<tabla[i]->gender<<") "<<"Location("<<tabla[i]->location<<") "<<std::endl;
    }
  
  
  std::cout<<"Gender Map display"<<std::endl;
  genderMap.display();
  //falta el de las localizacines

  std::cout<<"depSet*********************"<<std::endl;
  depSet.display();
  
  std::vector<int>pipal = depSet.unionDepto("antioquiA,BOGOTA");
  for(unsigned int i = 0; i < pipal.size(); i++)
    std::cout<<pipal[i]<<" ";
  std::cout<<std::endl;
  //std::cout<<"TEST"<<std::endl;
  //depSet.test();
  */
}

int binary_search(int x, const std::vector<int>&v)
{
  int left = 0, right = v.size()-1;
  while(left <= right)
    {
      int mid = (right+left)/2;
      if(v[mid]== x)
	return mid;
      else
	{
	  if(x> v[mid])
	    {
	      left = mid+1;
	    }
	  else
	    {
	      right = mid-1;
	    }
	}
    }
  return -1;
}

void swap(int i, int j, std::vector<int>& v){
  int temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
void bubble_sort(std::vector<int> &v)
{
  bool swap_used = true;
  while(swap_used)
    {
      swap_used = false;
      for(int i = 0; i < v.size()-1;++i)
	{
	  if(v[i]> v[i+1])
	    {
	      swap(i, i+1, v);
	      swap_used = true;
	    }
	}
    }
}


std::vector<int> BDCovid::busqueda(bool pGenero,int pDesde, int pHasta, std::string pLocation)
{
  /*
    GenderMap genderMap;//contine los generos
    BinLoc binaryTree;//contirne las edades
    DptoSet depSet;
  */
  std::vector<std::vector<int>> retorno;
  std::vector<int> retornoFinal;
  std::cout<<"antes de los generos"<<std::endl;
  retorno.push_back(genderMap.generarLista(pGenero));
  std::cout<<"ya se tienen los del genero: "<<retorno[0].size()<<std::endl;
  retorno.push_back(binaryTree.rango(pDesde, pHasta));
  std::cout<<"ya se tienen los de edad: "<<retorno[1].size()<<std::endl;
  retorno.push_back(depSet.unionDepto(pLocation));
  std::cout<<"ya se tienen los de locacion: "<<retorno[2].size()<<std::endl;
  
  //ahora bien un elemento es decir un elemento con id unico dado puede pasar si y sol si esta en las tres listas para esose vaa comparar de a pares
  //int elemento;
  /*
  for(int i = 0; i < retorno[1].size();i++)
    {
      std::cout<<retorno[1][i]<<" ";
    }
  std::cout<<std::endl;
  */
  //int contador = 0;
  //como se esta demorando tanto tiempo voy a usar binary search para enontrar las intersecciones
  /*
  for(int i = 0;i < retorno[2].size(); i++)
    {
      for(int e = 0; e < retorno[1].size();e++)
	{
	  for(int j = 0; j< retorno[0].size(); j++)
	    {
	      
	      
	      if(e != 0 && j == i && i == e && j == e)
		{
		  //std::cout<<"i: "<<i<<" j: "<<j<<" e: "<<e<<std::endl;
		  retornoFinal.push_back(i);
		}
	      //std::cout<<contador<<" "<<std::endl;
	    }
	}
    }
  
  */

  //std::cout<<"vector 1: "<<retorno[1].size()<<std::endl;
  std::vector<int> parcial;
  for(int i = 0; i < retorno[1].size(); i++)
    {
      
      int valor = binary_search(retorno[1][i], retorno[2]);
      
      if(valor != -1)
	{
	  //std::cout<<retorno[2][valor]<<std::endl;
	  parcial.push_back(retorno[2][valor]);
	}
    }
  //entonces hice el primer filtro

  /*
  for(int i = 0; i < retorno[0].size(); i++)
    {
      std::cout<<retorno[0][i]<<" ";
    }
  std::cout<<std::endl;
  el vector de generos no esta organizado
*/
  bubble_sort(retorno[0]);
  
  for(int i = 0; i < parcial.size(); i++)
    {
      int valor = binary_search(parcial[i], retorno[0]);
      //std::cout<<"elemento: "<<parcial[i]<<std::endl;
      if(valor != -1)
	{
	  retornoFinal.push_back(retorno[0][valor]);
	}
    }
  
  //del 

  std::cout<<"hay: "<<retornoFinal.size()<<" personas que satisfacen los parametros de:"<< tabla.size()<<std::endl;

  /*
  for(int i = 0; i < tabla.size();i++)
    {
      std::cout<<tabla[i]->idUnico<<" ";
    }
  std::cout<<std::endl;
  std::cout<<"persona:"<<tabla[0]->idUnico<<std::endl;
  */

 
  return retornoFinal;
  
  
  
  
}

void BDCovid::generarArchivoVis(bool pGenero,int pDesde, int pHasta, std::string pLocation)
{
  std::vector<int> resultado = busqueda(pGenero,pDesde, pHasta, pLocation);
  std::ofstream ofs("vis.txt",std::ios::app);
  if(ofs.good())
    {
      for(unsigned int i = 0; i < resultado.size();i++)
	{
	  int elemento = resultado[i];
	  ofs<<tabla[elemento-1]->location<<"\n";
	}

    }
  ofs.close();
  
  
}


#endif
