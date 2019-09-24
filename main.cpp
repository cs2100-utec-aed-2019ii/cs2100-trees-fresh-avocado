#include "BST.h"

using namespace std;

int main(int argc, char** argv) {

    BST<int> bst;

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);

    bst.print_inorder(bst.root);
    cout << endl;

//    bst.erase(bst.root, 2);
//
//    cout << bst.get_height(bst.root) << endl;
//
//    bst.print_inorder(bst.root);
//    cout << endl;

    Node<int>* node_with_5 = bst.find_node(5);
    vector<Node<int>*> ancestors_of_5 = bst.find_ancestors(node_with_5);

    cout << "Ancestors of 5: \n";
    for (auto node : ancestors_of_5) {
        cout << node->key << " ";
    }
    cout << endl;

    return 0;
}