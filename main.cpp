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

    vector< Node<int>* > nvec = {};

//    BST<int> generated = (bt.to_bst(nvec, bt.root));

    cout << "Are both trees the same? ";
    cout << bst.equal_trees(bst.root, (bt.to_bst(nvec, bt.root)).root) << endl;

    return 0;
}