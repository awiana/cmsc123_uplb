// Tiamzon, Edgar Alan Emmanuel III B.
// Exercise 4: AVL Tree
// AVL Implementation using BST ADT

#include <stdio.h>
#include <stdlib.h>

// Adjust these structures for AVL tree
typedef struct AVL_NODE {
    int key;
    struct AVL_NODE *left, *right, *parent;
    int height;
} AVL_NODE;

typedef struct AVL {
    AVL_NODE *root;
    int size;
    int maxSize;
} AVL;

// Create an AVL node (similar to createBSTNode)
AVL_NODE* createAVLNode(int key, AVL_NODE* L, AVL_NODE* R, AVL_NODE* P) {
    AVL_NODE *new_node = (AVL_NODE *)malloc(sizeof(AVL_NODE));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->key = key;
    new_node->left = L;
    new_node->right = R;
    new_node->parent = P;
    new_node->height = 1;  // Start with height 1 for leaf node

    return new_node;
}

// Create an AVL tree (similar to createBST)
AVL* createAVL(int max) {
    AVL* new_tree = (AVL *)malloc(sizeof(AVL));
    if (new_tree == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_tree->root = NULL;
    new_tree->size = 0;
    new_tree->maxSize = max;

    return new_tree;
}

// Function to calculate the height of a node
int heightOf(AVL_NODE *node) {
    return node ? node->height : 0;
}

// Update height based on child nodes
void updateHeight(AVL_NODE *node) {
    int leftHeight = heightOf(node->left);
    int rightHeight = heightOf(node->right);
    node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Calculate balance factor of a node
int balanceFactor(AVL_NODE *node) {
    return heightOf(node->left) - heightOf(node->right);
}

// Left rotate
void leftRotate(AVL *A, AVL_NODE *node) {
    AVL_NODE *rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (!node->parent) {
        A->root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;

    // Update heights
    updateHeight(node);
    updateHeight(rightChild);
}

// Right rotate
void rightRotate(AVL *A, AVL_NODE *node) {
    AVL_NODE *leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (!node->parent) {
        A->root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;

    // Update heights
    updateHeight(node);
    updateHeight(leftChild);
}

// Function to balance the AVL tree after insertion or deletion
void balance(AVL *A, AVL_NODE *node) {
    updateHeight(node);

    int balance = balanceFactor(node);

    // Left heavy
    if (balance > 1) {
        if (balanceFactor(node->left) < 0) {
            // Left-Right case
            leftRotate(A, node->left);
        }
        // Left-Left case
        rightRotate(A, node);
    }
    // Right heavy
    else if (balance < -1) {
        if (balanceFactor(node->right) > 0) {
            // Right-Left case
            rightRotate(A, node->right);
        }
        // Right-Right case
        leftRotate(A, node);
    }
}

// AVL insert function
void AVLInsert(AVL *A, AVL_NODE *node) {
    if (A->size == A->maxSize) {
        printf("ERROR: AVL Tree is full.\n");
        return;
    }

    AVL_NODE *current = A->root;
    AVL_NODE *parent = NULL;

    // Find the appropriate position to insert the new node
    while (current != NULL) {
        parent = current;
        if (node->key < current->key) {
            current = current->left;
        } else if (node->key > current->key) {
            current = current->right;
        } else {
            printf("ERROR: Duplicate key %d. Insertion invalid.\n", node->key);
            return;
        }
    }

    node->parent = parent;

    // Attach the new node to its parent
    if (!parent) {
        A->root = node;  // Tree was empty
    } else if (node->key < parent->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    A->size++;

    // Balance the tree starting from the parent of the inserted node
    while (parent) {
        balance(A, parent);
        parent = parent->parent;
    }
}

// Helper function to display the AVL tree in tree mode (same as BST)
void showTreeHelper(AVL_NODE* node, int tabs) {
    if (!node) return;
    showTreeHelper(node->right, tabs + 1);
    for (int i = 0; i < tabs; i++) printf("\t");
    printf("%d(%d)\n", node->key, node->height);
    showTreeHelper(node->left, tabs + 1);
}

void showTree(AVL* A) {
    showTreeHelper(A->root, 0);
}

int main() {
    char command;
    int key;
    AVL *A = createAVL(100);
    AVL_NODE* node;

    while (1) {
        scanf(" %c", &command);

        switch (command) {
            case '+':
                scanf("%d", &key);
                printf("Inserting key: %d\n", key);
                node = createAVLNode(key, NULL, NULL, NULL);
                AVLInsert(A, node);
                break;
            case 'p':
                printf("Tree (rotated +90 degrees): \n");
                showTree(A);
                printf("\n");
                break;
            case 'Q':
                free(A);
                return 0;
            default:
                printf("Unknown command: %c\n", command);
        }
    }
    return 0;
}
