#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <functional>
#include <algorithm>
#include <sstream>

using namespace std;

// Struct representing a version of the file, containing the version number, content, and hash value.
struct Version {
    int version_number;
    string content;
    size_t hash_value;
};

// Struct representing a callable object (functor) used to find a version with a specific version number.
// Used in conjunction with the find_if function from the C++ Standard Library.
struct VersionFinder {
    int target_version;

    VersionFinder(int version) : target_version(version) {}

    bool operator()(const Version& v) {
        return v.version_number == target_version;
    }
};


list<Version> versions;
int version_counter = 0;

void add(string content);
void print();
void load(int version);
void remove(int version);
void compare(int version1, int version2);
void search(const string& keyword);
size_t hash_string(const string& content);

int main() {
    char option;
    int version1, version2;
    string keyword, content, filename;
    ifstream file;
    
    cout << "Welcome to the Comp322 file versioning system!\n" << endl;
    cout << "To add the content of your file to version control press 'a'" << endl;
    cout << "To remove a version press 'r'" << endl;
    cout << "To load a version press 'l'" << endl;
    cout << "To print to the screen the detailed list of all versions press 'p'" << endl;
    cout << "To compare any 2 versions press 'c'" << endl;
    cout << "To search versions for a keyword press 's'" << endl;
    cout << "To exit press 'e'" << endl;

    while (true) {
        cout << "Please enter your choice: ";
        cin >> option;

        if (option == 'e') {
            break;
        }

        switch (option) {
            case 'a':
                cout << "Enter the filename: ";
                cin >> filename;
                file.open(filename);
                if (file.is_open()) {
                    content.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
                    add(content);
                    file.close();
                } else {
                    cout << "Error: Unable to open file." << endl;
                }
                break;
            case 'r':
                cout << "Enter the number of the version that you want to delete: ";
                cin >> version1;
                remove(version1);
                break;
            case 'l':
                cout << "Which version would you like to load? ";
                cin >> version1;
                load(version1);
                break;
            case 'p':
                print();
                break;
            case 'c':
                cout << "Please enter the number of the first version to compare: ";
                cin >> version1;
                cout << "Please enter the number of the second version to compare: ";
                cin >> version2;
                compare(version1, version2);
                break;
            case 's':
                cout << "Please enter the keyword that you are looking for: ";
                cin >> keyword;
                search(keyword);
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

// Adds a new version with the provided content to the version list.
void add(string content) {
    size_t new_hash = hash_string(content);

    for (const auto& version : versions) {
        if (version.hash_value == new_hash) {
            cout << "git322 did not detect any change to your file and will not create a new version." << endl;
            return;
        }
    }

    Version new_version;
    new_version.version_number = ++version_counter;
    new_version.content = content;
    new_version.hash_value = new_hash;
    versions.push_back(new_version);

    cout << "Your content has been added successfully." << endl;
}

// Prints the detailed list of all versions, including version number, hash value, and content.
void print() {
    cout << "Number of versions: " << versions.size() << endl;

    for (const auto& version : versions) {
        cout << "Version number: " << version.version_number << endl;
        cout << "Hash value: " << version.hash_value << endl;
        cout << "Content: " << version.content << endl << endl;
    }
}

// Loads the content of the specified version into the file "file.txt".
void load(int version) {
    auto it = find_if(versions.begin(), versions.end(), [&](const Version& v) {
        return v.version_number == version;
    });

    if (it != versions.end()) {
        string filename = "file.txt";
        ofstream file(filename);

        if (file.is_open()) {
            file << it->content;
            file.close();
            cout << "Version " << version << " loaded successfully. Please refresh your text editor to see the changes." << endl;
        } else {
            cout << "Error: Unable to open file." << endl;
        }
    } else {
        cout << "Please enter a valid version number. If you are not sure please press 'p' to list all valid version numbers." << endl;
    }
}

// Removes the specified version from the version list and updates the version numbers of the remaining versions.
void remove(int version) {
    auto it = find_if(versions.begin(), versions.end(), [&](const Version& v) {
        return v.version_number == version;
    });

    if (it != versions.end()) {
        versions.erase(it);
        cout << "Version " << version << " deleted successfully." << endl;

        // Update the version numbers
        for (auto& v : versions) {
            if (v.version_number > version) {
                v.version_number--;
            }
        }
    } else {
        cout << "Please enter a valid version number." << endl;
    }
}

// Compares the content of two specified versions line by line, showing the differences or indicating identical lines.
void compare(int version1, int version2) {
    auto it1 = find_if(versions.begin(), versions.end(), [version1](const Version& v) {
        return v.version_number == version1;
    });

    auto it2 = find_if(versions.begin(), versions.end(), [version2](const Version& v) {
        return v.version_number == version2;
    });

    if (it1 != versions.end() && it2 != versions.end()) {
        istringstream content1(it1->content);
        istringstream content2(it2->content);

        string line1, line2;
        int line_number = 0;

        while (getline(content1, line1) || getline(content2, line2)) {
            line_number++;

            if (line1 == line2) {
                cout << "Line " << line_number << ": <Identical>" << endl;
            } else {
                cout << "Line " << line_number << ": " << line1 << " <<>> " << line2 << endl;
            }

            line1.clear();
            line2.clear();
        }
    } else {
        cout << "Please enter valid version numbers for comparison." << endl;
    }
}

// Searches all versions for the specified keyword and prints the detailed information of the versions where the keyword is found.
void search(const string& keyword);
void search(const string& keyword) {
    bool found = false;

    for (const auto& version : versions) {
        if (version.content.find(keyword) != string::npos) {
            found = true;

            cout << "Version number: " << version.version_number << endl;
            cout << "Hash value: " << version.hash_value << endl;
            cout << "Content: " << version.content << endl;
            cout << endl;
        }
    }

    if (!found) {
        cout << "Your keyword '" << keyword << "' was not found in any version." << endl;
    }
}

// Computes and returns the hash value of the given content using std::hash.
size_t hash_string(const string& content) {
    hash<string> hasher;
    return hasher(content);
}