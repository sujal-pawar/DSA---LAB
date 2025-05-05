#include <iostream>
using namespace std;

// Node to store name, telephone, and key
class node {
    string name;
    string telephone;
    int key;

public:
    node() {
        key = 0;
        name == "";
        telephone == "";
    }

    friend class hashing;
};

// Hash function using ASCII value sum
int ascii_generator(string s) {
    int sum = 0;
    for (char c : s)
        sum += c;
    return sum % 100;
}

// Hashing class
class hashing {
private:
    node data[100];
    int size = 100;

public:
    // Function to create record
    void create_record(string n, string tele) {
        int k = ascii_generator(n);
        int index = k % size;

        for (int j = 0; j < size; j++) {
            if (data[index].key == 0) {
                data[index].key = k;
                data[index].name = n;
                data[index].telephone = tele;
                cout << "Record added successfully.\n";
                return;
            } else {
                index = (index + 1) % size;
            }
        }

        cout << "Hash table is full!\n";
    }

    // Function to search for a record
    void search_record(string name) {
        int k = ascii_generator(name);
        int index = k % size;

        for (int i = 0; i < size; i++) {
            if (data[index].key == k && data[index].name == name) {
                cout << "\nRecord Found:\n";
                cout << "Name      : " << data[index].name << endl;
                cout << "Telephone : " << data[index].telephone << endl;
                return;
            } else {
                index = (index + 1) % size;
            }
        }

        cout << "Record not found!\n";
    }

    // Function to delete a record
    void delete_record(string name) {
        int k = ascii_generator(name);
        int index = k % size;

        for (int i = 0; i < size; i++) {
            if (data[index].key == k && data[index].name == name) {
                data[index].key == 0;
                data[index].name == "";
                data[index].telephone == "";
                cout << "Record deleted successfully.\n";
                return;
            } else {
                index = (index + 1) % size;
            }
        }

        cout << "Record not found!\n";
    }

    // Function to update a record
    void update_record(string name) {
        int k = ascii_generator(name);
        int index = k % size;

        for (int i = 0; i < size; i++) {
            if (data[index].key == k && data[index].name == name) {
                string new_tele;
                cout << "Enter new telephone number: ";
                cin >> new_tele;
                data[index].telephone = new_tele;
                cout << "Record updated successfully.\n";
                return;
            } else {
                index = (index + 1) % size;
            }
        }

        cout << "Record not found!\n";
    }

    // Function to display all records
    void display_record() {
        cout << "\n\tName\t\tTelephone\n";
        cout << "-----------------------------------\n";
        for (int i = 0; i < size; i++) {
            if (data[i].key != 0) {
                cout << "\t" << data[i].name << "\t\t" << data[i].telephone << endl;
            }
        }
    }
};

// Main function
int main() {
    hashing s;
    string name, telephone;
    int choice;
    bool loop = true;

    while (loop) {
        cout << "\n-------------------------\n"
             << " Telephone Book Database \n"
             << "-------------------------\n"
             << "1. Create Record\n"
             << "2. Display Records\n"
             << "3. Search Record\n"
             << "4. Update Record\n"
             << "5. Delete Record\n"
             << "6. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nEnter name: ";
            cin >> name;
            cout << "Enter Telephone number: ";
            cin >> telephone;
            s.create_record(name, telephone);
            break;

        case 2:
            s.display_record();
            break;

        case 3:
            cout << "\nEnter the name: ";
            cin >> name;
            s.search_record(name);
            break;

        case 4:
            cout << "\nEnter the name: ";
            cin >> name;
            s.update_record(name);
            break;

        case 5:
            cout << "\nEnter name to delete: ";
            cin >> name;
            s.delete_record(name);
            break;

        case 6:
            loop = false;
            cout << "Exiting the program.\n";
            break;

        default:
            cout << "\nInvalid choice! Try again.\n";
        }
    }

    return 0;
}
