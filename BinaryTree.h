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

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

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

// Inorder traversal (sorted)
void inorder(Node* root) {
    if (root == NULL) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = NULL;
    int num, n;

    cout << "How many numbers do you want to enter? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter number: ";
        cin >> num;

        if (isPrime(num)) {
            root = insert(root, num);
        } else {
            cout << num << " is NOT prime, skipped.\n";
        }
    }

    cout << "\nPrime numbers in sorted order: ";
    inorder(root);

    return 0;
}