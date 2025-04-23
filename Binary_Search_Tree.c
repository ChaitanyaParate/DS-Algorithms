#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct BST {
    char word[10];
    char meaning[20];
    struct BST* left;
    struct BST* right;
} BST;


BST* createNode(const char* word, const char* meaning) {
    BST* newNode = (BST*)malloc(sizeof(BST));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = newNode->right = NULL;
    return newNode;
}

BST* insert(BST* root, const char* word, const char* meaning) {
    if (root == NULL) {
        return createNode(word, meaning);
    }

    if (strcmp(word, root->word) < 0) {
        root->left = insert(root->left, word, meaning);
    } else if (strcmp(word, root->word) > 0) {
        root->right = insert(root->right, word, meaning);
    }
    return root;
}


BST* minValueNode(BST* node) {
    BST* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


BST* deleteNode(BST* root, const char* word) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(word, root->word) < 0) {
        root->left = deleteNode(root->left, word);
    } else if (strcmp(word, root->word) > 0) {
        root->right = deleteNode(root->right, word);
    } else {
        
        if (root->left == NULL) {
            BST* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BST* temp = root->left;
            free(root);
            return temp;
        }

        BST* temp = minValueNode(root->right);
        strcpy(root->word, temp->word);
        strcpy(root->meaning, temp->meaning);
        root->right = deleteNode(root->right, temp->word);
    }
    return root;
}


void inOrderTraversal(BST* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Word: %s, Meaning: %s\n", root->word, root->meaning);
        inOrderTraversal(root->right);
    }
}


int treeHeight(BST* root) {
    if (root == NULL) return 0;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


void printLevel(BST* root, int level) {
    if (root == NULL) return;
    if (level == 1) {
        printf("%s ", root->word);
    } else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}


void levelOrderTraversal(BST* root) {
    int h = treeHeight(root);
    for (int i = 1; i <= h; i++) {
        printf("Level %d: ", i);
        printLevel(root, i);
        printf("\n");
    }
}


BST* mirrorTree(BST* root) {
    if (root == NULL) return NULL;
    
    BST* temp = root->left;
    root->left = mirrorTree(root->right);
    root->right = mirrorTree(temp);

    return root;
}


BST* copyTree(BST* root) {
    if (root == NULL) return NULL;
    
    BST* newNode = createNode(root->word, root->meaning);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    return newNode;
}


int main() {
    BST* root = NULL;
    int choice;
    char word[10], meaning[20];

    while (1) {
        printf("\nDictionary Operations:\n");
        printf("1. Insert a keyword\n");
        printf("2. Delete a keyword\n");
        printf("3. Display In-order Traversal\n");
        printf("4. Display Level-order Traversal\n");
        printf("5. Create Mirror Image and Display Level-order\n");
        printf("6. Copy Tree and Display In-order Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter word to insert: ");
                scanf("%s", word);
                printf("Enter meaning for '%s': ", word);
                scanf(" %s", meaning);
                root = insert(root, word, meaning);
                break;

            case 2:
                printf("Enter word to delete: ");
                scanf("%s", word);
                root = deleteNode(root, word);
                break;

            case 3:
                printf("In-order traversal of the BST:\n");
                inOrderTraversal(root);
                break;

            case 4:
                printf("Level-order traversal of the BST:\n");
                levelOrderTraversal(root);
                break;

            case 5:
                printf("Mirror image of BST in Level-order traversal:\n");
                mirrorTree(root);
                levelOrderTraversal(root);
                break;

            case 6:
                printf("Copy of BST in In-order traversal:\n");
                BST* copiedTree = copyTree(root);
                inOrderTraversal(copiedTree);
                break;

            case 7:
                exit(0);
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
