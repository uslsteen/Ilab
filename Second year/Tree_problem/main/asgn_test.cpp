#include "../test.hpp"
#include "../Tree.hpp"


void Input(std::vector<int>& keys, int num_of_keys)
{
    cin >> num_of_keys;
    keys.resize(num_of_keys);

    for (int i = 0; i < num_of_keys; ++i)
        cin >> keys[i];
}


void swap(avl_tree::Tree<int>& fst, avl_tree::Tree<int>& scnd)
{
    avl_tree::Tree<int> tmp(fst);

    fst = scnd;
    scnd = tmp;
}

int main()
{
    int num_of_keys1 = 0, num_of_keys2 = 0, num_of_keys3 = 0;

    vector<int> keys1, keys2, keys3;

    Input(keys1, num_of_keys1);
    Input(keys2, num_of_keys2);
    Input(keys3, num_of_keys3);

#if 0
    cout << "This program exist for test copy ctor and copy assgn!\n\n";
#endif

    avl_tree::Tree<int> fst_tree;
    cout << "There is start testing of first tree!\n";

    for (auto& key : keys1)
        fst_tree.insert(key);

    avl_tree::Tree<int> scnd_tree;
    cout << "There is start testing of second tree!\n";

    for (auto& key : keys2)
        scnd_tree.insert(key);

    avl_tree::Tree<int> third_tree;
    cout << "There is start testing of third tree!\n";

    for (auto& key : keys3)
        third_tree.insert(key);

    avl_tree::Tree<int> copy_ctor_tester(fst_tree);

    swap(third_tree, scnd_tree);

    return 0;
}
