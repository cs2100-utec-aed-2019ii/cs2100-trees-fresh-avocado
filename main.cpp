#include "BST.h"

using namespace std;

int main(int argc, char** argv) {

    BST<int> bst;

    bst.insert(40);
    bst.insert(35);
    bst.insert(41);
    bst.insert(34);
    bst.insert(36);
    bst.insert(42);

    cout << "BST:" << endl;
    bst.print_level_order(bst.root);
    cout << endl;

    BT<int> bt;
    bt.insert(1);
    bt.insert(2);
    bt.insert(3);
    bt.insert(4);
    bt.insert(5);
    bt.insert(6);

    cout << "BT:" << endl;
    bt.print_level_order(bt.root);
    cout << endl;

    cout << "Is this BT a BST? " << bt.is_bst(bt.root) << endl;
    cout << "Height of this BST: " << bst.get_height(bst.root) << endl;
    Node<int>* nodo_con_34 = bst.find_node(34);
    cout << "Finding node with value 34: " << nodo_con_34->key << endl;
    cout << "El nodo que le sigue a 34 es: " << (bst.find_next_node_in_same_level(bst.root, nodo_con_34))->key << endl;
    unsigned node_count = bst.count_nodes(bst.root);
    cout << "node_count en BST: " << node_count << endl;
    unsigned index = 0;
    cout << "El BST es completo? " << bst.is_complete(bst.root, index, node_count) << "\n";

    cout << "All paths from root to leaf nodes of BST: " << endl;
    bst.print_all_paths_from_root_to_leaf_nodes();
    cout << endl;

    cout << "Is BST height balanced? " << bst.is_height_balanced(bst.root) << "\n";

    cout << "CircularDoubleLinkedList in last level:" << endl;

    cout << "nodo_con_34->prev: ";
    cout << nodo_con_34->prev->key << endl;

    cout << "nodo_con_34->next: ";
    cout << nodo_con_34->next->key << endl;

    cout << "nodo_con_34->next->next: ";
    cout << nodo_con_34->next->next->key << endl;

    cout << "nodo_con_34->next->next->next: ";
    cout << nodo_con_34->next->next->next->key << endl;

    return 0;
}