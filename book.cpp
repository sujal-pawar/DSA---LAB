#include <iostream>
#include <string>
using namespace std;

struct node {
    string label;
    int ch_count;
    node* child[10];
};

class GT {
    node* root;

public:
    GT() {
        root = nullptr;
    }

    void create_tree() {
        int tchapters, i, j;
        root = new node;
        cout << "Enter name of book: ";
        cin.ignore(); // Clear newline from previous input
        getline(cin, root->label);
        cout << "Enter number of chapters in book: ";
        cin >> tchapters;
        root->ch_count = tchapters;

        for (i = 0; i < tchapters; i++) {
            root->child[i] = new node;
            cout << "Enter name of Chapter " << i + 1 << ": ";
            cin.ignore();
            getline(cin, root->child[i]->label);

            cout << "Enter number of sections in Chapter '" << root->child[i]->label << "': ";
            cin >> root->child[i]->ch_count;

            for (j = 0; j < root->child[i]->ch_count; j++) {
                root->child[i]->child[j] = new node;
                cout << "Enter name of Section " << j + 1 << ": ";
                cin.ignore();
                getline(cin, root->child[i]->child[j]->label);
                root->child[i]->child[j]->ch_count = 0; // No further children
            }
        }
    }

    void display() {
        int i, j;
        if (root != nullptr) {
            cout << "\n----- Book Hierarchy -----\n";
            cout << "Book Title: " << root->label << endl;

            for (i = 0; i < root->ch_count; i++) {
                cout << "  Chapter " << i + 1 << ": " << root->child[i]->label << endl;
                cout << "    Sections:" << endl;
                for (j = 0; j < root->child[i]->ch_count; j++) {
                    cout << "      - " << root->child[i]->child[j]->label << endl;
                }
            }
        } else {
            cout << "No book tree created yet.\n";
        }
    }
};

int main() {
    int choice;
    GT gt;

    while (true) {
        cout << "\n-----------------\n";
        cout << "Book Tree Menu\n";
        cout << "-----------------\n";
        cout << "1. Create Book Tree\n";
        cout << "2. Display Book Tree\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            gt.create_tree();
            break;
        case 2:
            gt.display();
            break;
        case 3:
            cout << "Thanks for using this program!\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
