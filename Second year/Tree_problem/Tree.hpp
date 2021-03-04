//
// Created by anon on 03.02.2021.
//

#ifndef TREE_PROBLEM_TREE_HPP
#define TREE_PROBLEM_TREE_HPP


#include <fstream>
#include <iostream>


/*       main conception of AVL tree      */

namespace avl_tree
{
    template<typename Data_t>
    class Tree final
    {

    private:
        struct Node;
        struct iterator;

    private:

        Node *root = nullptr;
        size_t size = 0;

        using double_iterator = std::pair<iterator, bool>;

        enum INSERT_SIDE
        {
            LEFT, RIGHT
        };

    public:
        Tree();

        explicit Tree(const Data_t &elem);

        Tree(const Tree &tree);

        Tree(Tree &&tree) noexcept;

        ~Tree();

        size_t get_size() { return size; }

        [[nodiscard]] bool is_balanced() const;

        [[nodiscard]] unsigned int get_heigth() const;

        //! Function for insertion elem into my avl_tree
        //! \param elem
        //! \return double iterator
        double_iterator insert(Data_t &elem);

        //! Function for finding not less than elem in my avl tree
        //! \param elem
        //! \return iterator
        iterator lower_bound(Data_t &elem) const;

        //! Function for getting begin to my avl_tree
        //! \return iterator
        iterator begin() const;

        //! Function for getting end to my avl_tree
        //! \return iterator
        iterator end() const;

        //! Function - hepler for lower_bound(...)
        //! \param nde
        //! \param elem
        //! \return iterator
        iterator Find_not_less(Node *nde, Data_t &elem) const;

        //! Function for balance my avl_tree
        //! \param nde
        //! \param root
        void Balance_tree(Node **nde, Node **root);

        //! Dump my avl_tree to png format
        //! \param dotname
        //! \param pngname
        void Tree_dump(const std::string &dotname, const std::string &pngname) const;

        //! Copy assignment operator
        //! \param rhs
        //! \return tree reference

        Tree &operator=(const Tree &rhs)
        {
            Tree<Data_t> tmp(rhs);

            this->root = tmp.root;
            this->size = tmp.size;

            return *(this);
        }

        //!  Move assignment operator
        //! \param other_tree
        //! \return tree reference
        Tree &operator=(Tree &&other_tree) noexcept
                {
            if (this != &other_tree)
            {
                delete root;

                root = other_tree.root;
                size = other_tree.size;

                other_tree.root = nullptr;
                other_tree.size = 0;
            }
            return *this;
        }

        void Insert_helper_func(INSERT_SIDE side, Data_t &elem, Node **cur, double_iterator &res);


    private:
        struct Node final
        {
            //private:
            Data_t elem = 0;

            Node *left = nullptr;
            Node *right = nullptr;

            Node *parent = nullptr;


            Node *next = nullptr;
            Node *prev = nullptr;

            unsigned int height = 0;


        public:
            Node(Data_t &elem_) : elem(elem_) {}

            Node(Data_t &elem_, Node *left_, Node *right_, Node *parent_, Node *next_, Node *prev_) : elem(elem_),
                                                                                                      left(left_),
                                                                                                      right(right_),
                                                                                                      parent(parent_),
                                                                                                      next(next_),
                                                                                                      prev(prev_) {
                correct_heigth();
            }

#if 0
            Node(Data_t &elem_, Node *left_, Node *right_, Node *parent_)
            {
                elem = elem_;
                left = left_;
                right = right_;
                parent = parent_;
                correct_heigth();
            }
#endif


            //! Function for fixing new heigth of subtree
            void correct_heigth();

            //! Function for getting heigth of left and rigth subtree of node
            //! This function useful for creating AVL - Tree
            int balance_factor() const;


            void set_parent(Node *parent);

            void set_l_chld(Node *l_chld);

            void set_r_chld(Node *r_chld);

            //! Function for making a rigth rotate around the node
            Node *right_rotate();

            //! Function for making a rigth rotate around the node
            Node *left_rotate();

            //! Function for balance node this by defenition AVL - Tree
            Node *balance_node();

            //! Function for finding node with min elem
            Node *min_node();

            //! Function for finding node with max elem
            Node *max_node();

            void Node_dump(std::ofstream &out) const;
        };

        struct iterator final
        {
            Node *nde_it;

        public:
            /* Simple constructor */
            iterator(Node *nde) : nde_it(nde) {}

            /* Copy constructor for iterator */
            iterator(const iterator &it) : nde_it(it.nde_it) {}


            /* Reloading operators for iterator */
            
            iterator &operator=(const iterator &it)
            {
                nde_it = it.nde_it;
                return *this;
            }

            Data_t operator*() const
            {
                return nde_it->elem;
            }

            bool operator==(const iterator &it) const
            {
                if (nde_it == it.nde_it)
                    return true;

                else return false;
            }

            bool operator!=(const iterator &it) const
            {
                return !(operator==(it));
            }

            iterator &operator++()
            {
                nde_it = nde_it->next;
                return *(this);
            }
        };

    };


    template<typename Data_t>
    Tree<Data_t>::Tree() {}

    //! Constructor of class Tree
    template<typename Data_t>
    Tree<Data_t>::Tree(const Data_t &elem) : size(1),
                                             root(new Node(elem)) {}


    //! Copy-ctor for my tree
    template<typename Data_t>
    Tree<Data_t>::Tree(const Tree<Data_t> &other_tree)
    {
        //Node* cur = root;

        if (other_tree.root != nullptr)
        {
            std::vector<iterator> buf;
            buf.reserve(other_tree.size);

            for (iterator iter = other_tree.begin(); iter != other_tree.end(); ++iter)
                buf.push_back(iter);

            //iterator cur = begin();
            for (size_t i = 0; i < other_tree.size; ++i)
                insert(buf[i].nde_it->elem);
        }

    }

    //! Move-ctor for my tree
    template<typename Data_t>
    Tree<Data_t>::Tree(Tree<Data_t> &&other_tree) noexcept
            : root(nullptr),
              size(0)
    {
        std::cout << "Move constructor is used!\n";

        // Copy the data pointer and its length from the
        root = other_tree.root;
        size = other_tree;

        other_tree.root = nullptr;
        other_tree.size = 0;
    }


    //! Destructor of class Tree without recoursion
    template<typename Data_t>
    Tree<Data_t>::~Tree()
    {
        Node *cur = root->min_node(), *prev = nullptr;

        while (cur != nullptr)
        {
            prev = cur;
            cur = cur->next;
            delete prev;
        }
    }

    //**********************************//        Next           //**********************************//
    //**********************************//    There is methods   //**********************************//
    //**********************************//     of structure      //**********************************//
    //**********************************//                       //**********************************//
    //**********************************//        TREE           //**********************************//
    //**********************************//                       //**********************************//
    //**********************************//                       //**********************************//

    template<typename Data_t>
    typename Tree<Data_t>::iterator Tree<Data_t>::begin() const
    {
        return iterator{root->min_node()};
    }

    template<typename Data_t>
    typename Tree<Data_t>::iterator Tree<Data_t>::end() const
    {
        return iterator{nullptr};
    }

    template<typename Data_t>
    typename Tree<Data_t>::iterator Tree<Data_t>::lower_bound(Data_t &elem) const
    {
        return Find_not_less(root, elem);
    }

    template<typename Data_t>
    typename Tree<Data_t>::iterator Tree<Data_t>::Find_not_less(Node *nde, Data_t &elem) const
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
                return ++iterator{nde};

            else return Find_not_less(nde->right, elem);
        }
        else if (elem == nde->elem)
            return iterator{nde};

        return iterator{nullptr};
    }

    template<typename Data_t>
    bool Tree<Data_t>::is_balanced() const
    {
        return (std::abs(root->balance_factor()) <= 1);
    }

    template<typename Data_t>
    unsigned int Tree<Data_t>::get_heigth() const
    {
        return root->height;
    }

    template<typename Data_t>
    void Tree<Data_t>::Balance_tree(Node **nde, Node **root)
    {
        while (*nde != *root)
        {
            *nde = (*nde)->balance_node();
            *nde = (*nde)->parent;
        }
        *root = (*root)->balance_node();
    }


    template<typename Data_t>
    void
    Tree<Data_t>::Insert_helper_func(Tree<Data_t>::INSERT_SIDE side, Data_t &elem, Node **cur, double_iterator &res)
    {
        Node* new_child;

        if (side == RIGHT)
        {
            new_child = new Node{elem, nullptr, nullptr, *cur, (*cur)->next, (*cur)};
            (*cur)->right = new_child;

            //! Checking for other node after cur
            if ((*cur)->next != nullptr)
                (*cur)->next->prev = new_child;
            //! By the way, we should retie cur->next to new_r_child in the end
            (*cur)->next = new_child;

        }
        else if (side == LEFT)
        {
            new_child = new Node{elem, nullptr, nullptr, *cur, (*cur), (*cur)->prev};
            (*cur)->left = new_child;

            if ((*cur)->prev != nullptr)
                (*cur)->prev->next = new_child;

            (*cur)->prev = new_child;
        }

        ++size;
        res.first = new_child;
        (*cur)->correct_heigth();
    }


    template<typename Data_t>
    typename Tree<Data_t>::double_iterator Tree<Data_t>::insert(Data_t &elem)
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
        } else {
            Node *cur = root;
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


    template<typename Data_t>
    void Tree<Data_t>::Tree_dump(const std::string &dotname, const std::string &pngname) const
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


//**********************************//        Next           //**********************************//
//**********************************//    There is methods   //**********************************//
//**********************************//     of structure      //**********************************//
//**********************************//                       //**********************************//
//**********************************//        NODE           //**********************************//
//**********************************//                       //**********************************//
//**********************************//                       //**********************************//


    template<typename Data_t>
    void Tree<Data_t>::Node::correct_heigth()
    {
        int r_hgth = (right != nullptr) ? right->height : 0;
        int l_hgth = (left != nullptr) ? left->height : 0;

        height = (1 + std::max(r_hgth, l_hgth));
    }

    template<typename Data_t>
    int Tree<Data_t>::Node::balance_factor() const
    {
        int r_hgth = (right != nullptr) ? right->height : 0;
        int l_hgth = (left != nullptr) ? left->height : 0;

        return r_hgth - l_hgth;
    }


    template<typename Data_t>
    void Tree<Data_t>::Node::set_l_chld(Node *l_chld)
    {
        left = l_chld;

        //! If l_chld exist, then we can
        if (l_chld != nullptr)
            l_chld->parent = this;

        correct_heigth();
    }

    template<typename Data_t>
    void Tree<Data_t>::Node::set_r_chld(Node *r_chld)
    {
        right = r_chld;

        //! If r_chld exist, then we can
        if (r_chld != nullptr)
            r_chld->parent = this;

        correct_heigth();
    }


    template<typename Data_t>
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::right_rotate()
    {
        Node *y = left;
        y->set_parent(parent);

        set_l_chld(y->right);   //old vers:: left = y->right;
        y->set_r_chld(this);    //old vers:: y->right = this;

        correct_heigth();
        y->correct_heigth();

        return y;
    }

    template<typename Data_t>
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::left_rotate()
    {
        Node *y = right;
        y->set_parent(parent);

        set_r_chld(y->left);  // old vers::  right = y->left;
        y->set_l_chld(this);  // old vers::  y->left = this;

        correct_heigth();
        y->correct_heigth();

        return y;
    }

    template<typename Data_t>
    void Tree<Data_t>::Node::set_parent(Node *prnt)
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


    template<typename Data_t>
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::balance_node()
    {
        //! Refresh height
        correct_heigth();

        int b_factor = balance_factor();

        if (b_factor == 2) {
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

    template<typename Data_t>
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::max_node()
    {
        auto cur_node = this;

        while (cur_node->right != nullptr)
            cur_node = cur_node->right;

        return cur_node;
    }


    template<typename Data_t>
    typename Tree<Data_t>::Node* Tree<Data_t>::Node::min_node()
    {
        auto cur_node = this;

        while (cur_node->left != nullptr)
            cur_node = cur_node->left;

        return cur_node;
    }

    template<typename Data_t>
    void Tree<Data_t>::Node::Node_dump(std::ofstream &out) const
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

#endif //TREE_PROBLEM_TREE_HPP
