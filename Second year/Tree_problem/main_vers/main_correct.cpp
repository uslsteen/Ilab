
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
    size_t num_of_keys = 0, num_of_qs = 0;
    int qs_first = 0, qs_second = 0;

    vector<int> keys;
    std::deque<queries_t> queries; // i used std::deque, cause i want to push_back per O(1)

    std::map<queries_t, bool> checking_table;

    cin >> num_of_keys;
    keys.resize(num_of_keys);

    for (size_t i = 0; i < num_of_keys; ++i)
        cin >> keys[i];

    cin >> num_of_qs;

#if 0
    queries.resize(num_of_qs); // When queries were std::vector
#endif

    for (size_t i = 0; i < num_of_qs; ++i)
    {
        cin >> qs_first >> qs_second;

        if (qs_first < qs_second)
            queries.push_back({qs_first, qs_second});

    }

    if ((num_of_keys != keys.size()) || (num_of_qs != queries.size()))
    {
        std::cerr << "Invalid input!\n";
        return 1;
    }
    
    cout << "This program exist for comparing two tree realisation!\n\n";

    avl_tree::Tree<int> my_tree;

    cout << "There is start testing of my tree!\n";
    vector<int> res_vec2 = Tree_testing(my_tree, keys, queries, MODE::CORRECT);

    for (auto& res : res_vec2)
        cout << res << " ";

#if 0
    cout << "\nThere is end testing of my_tree\n\n";
#endif

    std::set<int> std_tree;
    cout << "There is start testing of std::set!\n";
    vector<int> res_vec1 = Tree_testing(std_tree, keys, queries, MODE::CORRECT);

    for (auto& res : res_vec1)
        cout << res << " ";

#if 0
    cout << "\nThere is end testing of std::set\n\n";
#endif

    return 0;
}
