#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <cassert>
#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <cmath>
#include <set>
#include <stack>

// Forward declaration of BinarySearchTree class
template <typename T, typename Compare>
class BinarySearchTree;

// Forward declaration of Tree_grid_square and Tree_grid classes
template <typename T, typename Compare>
class Tree_grid_square;

template <typename T, typename Compare>
class Tree_grid;

template <typename T, typename Compare>
int get_max_elt_width(const BinarySearchTree<T, Compare>& tree);

template <typename T,
          typename Compare=std::less<T>>
class BinarySearchTree {

private:
    // A Node stores an element and pointers to its left and right children
    struct Node {
        Node() {}
        Node(const T &datum_in, Node *left_in, Node *right_in)
            : datum(datum_in), left(left_in), right(right_in) { }

        T datum;
        Node *left;
        Node *right;
    };

public:
    BinarySearchTree()
        : root(nullptr) { }

    BinarySearchTree(const BinarySearchTree &other)
        : root(copy_nodes_impl(other.root)) { }

    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this == &rhs) {
            return *this;
        }
        destroy_nodes_impl(root);
        root = copy_nodes_impl(rhs.root);
        return *this;
    }

    ~BinarySearchTree() {
        destroy_nodes_impl(root);
    }

    bool empty() const {
        return empty_impl(root);
    }

    size_t height() const {
        return static_cast<size_t>(height_impl(root));
    }

    size_t size() const {
        return static_cast<size_t>(size_impl(root));
    }

    void traverse_inorder(std::ostream &os) const {
        traverse_inorder_impl(root, os);
    }

    void traverse_preorder(std::ostream &os) const {
        traverse_preorder_impl(root, os);
    }

    bool check_sorting_invariant() const {
        return check_sorting_invariant_impl(root, less);
    }

    class Iterator {
    public:
        Iterator()
            : root(nullptr), current_node(nullptr) {}

        T &operator*() const {
            return current_node->datum;
        }

        T *operator->() const {
            return &current_node->datum;
        }

        Iterator &operator++() {
            if (current_node->right) {
                current_node = min_element_impl(current_node->right);
            } else {
                current_node = min_greater_than_impl(root, current_node->datum, less);
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator result(*this);
            ++(*this);
            return result;
        }

        bool operator==(const Iterator &rhs) const {
            return current_node == rhs.current_node;
        }

        bool operator!=(const Iterator &rhs) const {
            return current_node != rhs.current_node;
        }

    private:
        friend class BinarySearchTree;

        Node *root;
        Node *current_node;
        Compare less;

        Iterator(Node *root_in, Node* current_node_in, Compare less_in)
            : root(root_in), current_node(current_node_in), less(less_in) { }
    };

    Iterator begin() const {
        if (root == nullptr) {
            return Iterator();
        }
        return Iterator(root, min_element_impl(root), less);
    }

    Iterator end() const {
        return Iterator();
    }

    Iterator min_element() const {
        return Iterator(root, min_element_impl(root), less);
    }

    Iterator max_element() const {
        return Iterator(root, max_element_impl(root), less);
    }

    Iterator min_greater_than(const T &value) const {
        return Iterator(root, min_greater_than_impl(root, value, less), less);
    }

    Iterator find(const T &query) const {
        return Iterator(root, find_impl(root, query, less), less);
    }

    Iterator insert(const T &item) {
        assert(find(item) == end());
        root = insert_impl(root, item, less);
        return find(item);
    }

    std::string to_string() const {
        std::ostringstream oss;
        traverse_inorder(oss);
        return oss.str();
    }

    friend int get_max_elt_width<>(const BinarySearchTree<T, Compare>& tree);

private:
    Node *root;
    Compare less;

    static bool empty_impl(const Node *node) {
        return !node;
    }

    static int size_impl(const Node *node) {
        if (!node) return 0;
        return 1 + size_impl(node->left) + size_impl(node->right);
    }

    static int height_impl(const Node *node) {
        if (!node) return 0;
        return 1 + std::max(height_impl(node->left), height_impl(node->right));
    }

    static Node *copy_nodes_impl(Node *node) {
        if (!node) return nullptr;
        return new Node(node->datum, copy_nodes_impl(node->left), copy_nodes_impl(node->right));
    }

    static void destroy_nodes_impl(Node *node) {
        if (!node) return;
        destroy_nodes_impl(node->left);
        destroy_nodes_impl(node->right);
        delete node;
    }

    static Node * find_impl(Node *node, const T &query, Compare less) {
        while (node) {
            if (!less(node->datum, query) && !less(query, node->datum)) return node;
            if (less(node->datum, query)) node = node->right;
            else node = node->left;
        }
        return nullptr;
    }

    static Node * insert_impl(Node *node, const T &item, Compare less) {
        if (!node) return new Node(item, nullptr, nullptr);
        if (less(item, node->datum)) node->left = insert_impl(node->left, item, less);
        else node->right = insert_impl(node->right, item, less);
        return node;
    }

    static Node * min_element_impl(Node *node) {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }

    static Node * max_element_impl(Node *node) {
        if (!node) return nullptr;
        while (node->right) node = node->right;
        return node;
    }

    static bool check_sorting_invariant_impl(const Node *node, Compare less) {
        if (!node) return true;
        if ((node->left && less(node->datum, node->left->datum)) ||
            (node->right && less(node->right->datum, node->datum))) {
            return false;
        }
        return check_sorting_invariant_impl(node->left, less) &&
               check_sorting_invariant_impl(node->right, less);
    }

    static void traverse_inorder_impl(const Node *node, std::ostream &os) {
        if (!node) return;
        traverse_inorder_impl(node->left, os);
        os << node->datum << " ";
        traverse_inorder_impl(node->right, os);
    }

    static void traverse_preorder_impl(const Node *node, std::ostream &os) {
        if (!node) return;
        os << node->datum << " ";
        traverse_preorder_impl(node->left, os);
        traverse_preorder_impl(node->right, os);
    }

    static Node * min_greater_than_impl(Node *node, const T &val, Compare less) {
        Node *successor = nullptr;
        while (node) {
            if (less(val, node->datum)) {
                successor = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return successor;
    }
};

// Specialization of to_string() for BinarySearchTree<Duck, DuckWealthLess>
template <>
std::string BinarySearchTree<Duck, DuckWealthLess>::to_string() const {
    std::ostringstream oss;
    traverse_inorder(oss);
    return oss.str();
}

// Define get_max_elt_width() function
template <typename T, typename Compare>
int get_max_elt_width(const BinarySearchTree<T, Compare>& tree) {
    return static_cast<int>(std::log10(tree.size()) + 1);
}

template <typename T, typename Compare>
std::ostream &operator<<(std::ostream &os,
                         const BinarySearchTree<T, Compare> &tree) {
// DO NOT CHANGE THE IMPLEMENTATION OF THIS FUNCTION    
  os << "[ ";
  for (T& elt : tree) {
    os << elt << " ";
  }
  return os << "]";
}

#endif // BINARY_SEARCH_TREE_HPP
