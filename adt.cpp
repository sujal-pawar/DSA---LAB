#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

template <typename K, typename V>
class Dictionary {
private:
    struct HashEntry {
        K key;
        V value;
        bool isOccupied; // To track whether the slot is occupied or not

        HashEntry(K k, V v) : key(k), value(v), isOccupied(true) {}
        HashEntry() : isOccupied(false) {}
    };

    vector<HashEntry> table;
    int capacity;
    int size;

    // Hash function to map keys to indices
    int hash(K key) const {
        return std::hash<K>()(key) % capacity;
    }

public:
    Dictionary(int capacity = 10) : capacity(capacity), size(0) {
        table.resize(capacity);
    }

    // Insert a key-value pair into the dictionary
    void insert(K key, V value) {
        if (size == capacity) {
            throw overflow_error("Dictionary is full, can't insert more items.");
        }

        int index = hash(key);

        // Linear probing to find the appropriate index
        while (table[index].isOccupied && table[index].key != key) {
            index = (index + 1) % capacity;
        }

        if (!table[index].isOccupied) {
            table[index] = HashEntry(key, value);
            size++;
        } else {
            // Key already exists, so update the value
            table[index].value = value;
        }
    }

    // Find a value by key
    V find(K key) {
        int index = hash(key);

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % capacity;
        }

        throw runtime_error("Key not found.");
    }

    // Delete a key-value pair by key
    void remove(K key) {
        int index = hash(key);

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                table[index] = HashEntry();
                size--;
                return;
            }
            index = (index + 1) % capacity;
        }

        throw runtime_error("Key not found.");
    }

    // Display all key-value pairs in the dictionary
    void display() {
        for (int i = 0; i < capacity; i++) {
            if (table[i].isOccupied) {
                cout << "Key: " << table[i].key << ", Value: " << table[i].value << endl;
            }
        }
    }

    // Check if the dictionary is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Get the number of elements in the dictionary
    int getSize() const {
        return size;
    }
};

int main() {
    Dictionary<string, string> dict;

    // Insert key-value pairs
    dict.insert("apple", "fruit");
    dict.insert("carrot", "vegetable");
    dict.insert("banana", "fruit");

    // Display dictionary contents
    cout << "Dictionary contents after insertions:" << endl;
    dict.display();

    // Find a key
    try {
        cout << "\nFinding 'apple': " << dict.find("apple") << endl;
        cout << "Finding 'carrot': " << dict.find("carrot") << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    // Remove a key
    try {
        dict.remove("banana");
        cout << "\nAfter deleting 'banana':" << endl;
        dict.display();
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    // Attempt to find a deleted key
    try {
        cout << "\nFinding 'banana': " << dict.find("banana") << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
