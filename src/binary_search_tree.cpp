#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    if(root_ == nullptr) {
      root_ = new Node(key, value);
      root_ -> left = nullptr;
      root_ -> right = nullptr;
      return;
    }
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* node = find(key, root());
    if (node != nullptr) {
      return node->value;
    }
    return std::nullopt;
  }

  bool BinarySearchTree::Contains(int key) const {
    return find(key, root()) != nullptr;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root() == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if (root() == nullptr) {
      return std::nullopt;
    }
    return find_min(root())->key;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if (root() == nullptr) {
      return std::nullopt;
    }
    return find_max(root())->key;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node == nullptr) {
      Node* node2 = new Node(key, value);
      node = node2;
      node->right = nullptr;
      node->left = nullptr;
    }
    else if (node->key == key) {
      node->value = value;
    }
    else if (node->key < key) {
      insert(key, value, node->right);
    }
    else if (node->key > key) {
      insert(key, value, node->left);
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (node == nullptr) {
      return false;
    }
    else if (key < node->key) {
      remove(key, node->left);
    }
    else if (key > node->key) {
      remove(key, node->right);
    }
    else {
      if (node->left == nullptr && node->right == nullptr) {
        delete node;
        node = nullptr;
      }
      else if (node->left != nullptr && node->right != nullptr) {
        Node* node2 = find_min(node->right);
        node->key = node2->key;
        node->value = node2->value;
        remove(node2->key, node->right);
      }
      else if(node->left != nullptr && node->right == nullptr){
        Node* node1 = node->left;
        Node* node2 = node;
        node = node1;
        delete node2;
      } else if(node->left == nullptr && node->right != nullptr){
        Node* node1 = node->right;
        Node* node2 = node;
        node = node1;
        delete node2;
      }
    }
    return true;
  }

  void BinarySearchTree::clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    else if (node->key==key){
      return node;
    }
    else if (node->key < key) {
      return find(key, node->right);
    }
    return find(key, node->left);
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    else if (node->left == nullptr) {
      return node;
    }
    return find_min(node->left);
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->right == nullptr) {
      return node;
    }
    return find_max(node->right);
  }

}  // namespace assignment