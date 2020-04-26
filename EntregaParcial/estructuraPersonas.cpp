#include "estructuraPersonas.hpp"

void EstructuraPersonas::insert_node(persona *&node, T k, BSTNode<T> *p)
{

  if(node == nullptr)
    {
      node = new BSTNode<T>;
      node->key = k;
      node->left = nullptr;
      node->right = nullptr;
      node->parent = p;
    }
  else
    {
      if(k != node->key)
	{
	  if(k < node->key)
	    {
	      insert_node(node->left, k, node);
	    }
	  else
	    {
	      insert_node(node->right, k, node);
	    }
	}
    }

}
