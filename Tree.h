//
// Created by utec on 19/09/19.
//

#ifndef TREES_TREE_H
#define TREES_TREE_H

#include <iostream>

template <typename T>
class Node {
public:
    T key;
    Node<T>* left;
    Node<T>* right;
    explicit Node(T key): key{key}, left{nullptr}, right{nullptr} {}
};

template <typename T>
class Tree {
public:
    Node<T>* root;
    Tree(): root(nullptr) {}
    explicit Tree(T value) {
        root = new Node(value);
    }

    bool is_empty() { return root == nullptr; }

    Node<T>* find_node(T value) {
        Node<T>* curr = root;

        while (curr) {
            if (value == curr->key) {
                return curr;
            } else {
                if (value > curr->key)
                    curr = curr->right;
                else
                    curr = curr->left;
            }
        }
        return nullptr;
    } // finds node with matching value

    Node<T>* find_parent(T value) {
        Node<T>* curr = root;
        Node<T>* parent = nullptr;
        while (curr) {
            parent = curr;
            if (value > curr->key)
                curr = curr->right;
            else
                curr = curr->left;
        }
        return parent;
    } // finds the parent of the node with key == value

    void insert(T value) {
        Node<T>* new_node = new Node(value); // new node
        Node<T>* new_node_parent = nullptr; // new node's parent
        if (is_empty()) {
            root = new_node;
        } else { // tree not empty
            Node<T>* curr = root;
            while (curr) { // find new node's parent
                new_node_parent = curr;
                if (new_node->key > curr->key)
                    curr = curr->right;
                else
                    curr = curr->left;
            }
            // at this point, new_node_parent holds a ref to the new_node's parent
            if (new_node->key < new_node_parent->key)
                new_node_parent->left = new_node;
            else
                new_node_parent->left = new_node;
        }
    }

    void erase(Node<T>* root, T value) {
        Node<T>* node_to_delete = find_node(value);

        if (node_to_delete == nullptr) {
            using std::cout;
            cout << "Cannot delete non existent node\n";
        } else {
            if (node_to_delete->left == nullptr && node_to_delete->right == nullptr) { // node_to_delete is a leaf
                Node<T>* parent = find_parent(value);
                if (value > parent->key) { // nodo está a la derecha de parent
                    delete node_to_delete;
                    parent->right = nullptr;
                } else { // nodo está a la izquierda de parent
                    delete node_to_delete;
                    parent->left = nullptr;
                }
            } else if (node_to_delete->left == nullptr || node_to_delete->right == nullptr) { // node_to_delete has 1 child

                // find out where the node to delete child's is
                Node<T>* node_to_delete_child = nullptr;
                if (node_to_delete->left == nullptr) { // LEFT
                    node_to_delete_child = node_to_delete->left;
                    // swap values between node_to_delete and its child
                    T aux = node_to_delete_child->key;
                    node_to_delete_child->key = node_to_delete->key;
                    node_to_delete->key = aux;

                    delete node_to_delete_child;
                    node_to_delete->left = nullptr;
                } else { // RIGHT
                    node_to_delete_child = node_to_delete->right;
                    // swap values between node_to_delete and its child
                    T aux = node_to_delete_child->key;
                    node_to_delete_child->key = node_to_delete->key;
                    node_to_delete->key = aux;

                    delete node_to_delete_child;
                    node_to_delete->right = nullptr;
                }
            } else { // node_to_delete has 2 childs

            }
        }

    }

    ~Tree() {
        // TODO: free memory
    }

};

#endif //TREES_TREE_H
