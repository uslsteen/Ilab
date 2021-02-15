//
// Created by anon on 08.02.2021.
//

#ifndef TREE_PROBLEM_NODE_HPP
#define TREE_PROBLEM_NODE_HPP

#include <iostream>

namespace avl_tree::node
{
    template <typename Data_t>
    struct Node final
    {
        Data_t elem = 0;

        Node* left = nullptr;
        Node* right = nullptr;

        Node* parent = nullptr;

        Node* next = nullptr;
        Node* prev = nullptr;

        unsigned int height = 0;

    public:

        Node(Data_t& elem_) : elem(elem_)
        {}

        Node(Data_t& elem_, Node* left_, Node* right_, Node* parent_, Node* next_, Node* prev_) : elem(elem_),
                                                                                                  left(left_),
                                                                                                  right(right_),
                                                                                                  parent(parent_),
                                                                                                  next(next_),
                                                                                                  prev(prev_)

        {
            correct_heigth();
        }


        //! Function for fixing new heigth of subtree
        void correct_heigth();

        //! Function for getting heigth of left and rigth subtree of node
        //! This function useful for creating AVL - Tree
        int balance_factor() const;


        void set_parent(Node* parent);
        void set_l_chld(Node* l_chld);
        void set_r_chld(Node* r_chld);

        //! Function for making a rigth rotate around the node
        Node* right_rotate();

        //! Function for making a rigth rotate around the node
        Node* left_rotate();

        //! Function for balance node this by defenition AVL - Tree
        Node* balance_node();

        //! Function for finding node with min elem
        Node* min_node();
        //! Function for finding node with max elem
        Node* max_node();

        void Node_dump(std::ofstream& out) const;

    };

    template <typename Data_t>
    void Node<Data_t>::correct_heigth()
    {
        int r_hgth = (right != nullptr) ? right->height : 0;
        int l_hgth = (left != nullptr) ? left->height : 0;

        height = (1 + std::max(r_hgth, l_hgth));
    }

    template <typename Data_t>
    int Node<Data_t>::balance_factor() const
    {
        int r_hgth = (right != nullptr) ? right->height : 0;
        int l_hgth = (left != nullptr) ? left->height : 0;

        return r_hgth - l_hgth;
    }



    template <typename Data_t>
    void Node<Data_t>::set_l_chld(Node *l_chld)
    {
        left = l_chld;

        //! If l_chld exist, then we can
        if (l_chld != nullptr)
            l_chld->parent = this;

        correct_heigth();
    }

    template <typename Data_t>
    void Node<Data_t>::set_r_chld(Node *r_chld)
    {
        right = r_chld;

        //! If r_chld exist, then we can
        if (r_chld != nullptr)
            r_chld->parent = this;

        correct_heigth();
    }


    template <typename Data_t>
    typename Node<Data_t>::Node* Node<Data_t>::right_rotate()
    {
        Node* y = left;
        y->set_parent(parent);

        set_l_chld(y->right);   //old vers:: left = y->right;
        y->set_r_chld(this);    //old vers:: y->right = this;

        correct_heigth();
        y->correct_heigth();

        return y;
    }

    template <typename Data_t>
    typename Node<Data_t>::Node* Node<Data_t>::left_rotate()
    {
        Node* y = right;
        y->set_parent(parent);

        set_r_chld(y->left);  // old vers::  right = y->left;
        y->set_l_chld(this);  // old vers::  y->left = this;

        correct_heigth();
        y->correct_heigth();

        return y;
    }

    template <typename Data_t>
    void Node<Data_t>::set_parent(Node *prnt)
    {
        parent = prnt;

        if (prnt == nullptr)
            return;

        if (prnt->elem > elem)
            prnt->left = this;

        else if (prnt->elem < elem)
            prnt->right = this;

        //! Set height for new node
        prnt->correct_heigth();
    }


    template <typename Data_t>
    typename Node<Data_t>::Node* Node<Data_t>::Node::balance_node()
    {
        //! Refresh height
        correct_heigth();

        int b_factor = balance_factor();

        if (b_factor == 2)
        {
            if (right->balance_factor() < 0)
            {
                right = right->right_rotate();
                correct_heigth();
            }

            return left_rotate();
        }

        if (b_factor == -2)
        {
            if (left->balance_factor() > 0)
            {
                left = left->left_rotate();
                correct_heigth();
            }

            return right_rotate();
        }

        return this;
    }

    template <typename Data_t>
    typename Node<Data_t>::Node* Node<Data_t>::Node::max_node()
    {
        auto cur_node = this;

        while (cur_node->right != nullptr)
            cur_node = cur_node->right;

        return cur_node;
    }


    template <typename Data_t>
    typename Node<Data_t>::Node* Node<Data_t>::Node::min_node()
    {
        auto cur_node = this;

        while (cur_node->left != nullptr)
            cur_node = cur_node->left;

        return cur_node;
    }

    template <typename Data_t>
    void Node<Data_t>::Node_dump(std::ofstream& out) const
    {
        if (left != nullptr)
        {
            out << elem << " -> " << left->elem << ";\n";
            left->Node_dump(out);
        }

        if (right != nullptr)
        {
            out << elem << " -> " << right->elem << "\n";
            right->Node_dump(out);
        }

        if (next != nullptr)
            out << elem << " -> " << next->elem << "\n";

        out << elem << ";\n";
    }

}

#endif //TREE_PROBLEM_NODE_HPP
