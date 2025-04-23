#include <stdio.h>
#include <stdlib.h>

struct tbtnode {
    char data;
    int rbit, lbit;
    struct tbtnode *rightc, *leftc;
};

typedef struct tbtnode tbtnode;

tbtnode* create_node(char data) {
    tbtnode *new_node = (tbtnode*)malloc(sizeof(tbtnode));
    if (!new_node) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->lbit = new_node->rbit = 0;
    return new_node;
}

tbtnode* create_tree(tbtnode *head) {
    tbtnode *root, *temp, *curr;
    char ch, ch1;
    int flag;

    printf("Enter root data: ");
    char root_data;
    scanf(" %c", &root_data);
    
    root = create_node(root_data);
    head->lbit = 1;
    root->leftc = root->rightc = head;
    head->leftc = root;
    
    do {
        flag = 0;
        temp = root;
        
        printf("Enter data for new node: ");
        char node_data;
        scanf(" %c", &node_data);
        curr = create_node(node_data);
        
        while (flag == 0) {
            printf("Insert to the left or right of %c? (l/r): ", temp->data);
            scanf(" %c", &ch1);
            
            if (ch1 == 'l') {
                if (temp->lbit == 0) {
                    curr->rightc = temp;
                    curr->leftc = temp->leftc;
                    temp->leftc = curr;
                    temp->lbit = 1;
                    flag = 1;
                } else {
                    temp = temp->leftc;
                }
            } else if (ch1 == 'r') {
                if (temp->rbit == 0) {
                    curr->leftc = temp;
                    curr->rightc = temp->rightc;
                    temp->rightc = curr;
                    temp->rbit = 1;
                    flag = 1;
                } else {
                    temp = temp->rightc;
                }
            } else {
                printf("Invalid input. Please enter 'l' or 'r'.\n");
            }
        }

        printf("Do you want to add more nodes? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y');

    return head;
}

tbtnode* inorder_successor(tbtnode *temp) {
    tbtnode *x = temp->rightc;
    if (temp->rbit == 1) {
        while (x->lbit == 1) {
            x = x->leftc;
        }
    }
    return x;
}

void inorder_traversal(tbtnode *head) {
    tbtnode *temp = head->leftc;
    printf("Inorder traversal: ");
    while (temp != head) {
        while (temp->lbit == 1) {
            temp = temp->leftc;
        }
        printf("%c ", temp->data);
        
        while (temp->rbit == 0 && temp->rightc != head) {
            temp = inorder_successor(temp);
            printf("%c ", temp->data);
        }
        temp = temp->rightc;
    }
    printf("\n");
}

void preorder_traversal(tbtnode *head) {
    tbtnode *temp = head->leftc;
    printf("Preorder traversal: ");
    while (temp != head) {
        printf("%c ", temp->data);
        
        while (temp->lbit == 1) {
            temp = temp->leftc;
            printf("%c ", temp->data);
        }
        
        while (temp->rbit == 0 && temp->rightc != head) {
            temp = temp->rightc;
        }
        
        temp = temp->rightc;
    }
    printf("\n");
}



int main() {
    tbtnode *head = create_node('\0');
    head->rbit = 1; 
    head->leftc = head->rightc = head;
    
    head = create_tree(head);  
    
    inorder_traversal(head); 
    preorder_traversal(head); 
    
    
    return 0;
}
