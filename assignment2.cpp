#include <iostream>
#include <string>
using namespace std;

struct Node {
    string version;
    Node* next;
};

// Define the function to insert a new version
void insert(Node** head_ref, string new_version) {
    Node* new_node = new Node;
    new_node->version = new_version;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
    }
    else {
        Node* current = *head_ref;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Define the function to print the list of all versions
void print(Node* head) {
    Node* current = head;
    while (current != NULL) {
        cout << current->version << endl;
        current = current->next;
    }
}

// Define the function to compare 2 versions
void compare(Node* head, string version1, string version2) {
    Node* current = head;
    bool found1 = false;
    bool found2 = false;

    while (current != NULL) {
        if (current->version == version1) {
            found1 = true;
        }
        if (current->version == version2) {
            found2 = true;
        }
        current = current->next;
    }

    if (!found1) {
        cout << "Version " << version1 << " not found in the list." << endl;
    }
    if (!found2) {
        cout << "Version " << version2 << " not found in the list." << endl;
    }
    if (found1 && found2) {
        int comparison = version1.compare(version2);
        if (comparison == 0) {
            cout << "Version " << version1 << " and " << version2 << " are the same." << endl;
        }
        else if (comparison < 0) {
            cout << "Version " << version1 << " is older than " << version2 << "." << endl;
        }
        else {
            cout << "Version " << version1 << " is newer than " << version2 << "." << endl;
        }
    }
}

int main() {
    Node* head = NULL;

    while (true) {
        cout << "Welcome to the version control system." << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Add a new version" << endl;
        cout << "2. Print the list of all versions" << endl;
        cout << "3. Compare 2 versions" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            string new_version;
            cout << "Enter the version number: ";
            cin >> new_version;
            insert(&head, new_version);
            cout << "Version " << new_version << " added." << endl;
        }
        else if (choice == 2) {
            cout << "List of all versions:" << endl;
            print(head);
        }
        else if (choice == 3) {
            string version1, version2;
            cout << "Enter the first version number: ";
            cin >> version1;
            cout << "Enter the second version number: ";
            cin >> version2;
            compare(head, version1, version2);
        }
        else if (choice == 4) {
            cout << "Exiting version control system." << endl;
            break;
        }

    }
}