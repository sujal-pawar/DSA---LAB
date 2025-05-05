#include <iostream>
#include <cstring>
using namespace std;

int op;

class node {
public:
    node *left, *right;
    char word[50], mean[50];
};

class BT {
public:
    node *root;

    BT() {
        root = NULL;
    }

    void create();
    node* insert(node*, node*);
    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    void search(node*, char[]);
    void modify(node*, char[]);
    node* dlt(node*, char[]);
    node* findMin(node*);
    void findsmallest(node*);
    void findlargest(node*);
};

void BT::create() {
    int op;
    node *temp;
    do {
        temp = new node;
        cout << "Enter a word: ";
        cin >> temp->word;
        cout << "Enter its meaning: ";
        cin >> temp->mean;
        temp->left = temp->right = NULL;
        if (root == NULL) {
            root = temp;
        } else {
            root = insert(root, temp);
        }
        cout << "Want to insert again? (1 = Yes, 0 = No): ";
        cin >> op;
    } while (op == 1);
}

node* BT::insert(node *root, node *temp) {
    if (root == NULL)
        return temp;

    if (strcmp(temp->word, root->word) < 0)
        root->left = insert(root->left, temp);
    else if (strcmp(temp->word, root->word) > 0)
        root->right = insert(root->right, temp);
    else
        cout << "Duplicate word not allowed.\n";

    return root;
}

void BT::inorder(node *temp) {
    if (temp != NULL) {
        inorder(temp->left);
        cout << temp->word << ": " << temp->mean << endl;
        inorder(temp->right);
    }
}

void BT::preorder(node *temp) {
    if (temp != NULL) {
        cout << temp->word << ": " << temp->mean << endl;
        preorder(temp->left);
        preorder(temp->right);
    }
}

void BT::postorder(node *temp) {
    if (temp != NULL) {
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->word << ": " << temp->mean << endl;
    }
}

void BT::search(node *temp, char src[]) {
    if (temp != NULL) {
        int cmp = strcmp(src, temp->word);
        if (cmp == 0) {
            cout << "Word found!\n";
            cout << "Word: " << temp->word << "\nMeaning: " << temp->mean << endl;
        } else if (cmp < 0) {
            search(temp->left, src);
        } else {
            search(temp->right, src);
        }
    } else {
        cout << "Word not found.\n";
    }
}

void BT::modify(node *temp, char src[]) {
    if (temp != NULL) {
        int cmp = strcmp(src, temp->word);
        if (cmp == 0) {
            cout << "Word found. Enter new meaning: ";
            cin >> temp->mean;
            cout << "Meaning updated.\n";
        } else if (cmp < 0) {
            modify(temp->left, src);
        } else {
            modify(temp->right, src);
        }
    } else {
        cout << "Word not found.\n";
    }
}

node* BT::dlt(node *root, char src[]) {
    if (root == NULL)
        return NULL;

    int cmp = strcmp(src, root->word);

    if (cmp < 0)
        root->left = dlt(root->left, src);
    else if (cmp > 0)
        root->right = dlt(root->right, src);
    else {
        // Node to delete found
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        } else if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        } else {
            node* temp = findMin(root->right);
            strcpy(root->word, temp->word);
            strcpy(root->mean, temp->mean);
            root->right = dlt(root->right, temp->word);
        }
    }
    return root;
}

node* BT::findMin(node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

void BT::findsmallest(node *root) {
    if (root == NULL) return;
    while (root->left != NULL)
        root = root->left;
    cout << "Smallest word: " << root->word << "\n";
}

void BT::findlargest(node *root) {
    if (root == NULL) return;
    while (root->right != NULL)
        root = root->right;
    cout << "Largest word: " << root->word << "\n";
}

// -------- Main Function --------
int main() {
    BT b;
    int op;
    char src[100];
    while (1) {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert Word\n";
        cout << "2. Display (Inorder, Preorder, Postorder)\n";
        cout << "3. Search Word\n";
        cout << "4. Modify Meaning\n";
        cout << "5. Delete Word\n";
        cout << "6. Smallest & Largest Word\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> op;
        switch (op) {
            case 1:
                b.create();
                break;
            case 2:
                cout << "\nInorder:\n";
                b.inorder(b.root);
                cout << "\nPreorder:\n";
                b.preorder(b.root);
                cout << "\nPostorder:\n";
                b.postorder(b.root);
                break;
            case 3:
                cout << "Enter word to search: ";
                cin >> src;
                b.search(b.root, src);
                break;
            case 4:
                cout << "Enter word to modify: ";
                cin >> src;
                b.modify(b.root, src);
                break;
            case 5:
                cout << "Enter word to delete: ";
                cin >> src;
                b.root = b.dlt(b.root, src);
                break;
            case 6:
                b.findsmallest(b.root);
                b.findlargest(b.root);
                break;
            case 7:
                cout << "Exiting.\n";
                exit(0);
            default:
                cout << "Invalid option.\n";
        }
    }
    return 0;
}
