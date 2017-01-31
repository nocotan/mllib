#include "spr.hpp"
#include <iostream>
#include <memory>
using namespace std;
using namespace mllib;

int main() {
    shared_ptr< spr_tree<int> > tree(new spr_tree<int>(5));
    tree->insert(10);
    tree->insert(11);
    tree->insert(13);
    tree->insert(9);
    tree->insert(6);
    tree->insert(4);
    tree->insert(2);
    tree->insert(1);
    tree->insert(3);

    cout << "Tree: " << endl;
    cout << *tree << endl;

    auto pick = tree->prune();
    cout << "Picked subtree: " << endl;
    cout << *pick << endl;

    cout << "Picked tree: " << endl;
    cout << *tree << endl;

    tree->regraft(pick);
    cout << "Regraft: " << endl;
    cout << *tree << endl;
}
