#include "../test.hpp"
#include "../Tree.hpp"


void Input(std::vector<int>& keys, int num_of_keys)
{
    cin >> num_of_keys;
    keys.resize(num_of_keys);

    for (int i = 0; i < num_of_keys; ++i)
        cin >> keys[i];
}

int main()
{
    int num_of_keys1 = 0, num_of_keys2 = 0;

    vector<int> keys1, keys2;

    Input(keys1, num_of_keys1);
    Input(keys2, num_of_keys2);

#if 0
    cout << "This program exist for output double_free_alloc error!\n\n";
#endif

    avl_tree::Tree<int> fst_tree;
    cout << "There is start testing of first tree!\n";

    for (auto& key : keys1)
        fst_tree.insert(key);

    avl_tree::Tree<int> scnd_tree;
    cout << "There is start testing of second tree!\n";

    for (auto& key : keys2)
        scnd_tree.insert(key);


#if 0
    cout << "\nThere is end insertion in my trees\n\n";
#endif

    scnd_tree = fst_tree;


    return 0;
}
