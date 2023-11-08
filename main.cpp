#include "BSTree.cpp"

int main() {
    // BinTree<char> binTree(new BinTree<char>::Node('a',
    //     new BinTree<char>::Node('b',
    //         new BinTree<char>::Node('d'),
    //         new BinTree<char>::Node('e')
    //     ),
    //     new BinTree<char>::Node('c',
    //         new BinTree<char>::Node('f'),
    //             new BinTree<char>::Node('g')
    //     )
    // ));

    // TraversalType type = DF_LNR;

    // binTree.tranverse([](char& c) -> void { cout << c << " "; }, type);

    BinarySearchTree<int> bst;
    for (int i=0; i<10; i++) {
        bst.insert(rand() % 100);
    }

    bst.tranverse([](int& c) -> void { cout << setw(5) << c; }, DF_NLR);
    cout << endl;
    bst.tranverse([](int& c) -> void { cout << setw(5) << c; }, DF_LNR);

    // cout << endl << *(bst.find(34));
    // bst.remove(24);
    // cout << endl;
    // bst.tranverse([](int& c) -> void { cout << setw(5) << c; }, DF_LNR);
}