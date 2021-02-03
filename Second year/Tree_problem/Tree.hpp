//
// Created by anon on 03.02.2021.
//

#ifndef TREE_PROBLEM_TREE_HPP
#define TREE_PROBLEM_TREE_HPP

namespace avl_tree
{

    template <typename Data_t>
    class Tree final
    {
    private:
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
             {}

             Data_t get_elem()
             {
                 return elem;
             }

             unsigned int get_heigth()
             {
                 return height;
             }

             Node* balance();

             void set_parent(Node* parent);

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


    };
}

#endif //TREE_PROBLEM_TREE_HPP
