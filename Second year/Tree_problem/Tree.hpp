//
// Created by anon on 03.02.2021.
//

#ifndef TREE_PROBLEM_TREE_HPP
#define TREE_PROBLEM_TREE_HPP


 //! TODO:
 //! 1. Write realisation of rotation
 //! 2. Write method balance for node
 //! 3. Start writing method of classs tree: insertion, lower_bound() etc...

/*       main conception of AVL tree      */
//!

namespace avl_tree
{

    template <typename Data_t>
    class Tree final
    {
    private:

        /*        Start of helpful structures for my_tree      */
        struct Node final
        {
            Data_t elem = 0;

            Node* left = nullptr, * right = nullptr;
            Node* parent = nullptr;

            unsigned int height = 0;

        public:

             Node(Data_t elem_, Node* left_, Node* right_, Node* parent_) : elem(elem_),
                                                                            left(left_),
                                                                            right(right_),
                                                                            parent(parent_)
             {
                 set_heigth();
             }


             //! Function for fixing new heigth of subtree
             int set_heigth()
             {
                 int r_hgth = (right != nullptr) ? right->height : 0;
                 int l_hgth = (left != nullptr) ? right->height : 0;

                 return (1 + std::max(r_hgth, l_hgth));
             }

             //! Function for getting heigth of left and rigth subtree of node
             //! This function useful for creating AVL - tree
             int balance_factor()
             {
                 int r_hgth = (right != nullptr) ? right->height : 0;
                 int l_hgth = (left != nullptr) ? right->height : 0;

                 return r_hgth - l_hgth;
             }


             void set_parent(Node* parent);
             void set_l_child(Node* l_child);
             void set_r_child(Node* r_child);

             void right_rotate(Node* rigth);
             void left_rotate(Node* left);

        };


    private:
        struct iterator final
        {
            Node* nde_it;

        public:
            /* Simple constructor */
            iterator (Node* nde) : nde_it(nde)
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
                return nde_it->data;
            }
        };


    /*             End of helpful structures              */
    /*             Start interface of class AVL tree      */

    private:
        Node* root = nullptr;
        int nde_pos = 0;

    public:

        Tree(const Data_t& elem) : nde_pos(1),
                                   root(new Node(elem))
        {}

        ~Tree();

        void insert(Data_t& elem);

        iterator lower_bound(Data_t& elem);

        iterator begin();
        iterator end();

        bool is_balanced()
        {
            return (std::abs(root->balance_factor()) <= 1);
        }

        unsigned int get_heigth()
        {
            return root->height;
        }


    };
}

#endif //TREE_PROBLEM_TREE_HPP
