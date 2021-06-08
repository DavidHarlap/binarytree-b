#pragma once
#include <iostream>
#include <stdbool.h>
#include <vector>

using namespace std;
namespace ariel
{

    template <typename T>
    class BinaryTree
    {

    private:
            struct Node
            {
            
                T node_val;
                Node *right_node;
                Node *left_node;
                Node(const T &n_val) : node_val(n_val), right_node(nullptr), left_node(nullptr){ }
                
                ~Node() {
                    delete right_node;
                    delete left_node;
                }

            public:
                // copy
                Node(const Node &n) : node_val(n.node_val)
                {
                    right_node = (n.right_node) ? new Node(*n.right_node) : nullptr;
                    left_node = (n.left_node) ? new Node(*n.left_node) : nullptr;
                }
                 
                Node &operator=(Node n) {
                    if (this != &n) {
                        delete right_node;
                        delete left_node; 
                    
                        right_node = (n.right_node) ? new Node(*n.right_node) : nullptr;
                        left_node = (n.left_node) ? new Node(*n.left_node) : nullptr;
                        

                        return *this;
                    }
                    return *this;
                }
                
                //move
                Node(Node &&n) noexcept{
                    node_val = n.node_val;
                    right_node = n.right_node;
                    left_node = n.left_node;
                    n.left_node = nullptr;
                    n.right_node = nullptr;
                }

                
                Node &operator=(Node &&n) noexcept {
                    if (left_node){ delete left_node; }
                    if (right_node){ delete right_node; }
                    node_val = n.node_val;
                    right_node = n.right_node;
                    n.right_node = nullptr;
                    left_node = n.left_node;
                    n.left_node = nullptr;
                }

                
                
                /*T get_val()const{
                    return node_val;
                }*/

        };

        Node* root;

         Node* findNode(Node *root, const T val) {
            if (root == nullptr) {return nullptr;}
            if (root->node_val == val) {return root;}
            
            Node *r_Node = findNode(root->right_node, val);
            if (r_Node == nullptr) {
                return findNode(root->left_node, val);
            }

            return r_Node;
        }

    public:
    
        BinaryTree(): root(nullptr) { }
        ~BinaryTree(){ delete root;}

        //copy
         BinaryTree(const BinaryTree &bn) {
            root = new Node(*bn.root);
        }

        //move
        BinaryTree(BinaryTree &&bn) noexcept
        {
            root = bn.root;
            bn.root = nullptr;
        }


        BinaryTree &operator=(BinaryTree bn)
        {
            if (this != &bn)
            {
                delete root;
                root = new Node(*bn.root);
                return *this;
            }

            return *this;
        }
        
        BinaryTree &operator=(BinaryTree &&bn) noexcept
        {
            if (root)
            {
                delete root;
            }
            root = bn.root;
            bn.root = nullptr;
            return *this;
        }

        
        bool isEmpty() const { return root == nullptr; }
        
        BinaryTree <T> &add_root(const T t){
            if (root == nullptr)
            {
                root = new Node{t};
            }
            else
            {
                root->node_val = t;
            }
            return *this;
        }
            
        BinaryTree <T> &add_left(const T &t1, const T &t2){
            Node *temp = findNode(this->root, t1);
            if (temp == nullptr)
            {
                throw invalid_argument("Illigal argument");
            }
            if (temp->left_node == nullptr)
            {
                temp->left_node = new Node(t2);
            }
            else
            {
                temp->left_node->node_val = t2;
            }
            
            return *this;
        }

        BinaryTree <T> &add_right(const T &t1, const T &t2){
            Node *temp = findNode(this->root, t1);
            if (temp == nullptr)
            {
                throw invalid_argument("Illigal argument");
            }
            if (temp->right_node == nullptr)
            {
                temp->right_node = new Node(t2);
            }
            else
            {
                temp->right_node->node_val = t2;
            }
            
            return *this;
        }

        friend ostream &operator<<(ostream &os, const BinaryTree &Bt){
            return os<<"TREE";
        } 

 
        

        
        class Pre_iterator
        {
            private:
                Node *curr_node;
                std::vector<Node *> vec;
                unsigned long index;


                static void preV(Node **root, std::vector<Node *> &vec) {
                    if (*root != nullptr)
                    {
                        vec.push_back(*root);
                        preV(&(*root)->left_node, vec);
                        preV(&(*root)->right_node, vec);
                    }
                }

            public:
            
                Pre_iterator(Node* ptr= nullptr,unsigned long index = 0): curr_node(ptr), index(index){
                    vec.clear();
                    if (ptr != nullptr){
                        preV(&ptr, vec);
                    }
                    vec.push_back(nullptr);
                    curr_node = vec.at(0);
                }
                
                T& operator*() const{
                    return curr_node->node_val;
                }

                T* operator->() const {
                    return &(curr_node->node_val);
                }

                Pre_iterator &operator ++()
                {
                    curr_node=vec.at(++index);
                    return *this;
                }

                Pre_iterator operator++(int)
                {
                    Pre_iterator tmp = *this;
                    curr_node = vec.at(++index);
                    return tmp;
                }

                bool operator==(const Pre_iterator& other) const
                {
                    return curr_node==other.curr_node;
                }
                bool operator!=(const Pre_iterator& other) const
                {
                    return curr_node!=other.curr_node;
                }
            

        };

        class Post_iterator
        {
            private:
                Node *curr_node;
                std::vector<Node *> vec;
                unsigned long index;


                static void postV(Node **root, std::vector<Node *> &vec)
                {
                    if (*root != nullptr)
                    {
                        postV(&(*root)->left_node, vec);
                        postV(&(*root)->right_node, vec);
                        vec.push_back(*root);
                    }
                }

            public:
            
                Post_iterator(Node* ptr= nullptr,unsigned long index = 0): curr_node(ptr), index(index){
                    vec.clear();
                    if (ptr != nullptr){
                        postV(&ptr, vec);
                    }
                    vec.push_back(nullptr);
                    curr_node = vec.at(0);
                }
                
                T& operator*() const{
                    return curr_node->node_val;
                }

                T* operator->() const {
                    return &(curr_node->node_val);
                }

                Post_iterator &operator ++()
                {
                    curr_node=vec.at(++index);
                    return *this;
                }

                Post_iterator operator++(int)
                {
                    Post_iterator tmp = *this;
                    curr_node = vec.at(++index);
                    return tmp;
                }

                bool operator==(const Post_iterator& other) const
                {
                    return curr_node==other.curr_node;
                }
                bool operator!=(const Post_iterator& other) const
                {
                    return curr_node!=other.curr_node;
                }
            
            

        };

        class In_iterator
        {
            private:
                Node *curr_node;
                std::vector<Node *> vec;
                unsigned long index;


                static void inV(Node **root, std::vector<Node *> &vec)
                {
                    if (*root != nullptr)
                    {
                        inV(&(*root)->left_node, vec);
                        vec.push_back(*root);
                        inV(&(*root)->right_node, vec);
                    }
                }

            public:
            
                In_iterator(Node* ptr= nullptr,unsigned long index = 0): curr_node(ptr), index(index){
                    vec.clear();
                    if (ptr != nullptr){
                        inV(&ptr, vec);
                    }
                    vec.push_back(nullptr);
                    curr_node = vec.at(0);
                }
                
                T& operator*() const{
                    return curr_node->node_val;
                }

                T* operator->() const {
                    return &(curr_node->node_val);
                }

                In_iterator &operator ++()
                {
                    curr_node=vec.at(++index);
                    return *this;
                }

                In_iterator operator++(int)
                {
                    In_iterator tmp = *this;
                    curr_node = vec.at(++index);
                    return tmp;
                }

                bool operator==(const In_iterator& other) const
                {
                    return curr_node==other.curr_node;
                }
                bool operator!=(const In_iterator& other) const
                {
                    return curr_node!=other.curr_node;
                }
            
            

        };

        In_iterator begin() {
            return In_iterator(root);
        }
        In_iterator end() {
            return In_iterator(root);
        }
        Pre_iterator begin_preorder() {
            return Pre_iterator(root);
        }
        Pre_iterator end_preorder() {
            return Pre_iterator(root);
        }
        In_iterator begin_inorder() {
            return In_iterator(root);
        }
        In_iterator end_inorder() {
            return In_iterator(root);
        }
        Post_iterator begin_postorder() {
            return Post_iterator(root);
        }
        Post_iterator end_postorder() {
            return Post_iterator(root);
        }
    
    };


};