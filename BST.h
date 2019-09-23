//
// Created by Gabriel Spranger Rojas on 9/21/19.
//

#ifndef BST_BST_H
#define BST_BST_H

#include <iostream>

template <typename T>
class Node {
public:
    T key;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    explicit Node(T key): key{key} {}
    ~Node() {
        std::cout << "Deleted node with value: " << key << "\n";
    }
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

        while (curr != nullptr) {
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

    void insert(T key) {
        Node<T>* new_node = new Node(key);
        if (is_empty()) {
            root = new_node;
        } else {
            Node<T>* temp = root;
            Node<T>* parent = nullptr;
            while (temp) {
                parent = temp;
                if (key > temp->key)
                    temp = temp->right;
                else
                    temp = temp->left;
            }

            if (key < parent->key) {
                parent->left = new_node;
            } else {
                parent->right = new_node;
            }

        }
    }

    Node<T>* min(Node<T>* _root) {
        Node<T>* current = _root;

        /* loop down to find the leftmost leaf */
        while (current && current->left != NULL)
            current = current->left;

        return current;
    }

    Node<T>* max(Node<T>* _root) {
        Node<T>* current = _root;

        /* loop down to find the leftmost leaf */
        while (current && current->right != NULL)
            current = current->right;

        return current;
    }

    Node<T>* erase(Node<T>* _root, T key) {
        // base case
        if (_root == NULL)
            return _root;

        // If the key to be deleted is smaller than the root's key,
        // then it lies in left subtree
        if (key < _root->key)
            _root->left = erase(_root->left, key);

            // If the key to be deleted is greater than the root's key,
            // then it lies in right subtree
        else if (key > _root->key)
            _root->right = erase(_root->right, key);

            // if key is same as root's key, then This is the node
            // to be deleted
        else {
            // node with only one child or no child
            if (_root->left == NULL) {
                Node<T>* temp = _root->right;
                delete _root;
                return temp;
            } else if (_root->right == NULL) {
                Node<T>* temp = _root->left;
                delete _root;
                return temp;
            }

            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            Node<T>* temp = min(_root->right);

            // Copy the inorder successor's content to this node
            _root->key = temp->key;

            // Delete the inorder successor
            _root->right = erase(_root->right, temp->key);
        }
        return _root;
    }

    void print_inorder(Node<T>* node) { // left - node - right
        if (node == NULL)
            return;
        print_inorder(node->left);
        std::cout << node->key << " ";
        print_inorder(node->right);
    }

    void print_postorder(Node<T>* node) { // left - right - node
        if (node == NULL)
            return;
        // first recur on left subtree
        printPostorder(node->left);
        // then recur on right subtree
        printPostorder(node->right);
        // now deal with the node
        std::cout << node->data << " ";
    }

    void print_preorder(Node<T>* node) { // node - left - right
        if (node == NULL)
            return;
        // deal with the node
        std::cout << node->data << " ";
        // first recur on left subtree
        printPostorder(node->left);
        // then recur on right subtree
        printPostorder(node->right);
    }

    void clear(Node<T>* _root) {
        if (_root == nullptr)
            return;
        clear(_root->left);
        clear(_root->right);
        delete _root;
    }

    unsigned get_height(Node<T>* _root) {
        // TODO
        return 0;
    }

    ~Tree() {
        clear(root);
    }

};

#endif //BST_BST_H
