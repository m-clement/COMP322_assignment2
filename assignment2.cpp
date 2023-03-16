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

void remove(Node** head_ref, string version) {
    Node* current = *head_ref;
    Node* prev = NULL;

    // Traverse the list to find the node with the given version
    while (current != NULL && current->version != version) {
        prev = current;
        current = current->next;
    }

    // If the version is not found, print an error message
    if (current == NULL) {
        cout << "Version " << version << " not found in the list." << endl;
        return;
    }

    // Remove the node with the given version
    if (prev == NULL) {
        *head_ref = current->next;
    }
    else {
        prev->next = current->next;
    }
    delete current;
}

// Define the function to load a version
Node* load(Node* head, string version) {
    Node* current = head;
    while (current != NULL) {
        if (current->version == version) {
            return current;
        }
        current = current->next;
    }
    cout << "Version " << version << " not found in the list." << endl;
    return NULL;
}

// Define the function to search versions for a keyword
void search(Node* head, string keyword) {
    Node* current = head;
    bool found = false;

    while (current != NULL) {
        if (current->version.find(keyword) != string::npos) {
            cout << current->version << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "No versions found containing the keyword '" << keyword << "'." << endl;
    }
}

int main() {
    Node* head = NULL;
    string current_version;

    cout << "Welcome to the Comp322 file versioning system!\n" << endl;

    while (true) {
        cout << "To add the content of your file to version control press 'a'" << endl;
        cout << "To remove a version press 'r'" << endl;
        cout << "To load a version press 'l'" << endl;
        cout << "To print to the screen the detailed list of all versions press 'p'" << endl;
        cout << "To compare any 2 versions press 'c'" << endl;
        cout << "To search versions for a keyword press 's'" << endl;
        cout << "To exit press 'e'" << endl;

        char option;
        cin >> option;

        switch(option) {
            case 'a': {
                cout << "Enter the version name to be added: ";
                cin >> current_version;
                insert(&head, current_version);
                cout << "Version " << current_version << " has been added to version control." << endl;
                break;
            }
            case 'r': {
                cout << "Enter the version name to be removed: ";
                cin >> current_version;
                remove(&head, current_version);
                break;
            }
            case 'l': {
                cout << "Enter the version name to be loaded: ";
                cin >> current_version;
                if (load(head, current_version)) {
                    cout << "Version " << current_version << " has been loaded." << endl;
                }
                else {
                    cout << "Version " << current_version << " not found in the list." << endl;
                }
                break;
            }
            case 'p': {
                cout << "List of all versions:" << endl;
                print(head);
                break;
            }
            case 'c': {
                string version1, version2;
                cout << "Enter the name of the first version: ";
                cin >> version1;
                cout << "Enter the name of the second version: ";
                cin >> version2;
                compare(head, version1, version2);
                break;
            }
            case 's': {
                string keyword;
                cout << "Enter the keyword to search for: ";
                cin >> keyword;
                search(head, keyword);
                break;
            }
            case 'e': {
                cout << "Exiting program..." << endl;
                return 0;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }

        cout << endl;
    }
}