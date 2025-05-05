#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Node {
    string keyword;
    string meaning;
    int height;
    Node* left;
    Node* right;

    Node(string k, string m) : keyword(k), meaning(m), height(1), left(nullptr), right(nullptr) {}
};

class Dictionary {
private:
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, string keyword, string meaning) {
        if (!node) return new Node(keyword, meaning);

        if (keyword < node->keyword)
            node->left = insert(node->left, keyword, meaning);
        else if (keyword > node->keyword)
            node->right = insert(node->right, keyword, meaning);
        else {
            // If keyword exists, update meaning
            node->meaning = meaning;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        // Perform rotations to balance
        if (balance > 1 && keyword < node->left->keyword)
            return rightRotate(node);
        if (balance < -1 && keyword > node->right->keyword)
            return leftRotate(node);
        if (balance > 1 && keyword > node->left->keyword) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && keyword < node->right->keyword) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, string keyword) {
        if (!root) return root;

        if (keyword < root->keyword)
            root->left = deleteNode(root->left, keyword);
        else if (keyword > root->keyword)
            root->right = deleteNode(root->right, keyword);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        if (!root) return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        // Balance the tree
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void displayAscending(Node* node) {
        if (node) {
            displayAscending(node->left);
            cout << node->keyword << ": " << node->meaning << endl;
            displayAscending(node->right);
        }
    }

    void displayDescending(Node* node) {
        if (node) {
            displayDescending(node->right);
            cout << node->keyword << ": " << node->meaning << endl;
            displayDescending(node->left);
        }
    }

    int findMaxComparisons(Node* node) {
        return getHeight(node);
    }

    Node* search(Node* node, string keyword, int& comparisons) {
        comparisons++;
        if (!node || node->keyword == keyword)
            return node;

        if (keyword < node->keyword)
            return search(node->left, keyword, comparisons);
        else
            return search(node->right, keyword, comparisons);
    }

public:
    Dictionary() : root(nullptr) {}

    void addKeyword() {
        string keyword, meaning;
        cout << "Enter keyword: ";
        cin >> keyword;
        cout << "Enter meaning: ";
        cin.ignore();
        getline(cin, meaning);
        root = insert(root, keyword, meaning);
        cout << "Keyword added successfully!\n";
    }

    void deleteKeyword() {
        string keyword;
        cout << "Enter keyword to delete: ";
        cin >> keyword;
        root = deleteNode(root, keyword);
        cout << "Keyword deleted successfully!\n";
    }

    void updateKeyword() {
        string keyword, newMeaning;
        cout << "Enter keyword to update: ";
        cin >> keyword;
        cout << "Enter new meaning: ";
        cin.ignore();
        getline(cin, newMeaning);
        root = insert(root, keyword, newMeaning);
        cout << "Keyword updated successfully!\n";
    }

    void displaySorted(bool ascending = true) {
        if (ascending) {
            cout << "\nDictionary (Ascending order):\n";
            displayAscending(root);
        } else {
            cout << "\nDictionary (Descending order):\n";
            displayDescending(root);
        }
    }

    void searchKeyword() {
        string keyword;
        cout << "Enter keyword to search: ";
        cin >> keyword;
        int comparisons = 0;
        Node* result = search(root, keyword, comparisons);
        if (result) {
            cout << "Meaning: " << result->meaning << endl;
            cout << "Comparisons made: " << comparisons << endl;
        } else {
            cout << "Keyword not found!\n";
        }
    }

    void showMaxComparisons() {
        cout << "Maximum comparisons required (height): " << findMaxComparisons(root) << endl;
        cout << "Search complexity: O(log n)\n";
    }
};

// Main function
int main() {
    Dictionary dict;
    int choice;

    do {
        cout << "\nDictionary Operations:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Keyword\n";
        cout << "4. Display Ascending\n";
        cout << "5. Display Descending\n";
        cout << "6. Search Keyword\n";
        cout << "7. Show Maximum Comparisons\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: dict.addKeyword(); break;
            case 2: dict.deleteKeyword(); break;
            case 3: dict.updateKeyword(); break;
            case 4: dict.displaySorted(); break;
            case 5: dict.displaySorted(false); break;
            case 6: dict.searchKeyword(); break;
            case 7: dict.showMaxComparisons(); break;
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}
