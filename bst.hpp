#ifndef BST_H
#define BST_H

#include <iostream>
#include <initializer_list>

namespace spec {
 
template <typename T>
class bst {
private:
  struct Node;
public:
  bst() = default;
  bst(std::initializer_list<T>); 
  bst(const bst<T>&);
  bst(bst<T>&&);
  ~bst();

public:
  bst<T>& operator=(const bst<T>&);
  bst<T>& operator=(bst<T>&&); 
  template <typename E>friend std::ostream&  
    operator<<(std::ostream&, const bst<E>&);

public:
  void clear(); 
  void insert(const T&); 
  void remove(const T&);
  bool empty() const;
  size_t size() const; 
  bool contains(const T&);
  void swap(bst<T>&);

private:
  static void clear(Node*); 
  static void ostream_helper(std::ostream&, Node*);
  static size_t size(Node*);
  Node* address_of(const T&);
  Node* address_before(Node*); 
  Node* address_helper(Node*, Node*);
  void copy(Node*);
  Node* find_next_inorder(Node*);
  Node* find_prev_inorder(Node*); 
  std::string to_str(Node*) const;
  void remove(Node*);

private:
  struct Node {
    Node() : val{}, left{}, right{} {}
    Node(const T& v) : Node() {val = v;}
    Node(const Node&) = default;
    Node(Node&&) = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) = default;
    ~Node() = default;
    T val{};
    Node* left{};
    Node* right{};
  };
  Node* m_root{};
};

} // spec

#endif // BST_H