#include<iostream>
#include<cstdio>

using namespace std;

class avl_node
{
    string word, meaning;
    avl_node *left, *right;
    int height;
    public:
    avl_node(string w, string m) {
        word = w;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
    friend class avltree;
};

class avltree
{
    avl_node *root;

    public:
    avltree() { root = nullptr; }
    avl_node* getRoot() { return root; }  
    int height(avl_node*);
    int diff(avl_node*);
    avl_node *ll_rotation(avl_node*);
    avl_node *rr_rotation(avl_node*);
    avl_node *lr_rotation(avl_node*);
    avl_node *rl_rotation(avl_node*);
    avl_node *balance(avl_node*);
    void insert();
    avl_node *insert(avl_node*, string, string);
    void display(avl_node*);
    void inorder(avl_node*);
   
};

int avltree::height(avl_node *node) {
    return (node == nullptr) ? 0 : node->height;
}

int avltree::diff(avl_node *node) {
    return height(node->left) - height(node->right);
}

avl_node* avltree::ll_rotation(avl_node *node) {
    avl_node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    return temp;
}

avl_node* avltree::rr_rotation(avl_node *node) {
    avl_node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    return temp;
}

avl_node* avltree::lr_rotation(avl_node *node) {
    node->left = rr_rotation(node->left);
    return ll_rotation(node);
}

avl_node* avltree::rl_rotation(avl_node *node) {
    node->right = ll_rotation(node->right);
    return rr_rotation(node);
}

avl_node* avltree::balance(avl_node *node) {
    int balanceFactor = diff(node);
    if (balanceFactor > 1) {
        if (diff(node->left) > 0)
            node = ll_rotation(node);
        else
            node = lr_rotation(node);
    }
    else if (balanceFactor < -1) {
        if (diff(node->right) < 0)
            node = rr_rotation(node);
        else
            node = rl_rotation(node);
    }
    return node;
}

void avltree::insert() {
    char ch;
    do {
        string word, meaning;
        cout << "Enter word and its meaning: ";
        cin >> word;
        cin.ignore();
        getline(cin, meaning);
        root = insert(root, word, meaning);
        cout << "Do you want to add more words? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

avl_node* avltree::insert(avl_node *node, string word, string meaning) {
    if (node == nullptr)
        return new avl_node(word, meaning);

    if (word < node->word)
        node->left = insert(node->left, word, meaning);
    else if (word > node->word)
        node->right = insert(node->right, word, meaning);
    else {
        node->meaning = meaning;
        return node;
    }

    return balance(node);
}

void avltree::display(avl_node *node) {
    if (node == nullptr) {
        cout << "Dictionary is empty!" << endl;
    } else {
        cout << "Dictionary (Sorted Order):\n";
        inorder(node);
    }
}

void avltree::inorder(avl_node *node) {
    if (node) {
        inorder(node->left);
        cout << node->word << " : " << node->meaning << endl;
        inorder(node->right);
    }
}

int main() {
    avltree dict;
    int choice;
    do {
        cout << "\n1. Insert Word\n2. Display Dictionary\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            dict.insert();
            break;
        case 2:
             dict.display(dict.getRoot());  
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
