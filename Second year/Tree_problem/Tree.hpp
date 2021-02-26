//
// Created by anon on 03.02.2021.
//

#ifndef TREE_PROBLEM_TREE_HPP
#define TREE_PROBLEM_TREE_HPP


#include <fstream>
#include <iostream>
#include "Tree_iter.hpp"


/*       main conception of AVL tree      */

namespace avl_tree
{
    template <typename Data_t>
    class Tree final
    {
    private:
        node::Node<Data_t>* root = nullptr;
        size_t size = 0;

        using double_iterator = std::pair<iter::iterator<Data_t>, bool>;

        enum INSERT_SIDE{ LEFT, RIGHT };

    public:
        Tree();
        explicit Tree(const Data_t& elem);

        Tree(const Tree& tree);
        Tree(Tree&& tree) = delete;

        ~Tree();

        size_t get_size()
        {
            return size;
        }

        [[nodiscard]] bool is_balanced() const;

        [[nodiscard]] unsigned int get_heigth() const;

        //! Function for insertion elem into my avl_tree
        //! \param elem
        //! \return double iterator
        double_iterator insert(Data_t& elem);

        //! Function for finding not less than elem in my avl tree
        //! \param elem
        //! \return iterator
        iter::iterator<Data_t> lower_bound(Data_t& elem) const;

        //! Function for getting begin to my avl_tree
        //! \return iterator
        iter::iterator<Data_t> begin() const;

        //! Function for getting end to my avl_tree
        //! \return iterator
        iter::iterator<Data_t> end() const;

        //! Function - hepler for lower_bound(...)
        //! \param nde
        //! \param elem
        //! \return iterator
        iter::iterator<Data_t> Find_not_less(node::Node<Data_t>* nde, Data_t& elem) const;

        //! Function for balance my avl_tree
        //! \param nde
        //! \param root
        void Balance_tree(node::Node<Data_t>** nde, node::Node<Data_t>** root);

        //! Dump my avl_tree to png format
        //! \param dotname
        //! \param pngname
        void Tree_dump(const std::string& dotname, const std::string& pngname) const;


        Tree& operator=(const Tree& rhs) = delete;
        Tree operator =(Tree&& rhs) = delete;

        void Insert_helper_func(INSERT_SIDE side, Data_t& elem, node::Node <Data_t>** cur, double_iterator &res);
    };

    template <typename Data_t>
    Tree<Data_t>::Tree() {}

    //! Constructor of class Tree
    template <typename Data_t>
    Tree<Data_t>::Tree(const Data_t& elem) : size(1),
                                             root(new node::Node<Data_t>(elem))
    {}


    template <typename Data_t>
    Tree<Data_t>::Tree(const Tree<Data_t>& tree)
    {
        //node::Node<Data_t>* cur = root;

        if (tree.root != nullptr)
        {
            std::vector<iter::iterator<Data_t>> buf;
            buf.reserve(tree.size);

            for (iter::iterator<Data_t> iter = tree.begin(); iter != tree.end(); ++iter)
                buf.push_back(iter);

            //iter::iterator<Data_t> cur = begin();
            for (size_t i = 0; i < tree.size; ++i)
                insert(buf[i].nde_it->elem);
        }

    }



    //! Destructor of class Tree without recoursion
    template <typename Data_t>
    Tree<Data_t>::~Tree()
    {
        node::Node<Data_t>* cur = root->min_node(), *prev = nullptr;

        while (cur != nullptr)
        {
            prev = cur;
            cur = cur->next;
            delete prev;
        }
    }

    template <typename Data_t>
    typename iter::iterator<Data_t> Tree<Data_t>::begin() const
    {
        return iter::iterator<Data_t>{root->min_node()};
    }

    template <typename Data_t>
    typename iter::iterator<Data_t> Tree<Data_t>::end() const
    {
        return iter::iterator<Data_t>{nullptr};
    }

    template <typename Data_t>
    typename iter::iterator<Data_t> Tree<Data_t>::lower_bound(Data_t &elem) const
    {
        return Find_not_less(root, elem);
    }

    template <typename Data_t>
    typename iter::iterator<Data_t> Tree<Data_t>::Find_not_less(node::Node<Data_t>* nde, Data_t& elem) const
    {
        if (nde == nullptr)
            return iter::iterator<Data_t>{nullptr};

        //! Compare elem with nde->elem: chose the way
        if (elem < nde->elem)
        {
            if (nde->left == nullptr)
                return iter::iterator<Data_t>{nde};

            else return Find_not_less(nde->left, elem);
        }
        else if (elem > nde->elem)
        {
            if (nde->right == nullptr)
                return ++iter::iterator<Data_t>{nde};

            else return Find_not_less(nde->right, elem);
        }
        else if (elem == nde->elem)
            return iter::iterator<Data_t>{nde};

        return iter::iterator<Data_t>{nullptr};
    }

    template <typename Data_t>
    bool Tree<Data_t>::is_balanced() const
    {
        return (std::abs(root->balance_factor()) <= 1);
    }

    template <typename Data_t>
    unsigned int Tree<Data_t>::get_heigth() const
    {
        return root->height;
    }

    template <typename Data_t>
    void Tree<Data_t>::Balance_tree(node::Node<Data_t>** nde, node::Node<Data_t>** root)
    {
        while (*nde != *root)
        {
            *nde = (*nde)->balance_node();
            *nde = (*nde)->parent;
        }
        *root = (*root)->balance_node();
    }


    template <typename Data_t>
    void Tree<Data_t>::Insert_helper_func(Tree<Data_t>::INSERT_SIDE side, Data_t& elem, node::Node<Data_t>** cur, double_iterator& res)
    {
        node::Node<Data_t>* new_child;

        if (side == RIGHT)
        {
            new_child = new node::Node<Data_t>{elem, nullptr, nullptr, *cur, (*cur)->next, (*cur)};
            (*cur)->right = new_child;

            //! Checking for other node after cur
            if ((*cur)->next != nullptr)
                (*cur)->next->prev = new_child;
            //! By the way, we should retie cur->next to new_r_child in the end
            (*cur)->next = new_child;

        }
        else if (side == LEFT)
        {
            new_child = new node::Node<Data_t>{elem, nullptr, nullptr, *cur, (*cur), (*cur)->prev};
            (*cur)->left = new_child;

            if ((*cur)->prev != nullptr)
                (*cur)->prev->next = new_child;

            (*cur)->prev = new_child;
        }

        ++size;
        res.first = new_child;
        (*cur)->correct_heigth();
    }


    template <typename Data_t>
    typename Tree<Data_t>::double_iterator Tree<Data_t>::insert(Data_t& elem)
    {
        double_iterator res{iter::iterator<Data_t>{nullptr}, false};
        size_t old_size = size;
        //! If this insertion - first insertion
        if (size == 0)
        {
            root = new node::Node<Data_t>{elem};
            ++size;

            res.first = root;
            res.second = true;
            return res;
        }
        else
        {
            node::Node<Data_t>* cur = root;
            while (cur->elem != elem)
            {
                if (elem > cur->elem)
                {
                    if (cur->right == nullptr)
                    {
                        //! Creating new rigth child
                        Insert_helper_func(RIGHT, elem, &cur, res);

                        break;
                    }
                    else cur = cur->right;
                }
                else if (elem < cur->elem)
                {
                    if (cur->left == nullptr)
                    {
                        //! Creating new left child
                        Insert_helper_func(LEFT, elem, &cur, res);
                        break;
                    }
                    else cur = cur->left;
                }
            }

            if (size != old_size)
                res.second = true;

            Balance_tree(&cur, &root);
        }

        return res;
    }


    template <typename Data_t>
    void Tree<Data_t>::Tree_dump(const std::string& dotname, const std::string& pngname) const
    {
        std::ofstream fout;
        fout.open(dotname, std::ios::out);

        if (!fout.is_open())
        {
            std::cout << "Cannot open dump file: " << dotname << "\n";
            return;
        }

        fout << "digraph D {\n";

        if (root != nullptr)
            root->Node_dump(fout);

        fout << "}\n";
        fout.close();

        std::string promt = "dot " + dotname + " -Tpng > " + pngname;
        system(promt.c_str());
    }

    /*    Here I define methods for struct Node   */

}

#endif //TREE_PROBLEM_TREE_HPP
