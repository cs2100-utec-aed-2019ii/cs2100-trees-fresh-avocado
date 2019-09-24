//
// Created by Gabriel Spranger Rojas on 9/21/19.
//

#ifndef BST_BST_H
#define BST_BST_H

#include <iostream>
#include <vector>

template <typename T>
class Node {
public:
    T key;
    Node<T>* left = NULL;
    Node<T>* right = NULL;
    explicit Node(const T& key): key{key} {}
    ~Node() {
        std::cout << "Deleted node with value: " << key << "\n";
    }
};

template <typename T>
class BST {
public:
    Node<T>* root;
    BST(): root(NULL) {}
    explicit BST(const T& value) {
        root = new Node(value);
    }

    bool is_empty() { return root == NULL; }

    Node<T>* find_node(const T& value) {
        Node<T>* curr = root;

        while (curr != NULL) {
            if (value == curr->key) {
                return curr;
            } else {
                if (value > curr->key)
                    curr = curr->right;
                else
                    curr = curr->left;
            }
        }
        return NULL;
    } // finds node with matching value

    Node<T>* find_parent(const T& value) {
        Node<T>* curr = root;
        Node<T>* parent = NULL;
        while (curr) {
            parent = curr;
            if (value > curr->key)
                curr = curr->right;
            else
                curr = curr->left;
        }
        return parent;
    } // finds the parent of the node with key == value

    void insert(const T& key) {
        Node<T>* new_node = new Node(key);
        if (is_empty()) {
            root = new_node;
        } else {
            Node<T>* temp = root;
            Node<T>* parent = NULL;
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
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    Node<T>* max(Node<T>* _root) {
        Node<T>* current = _root;
        while (current && current->right != NULL)
            current = current->right;
        return current;
    }

    Node<T>* erase(Node<T>* _root, const T& key) {
        if (_root == NULL)
            return _root;

        // buscar en el sub-arbol izquierdo
        if (key < _root->key)
            _root->left = erase(_root->left, key);

        // buscar en el sub-arbol derecho
        else if (key > _root->key)
            _root->right = erase(_root->right, key);

        // son iguales, entonces borrar el nodo
        else {
            // nodo tiene un solo hijo o ningun hijo
            if (_root->left == NULL) {
                Node<T>* temp = _root->right;
                delete _root;
                return temp;
            } else if (_root->right == NULL) {
                Node<T>* temp = _root->left;
                delete _root;
                return temp;
            }

            // nodo tiene dos hijos, agarrar el inorder_succesor
            Node<T>* temp = min(_root->right);

            // cambiar valores entre ambos nodos
            _root->key = temp->key;

            // borrar inorder successor
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
        printPostorder(node->left);
        printPostorder(node->right);
        std::cout << node->data << " ";
    }

    void print_preorder(Node<T>* node) { // node - left - right
        if (node == NULL)
            return;
        std::cout << node->data << " ";
        printPostorder(node->left);
        printPostorder(node->right);
    }

    void clear(Node<T>* _root) {
        if (_root == NULL)
            return;
        clear(_root->left);
        clear(_root->right);
        delete _root;
    }

    unsigned get_height(Node<T>* node) {
        if (node == NULL)
            return 0;
        else {
            // sacar la altura de casa sub-arbol
            int left_height = get_height(node->left);
            int right_height = get_height(node->right);

            // retornar la mayor altura de ambas
            if (left_height > right_height)
                return left_height+1;
            else
                return right_height+1;
        }
    }

    bool operator==(const BST& lhs) {
        // TODO: mismo contenido y estructura
        return false;
    }

    std::vector<Node<T>*> find_ancestors(Node<T>* node) {
        std::vector<Node<T>*> ancestors = {};
        if (node == root || node == NULL)
            return ancestors;
        else {
            T node_key = node->key;
            Node<T>* temp = root;
            while (temp != NULL && temp->key != node_key) {
                ancestors.push_back(temp);
                if (node_key > temp->key)
                    temp = temp->right;
                else
                    temp = temp->left;
            }
            return ancestors;
        }
    }

    ~BST() {
        clear(root);
    }

};

#endif //BST_BST_H
