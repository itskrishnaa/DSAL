#include <iostream>
#include <stack>
#include <string>
using namespace std;
class Node {
public:
    char value;
    Node* left;
    Node* right;
    Node(char val) {
        value = val;
        left = right = nullptr;
    }
};
Node* construct_expression_tree(const string& prefix) {
    stack<Node*> s;
    for (int i = prefix.size() - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isalnum(c)) {
            s.push(new Node(c));
        }
        else {
            Node* node = new Node(c);
            node->left = s.top(); s.pop();
            node->right = s.top(); s.pop();
            s.push(node); }
    }    return s.top();
}
void post_order_traversal(Node* root) {
    if (!root) return;
    stack<Node*> stack1, stack2;
    stack1.push(root);
    while (!stack1.empty()) {
        Node* node = stack1.top();
        stack1.pop();
        stack2.push(node);
        if (node->left) stack1.push(node->left);
        if (node->right) stack1.push(node->right);  }
    while (!stack2.empty()) {
        cout << stack2.top()->value << " ";
        stack2.pop();    }
    cout << endl;
}
void delete_tree(Node* root) {
    if (root == nullptr) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;}
int main() {
    string prefix_expression;
    Node* root = nullptr;
    int choice;
    do {
        cout << "Menu:\n";
        cout << "1. Construct Expression Tree\n";
        cout << "2. Post-order Traversal\n";
        cout << "3. Delete Tree\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter the prefix expression: ";
                cin >> prefix_expression;
                root = construct_expression_tree(prefix_expression);
                cout << "Expression tree constructed successfully!\n";
                break;
            case 2:
                if (root == nullptr) {
                    cout << "Tree is not constructed yet!\n";
                } else {
                    cout << "Post-order traversal: ";
                    post_order_traversal(root);}
                break;
            case 3:
                if (root == nullptr) {
                    cout << "Tree is not constructed yet!\n";
                } else {
                    delete_tree(root);
                    root = nullptr;
                    cout << "Tree deleted successfully!\n";        }
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";}
    } while (choice != 4);
    return 0;       }
