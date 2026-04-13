#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <vector>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = NULL;
    }
};

// Insert into BST
Node* insertNode(Node* root, int value, bool& inserted) {
    if (root == NULL) {
        inserted = true;
        return new Node(value);
    }

    if (value < root->data)
        root->left = insertNode(root->left, value, inserted);
    else if (value > root->data)
        root->right = insertNode(root->right, value, inserted);

    return root;
}

// Search function logic
bool searchNode(Node* root, int value) {
    if (root == NULL) return false;
    if (root->data == value) return true;
    
    if (value < root->data)
        return searchNode(root->left, value);
    else
        return searchNode(root->right, value);
}

// Inorder traversal helper
void inorder(Node* root, std::vector<int>& out) {
    if (root == NULL) return;

    inorder(root->left, out);
    out.push_back(root->data);
    inorder(root->right, out);
}

// Print inorder traversal
void inorderPrint(Node* root) {
    if (root == NULL) return;

    inorderPrint(root->left);
    cout << root->data << " ";
    inorderPrint(root->right);
}

class BinaryTree {
private:
    Node* root;
    int nodeCount;

    void destroy(Node* node) {
        if (node == NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinaryTree() : root(NULL), nodeCount(0) {}
    ~BinaryTree() { destroy(root); }

    void insert(int value) {
        bool inserted = false;
        root = insertNode(root, value, inserted);
        if (inserted) nodeCount++;
    }
    
    bool find(int value) const { return searchNode(root, value); }

    std::vector<int> sort() const {
        std::vector<int> res;
        inorder(root, res);
        return res;
    }
    
    void printInorder() const { inorderPrint(root); }
    long long getMemoryUsage() const { return static_cast<long long>(nodeCount) * sizeof(Node); }
    Node* getRoot() const { return root; }
};

#endif // BINARYTREE_H