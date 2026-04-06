#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <vector>
#include <algorithm>

//Each node stores its height so we don't have to recalculate it recursively every time we check balance.
struct AVLNode {
    int data;
    AVLNode *left, *right;
    int height; 
    AVLNode(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    int nodeCount;

    //Helper to safely get height of a null node (which is 0)
    int getHeight(AVLNode* n) { return n ? n->height : 0; }

    //Balance Factor = height(left) - height(right)
    //Positive means left-heavy, negative means right-heavy
    int getBalance(AVLNode* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

    //Right Rotation: Used when the left subtree is too tall.
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        //Perform rotation
        x->right = y;
        y->left = T2;

        //Update heights (order matters: child first, then parent)
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x; // New root of this subtree
    }

    //Left Rotation: Used when the right subtree is too tall.
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode* insert(AVLNode* node, int val) {
        //Standard BST insertion
        if (!node) {
            nodeCount++;
            return new AVLNode(val);
        }
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        else return node; // No duplicate primes allowed

        //Update height of this ancestor node
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        //Get the balance factor to check if it became unbalanced
        int balance = getBalance(node);

        //Case 1: Left Left (Single Right Rotation)
        if (balance > 1 && val < node->left->data) 
            return rightRotate(node);

        //Case 2: Right Right (Single Left Rotation)
        if (balance < -1 && val > node->right->data) 
            return leftRotate(node);

        //Case 3: Left Right (Double Rotation: Left then Right)
        if (balance > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //Case 4: Right Left (Double Rotation: Right then Left) ---
        if (balance < -1 && val < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; //Return the (potentially new) root of the subtree
    }

    bool search(AVLNode* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;
        return (val < node->data) ? search(node->left, val) : search(node->right, val);
    }

    void inorder(AVLNode* node, std::vector<int>& res) {
        if (!node) return;
        inorder(node->left, res);
        res.push_back(node->data);
        inorder(node->right, res);
    }

public:
    AVLTree() : root(nullptr), nodeCount(0) {}
    
    void insert(int val) { root = insert(root, val); }
    
    bool search(int val) { return search(root, val); }
    
    //In-order traversal always yields a sorted list
    std::vector<int> sort() {
        std::vector<int> res;
        inorder(root, res);
        return res;
    }

    long long getMemoryUsage() { 
        return (long long)nodeCount * sizeof(AVLNode); 
    }
};

#endif