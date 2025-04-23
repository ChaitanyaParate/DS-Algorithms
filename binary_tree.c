#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treenode {
    char data[10];
    struct treenode *left;
    struct treenode *right;
};

// Function to create a new tree node
struct treenode* createNode(const char* data) {
    struct treenode *newNode = (struct treenode*)malloc(sizeof(struct treenode));
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create the tree
void create(struct treenode *root) {
    char choice;
    char ch[10];
    struct treenode *curr;
    printf("Do you want to add a child to the tree? (Y/N): ");
    scanf(" %c", &choice); // added space before %c to handle newline
    while(choice == 'y' || choice == 'Y') {
        printf("Enter the data for the new node: ");
        scanf("%s", ch);
        curr = createNode(ch);
        struct treenode *temp = root;
        int flag = 0;
        while(flag == 0) {
            printf("Node to be created (L/R): ");
            scanf(" %c", &ch[0]); // changed to read a single character
            if(ch[0] == 'l' || ch[0] == 'L') {
                if(temp->left == NULL) {
                    temp->left = curr;
                    flag = 1;
                } else {
                    temp = temp->left;
                }
            } else if(ch[0] == 'r' || ch[0] == 'R') {
                if(temp->right == NULL) {
                    temp->right = curr;
                    flag = 1;
                } else {
                    temp = temp->right;
                }
            } else {
                printf("\nPlease enter an appropriate value.\n");
            }
        }
        printf("Do you want to add another child? (Y/N): ");
        scanf(" %c", &choice);
    }
}

// Recursive Preorder Traversal
void preorderRecursive(struct treenode *node) {
    if (node == NULL) return;
    printf("%s ", node->data);
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}

// Non-recursive Preorder Traversal
void preorderNonRecursive(struct treenode *root) {
    if (root == NULL) return;
    struct treenode *stack[100]; // Simple stack implementation
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct treenode *node = stack[top--];
        printf("%s ", node->data);
        if (node->right) stack[++top] = node->right; // Push right first so left is processed first
        if (node->left) stack[++top] = node->left;
    }
}

// Recursive Inorder Traversal
void inorderRecursive(struct treenode *node) {
    if (node == NULL) return;
    inorderRecursive(node->left);
    printf("%s ", node->data);
    inorderRecursive(node->right);
}

// Non-recursive Inorder Traversal
void inorderNonRecursive(struct treenode *root) {
    struct treenode *stack[100];
    int top = -1;
    struct treenode *current = root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%s ", current->data);
        current = current->right;
    }
}

// Recursive Postorder Traversal
void postorderRecursive(struct treenode *node) {
    if (node == NULL) return;
    postorderRecursive(node->left);
    postorderRecursive(node->right);
    printf("%s ", node->data);
}

// Non-recursive Postorder Traversal
void postorderNonRecursive(struct treenode *root) {
    if (root == NULL) return;
    struct treenode *stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;

    while (top1 >= 0) {
        struct treenode *node = stack1[top1--];
        stack2[++top2] = node;
        if (node->left) stack1[++top1] = node->left;
        if (node->right) stack1[++top1] = node->right;
    }

    while (top2 >= 0) {
        printf("%s ", stack2[top2--]->data);
    }
}

int main() {
    struct treenode *root = createNode("Root");
    create(root);

    printf("\nPreorder Traversal (Recursive): ");
    preorderRecursive(root);
    printf("\nPreorder Traversal (Non-Recursive): ");
    preorderNonRecursive(root);

    printf("\nInorder Traversal (Recursive): ");
    inorderRecursive(root);
    printf("\nInorder Traversal (Non-Recursive): ");
    inorderNonRecursive(root);

    printf("\nPostorder Traversal (Recursive): ");
    postorderRecursive(root);
    printf("\nPostorder Traversal (Non-Recursive): ");
    postorderNonRecursive(root);

    return 0;
}

