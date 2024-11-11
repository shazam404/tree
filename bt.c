#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
};

struct tree{
    struct node* root;
};

struct node* createNode(int data){
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(struct tree* tree, int data){
    struct node* newNode = createNode(data);

    if(tree->root == NULL){
        tree->root = newNode;
        return;
    }

    struct node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = tree->root;

    while(front < rear){
        struct node* temp = queue[front++];

        if(temp->left == NULL){
            temp->left = newNode;
            return;
        } else {
            queue[rear++] = temp->left;
        }

        if(temp->right == NULL){
            temp->right = newNode;
            return;
        } else {
            queue[rear++] = temp->right;
        }
    }

}

int height(struct node* node){
    if(node == NULL)
        return 0;

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void preorder(struct node* node){
    if(node == NULL)
        return;

    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

void inorder(struct node* node){
    if(node == NULL)
        return;

    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}

void postorder(struct node* node){
    if(node == NULL)
        return;

    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}

void levelOrder(struct tree* tree){
    struct node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = tree->root;

    while(front < rear){
        struct node* temp = queue[front++];

        printf("%d ", temp->data);

        if(temp->left != NULL)
            queue[rear++] = temp->left;

        if(temp->right != NULL)
            queue[rear++] = temp->right;
    }
}

int main() {
    struct tree* tree = (struct tree*) malloc(sizeof(struct tree));
    tree->root = NULL;

    int choice, data;
    while(1){
        printf("\n1. Insert\n2. Height\n3. Preorder\n4. Inorder\n5. Postorder\n6. Level Order\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insert(tree, data);
                break;
            case 2:
                printf("Height of the tree is: %d\n", height(tree->root));
                break;
            case 3:
                printf("Preorder traversal: ");
                preorder(tree->root);
                printf("\n");
                break;
            case 4:
                printf("Inorder traversal: ");
                inorder(tree->root);
                printf("\n");
                break;
            case 5:
                printf("Postorder traversal: ");
                postorder(tree->root);
                printf("\n");
                break;
            case 6:
                printf("Level order traversal: ");
                levelOrder(tree);
                printf("\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
}