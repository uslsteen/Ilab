//
// Created by anon on 03.02.2021.
//

#ifndef TREE_PROBLEM_TREE_HPP
#define TREE_PROBLEM_TREE_HPP


#include <fstream>
#include <iostream>


 //! TODO:
 //! 1. Write realisation of rotation // DONE
 //! 2. Write method balance for node // DONE
 //! 3. Start writing method of classs tree: insertion, lower_bound() etc...

/*       main conception of AVL tree      */

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

            Node* left = nullptr;
            Node* right = nullptr;

            Node* parent = nullptr;

            Node* next = nullptr;
            Node* prev = nullptr;

            unsigned int height = 0;

        public:

             explicit Node(Data_t& elem_) : elem(elem_)
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
             int correct_heigth()
             {
                 int r_hgth = (right != nullptr) ? right->height : 0;
                 int l_hgth = (left != nullptr) ? left->height : 0;

                 height = (1 + std::max(r_hgth, l_hgth));
             }

             //! Function for getting heigth of left and rigth subtree of node
             //! This function useful for creating AVL - Tree
             int balance_factor()
             {
                 int r_hgth = (right != nullptr) ? right->height : 0;
                 int l_hgth = (left != nullptr) ? left->height : 0;

                 return r_hgth - l_hgth;
             }


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

             void Node_dump(std::ofstream& out);

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


    /*             End of defenition helpful structures              */



    /*             Start interface of class AVL tree      */

    private:
        Node* root = nullptr;
        int nde_pos = 0; ///????? should i use it?
        size_t size = 0;

        using double_iterator = std::pair<iterator, bool>;

    public:

        Tree();
        Tree(const Data_t& elem);
        ~Tree();

        bool is_balanced();

        unsigned int get_heigth();



        double_iterator insert(Data_t& elem);
        iterator lower_bound(Data_t& elem);
        iterator begin();
        iterator end();

        iterator Find_not_less(Node* nde, Data_t& elem);

        void Balance_tree(Node* nde, Node* root);

        void Tree_dump(const std::string& dotname, const std::string& pngname);

    };

    template <typename Data_t>
    Tree<Data_t>::Tree() :                   nde_pos(0),
                                             size(0),
                                             root(nullptr)
    {}

    //! Simple constructor of class Tree
    template <typename Data_t>
    Tree<Data_t>::Tree(const Data_t& elem) : nde_pos(1),
                                             size(1),
                                             root(new Node(elem))
    {}

    //! Destructor of class Tree without recoursion
    template <typename Data_t>
    Tree<Data_t>::~Tree()
    {
        Node* cur = root->min_node(), *prev = nullptr;

        while (cur != nullptr)
        {
            prev = cur;
            cur = cur->next;
            delete prev;
        }
    }

    template <typename Data_t>
    typename Tree<Data_t>::iterator Tree<Data_t>::begin()
    {
        return iterator{root->min_node()};
    }

    template <typename Data_t>
    typename Tree<Data_t>::iterator Tree<Data_t>::end()
    {
        return iterator{nullptr};
    }

    template <typename Data_t>
    typename Tree<Data_t>::iterator Tree<Data_t>::lower_bound(Data_t &elem)
    {
        return Find_not_less(root, elem);
    }

    template <typename Data_t>
    typename Tree<Data_t>::iterator Tree<Data_t>::Find_not_less(Node* nde, Data_t& elem)
    {
        if (nde == nullptr)
            return iterator{nullptr};

        //! Compare elem with nde->elem: chose the way
        if (elem < nde->elem)
        {
            if (nde->left == nullptr)
                return iterator{nde};

            else return Find_not_less(nde->left, elem);
        }
        else if (elem > nde->elem)
        {
            if (nde->right == nullptr)
                return iterator{nde};

            else return Find_not_less(nde->right, elem);
        }
        else if (elem == nde->elem)
            return iterator{nde};
    }

    template <typename Data_t>
    bool Tree<Data_t>::is_balanced()
    {
        return (std::abs(root->balance_factor()) <= 1);
    }

    template <typename Data_t>
    unsigned int Tree<Data_t>::get_heigth()
    {
        return root->height;
    }



    template <typename Data_t>
    void Tree<Data_t>::Balance_tree(Node* nde, Node* root)
    {
        while (nde != root)
        {
            nde->balance_node();
            nde = nde->parent;
        }
        root->balance_node();
    }

    template <typename Data_t>
    typename Tree<Data_t>::double_iterator Tree<Data_t>::insert(Data_t& elem)
    {
        double_iterator res{iterator{nullptr}, false};
        size_t old_size = size;
        //! If this insertion - first insertion
        if (size == 0)
        {
            root = new Node{elem};
            ++size;

            res.first = root;
            res.second = true;
            return res;
        }
        else
        {
            Node* cur = root;
            while (cur->elem != elem)
            {
                if (elem > cur->elem)
                {
                    if (cur->right == nullptr)
                    {
                        //! Creating new rigth child

                        Node* new_r_child = cur->right;
                        new_r_child = new Node{elem, nullptr, nullptr, cur, cur->next, cur};
                        cur->right = new_r_child;

                        //! Checking for other node after cur
                        if (cur->next != nullptr)
                            cur->next->prev = new_r_child;

                        //! By the way, we should retie cur->next to new_r_child in the end
                        cur->next = new_r_child;

                        ++size;
                        res.first = new_r_child;
                        cur->correct_heigth();
                        break;
                    }
                    else cur = cur->right;
                }
                else if (elem < cur->elem)
                {
                    if (cur->left == nullptr)
                    {
                        //! Creating new left child
                        Node* new_l_child = cur->left;
                        new_l_child = new Node{elem, nullptr, nullptr, cur, cur->next, cur};
                        cur->left = new_l_child;

                        if (cur->prev != nullptr)
                            cur->prev->next = new_l_child;

                        cur->prev = new_l_child;

                        ++size;
                        res.first = new_l_child;
                        cur->correct_heigth();
                        break;
                    }
                    else cur = cur->left;
                }
            }

            if (size != old_size)
                res.second = true;

            if (res.second)
            {
                while (cur != root)
                {
                    cur = cur->balance_node();
                    cur = cur->parent;
                }
                root = root->balance_node();
            }
               // Balance_tree(cur, root);
        }

        return res;
    }

    template <typename Data_t>
    void Tree<Data_t>::Tree_dump(const std::string& dotname, const std::string& pngname)
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


    template <typename Data_t>
    void Tree<Data_t>::Node::set_l_chld(Node *l_chld)
    {
        left = l_chld;

        //! If l_chld exist, then we can
        if (l_chld != nullptr)
        {
            l_chld->parent = this;
        }
        correct_heigth();
    }

    template <typename Data_t>
    void Tree<Data_t>::Node::set_r_chld(Node *r_chld)
    {
        left = r_chld;

        //! If r_chld exist, then we can
        if (r_chld != nullptr)
        {
            r_chld->parent = this;
        }
        correct_heigth();
    }


    template <typename Data_t>
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::right_rotate()
    {
        Node* y = left;
        //y->set_parent(parent);
        //parent->set_parent(y);

        //set_l_chld(y->right);   //old vers:: left = y->right;
        //y->set_r_chld(this);    //old vers:: y->right = this;

        left = y->right;
        y->right = this;

        //y->right->left = nullptr;  // stupid idea???

        correct_heigth();
        y->correct_heigth();

        return y;
    }

    template <typename Data_t>
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::left_rotate()
    {
        Node* y = right;
        //y->set_parent(parent);
        //parent->set_parent(y);

        right = y->left;
        y->left = this;

        //set_r_chld(y->left);  // old vers::  right = y->left;
        //y->set_l_chld(this);  // old vers::  y->left = this;

        //y->left->right = nullptr; // stupid idea???

        correct_heigth();
        y->correct_heigth();

        return y;
    }


    template <typename Data_t>
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::balance_node()
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
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::max_node()
    {
        auto cur_node = this;

        while (cur_node != nullptr)
            cur_node = cur_node->right;

        return cur_node;
    }


    template <typename Data_t>
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::min_node()
    {
        auto cur_node = this;

        while (cur_node != nullptr)
            cur_node = cur_node->left;

        return cur_node;
    }

    template <typename Data_t>
    void Tree<Data_t>::Node::Node_dump(std::ofstream& out)
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


   template <typename Data_t>
   void Tree<Data_t>::Node::set_parent(Node *prnt)
   {
       parent = prnt; // y->set_parent(x); => parent of y = x
                      // parent->set_parent(y);
       if (prnt == nullptr)
           return;

       if (prnt->elem > elem)
           prnt->left = this;

       else if (prnt->elem < elem)
           prnt->right = this;

       //! Set height for new node
       prnt->correct_heigth();
   }

}



#endif //TREE_PROBLEM_TREE_HPP
