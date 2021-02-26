
#include "test.hpp"
#include "Tree.hpp"


std::string dotname_orig = "tree_orig.dot";
std::string pngname_orig = "tree_orig.png";

std::string dotname_cpy = "tree_cpy.dot";
std::string pngname_cpy = "tree_cpy.png";

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Lack of the arguments!\n" << "Please, try once more!\n";
        return 0;
    }

    opt_t option = Get_options(argc, argv);

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
    vector<int> res_vec2 = Tree_testing(my_tree, keys, queries, option);


    if (option == C_KEY)
    {
        for (auto& res : res_vec2)
            cout << res << " ";

        cout << "\nThere is end testing of my_tree\n\n";
    }

    avl_tree::Tree<int> cpy_my_tree(my_tree);

    std::set<int> std_tree;
    cout << "There is start testing of std::set!\n";
    vector<int> res_vec1 = Tree_testing(std_tree, keys, queries, option);

    if (option == C_KEY)
    {
        for (auto& res : res_vec1)
            cout << res << " ";

        cout << "\nThere is end testing of std::set\n\n";
    }


    my_tree.Tree_dump(dotname_orig, pngname_orig);
    cpy_my_tree.Tree_dump(dotname_cpy, pngname_cpy);

    return 0;
}
