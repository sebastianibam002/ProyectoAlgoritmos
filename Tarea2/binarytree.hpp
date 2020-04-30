#ifndef _BINARYTREE_HPP
#define _BINARYTREE_HPP

#include <iostream>

template <typename T>
struct BSTNode {
  T key;
  //numero de repeticiones del mismo elemento
  int reps;
  BSTNode<T> *left;
  BSTNode<T> *right;
  BSTNode<T> *parent;
};


template <typename T>
class BST {
private:
  BSTNode<T> *root;

  void insert_node(BSTNode<T>* &node, BSTNode<T>* p, T k);
  void destroy_recursive(BSTNode<T> *node);
  void display_node(BSTNode<T> *node, int count);
  BSTNode<T>* find_node(BSTNode<T> *node, T k);
  BSTNode<T>* minimum(BSTNode<T> *node);
  BSTNode<T>* maximum(BSTNode<T> *node);
  BSTNode<T>* predecessor(BSTNode<T> *node);
  BSTNode<T>* successor(BSTNode<T> *node);
  BSTNode<T>* remove_node(BSTNode<T>* &node, T k);
  int recursive_capacity(BSTNode<T>* node);

public:
  BST() { root = nullptr; }
  ~BST() { destroy_recursive(root); }
  //calcula el numero total de llaves registradas en el arbol es decir el numero total dse llaves con lasrepetidas
  int capacity();
  bool empty() { return root == nullptr; }
  void display();
  void insert(T k) { insert_node(root, nullptr, k); }
  BSTNode<T>* find(T k) { return find_node(root, k); }
  BSTNode<T>* remove(T k) { return remove_node(root, k); }

  /*--------*/
  void test();
  /*--------*/
};


template<typename T>
int BST<T>::recursive_capacity(BSTNode<T>* node){
  if(node == nullptr){
    return 0;
  }
  else if(node->left == nullptr && node->right == nullptr){
    return node->reps;
  }else{
    return recursive_capacity(node->left) + recursive_capacity(node->right) + node->reps;
  }
}



template<typename T>
int BST<T>::capacity(){
  return recursive_capacity(root);
}

template <typename T>
void BST<T>::insert_node(BSTNode<T>* &node, BSTNode<T> *p, T k) {
  if(node == nullptr){
      node = new BSTNode<T>;
      node->key = k;
      node->left = nullptr;
      node->right = nullptr;
      node->parent = p;
      node->reps = 1;
    }else{
      if(k != node->key){
        if(k < node->key){
          insert_node(node->left, node, k);
        }else{
          insert_node(node->right, node, k);
        }
      }else{
        node->reps++;
      }
    }
  }

template <typename T>
void BST<T>::display_node(BSTNode<T> *node, int count) {
  if(node != nullptr){
    count++;
    display_node(node->left, count);
    std::cout << "(" << count-1 << ")" << "(" <<node->key << "," <<node->reps<<")"<<" ";
    display_node(node->right, count);
  }
}

template <typename T>
void BST<T>::display(){
  display_node(root, 0);
  std::cout << std::endl;
}

template <typename T>
void BST<T>::destroy_recursive(BSTNode<T> *node) {
  if(node != nullptr){
    destroy_recursive(node->left);
    destroy_recursive(node->right);
    delete node;
  }
}

template <typename T>
BSTNode<T>* BST<T>::find_node(BSTNode<T> *node, T k) {
  if(node == nullptr) return nullptr;
  if(node->key == k) return node;
  if(node->key < k)
    return find_node(node->right, k);
  else
    return find_node(node->left, k);
}

template <typename T>
BSTNode<T>* BST<T>::minimum(BSTNode<T> *node) {
  while(node->left != nullptr)
    node = node->left;
  return node;
}

template <typename T>
BSTNode<T>* BST<T>::maximum(BSTNode<T> *node) {
  while(node->right != nullptr)
    node = node->right;
  return node;
}

template <typename T>
BSTNode<T>* BST<T>::predecessor(BSTNode<T> *node) {
  if(node->left != nullptr)
    return maximum(node->left);
  else{
    BSTNode<T>* p = node->parent;
    while(p != nullptr && node == p->left){
      node = p;
      p = node->parent;
    }
    return p;
  }
}

template <typename T>
BSTNode<T>* BST<T>::successor(BSTNode<T> *node) {
  if(node->right != nullptr)
    return minimum(node->right);
  else{
    BSTNode<T>* p = node->parent;
    while(p != nullptr && node == p->right){
      node = p;
      p = node->parent;
    }
    return p;
  }
}

template <typename T>
BSTNode<T>* BST<T>::remove_node(BSTNode<T>* &node, T k) {
  BSTNode<T>* n = find_node(node, k);
  if(n != nullptr){
    BSTNode<T>* p = n->parent;

    //Case 1: No children
    if(n->left == nullptr && n->right == nullptr){
      //
      std::cout<<"Case1\n";
      if(n->reps ==1){
        if(p == nullptr){ //if node is root
          root = nullptr;
        }else{
          if(n == p->left){
            p->left = nullptr;
          }else{
            p->right = nullptr;
          }
        }
	  delete n;
  }else{
	  //en caso de que las repeteiciones sean un valor diferentes a uno solose le resta uno a las repeticiones
	  n->reps--;
  }
}


    //Case 2: One child
    else if(n->left == nullptr || n->right == nullptr){
      //
      std::cout<<"Case2\n";
      //
      if(n->reps == 1){
	  BSTNode<T>* c;
	  if(n == p->left){ //if n is left child
	    if(n->left != nullptr) //if child was left
	      c = n->left;
	    else //if child was right
	      c = n->right;
	    if(p != nullptr) p->left = c;
	  }else{ //if n is right child
	    if(n->left != nullptr) //if child was left
	      c = n->left;
	    else //if child was right
	      c = n->right;
	    if(p != nullptr) p->right = c;
	  }
	  c->parent = p;
	  delete n;
	}else{
	  n->reps--;
	}
}

    //Case 3: Two children
    else{
      //
      std::cout<<"Case3\n";
      //
      if(n->reps == 1)
	{
	  BSTNode<T>* s = successor(n);
	  T new_key = s->key;
	  p = remove_node(s->parent, s->key);
	  n->key = new_key;
	}else{
	  n->reps--;
	}

     }

    return p;
  }
  return nullptr;
}


/*--------*/
template <typename T>
void BST<T>::test() {

  std::cout << "Lowest element: " << minimum(root)->key << "\n";
  std::cout << "Highest element: " << maximum(root)->key << "\n";

  std::cout << "Predecessor of Sneezy is "
  	    << predecessor(find("Sneezy"))->key
  	    << "\n";
  std::cout << "Successor of Dopey is "
  	    << successor(find("Dopey"))->key
  	    << "\n";

  std::cout<<(root->left)->reps<<std::endl;
}
/*--------*/

#endif
