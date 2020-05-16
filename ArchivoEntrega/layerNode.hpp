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

#include <stdio.h>


/*
***************************************************
ACA COMIENZA EL MAPA QUE SE USA PARA EL GENERO
************************************************
*/



const int INITIAL_SIZE = 5;

struct nodeGender
{
  //el value que corresponde al genero
  bool value;
  //el key que es el id unico
  int key;
  //el next indicando el siguiente en el bucket
  nodeGender* next;
};


class GenderMap
{
private:
  //como es parecido a un mapa se usa una tabla hash 
  nodeGender** table;
  int table_size;
  int count;

  //el que se encarga de volver a acomodar a todos los eleemntos
  void reHash();
  //la funcion has que se tiene
  int hash_fun(int key);
  //para buscar en el bucket
  nodeGender* search_bucket(int i, int key);
public:
  //constructor y destructor de la clase
  GenderMap();
  ~GenderMap();

  //metodos base
  int size();
  
  bool empty();

  //para insetar un elemento dado un id unico y un valor que es el genero
  void insert(int pKey, bool value);
  //para ver como se van organizando se inluye el display
  void display();
  //con el fin de borrarlo al final
  void clear();
 
  std::vector<int> generarLista(bool pGenero);//genera un vector que contiene los nombres que contienen cierta propiedad es decir el genero
  //metodo para poder ir probando los demas metodos
  void test();
  
};


//no retorna nada y no tiene parametro es probar metodos privados
void GenderMap::test()
{
  std::cout<<"Test"<<std::endl;
}

//requiere una variable de tipo booleano donde true es mujern y false es hombre y retorna un vector con los ids de estos
std::vector<int> GenderMap::generarLista(bool pGenero)
{
  //recordar si es true es mujer si es hombre es false

  std::vector<int> retorno;
  nodeGender* cursor = new nodeGender;
  std::cout<<"generando lista generos.."<<std::endl;
  //se recorre tabla hash como el set
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

//destructor
GenderMap::~GenderMap()
{
  clear();
  delete[] table;
}

//forma recursiva de borrar un bucket, parametro el nodo de la tabla y no retorna nada
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

//wrapper para clear_bucket con cada uno de los elementos de table_size
void GenderMap::clear()
{

  
  for(int i = 0; i < table_size; ++i)
    {
      clear_bucket(table[i]);
      table[i] = nullptr;
      //std::cout<<table[i]<<std::endl;
      
    }

}



//constructor
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

//retorna el numero de elementos, no requiere parametros de entrada
int GenderMap::size()
{
  return count;
}

//retorna si esta vacio, no requiere parametro s de entrada
bool GenderMap::empty()
{
  return count == 0;
}

//funcion hash que organiza donde deberian ir los elementos
int GenderMap::hash_fun(int key)
{

  return key%table_size;
  
}
//insert a la estructura, requiere la llave que es el id unico y genero y no retorna

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

//metodo que retorna el apuntador a nodeGender de en que bucket se encuentra el elemento en teoria

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
//se utiliza para ver como esta quedando la estructura
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
 *ACA COMIENZA LA ESTRUCTURA QUE CONTIENE LA INFORMACION DE LA EDAD EN UN BINARY TREE
 *
 */

//corresponde al rango de error que puede haber entre los rangos de edad, por ejemplo si se introduce 10 como edad minima pero el minimo elemento es 15 entonces va viendo si se encuentra y así hasta que llegue al valor minimo
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

  //el padre
  nodeLoc* parent;
  
};



class BinLoc
{

private:
  //el primer elemento que se introduce
  nodeLoc* root;
  //funcion que muetra los atributos de un node
  void displayNode(nodeLoc* pNode, int count);
  //funcion que permite insertar un nodo dada un idUnico, edad, el padre y el nodo base
  void insertNode(nodeLoc* &pNode, int pKey, int pIdUnico, nodeLoc* pParent);
  //funcion para destruir recursivamente todos los elementos de la estructura
  void destroyRecursive(nodeLoc* pNode);
  //encuentra el maximo en el arbol (hablando de edad)
  nodeLoc* maximum(nodeLoc *t);
  //encuentra el minimo en el arbol (hablando de edad)
  nodeLoc* minimum(nodeLoc *t);
  //encuentra un nodo, dada la edad que es el mismo idunico y el nodo desde donde debe comenzar a buscar
  nodeLoc* findNode(nodeLoc* pNode, int pEdad);
  //almacena la cantidad de elementos que hay en el arbol
  int size;
public:
  //constructor inicializ los atributos
  BinLoc(){root = nullptr;}
  //destructor recursivo
  ~BinLoc(){destroyRecursive(root);}
  //wrapper para insertar un elemento con la propiedad de los arboles binarios, aunque permite elementos repetidos es decir el key no es unica mas su valor si lo es
  void insert(int pKey, int pIdUnico){insertNode(root, pKey, pIdUnico, nullptr);}
  //muestra en la terminal como queda el arbol
  void display();
  //encuentra el predecesor dado un nodo
  nodeLoc* predecessor(nodeLoc *pNode);
  //encuentra el sucesor dado un nodo
  nodeLoc* successor(nodeLoc *pNode);
  //wrapper para el metodo de find_node pero lo busca desde el root
  nodeLoc* find(int pEdad){return findNode(root, pEdad);}
  //revisa si contiene cierta edad
  bool contains(int pEdad);//este elemento existe en la estructura
  //busca el siguiente elemento que se encuentre en el arbol con la edad mas parecida dentro del rango del valor next
  int searchNext(int pEdad);
  //busca el anterior elemento que se encuentre en el arbol dentro del rango de next
  int searchLast(int pEdad);
  //retorna la cantidad de elementos que hay en el arbol
  int tamano();
  //metodo que dado un rango es decir un desde y un hasta retorna los elementos del arbol que se encuentran dentro del rango incluyente[pDesde, pHasta] siedo int enteros
  std::vector<int> rango(int pDesde, int pHasta);
  //metodo para probar metodos privados de la estructura
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
		  retorno.push_back(temp->idUnico);
		  temp = successor(temp);
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
  
public:
  DptoSet();

  //le introduzco una llave que es el idUnico y el departametno en formato "amazonas"
  void insert(int pKey, std::string value);
  //muestra los elementos que hay en un set dado
  void displaySet(int pNumero);
  //muestra todos los elementos que hay en el todos los set
  void display();
  //genera un vector dado un numero de de que departamento se esta hablando
  std::vector<int> generarLista(int valor);
  //genera una union entre los ids de las personas que se encuentren en departamentos dados en formato("Amazonas,Bogota,Cundinamarca,Antioquia")
  std::vector<int> unionDepto(std::string pString); 
  //metodo para ir probando los metodos privados de la clase
  void test();
};




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
  
  int lista[33] = {5,8,11,13,15,17,18,19,20,23,25,27,41,44,47,50,52,54,63,66,68,70,73,76,81,85,86,88,91,94,95,97,99};
    
  for(int i = 0; i < 33;i++)
    {

      //std::cout<<"casos: "<<casos<<"lista[i]: "<<lista[i]<<std::endl;
      if(casos == lista[i])
	{
	  
	  (elementos[i]).insert(pKey);
	  
	}
      
    }
  

 
}

void DptoSet::displaySet(int pNumero)
{

  std::set<int>::iterator it;
  
  for(it = (elementos[pNumero]).begin(); it != elementos[pNumero].end(); it++)
    {
      std::cout<<*it<<" ";
    }

  std::cout<<std::endl;
}

void DptoSet::display()
{
  
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
  DptoSet depSet;//contene las locaciones
  //colocar set
public:
  //constructor
  BDCovid();
  //metodo que retorna un vector luego de filtrar los parametros, genero ,rango  de edad(desde, hasta), y una string de locacion ("Amazonas,Bogota")
  std::vector<int> busqueda(bool pGenero,int pDesde, int pHasta, std::string pLocation);
  //genera los archivos de tipo texto que luego python utiliza para poder hacer un display de la informacion dados los mismos parametro que busqueda
  void generarArchivoVis(bool pGenero,int pDesde, int pHasta, std::string pLocation);
};

BDCovid::BDCovid()
{
  //comienza a leer todos los valores que hay en el datasetfinal.txt
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
	      
	}
      
    }
  
  ifs.close();

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
  
  std::cout<<"hay: "<<retornoFinal.size()<<" personas que satisfacen los parametros de:"<< tabla.size()<<std::endl;

 
  return retornoFinal;
  
  
  
  
}



void BDCovid::generarArchivoVis(bool pGenero,int pDesde, int pHasta, std::string pLocation)
{

  //std::ifstream ifs("vis.txt");

  std::remove("vis.txt");
  //revisar si el archivo contiene un valor
  std::vector<int> resultado = busqueda(pGenero,pDesde, pHasta, pLocation);
  std::ofstream ofs("vis.txt",std::ios::app);

  bubble_sort(resultado);
  
  
  //std::cout<<std::endl;

  
  
  if(ofs.good())
    {
      
      //int elemento = std::stoi(tabla[resultado[0]-1]->location);
      for(int i = 0; i <tabla.size(); i++)
	{
	  
	  int elemento = binary_search(tabla[i]->idUnico,resultado);
	  if(elemento != -1)
	    {
	      ofs<<tabla[i]->location<<"\n";
	    }
	  //std::cout<<tabla[i]->idUnico<<" ";
	  
	}
      //std::cout<<std::endl;
      
    }
  
  /*
  for(int i = 0; i <resultado.size(); i++)
    std::cout<<resultado[i]<<" ";
  std::cout<<std::endl;
  */
  ofs.close();
  
  
}

#endif
