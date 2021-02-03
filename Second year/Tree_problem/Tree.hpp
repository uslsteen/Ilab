//
// Created by anon on 03.02.2021.
//

#ifndef TREE_PROBLEM_TREE_HPP
#define TREE_PROBLEM_TREE_HPP

namespace avl_tree
{



    /* There is i write class for AVL tree */
    //! Class consist of:
    //! 1. Node with left, rigth child and parent. Ofc, data also.
    //! 2. iterator
    //! Root of the tree

    template <typename Data_t>
    class Tree final
    {
    private:

        struct Node
        {
            Data_t data = 0;

            Node* left = nullptr, * right = nullptr;
            Node* parent = nullptr;

            

        };


    };
}

#endif //TREE_PROBLEM_TREE_HPP
