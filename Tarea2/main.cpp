#include <string>
#include "binarytree.hpp"
using namespace std;


int main() {
  BST<string> my_tree;

  my_tree.insert("Grumpy");
  my_tree.insert("Bashful");
  my_tree.insert("Doc");
  my_tree.insert("Dopey");
  my_tree.insert("Happy");
  my_tree.insert("Sneezy");
  my_tree.insert("Sleepy");
  my_tree.insert("Dopey");
  my_tree.test();
  my_tree.display();
  my_tree.capacity();
  /*
  cout << my_tree.capacity() << endl;
  
  string name = "Dop";
  if(!my_tree.find(name))
    cout << name << " is not in the tree.\n";
  else
    cout << name << " is in the tree!\n";

  my_tree.test();

  my_tree.remove("Dopey");
  my_tree.display();

  cout << my_tree.capacity() << endl;
  
  my_tree.remove("Grumpy");
  my_tree.display();

  my_tree.remove("Doc");
  my_tree.display();

  my_tree.remove("Sleepy");
  my_tree.display();

  my_tree.remove("Bashful");
  my_tree.display();

  my_tree.remove("Happy");
  my_tree.display();

  my_tree.remove("Dopey");
  my_tree.display();

  my_tree.remove("Sneezy");
  my_tree.display();

  cout << my_tree.capacity() << endl;
  */
  return 0;
}
