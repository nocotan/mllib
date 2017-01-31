#ifndef MLLIB_SPR_TREE_H
#define MLLIB_SPR_TREE_H

/**
 * @file spr.hpp
 * @author nocotan
 * @date 2017/01/30
 *
 *
 * SPR: Subtree-Pruning-Regrafting
 *
 * SPR is a procedure to prune away a randomly chosen subtree and then reattach
 * it at a random point on a randomly selected edge of the remaing tree. To
 * determine the acceptance probability, it is neccessary to be very explicit
 * about all of the steps.
 *
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <string>

namespace mllib {

    /**
     * SPR-tree node class
     */
    template<typename T>
    struct node : public std::enable_shared_from_this< node<T> > {
        T data;
        int label;
        std::shared_ptr< node<T> > root;
        std::shared_ptr< node<T> > left;
        std::shared_ptr< node<T> > right;

        node();
        node(T data);
        node(T data, std::shared_ptr< node<T> > root);

        void insert(T data);
        const bool has_data(T data) const;
        std::shared_ptr< node<T> > find(T data);

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const node<U>& nd);

        private:
            void insert_left(T left);
            void insert_right(T right);
            void disp(int depth) const;
    };


    /**
     * SPR-tree class
     * this class implements a binary-tree which has prune and regraft method.
     */
    template<typename T>
    struct spr_tree : public std::enable_shared_from_this< spr_tree<T> > {
        std::shared_ptr< node<T> > root;

        spr_tree();
        spr_tree(T data);
        spr_tree(const spr_tree& tree);

        void insert(T data);
        const bool has_data(T data) const;
        std::shared_ptr< spr_tree<T> > find(T data);

        std::shared_ptr< node<T> > prune();
        void regraft(std::shared_ptr< node<T> > nd);

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const spr_tree<U>& tree);

        private:
            std::vector< std::shared_ptr< node<T> > > pick(std::shared_ptr< node<T> > current_ptr);
    };

    /**
     * alias
     */
    template<typename T> using nd_ptr = std::shared_ptr< node<T> >;
    template<typename T> using nd_vec = std::vector< nd_ptr<T> >;
    template<typename T> using nd_que = std::queue< nd_ptr<T> >;
    template<typename T, typename U> using nd_map = std::map<nd_ptr<T>, U>;
    template<typename T> using tree_ptr = std::shared_ptr< spr_tree<T> >;


    /**
     *
     * SPR-tree node
     *
     */

    template<typename T> node<T>::node()
        : left(nullptr), right(nullptr), root(nullptr) { }

    template<typename T> node<T>::node(T data)
        : left(nullptr), right(nullptr), data(data), root(nullptr) { }

    template<typename T> node<T>::node(T data, nd_ptr<T> root)
        : left(nullptr), right(nullptr), data(data), root(root) { }

    template<typename T> void node<T>::insert(T data) {
        if (this->data > data) {
            if (this->left == nullptr) {
                this->insert_left(data);
            }
            else {
                this->left->insert(data);
            }
        }
        else if (this->data < data) {
            if (this->right == nullptr) {
                this->insert_right(data);
            }
            else {
                this->right->insert(data);
            }
        }
    }

    template<typename T> const bool node<T>::has_data(T data) const{
        if (this->data == data)
            return true;
        else if (this->left == nullptr && this->right == nullptr)
            return false;
        else if (this->left != nullptr)
            return this->left->has_data(data);
        else if (this->right != nullptr)
            return this->right->has_data(data);
        else
            return this->left->has_data(data) || this->right->has_data(data);

        return false;
    }

    template<typename T> nd_ptr<T> node<T>::find(T data) {
        if (this->data == data) return this->shared_from_this();
        if (this->left->find(data) != nullptr) return this->left->find(data);
        if (this->right->find(data) != nullptr) return this->right->find(data);
        return nullptr;
    }

    template<typename T> void node<T>::insert_left(T data) {
        this->left = std::make_shared< node<T> >(data, this->shared_from_this());
    }

    template<typename T> void node<T>::insert_right(T data) {
        this->right = std::make_shared< node<T> >(data, this->shared_from_this());
    }

    template<typename T> void node<T>::disp(int depth) const {
        if (depth == 0)
            std::cout << " . " << this->data << std::endl;
        else {
            std::string cap(depth, ' ');
            std::cout << cap << "|-- ";
            std::cout << this->data << std::endl;
        }

        if (this->left != nullptr)
            this->left->disp(depth+1);
        if (this->right != nullptr)
            this->right->disp(depth+1);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const node<T>& nd) {
        nd.disp(0);
        return os;
    }



    /**
     *
     * SPR-tree
     *
     */

    template<typename T> spr_tree<T>::spr_tree()
        : root(nullptr) { }

    template<typename T> spr_tree<T>::spr_tree(T data)
        : root(std::make_shared< node<T> >(data)) { }

    template<typename T> spr_tree<T>::spr_tree(const spr_tree& tree)
        : root(tree.root) { }

    template<typename T> void spr_tree<T>::insert(T data) {
        this->root->insert(data);
    }

    template<typename T> const bool spr_tree<T>::has_data(T data) const {
        return this->root->has_data(data);
    }

    template<typename T> tree_ptr<T> spr_tree<T>::find(T data) {
        return this->root->find(data);
    }

    /**
     * Prune step
     */
    template<typename T> nd_ptr<T> spr_tree<T>::prune() {
        int dir;
        // 0->left, 1->right
        if (this->root->left  == nullptr)
            dir = 1;
        else if (this->root->right == nullptr)
            dir = 0;
        else {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dir_dist(0,1);
            dir = dir_dist(mt);
        }

        nd_vec<T> pick_list;

        if (dir == 0) {
            pick_list = this->pick(this->root->left);
        }
        else {
            pick_list = this->pick(this->root->right);
        }

        std::sort(pick_list.begin(), pick_list.end());
        pick_list.erase(std::unique(pick_list.begin(), pick_list.end()), pick_list.end());

        nd_ptr<T> empty_ptr;

        int n = pick_list.size();
        if (n == 0)
            return empty_ptr;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> target_dist(0,n-1);
        int target = target_dist(mt);

        auto&& res = pick_list[target];

        if (res->root->left == res) {
            res->root->left = nullptr;
            res->root = nullptr;
        }
        else {
            res->root->right = nullptr;
            res->root = nullptr;
        }

        return pick_list[target];
    }

    template<typename T> void spr_tree<T>::regraft(nd_ptr<T> nd) {
        int dir;
        // 0->left, 1->right
        if (this->root->left  == nullptr)
            dir = 1;
        else if (this->root->right == nullptr)
            dir = 0;
        else {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dir_dist(0,1);
            dir = dir_dist(mt);
        }

        nd_vec<T> pick_list;

        if (dir == 0) {
            pick_list = this->pick(this->root->left);
            if (pick_list.size() == 0)
                pick_list = this->pick(this->root->right);
        }
        else
            pick_list = this->pick(this->root->right);
            if (pick_list.size() == 0)
                pick_list = this->pick(this->root->left);

        nd_vec<T> target_list;
        for (auto elem : pick_list) {
            if (elem->left == nullptr || elem->right == nullptr)
                target_list.push_back(elem);
        }

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> target_dist(0,target_list.size()-1);
        int target = target_dist(mt);

        auto&& target_nd = target_list[target];

        if (target_nd->left == nullptr) {
            target_nd->left = nd;
            nd->root = target_nd;
        }
        else if (target_nd->right == nullptr){
            target_nd->right = nd;
            nd->root = target_nd;
        }

    }

    /**
     * DFS
     * pick up target node by depth first search.
     */
    template<typename T>
    std::vector< nd_ptr<T> > spr_tree<T>::pick(nd_ptr<T> current_ptr) {
        nd_vec<T> pick_list;
        nd_map<T, int> memo;
        nd_que<T> que;

        while (true) {
            memo[current_ptr] = 1;
            if (current_ptr->left != nullptr || current_ptr->right != nullptr) {
                pick_list.push_back(current_ptr);
            }

            if (current_ptr->left != nullptr && memo.count(current_ptr->left) == 0) {
                que.push(current_ptr);
                current_ptr = current_ptr->left;
            }
            else if (current_ptr->right != nullptr && memo.count(current_ptr->right) == 0) {
                que.push(current_ptr);
                current_ptr = current_ptr->right;
            }
            else if (!que.empty()) {
                current_ptr = que.front();
                que.pop();
            }
            else break;
        }

        return pick_list;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const spr_tree<T>& tree) {
        std::cout << *tree.root;
        return os;
    }

};

#endif
