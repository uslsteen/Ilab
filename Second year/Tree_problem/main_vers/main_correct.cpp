
#include "../test.hpp"
#include "../Tree.hpp"

#if 0
    std::string dotname_orig = "../tree_orig.dot";
    std::string pngname_orig = "../tree_orig.png";

    std::string dotname_cpy = "../tree_cpy.dot";
    std::string pngname_cpy = "../tree_cpy.png";
#endif

int main()
{
    cout << "This program exist for comparing two tree realisation!\n\n";

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
    vector<int> res_vec2 = Tree_testing(my_tree, keys, queries, MODE::CORRECT);

    for (auto& res : res_vec2)
        cout << res << " ";

    cout << "\nThere is end testing of my_tree\n\n";

    std::set<int> std_tree;
    cout << "There is start testing of std::set!\n";
    vector<int> res_vec1 = Tree_testing(std_tree, keys, queries, MODE::CORRECT);

    for (auto& res : res_vec1)
        cout << res << " ";

    cout << "\nThere is end testing of std::set\n\n";

    return 0;
}
