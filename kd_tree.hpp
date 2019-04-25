/******************************************************************************
/* @file Contains the kd tree class.
/*
/* TODO review and unit test
/* TODO doxy-doc
/*
/* @author langenhagen
/* @version 151021
/******************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <assert.h>
#include <memory>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS


namespace barn {


    /** Implements a kd-tree for fast region search.
    */
    template< typename data_t /*data type*/, size_t n_dims = 2 /*number of dimensions of the data type*/>
    class kd_tree {
    public: // inner typedefs
        struct node_t;
        using node_ptr = std::shared_ptr<node_t>;

    public: // inner classes

        /** Represents nodes in the kd-tree.
        */
        struct node_t {
            data_t data;                ///< data field
            node_ptr parent = nullptr;  ///< parent
            node_ptr left = nullptr;    ///< left child
            node_ptr right = nullptr;   ///< right child
        };

        /** Forward iterator.
        Iterates in a depth-first-manner from the root node via the left side to the right leaves leaves.
        TODO make bidirectional
        TODO add const_iterator
        */
        class iterator : public std::iterator<std::forward_iterator_tag, node_ptr> {

        private: // vars
            node_ptr curr_ = nullptr;
            node_ptr prev_ = nullptr;

        public: // operations

            // ctors
            iterator() noexcept {}
            iterator(node_ptr n) : curr_(n), prev_(curr_ == nullptr ? nullptr : curr_->parent) {}

            // increment / decrement operations
            inline iterator& operator++() { return advance(); } // prefix++
            inline iterator  operator++(int) { iterator tmp(*this); ++(*this); return tmp; } // postfix++

            // equality / inequality operations
            inline bool operator==(const iterator& other) const { return  curr_ == other.curr_ && prev_ == other.prev_; }
            inline bool operator!=(const iterator& other) const { return  curr_ != other.curr_ || prev_ != other.prev_; }

            // dereference operations
            inline node_t& operator*() { return *curr_; }
            inline node_ptr operator->() { return curr_; }

            /** Makes the iterator a canonical end iterator.
            Functions main purpose is not breaking client code in case of refactoring.
            */
            inline iterator& make_end() noexcept {
                curr_ = nullptr;
                prev_ = nullptr;
                return *this;
            }

        private: // helpers

            /** Traverses the iterator to the next node in a depth-first-manner.
            */
            iterator& advance() {

                if (curr_->left == nullptr && curr_->right == nullptr) {
                    prev_ = curr_;
                    curr_ = curr_->parent;
                    return advance();
                }

                if (prev_ == curr_->parent) {
                    prev_ = curr_;
                    curr_ = curr_->left;
                    return *this;
                }
                else if (prev_ == curr_->left) {
                    prev_ == curr_;
                    curr_ = curr_->right;
                    return *this;
                }
                else if (prev_ == curr_->right) /*prev_ == curr_->right*/ {
                    if (curr_->parent == nullptr)
                        return make_end();
                    prev_ = curr_;
                    curr_ = curr_->parent;
                    return advance();
                }
            }
        };

    private: // vars

        node_ptr root_ = nullptr;    ///< the root node

    public: // ctors & dtor

        /** Creates an empty tree.
        */
        kd_tree() noexcept
        {}

        /** Creates a balanced tree from the given elements.
        */
        template< typename iter_t>
        kd_tree(const iter_t start, const iter_t end) {
            root_ = create_kd_node_hierarchy(start, end, 0);
        }

    public: // methods

        /** Inserts a node into the tree structure.
        CAUTION: Tree may not be balanced.
        */
        inline node_ptr insert(const data_t& data) {
            return do_insert(data, root_, nullptr, 0);
        }

        /** Retrieves all data elements that lie in the circle given by the center and radius parameters.
        just bragging about the type of radius.. I know, a plain template param would do ...maybe better
        */
        inline std::vector<data_t*> find_points_within_range(const data_t& center, const typename std::remove_reference<decltype(center[0])>::type radius) const {
            return do_find_points_within_range(center, radius, root_, 0);
        }

        /** For debugging purposes.
        */
        std::ostream& __to_stream(std::ostream& os, const size_t layer = 0) {
            if (root_->left != nullptr)
                to_stream(os, root_->left, layer + 1);
            os << root_->data << " layer: " << layer << "\n";
            if (root_->right != nullptr)
                to_stream(os, root_->right, layer + 1);

            return os;
        }

        /** For debugging purposes.
        */
        std::ostream& __to_stream(std::ostream& os, node_ptr n, const size_t layer = 0) {
            if (n->left != nullptr)
                to_stream(os, n->left, layer + 1);
            os << n->data << " layer: " << layer << "\n";
            if (n->right != nullptr)
                to_stream(os, n->right, layer + 1);

            return os;
        }

        // iterator methods
        inline iterator begin() { return iterator(root_); }
        inline iterator end() { iterator i; return i.make_end(); }

    private: // helpers

        /** Recursively creates a kd tree hierarchy from the elements in the given ranges.
        */
        template< typename iter_t>
        node_ptr create_kd_node_hierarchy(const iter_t start, const iter_t end, size_t axis, const node_ptr& parent = nullptr) {
            assert(axis < n_dims && "axis must be smaller than the number of point dimensions");

            if (std::distance(start, end) < 1)
                return nullptr;

            iter_t middle = std::next(start, std::distance(start, end) / 2);

            std::nth_element(
                start,
                middle,
                end,
                [&axis](const data_t& i, const data_t& j) { return i[axis] < j[axis]; });

            axis = (axis + 1) % n_dims;

            node_ptr ret = create_node();
            ret->data = *middle;
            ret->parent = parent;
            ret->left = create_kd_node_hierarchy(start, middle, axis);
            ret->right = create_kd_node_hierarchy(std::next(middle, 1), end, axis);
            return ret;
        }

        /** Factory method for node pointers.
        */
        inline node_ptr create_node() {
            return std::make_shared<node_t>();
        }

        /** Recursively inserts a node at the right place.
        CAUTION: Does not auto-balance the tree.
        */
        node_ptr do_insert(const data_t& data, node_ptr& current_node, node_ptr parent_node, const size_t axis) {
            assert(axis < n_dims && "axis must be smaller than the number of point dimensions");

            if (current_node == nullptr) {
                current_node = create_node();
                current_node->data = data;
                current_node->parent = parent_node;
            }
            else if (data[axis] <= current_node->data[axis]) {
                current_node->left = do_insert(data, current_node->left, current_node, (axis + 1) % n_dims);
            }
            else {
                current_node->right = do_insert(data, current_node->right, current_node, (axis + 1) % n_dims);
            }

            return current_node;
        }

        /** Recursively retrieves all data elements that lie in the circle given by the center and radius parameters.
        */
        std::vector<data_t*> do_find_points_within_range(
            const data_t& center,
            const typename std::remove_reference<decltype(center[0])>::type radius,
            const node_ptr& current_node,
            const size_t axis) const {

            assert(axis < n_dims && "axis must be smaller than the number of point dimensions");

            std::vector<data_t*> ret;

            if (current_node == nullptr)
                return ret;

            data_t &current_data = current_node->data;

            const auto axis_projected_distance = current_data[axis] - center[axis];
            if (axis_projected_distance > radius) {
                // *** current point lies not in range ***

                if (current_data[axis] > center[axis])
                    // *** current point too big ** => go left
                    ret = do_find_points_within_range(center, radius, current_node->left, (axis + 1) % n_dims);
                else
                    // *** current point too small *** => go right
                    ret = do_find_points_within_range(center, radius, current_node->right, (axis + 1) % n_dims);
            }
            else {
                // *** current point lies in bounding area ***
                if (distance(current_data, center) <= radius)
                    ret.push_back(&current_data);

                auto left = do_find_points_within_range(center, radius, current_node->left, (axis + 1) % n_dims);
                auto right = do_find_points_within_range(center, radius, current_node->right, (axis + 1) % n_dims);
                ret.insert(ret.end(), left.begin(), left.end());
                ret.insert(ret.end(), right.begin(), right.end());
            }

            return ret;
        }


        /** Calculates the euclidean distance between two data elements.
        I'd like to discuss this with you. (Scope, encapsulation, independence and of course sqrt).
        */
        auto distance(const data_t& a, const data_t& b) const {

            typename std::decay<decltype(a[0])>::type dist(0);

            for (int i = 0; i < n_dims; ++i)
                dist += (a[i] - b[i]) * (a[i] - b[i]);
            return sqrt(dist);
        }
    };

} // END namespace barn