//
// Created by Gabriel Spranger Rojas on 9/21/19.
//

#ifndef BST_BST_H
#define BST_BST_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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
        Node<T>* curr = _root;
        while (curr && curr->left != NULL)
            curr = curr->left;
        return curr;
    }

    Node<T>* max(Node<T>* _root) {
        Node<T>* curr = _root;
        while (curr && curr->right != NULL)
            curr = curr->right;
        return curr;
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

            // nodo tiene dos hijos, agarrar el min(max())
            Node<T>* temp = min(_root->right);

            // cambiar valores entre ambos nodos
            _root->key = temp->key;

            // borrar min(max())
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
        print_postorder(node->left);
        print_postorder(node->right);
        std::cout << node->data << " ";
    }

    void print_preorder(Node<T>* node) { // node - left - right
        if (node == NULL)
            return;
        std::cout << node->data << " ";
        print_preorder(node->left);
        print_preorder(node->right);
    }

    void print_level_order(Node<T>* _root) {
        if (_root == NULL)
            return;

        std::queue< Node<T>* > q;

        q.push(_root);

        while (!q.empty()) {
            // number of nodes at the current level
            unsigned node_count = q.size();

            // delete all nodes in the current level
            // insert all nodes in the next level
            while (node_count > 0) {
                Node<T>* node = q.front();
                std::cout << node->key << " ";
                q.pop();
                if (node->left != NULL)
                    q.push(node->left);
                if (node->right != NULL)
                    q.push(node->right);
                --node_count;
            }
            std::cout << std::endl;
        }
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

    bool equal_trees(Node<T>* _root1, Node<T>* _root2) {
        if (_root1 == NULL && _root2 == NULL)
            return true;

        if (_root1 != NULL && _root2 != NULL) {
            return (_root1->key == _root2->key) && equal_trees(_root1->left, _root2->left) && equal_trees(_root1->right, _root2->right);
        }

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

template <class T>
class BT {
public:
    Node<T>* root;
    BT(): root(NULL) {}
    explicit BT(const T& value) {
        root = new Node(value);
    }

    void print_inorder(Node<T>* _root) {
        if (_root == NULL)
            return;

        print_inorder(_root->left);
        std::cout << _root->key << " ";
        print_inorder(_root->right);
    }

    void insert(T key) {
        std::queue< Node<T>* > q;
        if (root != NULL) {
            q.push(root);
        } else {
            Node<T>* new_root = new Node(key);
            root = new_root;
            q.push(new_root);
        }

        // level order traversal hasta encontrar un espacio libre
        while (!q.empty()) {
            Node<T>* temp = q.front();
            q.pop();

            if (temp->left == NULL) {
                temp->left = new Node(key);
                break;
            } else
                q.push(temp->left);

            if (temp->right == NULL) {
                temp->right = new Node(key);
                break;
            } else
                q.push(temp->right);
        }
    }

    bool equal_trees(Node<T>* _root1, Node<T>* _root2) {
        if (_root1 == NULL && _root2 == NULL)
            return true;

        if (_root1 != NULL && _root2 != NULL) {
            return (_root1->key == _root2->key) && equal_trees(_root1->left, _root2->left) && equal_trees(_root1->right, _root2->right);
        }

        return false;
    }

    void clear(Node<T>* _root) {
        if (_root == NULL)
            return;
        clear(_root->left);
        clear(_root->right);
        delete _root;
    }

private:

    void push_all_nodes(std::vector< Node<T>* >& nvec, Node<T>* _root) { // left - node - right
        std::stack<Node<T>*> s;
        Node<T>* curr = root;

        while (curr != NULL || s.empty() == false) {
            /* Reach the left most Node of the
               curr Node */
            while (curr !=  NULL)
            {
                /* place pointer to a tree node on
                   the stack before traversing
                  the node's left subtree */
                s.push(curr);
                curr = curr->left;
            }

            /* Current must be NULL at this point */
            curr = s.top();
            s.pop();

            cout << curr->data << " ";

            /* we have visited the node and its
               left subtree.  Now, it's right
               subtree's turn */
            curr = curr->right;

        } /* end of while */
    }

public:

    BST<T>& to_bst(std::vector< Node<T>* >& nvec, Node<T>* _root) {
        // push all nodes into vector
        push_all_nodes(nvec, _root);

        // create the BST
        BST<T> bst;

        // insert each element into the new bst
        for (auto node : nvec)
            bst.insert(node->key);

        // return bst
        return bst;
    }

    void print_level_order(Node<T>* _root) {
        if (_root == NULL)
            return;

        std::queue< Node<T>* > q;

        q.push(_root);

        while (!q.empty()) {
            // number of nodes at the current level
            unsigned node_count = q.size();

            // delete all nodes in the current level
            // insert all nodes in the next level
            while (node_count > 0) {
                Node<T>* node = q.front();
                std::cout << node->key << " ";
                q.pop();
                if (node->left != NULL)
                    q.push(node->left);
                if (node->right != NULL)
                    q.push(node->right);
                --node_count;
            }
            std::cout << std::endl;
        }
    }

    ~BT() {
        clear(root);
    }

};

#endif //BST_BST_H
