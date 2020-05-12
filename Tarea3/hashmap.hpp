#ifndef __HASHMAP_HPP
#define __HASHMAP_HPP

#include <iostream>
#include <stdexcept>
#include <string>

const int INITIAL_SIZE = 5;

template <typename VT>
struct KeyValueNode {
  std::string key;
  VT value;
  KeyValueNode<VT> *next;
};

template <typename VT>
class HashMap {
private:
  KeyValueNode<VT> **table;
  int table_size;  
  int count;

  int hash_fun(std::string key);
  KeyValueNode<VT>* search_bucket(int i, std::string key);
  void rehash();
  
public:
  HashMap();
  ~HashMap();

  int size();
  bool empty();
  void clear();
  void insert(std::string key, VT value);
  
  /* Métodos a implementar */
  VT get(std::string key);
  bool contains(std::string key);
  void remove(std::string key);
  /* ********************* */

  void display();
};


template <typename VT>
HashMap<VT>::HashMap() {
  table_size = INITIAL_SIZE;
  table = new KeyValueNode<VT>*[table_size];
  for(int i = 0; i < table_size; ++i) table[i] = nullptr;
  count = 0;
}

template <typename VT>
HashMap<VT>::~HashMap() {
  clear();
  delete[] table;
}

template <typename VT>
int HashMap<VT>::hash_fun(std::string key) {
  int index = 0;
  for(char c : key)
    index += c;
  return index % table_size;
}

template <typename VT>
int HashMap<VT>::size() {
  return count;
}

template <typename VT>
bool HashMap<VT>::empty() {
  return count == 0;
}

template <typename VT>
void HashMap<VT>::clear() {
  KeyValueNode<VT> *cursor;
  for(int i = 0; i < table_size; ++i){
    cursor = table[i];
    while(table[i] != nullptr){
      cursor = cursor->next;
      delete table[i];
      table[i] = cursor;
    }
  }
  count = 0;
}

template <typename VT>
KeyValueNode<VT>* HashMap<VT>::search_bucket(int i, std::string key) {
  KeyValueNode<VT> *cursor = table[i];
  while(cursor != nullptr){
    if(cursor->key == key) return cursor;
    cursor = cursor->next;
  }
  return nullptr;
}

template <typename VT>
void HashMap<VT>::insert(std::string key, VT value) {
  if(count == 2*table_size) rehash();
  int index = hash_fun(key);
  KeyValueNode<VT> *cursor = search_bucket(index, key);
  if(cursor != nullptr){
    cursor->value = value;
  } else{
    KeyValueNode<VT> *new_node = new KeyValueNode<VT>;
    new_node->key = key;
    new_node->value = value;
    new_node->next = table[index];
    table[index] = new_node;
    count++;
  }
}

template <typename VT>
void HashMap<VT>::rehash() {
  int old_table_size = table_size;
  KeyValueNode<VT> **old_table = table;
  table_size *= 2;
  table = new KeyValueNode<VT>*[table_size];
  for(int i = 0; i < table_size; ++i) table[i] = nullptr;
  count = 0;

  KeyValueNode<VT> *cursor;
  for(int i = 0; i < old_table_size; ++i){
    cursor = old_table[i];
    while(old_table[i] != nullptr){
      insert(cursor->key, cursor->value);
      cursor = cursor->next;
      delete old_table[i];
      old_table[i] = cursor;
    }
  }
  delete[] old_table;
}


/* *********************************** */

template <typename VT>
VT HashMap<VT>::get(std::string key){
    if (contains() == true){
        return <VT> KeyValueNode.value();
    }else{
        throw runtime_error("get: Attempting to get a nonexistent key\n");
    }

}


template <typename VT>
bool HashMap<VT>::contains(std::string key){
    if(search_bucket(hash_fun(key), key)->key == key){
        return true;
    }else{
        return false;
    }
}


template <typename VT>
void HashMap<VT>::remove(std::string key){

}


/* *********************************** */


template <typename VT>
void HashMap<VT>::display() {
  std::cout << count << " elements:\n";
  KeyValueNode<VT> *cursor;
  for(int i = 0; i < table_size; ++i){
    cursor = table[i];
    while(cursor != nullptr){
      std::cout << "(" << cursor->key
                << "," << cursor->value
                << ") ";
      cursor = cursor->next;
    }
    std::cout << std::endl;
  }
}


#endif
