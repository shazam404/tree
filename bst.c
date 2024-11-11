#include <stdio.h>
#include <stdlib.h>

// Structure representing a node in the binary search tree (BST)
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert an item into the BST
struct Node* BSTInsert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = BSTInsert(root->left, data);
    } else if (data > root->data) {
        root->right = BSTInsert(root->right, data);
    } else {
        printf("Item %d already exists in the BST.\n", data);
    }

    return root;
}

// Function to search for an item in the BST and return the node and its parent
struct Node* BSTSearch(struct Node* root, int key, struct Node** parent) {
    struct Node* current = root;
    *parent = NULL;

    while (current != NULL && current->data != key) {
        *parent = current;
        if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return current;
}

// Inorder traversal using a stack (non-recursive)
void BSTInorderStack(struct Node* root) {
    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

// Helper function to find the minimum value node in the tree
struct Node* BST_Findmin(struct Node* root) {
    struct Node* current = root;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Helper function to find the maximum value node in the tree
struct Node* BST_findmax(struct Node* root) {
    struct Node* current = root;
    while (current && current->right != NULL)
        current = current->right;
    return current;
}

// Function to delete a node from the BST
struct Node* BSTDelete(struct Node* root, int key) {
    if (root == NULL) {
        printf("Node with key %d not found.\n", key);
        return root;
    }

    if (key < root->data) {
        root->left = BSTDelete(root->left, key);
    } else if (key > root->data) {
        root->right = BSTDelete(root->right, key);
    } else {
        // Node to be deleted found

        // Case 1: Node has no children (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: Node has one child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Node has two children
        struct Node* temp = BST_Findmin(root->right);
        root->data = temp->data;
        root->right = BSTDelete(root->right, temp->data);
    }

    return root;
}

// Function to find the inorder successor of a node
struct Node* BST_Successor(struct Node* root, int key) {
    struct Node* current = BSTSearch(root, key, NULL);
    if (current == NULL) {
        printf("Node with key %d not found.\n", key);
        return NULL;
    }

    if (current->right != NULL) {
        return BST_Findmin(current->right);
    }

    struct Node* successor = NULL;
    struct Node* ancestor = root;
    while (ancestor != current) {
        if (current->data < ancestor->data) {
            successor = ancestor;
            ancestor = ancestor->left;
        } else {
            ancestor = ancestor->right;
        }
    }

    return successor;
}

// Function to find the inorder predecessor of a node
struct Node* BST_Predecessor(struct Node* root, int key) {
    struct Node* current = BSTSearch(root, key, NULL);
    if (current == NULL) {
        printf("Node with key %d not found.\n", key);
        return NULL;
    }

    if (current->left != NULL) {
        return BST_findmax(current->left);
    }

    struct Node* predecessor = NULL;
    struct Node* ancestor = root;
    while (ancestor != current) {
        if (current->data > ancestor->data) {
            predecessor = ancestor;
            ancestor = ancestor->right;
        } else {
            ancestor = ancestor->left;
        }
    }

    return predecessor;
}

// Menu-driven program
int main() {
    struct Node* root = NULL;
    int choice, key;
    struct Node* parent = NULL;
    struct Node* result;

    do {
        printf("\n\n---- Binary Search Tree Menu ----\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Inorder Traversal (using Stack)\n");
        printf("4. Delete\n");
        printf("5. Find Minimum\n");
        printf("6. Find Maximum\n");
        printf("7. Find Successor\n");
        printf("8. Find Predecessor\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item to insert: ");
                scanf("%d", &key);
                root = BSTInsert(root, key);
                break;

            case 2:
                printf("Enter item to search: ");
                scanf("%d", &key);
                result = BSTSearch(root, key, &parent);
                if (result != NULL) {
                    printf("Item %d found.\n", result->data);
                    if (parent != NULL)
                        printf("Parent: %d\n", parent->data);
                    else
                        printf("Item is the root node.\n");
                } else {
                    printf("Item not found.\n");
                }
                break;

            case 3:
                printf("Inorder Traversal: ");
                BSTInorderStack(root);
                printf("\n");
                break;

            case 4:
                printf("Enter item to delete: ");
                scanf("%d", &key);
                root = BSTDelete(root, key);
                break;

            case 5:
                result = BST_Findmin(root);
                if (result != NULL) {
                    printf("Minimum value: %d\n", result->data);
                } else {
                    printf("Tree is empty.\n");
                }
                break;

            case 6:
                result = BST_findmax(root);
                if (result != NULL) {
                    printf("Maximum value: %d\n", result->data);
                } else {
                    printf("Tree is empty.\n");
                }
                break;

            case 7:
                printf("Enter item to find successor: ");
                scanf("%d", &key);
                result = BST_Successor(root, key);
                if (result != NULL) {
                    printf("Successor of %d is %d.\n", key, result->data);
                } else {
                    printf("No successor found.\n");
                }
                break;

            case 8:
                printf("Enter item to find predecessor: ");
                scanf("%d", &key);
                result = BST_Predecessor(root, key);
                if (result != NULL) {
                    printf("Predecessor of %d is %d.\n", key, result->data);
                } else {
                    printf("No predecessor found.\n");
                }
                break;

            case 9:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 9);

    return 0;
}
