//
// Created by anon on 08.02.2021.
//


#ifndef TREE_PROBLEM_TREE_ITER_HPP
#define TREE_PROBLEM_TREE_ITER_HPP

#include "Node.hpp"

namespace avl_tree::iter
{

    template <typename Data_t>
    struct iterator final
    {
        node::Node<Data_t>* nde_it;

    public:
        /* Simple constructor */
        iterator (node::Node<Data_t>* nde) : nde_it(nde)
        {}

        /* Copy constructor for iterator */
        iterator(const iterator& it) : nde_it(it.nde_it)
        {}

        /* Reloading operator for iterator */
        iterator& operator =(const iterator& it)
        {
            nde_it = it.nde_it;
            return *this;
        }

        Data_t operator *()
        {
            return nde_it->elem;
        }

        bool operator ==(const iterator& it)
        {
            if (nde_it == it.nde_it)
                return true;

            else return false;
        }

        bool operator !=(const iterator& it)
        {
            return !(operator==(it));
        }

        iterator& operator ++()
        {
            nde_it = nde_it->next;
            return *(this);
        }

    };

}

#endif //TREE_PROBLEM_TREE_ITER_HPP
