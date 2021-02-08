
#include "test.hpp"
#include "Tree.hpp"


std::string dotname = "tree7.dot";
std::string pngname = "tree7.png";

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


    avl_tree::Tree<int> my_tree;
    cout << "There is start testing of my tree!\n";
    vector<int> res_vec2 = Tree_testing(my_tree, keys, queries);

    for (auto res : res_vec2)
        cout << res << " ";

    cout << "\nThere is end testing of my_tree\n\n";


    std::set<int> std_tree;
    cout << "There is start testing of std::set!\n";
    vector<int> res_vec1 = Tree_testing(std_tree, keys, queries);

    for (auto res : res_vec1)
        cout << res << " ";

    cout << "\nThere is end testing of std::set\n\n";

    //my_tree.Tree_dump(dotname, pngname);

    return 0;
}




/*
enum MODES_OF_CODEGEN
{
    RANDOM,
    IN_GRADUATE,
};

const int MODE = IN_GRADUATE;

int main()
{
    int req_size = 0, quer_size = 0, max_req = 0, quer_fst = 0, quer_scnd = 0, req = 1, i = 0;

    std::cout << "Input max value of req:\n";
    std::cin >> max_req;

    std::cout << "Input size of requests:\n";
    std::cin >> req_size;

    std::cout << "Input size of queiries:\n";
    std::cin >> quer_size;

    std::vector<int> reqs;
    std::vector<queries_t> quers;
    reqs.resize(req_size); quers.resize(quer_size);

    srand(clock());

    std::cout << req_size << "\n";

    switch(MODE)
    {
        case RANDOM:

            for (int i = 0; i < req_size; ++i)
            {
                reqs[i] = (rand() % max_req) + 1;
                cout << reqs[i] << " ";
            }


            std::cout << "\n" << quer_size << "\n";

            for (int i = 0; i < quer_size; ++i)
            {
                quers[i].frst = (rand() % max_req) + 1;
                quers[i].scnd = (rand() % max_req) + 1;

                if (quers[i].frst > quers[i].scnd)
                    std::swap(quers[i].frst, quers[i].scnd);

                else if (quers[i].frst == quers[i].scnd && quers[i].scnd != max_req)
                    quers[i].scnd++;

                else if (quers[i].frst == quers[i].scnd && quers[i].scnd == max_req)
                {
                    quers[i].scnd--;
                    quers[i].frst -= 2;

                }

                cout << quers[i].frst << " " << quers[i].scnd << " ";
            }

        case IN_GRADUATE:

            quer_size = 1;

            for (int i = 0; i < req_size; ++i, req+=5)
            {
                reqs[i] = req;
                std::cout << reqs[i] << " ";
            }

            quer_fst = (rand() % max_req) + 1;
            quer_scnd = (rand() % max_req) + 1;

            if (quer_fst > quer_scnd)
                std::swap(quer_fst, quer_scnd);

            else if (quer_fst == quer_scnd && quer_scnd != max_req)
                quers[i].scnd++;

            std::cout << "\n" << quer_size << "\n";
            std::cout << quer_fst << " " << quer_scnd << " ";
    }
}
*/

