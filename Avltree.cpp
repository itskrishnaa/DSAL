#include <iostream>
using namespace std;

class node {
public:
    string key, meaning;
    node *left = nullptr, *right = nullptr;
};

struct AVL {
    node *root = nullptr;
};

node* insert(node *cur, node *temp);
node* balance(node *temp);
int height(node *temp);
int dif(node *temp);
node* LL(node *par);
node* RR(node *par);
node* LR(node *par);
node* RL(node *par);
node* delete_n(node *cur, string key1);
node* extractmin(node *t);
bool search(node *cur, string key1);

void create(AVL &a) {
    char answer;
    do {
        node *temp = new node();
        cout << "\nEnter keyword: "; cin >> temp->key;
        cout << "Enter meaning: "; cin >> temp->meaning;
        a.root = insert(a.root, temp);
        cout << "Add another word? (y/n): "; cin >> answer;
    } while (answer == 'y' || answer == 'Y');
}

node* insert(node *cur, node *temp) {
    if (!cur) return temp;
    if (temp->key < cur->key) cur->left = insert(cur->left, temp);
    else if (temp->key > cur->key) cur->right = insert(cur->right, temp);
    return balance(cur);
}

node* balance(node *temp) {
    int bal = dif(temp);
    if (bal >= 2) temp = (dif(temp->left) < 0) ? LR(temp) : LL(temp);
    else if (bal <= -2) temp = (dif(temp->right) < 0) ? RR(temp) : RL(temp);
    return temp;
}

int height(node *temp) {
    return temp ? max(height(temp->left), height(temp->right)) + 1 : -1;
}

int dif(node *temp) {
    return height(temp->left) - height(temp->right);
}

node* LL(node *par) {
    node *temp = par->left;
    par->left = temp->right;
    temp->right = par;
    return temp;
}

node* RR(node *par) {
    node *temp = par->right;
    par->right = temp->left;
    temp->left = par;
    return temp;
}

node* LR(node *par) {
    par->left = RR(par->left);
    return LL(par);
}

node* RL(node *par) {
    par->right = LL(par->right);
    return RR(par);
}

void display(node *temp, bool ascending = true) {
    if (!temp) return;
    if (ascending) {
        display(temp->left);
        cout << temp->key << " : " << temp->meaning << endl;
        display(temp->right);
    } else {
        display(temp->right);
        cout << temp->key << " : " << temp->meaning << endl;
        display(temp->left);
    }
}

bool search(node *cur, string key1) {
    if (!cur) return false;
    if (cur->key == key1) return true;
    return search(key1 < cur->key ? cur->left : cur->right, key1);
}

node* delete_n(node *cur, string key1) {
    if (!cur) return cur;
    if (key1 < cur->key) cur->left = delete_n(cur->left, key1);
    else if (key1 > cur->key) cur->right = delete_n(cur->right, key1);
    else {
        node *l = cur->left, *r = cur->right;
        delete cur;
        if (!r) return l;
        node *m = r;
        while (m->left) m = m->left;
        m->right = extractmin(r);
        m->left = l;
        return balance(m);
    }
    return balance(cur);
}

node* extractmin(node *t) {
    if (!t->left) return t->right;
    t->left = extractmin(t->left);
    return balance(t);
}

int main() {
    AVL a;
    char c;
    int ch;
    do {
        cout << "\n1.Insert\n2.Display\n3.Search\n4.Delete\nEnter choice: ";
        cin >> ch;
        switch (ch) {
            case 1: create(a); break;
            case 2: display(a.root); break;
            case 3: {
                string key;
                cout << "Enter keyword to search: "; cin >> key;
                cout << (search(a.root, key) ? "Found" : "Not Found") << endl;
                break;
            }
            case 4: {
                string key;
                cout << "Enter keyword to delete: "; cin >> key;
                a.root = delete_n(a.root, key);
                break;
            }
            default: cout << "Wrong choice!" << endl;
        }
        cout << "Continue? (y/n): "; cin >> c;
    } while (c == 'y' || c == 'Y');
    return 0;
}

