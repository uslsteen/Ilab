#include "../test.hpp"
#include "../Tree.hpp"


int main()
{
    int num_of_keys = 0, num_of_qs = 0;

    vector<int> keys;
    vector<queries_t> queries;

    cin >> num_of_keys;
    keys.resize(num_of_keys);

    for (int i = 0; i < num_of_keys; ++i)
        cin >> keys[i];

    cin >> num_of_qs;
    queries.resize(num_of_qs);

    for (int i = 0; i < num_of_qs; ++i)
        cin >> queries[i].frst >> queries[i].scnd;

    avl_tree::Tree<int> my_tree;

    cout << "There is start testing of my tree!\n";
    vector<int> res_vec2 = Tree_testing(my_tree, keys, queries, MODE::TIME);


    std::set<int> std_tree;
    cout << "There is start testing of std::set!\n";
    vector<int> res_vec1 = Tree_testing(std_tree, keys, queries, MODE::TIME);

    return 0;
}
