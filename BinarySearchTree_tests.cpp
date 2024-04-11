#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"

TEST(test_empty_tree) {
    BinarySearchTree<int> tree;
    
    // Test empty tree properties
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0);
    ASSERT_EQUAL(tree.height(), 0);
}

TEST(test_insert_and_size) {
    BinarySearchTree<int> tree;
    
    // Insert elements into the tree
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // Test size of the tree
    ASSERT_EQUAL(tree.size(), 5);
}

TEST(test_height) {
    BinarySearchTree<int> tree;
    
    // Insert elements into the tree
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // Test height of the tree
    ASSERT_EQUAL(tree.height(), 3); // Height should be 3
}

TEST(test_traversal) {
    BinarySearchTree<int> tree;
    
    // Insert elements into the tree
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    std::stringstream ss;
    
    // Traverse tree in-order and compare with expected output
    tree.traverse_inorder(ss);
    ASSERT_EQUAL(ss.str(), "3 5 7 10 15 ");
}

TEST(test_find) {
    BinarySearchTree<int> tree;
    
    // Insert elements into the tree
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // Test finding elements in the tree
    ASSERT_NOT_EQUAL(tree.find(5), tree.end());
    ASSERT_EQUAL(*tree.find(5), 5);
    ASSERT_EQUAL(tree.find(100), tree.end()); // Element not in tree
}

TEST(test_min_max) {
    BinarySearchTree<int> tree;
    
    // Insert elements into the tree
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // Test minimum and maximum elements in the tree
    ASSERT_EQUAL(*tree.min_element(), 3);
    ASSERT_EQUAL(*tree.max_element(), 15);
}

TEST(test_copy_constructor_and_assignment_operator) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    
    // Test copy constructor
    BinarySearchTree<int> copy_tree(tree);
    ASSERT_EQUAL(tree.size(), copy_tree.size());
    
    // Test assignment operator
    BinarySearchTree<int> assigned_tree;
    assigned_tree = tree;
    ASSERT_EQUAL(tree.size(), assigned_tree.size());
}

TEST(test_min_greater_than_empty_tree) {
    BinarySearchTree<int> tree;
    
    // Test min_greater_than on empty tree
    ASSERT_EQUAL(tree.min_greater_than(5), tree.end());
}

TEST(test_iterator) {
    BinarySearchTree<int> tree;
    
    // Insert elements into the tree
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    std::vector<int> elements;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        elements.push_back(*it);
    }
    
    // Test elements retrieved by iterator
    std::vector<int> expected{3, 5, 7, 10, 15};
    ASSERT_EQUAL(elements.size(), expected.size()); // Check sizes first
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQUAL(elements[i], expected[i]); // Check each element
    }
}

TEST(test_inorder_traversal_order) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    std::stringstream ss;
    
    // Traverse tree in-order and compare with expected output
    tree.traverse_inorder(ss);
    ASSERT_EQUAL(ss.str(), "3 5 7 10 15 ");
}

TEST(test_preorder_traversal_order) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    std::stringstream ss;
    
    // Traverse tree in pre-order and compare with expected output
    tree.traverse_preorder(ss);
    ASSERT_EQUAL(ss.str(), "10 5 3 7 15 ");
}

TEST(test_copy_constructor_non_empty_tree) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    
    // Test copy constructor with non-empty tree
    BinarySearchTree<int> copy_tree(tree);
    ASSERT_EQUAL(tree.size(), copy_tree.size());

    // Compare elements of the trees manually
    auto tree_it = tree.begin();
    auto copy_tree_it = copy_tree.begin();
    while (tree_it != tree.end() && copy_tree_it != copy_tree.end()) {
        ASSERT_EQUAL(*tree_it, *copy_tree_it);
        ++tree_it;
        ++copy_tree_it;
    }
    // Ensure both iterators reached the end at the same time
    ASSERT_TRUE(tree_it == tree.end() && copy_tree_it == copy_tree.end());
}

TEST(test_assignment_operator_non_empty_tree) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    
    // Test assignment operator with non-empty tree
    BinarySearchTree<int> assigned_tree;
    assigned_tree = tree;
    ASSERT_EQUAL(tree.size(), assigned_tree.size());

    // Compare elements of the trees manually
    auto tree_it = tree.begin();
    auto assigned_tree_it = assigned_tree.begin();
    while (tree_it != tree.end() && assigned_tree_it != assigned_tree.end()) {
        ASSERT_EQUAL(*tree_it, *assigned_tree_it);
        ++tree_it;
        ++assigned_tree_it;
    }
    // Ensure both iterators reached the end at the same time
    ASSERT_TRUE(tree_it == tree.end() && assigned_tree_it == assigned_tree.end());
}

TEST(test_find_absent_element) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    
    // Test finding an element not in the tree
    ASSERT_EQUAL(tree.find(100), tree.end());
}

TEST(test_min_max_empty_tree) {
    BinarySearchTree<int> tree;
    
    // Test minimum and maximum elements on an empty tree
    ASSERT_EQUAL(tree.min_element(), tree.end());
    ASSERT_EQUAL(tree.max_element(), tree.end());
}

TEST(test_iterator_increment) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    std::vector<int> elements;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        elements.push_back(*it);
    }

    // Test elements retrieved by iterator
    std::vector<int> expected{5, 10, 15};
    ASSERT_EQUAL(elements.size(), expected.size()); // Check sizes first
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQUAL(elements[i], expected[i]); // Check each element
    }
}

TEST(test_copy_constructor_empty_tree) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int> copy_tree(tree);
    ASSERT_TRUE(copy_tree.empty()); // Copied tree should also be empty
    ASSERT_EQUAL(copy_tree.size(), 0); // Copied tree size should be 0
}

// Test case for tree balance
TEST(test_tree_balance) {
    BinarySearchTree<int> tree;
    // Insert elements in a sorted order to ensure a balanced tree
    for (int i = 1; i <= 15; ++i) {
        tree.insert(i);
    }
    ASSERT_EQUAL(tree.size(), 15);
    ASSERT_EQUAL(tree.height(), 15); // Balanced tree height should be log2(n)
}

TEST(test_large_set_elements) {
    BinarySearchTree<int> tree;
    // Inserting large number of elements
    for (int i = 0; i < 10000; ++i) {
        tree.insert(i);
    }
    ASSERT_EQUAL(tree.size(), 10000);
    ASSERT_EQUAL(tree.height(), 10000); // Height of a balanced tree with 10000 nodes
}

TEST(test_tree_height) {
    BinarySearchTree<int> tree;
    
    // Insert some elements
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // Check if the height of the tree matches the expected height
    ASSERT_EQUAL(tree.height(), 3);
}

TEST(test_min_max_elements) {
    BinarySearchTree<int> tree;
    
    // Insert some elements
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // Check if the minimum and maximum elements are found correctly
    ASSERT_EQUAL(*(tree.min_element()), 3);
    ASSERT_EQUAL(*(tree.max_element()), 15);
}

TEST(test_find_existing_elements) {
    BinarySearchTree<int> tree;
    
    // Insert some elements
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    // Search for existing elements
    ASSERT_NOT_EQUAL(tree.find(10), tree.end());
    ASSERT_NOT_EQUAL(tree.find(5), tree.end());
    ASSERT_NOT_EQUAL(tree.find(15), tree.end());
    ASSERT_NOT_EQUAL(tree.find(3), tree.end());
    ASSERT_NOT_EQUAL(tree.find(7), tree.end());
}

TEST(test_find_in_empty_tree) {
    BinarySearchTree<int> tree;
    
    // Search for elements in an empty tree
    ASSERT_EQUAL(tree.find(10), tree.end());
    ASSERT_EQUAL(tree.find(5), tree.end());
    ASSERT_EQUAL(tree.find(15), tree.end());
}

TEST(test_copy_empty_tree) {
    BinarySearchTree<int> tree;
    
    // Test copy constructor with empty tree
    BinarySearchTree<int> copy_tree(tree);
    ASSERT_TRUE(copy_tree.empty());
    
    // Test assignment operator with empty tree
    BinarySearchTree<int> assigned_tree;
    assigned_tree = tree;
    ASSERT_TRUE(assigned_tree.empty());
}

TEST(test_iterator_empty_tree) {
    BinarySearchTree<int> tree;
    
    // Test iteration over empty tree
    std::vector<int> elements;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        elements.push_back(*it);
    }
    
    // Test if no elements are retrieved
    ASSERT_TRUE(elements.empty());
}

TEST(test_non_integer_data_types) {
    BinarySearchTree<std::string> tree;
    
    // Insert elements of string type
    tree.insert("apple");
    tree.insert("banana");
    tree.insert("orange");
    
    // Test size of the tree
    ASSERT_EQUAL(tree.size(), 3);
}

TEST(test_smallest_and_largest_values) {
    BinarySearchTree<int> tree;
    
    // Insert smallest and largest possible values
    tree.insert(std::numeric_limits<int>::min());
    tree.insert(std::numeric_limits<int>::max());
    
    // Test size of the tree
    ASSERT_EQUAL(tree.size(), 2);
}

TEST(test_character_data_type) {
    BinarySearchTree<char> tree;
    
    // Insert character elements
    tree.insert('b');
    tree.insert('a');
    tree.insert('d');
    tree.insert('c');
    
    // Test size of the tree
    ASSERT_EQUAL(tree.size(), 4);
    
    // Test traversal order
    std::stringstream ss;
    tree.traverse_inorder(ss);
    ASSERT_EQUAL(ss.str(), "a b c d ");
}

TEST(test_decimal_data_type) {
    BinarySearchTree<double> tree;
    
    // Insert decimal elements
    tree.insert(3.14);
    tree.insert(1.618);
    tree.insert(2.718);
    
    // Test size of the tree
    ASSERT_EQUAL(tree.size(), 3);
    
    // Test traversal order
    std::stringstream ss;
    tree.traverse_inorder(ss);
    ASSERT_EQUAL(ss.str(), "1.618 2.718 3.14 ");
}

TEST(test_string_data_type) {
    BinarySearchTree<std::string> tree;
    
    // Insert string elements
    tree.insert("banana");
    tree.insert("apple");
    tree.insert("orange");
    tree.insert("grape");
    
    // Test size of the tree
    ASSERT_EQUAL(tree.size(), 4);
    
    // Test traversal order
    std::stringstream ss;
    tree.traverse_inorder(ss);
    ASSERT_EQUAL(ss.str(), "apple banana grape orange ");
}

TEST_MAIN()
