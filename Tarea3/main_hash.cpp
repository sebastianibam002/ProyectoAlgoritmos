#include <iostream>
#include "hashmap.hpp"
using namespace std;


int main() {
  HashMap<int> my_map;
  cout << my_map.size() << " " << my_map.empty() << endl;
  
  my_map.insert("a", 24);
  my_map.insert("c", 65);
  my_map.insert("h", -3);
  my_map.insert("k", 5);
  my_map.insert("t", -8);
  my_map.insert("o", 12);
  my_map.insert("s", -4);
  my_map.insert("k", 9);
  my_map.insert("n", 0);
  my_map.insert("l", 10);
  my_map.insert("x", 2);
  my_map.insert("y", -45);

  my_map.display();
  
  // string s = "o";
  // if(my_map.contains(s)){
  //   cout << "Value with key '" << s << "': " << my_map.get(s) << endl;
  //   my_map.remove(s);
  // }
  // my_map.display();
  
  // if(my_map.contains(s)) cout << "Key '" << s << "' is in the map\n";
  // else cout << "Key '" << s << "' is NOT in the map\n";
  
  return 0;
}
