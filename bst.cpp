#include <iostream>
#include <algorithm>  // Include this for std::swap
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // Utility function to insert a new node
    Node* insert(Node* root, int data) {
        if (root == nullptr) {
            return new Node(data);
        }

        if (data < root->data) {
            root->left = insert(root->left, data);
        } else {
            root->right = insert(root->right, data);
        }
        return root;
    }

    // Utility function to find the height (longest path) of the tree
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return max(leftHeight, rightHeight) + 1;
    }

    // Utility function to find the minimum value in the tree
    Node* findMin(Node* root) {
        while (root && root->left) {
            root = root->left;
        }
        return root;
    }

    // Utility function to swap left and right pointers at every node
    void swapChildren(Node* node) {
        if (node == nullptr) return;

        std::swap(node->left, node->right);  // Use std::swap from <algorithm>
        swapChildren(node->left);
        swapChildren(node->right);
    }

    // Utility function to search for a value
    bool search(Node* root, int data) {
        if (root == nullptr) {
            return false;
        }

        if (data == root->data) {
            return true;
        } else if (data < root->data) {
            return search(root->left, data);
        } else {
            return search(root->right, data);
        }
    }

public:
    BST() : root(nullptr) {}

    // Insert a new node
    void insert(int data) {
        root = insert(root, data);
    }

    // Find the number of nodes in the longest path
    int getHeight() {
        return height(root);
    }

    // Find the minimum value in the tree
    int getMin() {
        Node* minNode = findMin(root);
        return minNode ? minNode->data : -1;  // Return -1 if the tree is empty
    }

    // Swap the left and right pointers at every node
    void swap() {
        swapChildren(root);
    }

    // Search for a value
    bool search(int data) {
        return search(root, data);
    }

    // Utility function to print the tree in-order (for visualization)
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void printInOrder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;

    // Constructing the BST by inserting values in the given order
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    // Print in-order traversal of the tree
    cout << "In-order traversal of the tree: ";
    tree.printInOrder();

    // i. Insert new node
    cout << "Inserting node with value 25..." << endl;
    tree.insert(25);
    tree.printInOrder();

    // ii. Find number of nodes in the longest path (height)
    cout << "Height of the tree (longest path): " << tree.getHeight() << endl;

    // iii. Minimum data value found in the tree
    cout << "Minimum value in the tree: " << tree.getMin() << endl;

    // iv. Change the tree so that the roles of the left and right pointers are swapped
    cout << "Swapping left and right children of every node..." << endl;
    tree.swap();
    tree.printInOrder();

    // v. Search a value
    int searchVal = 40;
    cout << "Searching for value " << searchVal << " in the tree: ";
    if (tree.search(searchVal)) {
        cout << "Found!" << endl;
    } else {
        cout << "Not found!" << endl;
    }

    return 0;
}
