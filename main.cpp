#include "BST.h"

using namespace std;

int main(int argc, char** argv) {

    BST<int> bst;

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);

    cout << "BST:" << endl;
    bst.print_level_order(bst.root);
    cout << endl;

    BT<int> bt;
    bt.insert(1);
    bt.insert(2);
    bt.insert(3);
    bt.insert(4);
    bt.insert(5);

    cout << "BT:" << endl;
    bt.print_level_order(bt.root);
    cout << endl;

    cout << "Is this BT a BST? " << bt.is_bst(bt.root) << endl;
    cout << "Height of this BT: " << bt.get_height(bt.root) << endl;
    Node<int>* nodo_con_4 = bt.find_node(bt.root, 4);
    cout << "Finding node with value 4: " << nodo_con_4->key << endl;
    cout << "El nodo que le sigue a 4 es: " << (bt.find_next_node_in_same_level(bt.root, nodo_con_4))->key << endl;

    return 0;
}