#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Function to construct the OBST from the root table
Node* constructOBST(const vector<vector<int>>& root, int i, int j, const vector<int>& keys) {
    if (i > j) return nullptr;
    
    int rootIndex = root[i][j];  // Get root index for current subtree
    Node* node = new Node(keys[rootIndex - 1]);  // Adjusting for 1-based indexing
    
    // Recursively build left and right subtrees
    node->left = constructOBST(root, i, rootIndex - 1, keys);
    node->right = constructOBST(root, rootIndex + 1, j, keys);
    
    return node;
}

// Function to build the Optimal Binary Search Tree (OBST)
Node* buildOBST(const vector<int>& keys, const vector<double>& probs) {
    int n = keys.size();
    
    // DP table for storing costs and sum of probabilities
    vector<vector<double>> cost(n + 1, vector<double>(n + 1, 0)); 
    vector<vector<double>> sum(n + 1, vector<double>(n + 1, 0)); 
    vector<vector<int>> root(n + 1, vector<int>(n + 1, 0));   
    
    // Base case: single key cost is just the probability
    for (int i = 1; i <= n; i++) {
        cost[i][i] = probs[i-1];  // Cost for a single key
        sum[i][i] = probs[i-1];   // Sum of probabilities for a single key
        root[i][i] = i;           // Root for single key
    }
    
    // Fill the cost and root tables for all subtrees of length L
    for (int L = 2; L <= n; L++) { // L is the length of the range
        for (int i = 1; i <= n - L + 1; i++) {  // i is the start of the range
            int j = i + L - 1;  // j is the end of the range
            
            // Calculate sum of probabilities for the range [i, j]
            sum[i][j] = sum[i][j-1] + probs[j-1];
            
            // Initialize cost to a large value to find the minimum
            cost[i][j] = INT_MAX;
            
            // Try each key as root and calculate the cost
            for (int r = i; r <= j; r++) {
                double c = ((r > i) ? cost[i][r-1] : 0) + // Left cost
                           ((r < j) ? cost[r+1][j] : 0) + // Right cost
                           sum[i][j]; // Total sum of probabilities
                
                // Update cost and root if this root gives a better cost
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;  // Store the root index
                }
            }
        }
    }
    
    // Construct the OBST from the root table
    return constructOBST(root, 1, n, keys);
}

// Function to perform an in-order traversal of the OBST
void printInOrder(Node* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    cout << root->key << " ";
    printInOrder(root->right);
}

// Function to print the structure of the BST
void printBST(Node* root, string indent = "", bool last = true) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "└──";
            indent += "   ";
        } else {
            cout << "├──";
            indent += "│  ";
        }
        cout << root->key << endl;
        
        printBST(root->left, indent, false);
        printBST(root->right, indent, true);
    }
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;
    
    vector<int> keys(n);
    vector<double> probs(n);
    
    cout << "Enter the sorted keys: ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }
    
    cout << "Enter the search probabilities for each key: ";
    double total = 0;
    for (int i = 0; i < n; i++) {
        cin >> probs[i];
        total += probs[i];
    }
    
    // Normalize probabilities if they don't sum to 1
    if (total != 1.0) {
        cout << "Probabilities don't sum to 1. Normalizing..." << endl;
        for (int i = 0; i < n; i++) {
            probs[i] /= total;
        }
    }
    
    // Build the OBST
    Node* root = buildOBST(keys, probs);
    
    // Print the in-order traversal of the OBST
    cout << "\nIn-order traversal of the OBST: ";
    printInOrder(root);
    cout << "\n\nBST structure:\n";
    printBST(root);
    
    return 0;
}
