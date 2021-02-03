//
// Created by anon on 03.02.2021.
//

#ifndef TREE_PROBLEM_TEST_HPP
#define TREE_PROBLEM_TEST_HPP

#include "my_time.hpp"

using std::vector;
using std::cin;
using std::cout;
using std::endl;

struct queries_t
{
    int frst, scnd;
};


template <typename Tree>
vector<int> Tree_testing(Tree& tree, vector<int>& keys, vector<queries_t>& queries)
{
    Time::Timer tmer;

    vector<int> res(queries.size());

    for (auto key : keys)
        tree.insert(key);

    for (int q_beg = 0, q_end = queries.size(); q_beg != q_end; ++q_beg)
    {
        auto start_it = tree.lower_bound(queries[q_beg].frst);
        auto end_it = tree.end();
        int cnter = 0;

        if (start_it == end_it)
            cout << "Add processing!\n";

        while ((start_it != end_it) && (*start_it <= queries[q_beg].scnd))
        {
            ++start_it;
            ++cnter;
        }

        res[q_beg] = cnter;
    }

    cout << "Time elapsed: " << tmer.elapsed() << " msecs" << endl;

    return res;
}

#endif //TREE_PROBLEM_TEST_HPP
