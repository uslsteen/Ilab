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

#include <unistd.h>
#include <getopt.h>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

typedef struct option OPT;

//! Keys as bit constant
#define T_KEY 0x1
#define C_KEY 0x2
#define D_KEY 0x4


enum
{
    INV_KEY = -2,
    END_OF_KEYS = -1
};

typedef int opt_t;

const OPT OPTIONS[] =
        {
                {"time", 0, NULL, 'T'},
                {"corrective", 0, NULL, 'C'},
                {"dump", 0, NULL, 'C'},
                {0, 0, 0, 0},
        };

const char OPT_STR[] = "TCD";



struct queries_t
{
    int frst, scnd;
};


template <typename Tree>
std::vector<int> Tree_testing(Tree& tree, std::vector<int>& keys, std::vector<queries_t>& queries, opt_t option)
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

    if (option == T_KEY)
        std::cout << "Time elapsed: " << tmer.elapsed() << " msecs\n" << std::endl;

    return res;
}


//! Function for processing key from stdin
//! There is processing keys:
//! -T:
//! -C:
opt_t Get_options(int argc, char** argv)
{
    int getopt_res = 0;
    int opt_checker = 0;

    while (true)
    {
        getopt_res = getopt_long(argc, argv, OPT_STR, OPTIONS, NULL);

        switch (getopt_res)
        {
            case '?':
                return INV_KEY;

            case 'T':
                opt_checker |= T_KEY;
                    return opt_checker;

            case 'C':
                opt_checker |= C_KEY;
                    return opt_checker;

            case 'D':
                opt_checker |= D_KEY;
                    return opt_checker;

            case -1:
                    return opt_checker;

            default:
                printf("Unrecognized return value: %d\n", getopt_res);
                return INV_KEY;
        }
    }
}

#endif //TREE_PROBLEM_TEST_HPP
