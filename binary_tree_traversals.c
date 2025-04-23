#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treenode {
    char data[100];
    struct treenode* left;
    struct treenode* right;
};

struct treenode* stack[100];
int top = -1;

void push(struct treenode* node) {
    if (top == 100 - 1) {
        return;
    }
    stack[++top] = node;
}

struct treenode* pop() {
    if (top == -1) {
        return NULL;
    }
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

struct treenode* peek() {
    return stack[top];
}

struct treenode* create_r(struct treenode* root) {
    char ch;
    struct treenode* curr = NULL;

    printf("Do you want to add a left child of %s? (y/n): ", root->data);
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y') {
        curr = (struct treenode*)malloc(sizeof(struct treenode));
        printf("Enter data for the left child of %s: ", root->data);
        scanf("%s", curr->data);
        curr->left = NULL;
        curr->right = NULL;
        root->left = curr;
        create_r(curr);
    }

    printf("Do you want to add a right child of %s? (y/n): ", root->data);
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y') {
        curr = (struct treenode*)malloc(sizeof(struct treenode));
        printf("Enter data for the right child of %s: ", root->data);
        scanf("%s", curr->data);
        curr->left = NULL;
        curr->right = NULL;
        root->right = curr;
        create_r(curr);
    }

    return root;
}

void inorder_recursive(struct treenode* root) {
    if (root != NULL) {
        inorder_recursive(root->left);
        printf("%s ", root->data);
        inorder_recursive(root->right);
    }
}

void inorder_nonrec(struct treenode* root) {
    struct treenode* temp = root;

    while (1) {
        while (temp != NULL) {
            push(temp);
            temp = temp->left;
        }

        if (isEmpty()) {
            break;
        }

        temp = pop();
        printf("%s ", temp->data);

        temp = temp->right;
    }
}

void preorder_nonrec(struct treenode* root) {
    struct treenode* temp = root;

    while (1) {
        while (temp != NULL) {
            printf("%s ", temp->data);
            push(temp);
            temp = temp->left;
        }

        if (isEmpty()) {
            break;
        }

        temp = pop();
        temp = temp->right;
    }
}

void postorder_nonrec(struct treenode* root) {
    struct treenode* temp = root;
    struct treenode* lastVisited = NULL;

    while (1) {
        while (temp != NULL) {
            push(temp);
            temp = temp->left;
        }

        while (!isEmpty() && (peek()->right == NULL || peek()->right == lastVisited)) {
            temp = pop();
            printf("%s ", temp->data);
            lastVisited = temp;
        }

        if (isEmpty()) {
            break;
        }

        temp = peek()->right;
    }
}

void preorder(struct treenode* root) {
    if (root != NULL) {
        printf("%s ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct treenode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%s ", root->data);
    }
}

int main() {
    struct treenode* root = (struct treenode*)malloc(sizeof(struct treenode));
    int choice;

    printf("Enter data for the root node: ");
    scanf("%s", root->data);

    root->left = NULL;
    root->right = NULL;

    create_r(root);

    do {
        printf("\nChoose a traversal method:\n");
        printf("1. Recursive Inorder Traversal\n");
        printf("2. Non-Recursive Inorder Traversal\n");
        printf("3. Recursive Preorder Traversal\n");
        printf("4. Non-Recursive Preorder Traversal\n");
        printf("5. Recursive Postorder Traversal\n");
        printf("6. Non-Recursive Postorder Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Recursive Inorder Traversal: ");
                inorder_recursive(root);
                printf("\n");
                break;
            case 2:
                printf("Non-Recursive Inorder Traversal: ");
                inorder_nonrec(root);
                printf("\n");
                break;
            case 3:
                printf("Recursive Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Non-Recursive Preorder Traversal: ");
                preorder_nonrec(root);
                printf("\n");
                break;
            case 5:
                printf("Recursive Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 6:
                printf("Non-Recursive Postorder Traversal: ");
                postorder_nonrec(root);
                printf("\n");
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
