//
// Created by anon on 03.02.2021.
//

#ifndef TREE_PROBLEM_TEST_HPP
#define TREE_PROBLEM_TEST_HPP

#include "my_time.hpp"
#include <vector>
#include <iostream>
#include <set>
#include <ctime>
#include <string>

using std::vector;
using std::cin;
using std::cout;
using std::endl;





struct queries_t
{
    int frst, scnd;
};



template <typename Tree>
std::vector<int> Tree_testing(Tree& tree, std::vector<int>& keys, std::vector<queries_t>& queries)
{
    Time::Timer tmer;

    std::vector<int> res(queries.size());

    for (auto key : keys)
        tree.insert(key);


    for (int q_beg = 0, q_end = queries.size(); q_beg != q_end; ++q_beg)
    {
        auto cur_it = tree.lower_bound(queries[q_beg].frst);
        auto end_it = tree.end();
        int cnter = 0;

        if (cur_it == end_it)
            std::cout << "Add processing!\n";

        while ((cur_it != end_it) && (*cur_it < queries[q_beg].scnd))
        {
            ++cur_it;
            ++cnter;
        }

        res[q_beg] = cnter;
    }

    std::cout << "Time elapsed: " << tmer.elapsed() << " msecs" << std::endl;

    return res;
}

#endif //TREE_PROBLEM_TEST_HPP
