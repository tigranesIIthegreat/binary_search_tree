#include "bst.hpp"

namespace spec {

// CONSTRUCTORS AND DESTRUCTOR

template <typename T>
bst<T>::bst(std::initializer_list<T> ilist) {
  auto begin = ilist.begin();
  auto end = ilist.end();
  for (; begin != end; ++begin) {
    insert(*begin);
  }
}

template <typename T>
bst<T>::bst(const bst<T>& oth) : m_root{} {
  copy(oth.m_root);
}

template <typename T>
bst<T>::bst(bst<T>&& oth) {
  m_root = oth.m_root;
  oth.m_root = nullptr;
}

template <typename T>
bst<T>::~bst() {
  this->clear(m_root);
}

// OPERATORS

template <typename T>
bst<T>& bst<T>::operator=(const bst<T>& rhs) {
  bst<T> temp(rhs);
  this->swap(temp);
  return *this;
}

template <typename T>
bst<T>& bst<T>::operator=(bst<T>&& rhs) {
  this->clear();
  m_root = rhs.m_root;
  rhs.m_root = nullptr;
  return *this;
}

template <typename E>
std::ostream& operator<<(std::ostream& os, const bst<E>& tree) {
  tree.ostream_helper(os, tree.m_root);
  return os;
}

// MAIN FUNCTIONALITY 

template <typename T>
void bst<T>::clear() {
  clear(m_root);
}

template <typename T>
void bst<T>::insert(const T& v) {
  if (m_root == nullptr) {
    m_root = new Node(v);
    return;
  }
  auto root = m_root;
  while (root) {
    if (v < root->val) {
      if (root->left == nullptr) {
        root->left = new Node(v);
        return;
      }
      else root = root->left;
    }
    else {
      if (root->right == nullptr) {
        root->right = new Node(v);
        return;
      }
      else root = root->right;
    }
  }
}

template <typename T>
bool bst<T>::empty() const {
  return m_root == nullptr;
}

template <typename T>
size_t bst<T>::size() const {
  return size(m_root);
}

template <typename T>
void bst<T>::swap(bst<T>& oth) {
  Node* tmp = oth.m_root;
  oth.m_root = m_root;
  m_root = tmp;
}

template <typename T>
bool bst<T>::contains(const T& v) {
  return address_of(v) != nullptr;
}

template <typename T>
void bst<T>::remove(const T& v) {
  auto address = this->address_of(v);
  remove(address);
}

template <typename T>
void bst<T>::remove(Node* root) {
  if (root == nullptr) return;
  auto parent = address_before(root);
  if (parent) {
    if (!root->left && !root->right) {
      delete root;
      if (parent->left == root)
        parent->left = nullptr;
      else 
        parent->right = nullptr;
      return;
    }
    if (!root->left && root->right) {
      if (parent->left == root)
        parent->left = root->right;
      else
        parent->right = root->right;
      delete root;
      return;
    }
    if (root->left && !root->right) {
      if (parent->left == root)
        parent->left = root->left;
      else
        parent->right = root->left;
      delete root;
      return;
    }
    if (root->left && root->right) {
      auto next = find_next_inorder(root);
      std::swap(root->val, next->val);
      remove(next);
      return;
    }
  }
  if (!parent) {
    if (!root->right && !root->left) {
      delete root;
      m_root = nullptr;
      return;
    }
    if (!root->left && root->right) {
      m_root = root->right;
      delete root;
      return;
    }
    if (root->left && !root->right) {
      m_root = root->left;
      delete root;
      return;
    }
    if (root->left && root->right) {
      auto next = find_next_inorder(root);
      std::swap(root->val, next->val);
      remove(next);
      return;
    }
  }
}

template <typename T>
std::string bst<T>::to_str(Node* root) const {
  if (root == nullptr) return " ";
  std::string result;
  result += to_str(root->left);
  result += std::to_string(root->val);
  result += to_str(root->right);
  return result;
}

// HELPER FUNCTIONS

template <typename T>
void bst<T>::ostream_helper(std::ostream& os, Node* root) {
  if (root == nullptr)
    return;
  ostream_helper(os, root->left);
  os << root->val << " ";
  ostream_helper(os, root->right);
}

template <typename T>
void bst<T>::clear(Node* root) {
  if (root == nullptr)
    return;
  clear(root->left);
  clear(root->right);
  delete root;
}

template <typename T>
size_t bst<T>::size(Node* root) {
  if (root == nullptr) return 0;
  return 1 + size(root->left) + size(root->right);
}

template <typename T>
typename bst<T>::Node* bst<T>::address_of(const T& v) {
  if (m_root == nullptr) return nullptr;
  auto root{m_root};
  while (root) {
    if (root->val == v) return root;
    if (v < root->val) root = root->left;
    else root = root->right;
  }
  return root;
}

template <typename T>
typename bst<T>::Node* bst<T>::address_before(Node* address) {
  return address_helper(m_root, address);
}

template <typename T>
typename bst<T>::Node* bst<T>::address_helper(Node* r, Node* address) {
  if (m_root == address) return nullptr;
  if (r->left == address || r->right == address) return r;
  if (!r->left && r->right) return address_helper(r->right, address);
  if (r->left && !r->right) return address_helper(r->left, address);
  if (r->left && r->right) {
    if (address_helper(r->left, address)) return address_helper(r->left, address);
    if (address_helper(r->right, address)) return address_helper(r->right, address);
  }
  // std::cout << result->val;
  // return result;
  return nullptr;
}

template <typename T>
void bst<T>::copy(Node* src) {
  if (src == nullptr) return;
  insert(src->val);
  if (src->left) copy(src->left);
  if (src->right) copy(src->right);
}

template <typename T>
typename bst<T>::Node* bst<T>::find_next_inorder(Node* root) {
  if (root == nullptr) return nullptr;
  if (root->right == nullptr) return nullptr;
  root = root->right;
  while (root->left)
    root = root->left;
  return root;
}

template <typename T>
typename bst<T>::Node* bst<T>::find_prev_inorder(Node* root) {
  if (root == nullptr) return nullptr;
  if (root->left == nullptr) return nullptr;
  root = root->left;
  while (root->right)
    root = root->right;
  return root;
}

} // spec
