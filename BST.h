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

    BST(const BST& other) {
        std::stack<Node<T>*> s;
        Node<T>* curr = other.root;

        while (curr != NULL || !s.empty()) {
            while (curr !=  NULL) {
                s.push(curr);
                curr = curr->left;
            }

            curr = s.top();
            s.pop();

            insert(curr->key);

            curr = curr->right;
        }
    }

    bool is_height_balanced(Node<T>* _root) {
        int left_tree_height = get_height(_root->left);
        int right_tree_height = get_height(_root->right);

        int diff = left_tree_height - right_tree_height;

        // si al diff de alturas de ambos sub arboles es maximo 1, entonces el arbol esta height-balanced
        return abs(diff) <= 1;
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

    // te retorna el mismo nodo si no hay más nodos en el mismo nivel
    Node<T>* find_next_node_in_same_level(Node<T>* _root, Node<T>* node) {
        if (node == NULL)
            return node;

        std::queue< Node<T>* > q;

        q.push(_root);

        bool nodo_esta_en_este_nivel = false;

        while (!q.empty()) {
            // number of nodes at the current level
            unsigned node_count = q.size();

            // check if we are in the node's level
            // then, check for all nodes in that level
            // return the one next to the node passed in

            std::vector< Node<T>* > nodes_in_same_level(0);

            // delete all nodes in the current level
            // insert all nodes in the next level
            while (node_count > 0) {
                Node<T>* _node = q.front();

                nodes_in_same_level.push_back(_node);

                q.pop();
                if (_node->left != NULL)
                    q.push(_node->left);
                if (_node->right != NULL)
                    q.push(_node->right);
                --node_count;
            }

            unsigned nodes_in_same_level_size = nodes_in_same_level.size();

            unsigned index_of_node;

            for (unsigned i = 0; i < nodes_in_same_level_size; ++i) {
                if (node == nodes_in_same_level[i]) {
                    nodo_esta_en_este_nivel = true;
                    index_of_node = i;
                    break;
                }
            }

            if (nodo_esta_en_este_nivel && index_of_node != nodes_in_same_level_size-1 && nodes_in_same_level_size > 1) {
                return nodes_in_same_level[index_of_node+1]; // retornando el siguiente
            }

        }
        return node; // no lo encontró :(
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

    bool is_complete(Node<T>* _root, unsigned index, unsigned int number_nodes) {
        // An empty tree is complete
        if (_root == NULL)
            return true;

        // If index assigned to current node is more than
        // number of nodes in tree, then tree is not complete
        if (index >= number_nodes)
            return false;

        // Recur for left and right subtrees
        return is_complete(_root->left, 2*index+1, number_nodes) &&
                is_complete(_root->right, 2*index+2, number_nodes);
    }

    unsigned int count_nodes(Node<T>* _root) {
        if (_root == NULL)
            return 0;
        return (1 + count_nodes(_root->left) + count_nodes(_root->right));
    }

    void print_path_to_node(Node<T>* node) {
        Node<T>* curr = root;

        while (curr != NULL) {
            if (node->key == curr->key) {
                std::cout << curr->key << " ";
                break;
            } else {
                if (node->key > curr->key) {
                    std::cout << curr->key << " ";
                    curr = curr->right;
                } else {
                    std::cout << curr->key << " ";
                    curr = curr->left;
                }
            }
        }
    }

    void print_all_paths_from_root_to_leaf_nodes() {
        unsigned last_level = get_height(root)-1;
        unsigned current_level = 0;

        std::queue< Node<T>* > q;
        std::vector< Node<T>* > leaf_nodes = {};

        q.push(root);

        while (!q.empty()) {
            // number of nodes at the current level
            unsigned node_count = q.size();

            // delete all nodes in the current level
            // insert all nodes in the next level
            while (node_count > 0) {
                Node<T>* node = q.front();

                // CODE HERE
                if (current_level == last_level) {
                    leaf_nodes.push_back(node);
                }

                q.pop();
                if (node->left != NULL)
                    q.push(node->left);
                if (node->right != NULL)
                    q.push(node->right);
                --node_count;
            }
            ++current_level;
        }

        for (auto leaf : leaf_nodes) {
            print_path_to_node(leaf);
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

    BT(const BT& other) {
        std::stack<Node<T>*> s;
        Node<T>* curr = other.root;

        while (curr != NULL || !s.empty()) {
            while (curr !=  NULL) {
                s.push(curr);
                curr = curr->left;
            }

            curr = s.top();
            s.pop();

            insert(curr->key);

            curr = curr->right;
        }
    }

    bool is_complete(Node<T>* _root, unsigned index, unsigned int node_count) {
        if (_root == NULL)
            return true;

        if (index >= node_count)
            return false;

        return (is_complete(_root->left, 2*index + 1, node_count) &&
               is_complete(_root->right, 2*index + 2, node_count));
    }

    unsigned int count_nodes(Node<T>* _root) {
        if (_root == NULL)
            return 0;
        return (1 + count_nodes(_root->left) + count_nodes(_root->right));
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
            return; // otherwise the root is inserted twice
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

    BST<T>& to_bst(std::vector< Node<T>* >& nvec, Node<T>* _root) {
        // TODO
    }

    bool is_bst(Node<T>* _root) {
        return is_bst_aux(_root, INT_MIN, INT_MAX);
    }

    bool is_bst_aux(Node<T>* _root, unsigned min, unsigned max) {
        if (_root == NULL)
            return true;

        if (_root->key < min || _root->key > max)
            return false;

        return is_bst_aux(_root->left, min, _root->key-1) && is_bst_aux(_root->right, _root->key+1, max);
    }

    Node<T>* find_node(Node<T>* _root, const T& value) {
        if (_root == NULL)
            return NULL;

        std::queue< Node<T>* > q;

        q.push(_root);

        while (!q.empty()) {
            // number of nodes at the current level
            unsigned node_count = q.size();

            // delete all nodes in the current level
            // insert all nodes in the next level
            while (node_count > 0) {
                Node<T>* node = q.front();
                if (node->key == value)
                    return node;
                q.pop();
                if (node->left != NULL)
                    q.push(node->left);
                if (node->right != NULL)
                    q.push(node->right);
                --node_count;
            }
        }
    }

    // te retorna el mismo nodo si no hay más nodos en el mismo nivel
    Node<T>* find_next_node_in_same_level(Node<T>* _root, Node<T>* node) {
        if (node == NULL)
            return node;

        std::queue< Node<T>* > q;

        q.push(_root);

        bool nodo_esta_en_este_nivel = false;

        while (!q.empty()) {
            // number of nodes at the current level
            unsigned node_count = q.size();

            // check if we are in the node's level
            // then, check for all nodes in that level
            // return the one next to the node passed in

            std::vector< Node<T>* > nodes_in_same_level(0);

            // delete all nodes in the current level
            // insert all nodes in the next level
            while (node_count > 0) {
                Node<T>* _node = q.front();

                nodes_in_same_level.push_back(_node);

                q.pop();
                if (_node->left != NULL)
                    q.push(_node->left);
                if (_node->right != NULL)
                    q.push(_node->right);
                --node_count;
            }

            unsigned nodes_in_same_level_size = nodes_in_same_level.size();

            unsigned index_of_node;

            for (unsigned i = 0; i < nodes_in_same_level_size; ++i) {
                if (node == nodes_in_same_level[i]) {
                    nodo_esta_en_este_nivel = true;
                    index_of_node = i;
                    break;
                }
            }

            if (nodo_esta_en_este_nivel && index_of_node != nodes_in_same_level_size-1 && nodes_in_same_level_size > 1) {
                return nodes_in_same_level[index_of_node+1]; // retornando el siguiente
            }

        }
        return node; // no lo encontró :(
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
