#include "estructuraPersonas.hpp"

void EstructuraPersonas::insert_node(person *&pPersona, int pId, std::string pLocation, bool pGender, int pAge, person *p)
{

  if(pPersona == nullptr)
    {
      pPersona = new person;
      pPersona->id = pId;
      //atributos de una persona
      pPersona->location = pLocation;
      pPersona->gender = pGender;
      pPersona->age = pAge;
      //en el caso de que no tenga
      pPersona->left = nullptr;
      pPersona->right = nullptr;
      pPersona->parent = p;
    }
  else
    {
      if(pId != pPersona->id)
	{
	  if(pId < pPersona->id)
	    {
	      insert_node(pPersona->left, pId, pLocation, pGender, pAge, pPersona);
	    }
	  else
	    {
	      insert_node(pPersona->right, pId, pLocation, pGender, pAge, pPersona);
	    }
	}
    }

}
