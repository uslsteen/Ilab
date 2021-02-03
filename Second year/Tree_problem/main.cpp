#include <iostream>
#include <vector>
#include <set>
#include "test.hpp"


int main()
{
    cout << " This program exist for comparing two tree realisation!\n";

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


    /* std::set tree test */
    std::set<int> std_tree;
    cout << "There is start testing of std::set!\n";
    vector<int> res_vec = Tree_testing(std_tree, keys, queries);

    for (auto res : res_vec)
        cout << res << " ";


    cout << "\nThere is end testing of std::set\n";

    /* my tree test */

    return 0;
}
