#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
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
Node* insert(Node* root, int value) {
    if (root == NULL)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

//Search BST
bool searchNode(Node* root, int value) {
    if (root == NULL) return false;
    if (root->data == value) return true;
    if (value < root->data) return searchNode(root->left, value);
    return searchNode(root->right, value);
}

// Inorder traversal (sorted)
void inorder(Node* root) {
    if (root == NULL) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

class BinaryTree {
private:
    Node* root;

    void destroy(Node* node) {
        if (node == NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinaryTree() : root(NULL) {}
    ~BinaryTree() { destroy(root); }

    void insert(int value) { root = ::insert(root, value); }
    void printInorder() const { ::inorder(root); }
    Node* getRoot() const { return root; }
};

#endif // BINARYTREE_H