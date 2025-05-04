#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int key) : value(key) {}
};

class BinarySearchTree {
public:
    Node* root = nullptr;

    void insertValue(int key) {
        root = insert(root, key);
    }

    int height(Node* root) {
        return root ? max(height(root->left), height(root->right)) + 1 : 0;
    }

    int findMin(Node* root) {
        while (root && root->left) root = root->left;
        return root ? root->value : -1;
    }

    void swapChildren(Node* root) {
        if (!root) return;
        swap(root->left, root->right);
        swapChildren(root->left);
        swapChildren(root->right);
    }

    Node* searchValue(int key) {
        return search(root, key);
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }

private:
    Node* insert(Node* root, int key) {
        if (!root) return new Node(key);
        if (key < root->value) root->left = insert(root->left, key);
        else root->right = insert(root->right, key);
        return root;
    }

    Node* search(Node* root, int key) {
        if (!root || root->value == key) return root;
        return search(key < root->value ? root->left : root->right, key);
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->value << " ";
            inorder(root->right);
        }
    }
};

int main() {
    BinarySearchTree bst;
    int choice, value;

    do {
        cout << "\n1.Insert\n2.Height\n3.Minimum\n4.Swap Children\n5.Search\n6.Inorder\n7.Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: cout << "Value: "; cin >> value; bst.insertValue(value); break;
            case 2: cout << "Height: " << bst.height(bst.root) << endl; break;
            case 3: cout << "Minimum: " << bst.findMin(bst.root) << endl; break;
            case 4: bst.swapChildren(bst.root); cout << "Children swapped.\n"; break;
            case 5: cout << "Value: "; cin >> value; 
                    cout << (bst.searchValue(value) ? "Found\n" : "Not Found\n"); break;
            case 6: cout << "Inorder: "; bst.inorderTraversal(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
