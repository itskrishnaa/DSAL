#include <iostream>
#include <vector>
using namespace std;

struct Node {
    string name;
    Node* child[10];
    int childCount;
};

class GT {
public:
    GT() : root(nullptr) {}
    void createTree();
    void display(Node* node);
    int calculateHeight(Node* node);
    void menu();

private:
    Node* root;
};

void GT::createTree() {
    root = new Node;
    cout << "Enter book name: ";
    getline(cin, root->name);
    cout << "Enter number of chapters: ";
    cin >> root->childCount;
    cin.ignore();

    for (int i = 0; i < root->childCount; i++) {
        root->child[i] = new Node;
        cout << "Enter chapter " << i + 1 << " name: ";
        getline(cin, root->child[i]->name);
        cout << "Enter number of sections in " << root->child[i]->name << ": ";
        cin >> root->child[i]->childCount;
        cin.ignore();

        for (int j = 0; j < root->child[i]->childCount; j++) {
            root->child[i]->child[j] = new Node;
            cout << "Enter section " << j + 1 << " name: ";
            getline(cin, root->child[i]->child[j]->name);
        }
    }
}

void GT::display(Node* node) {
    if (!node) return;
    cout << "\nBook: " << node->name;
    for (int i = 0; i < node->childCount; i++) {
        cout << "\n Chapter " << i + 1 << ": " << node->child[i]->name << "\n Sections:";
        for (int j = 0; j < node->child[i]->childCount; j++) {
            cout << "\n  - " << node->child[i]->child[j]->name;
        }
    }
}

int GT::calculateHeight(Node* node) {
    if (!node) return 0;
    int maxHeight = 0;
    for (int i = 0; i < node->childCount; i++) {
        maxHeight = max(maxHeight, calculateHeight(node->child[i]));
    }
    return maxHeight + 1;
}

void GT::menu() {
    int choice;
    do {
        cout << "\n1. Create Tree\n2. Display Tree\n3. Tree Height\n4. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: createTree(); break;
            case 2: display(root); break;
            case 3: cout << "\nTree Height: " << calculateHeight(root) << endl; break;
            case 4: cout << "\nExiting...\n"; break;
            default: cout << "\nInvalid choice!\n";
        }
    } while (choice != 4);
}

int main() {
    GT tree;
    tree.menu();
    return 0;
}
