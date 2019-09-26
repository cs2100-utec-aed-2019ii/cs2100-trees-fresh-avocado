#include "BST.h"

using namespace std;

int main(int argc, char** argv) {

    BST<int> bst;

    bst.insert(40);
    bst.insert(35);
    bst.insert(41);
    bst.insert(34);
    bst.insert(36);

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
    cout << "Height of this BT: " << bt.get_height(bt.root) << endl;
    Node<int>* nodo_con_4 = bt.find_node(bt.root, 4);
    cout << "Finding node with value 4: " << nodo_con_4->key << endl;
    cout << "El nodo que le sigue a 4 es: " << (bt.find_next_node_in_same_level(bt.root, nodo_con_4))->key << endl;
    unsigned node_count = bst.count_nodes(bst.root);
    cout << "node_count en BT: " << node_count << endl;
    unsigned index = 0;
    cout << "El BST es completo? " << bst.is_complete(bst.root, index, node_count) << "\n";

    cout << "All paths from root to leaf nodes of BST: " << endl;
    bst.print_all_paths_from_root_to_leaf_nodes();
    cout << endl;

    cout << "Is BST height balanced? " << bst.is_height_balanced(bst.root) << "\n";

    return 0;
}