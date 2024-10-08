// tiamzon, edgar alan emmanuel III b.
// exercise 4: AVL tree
// avl implementation using bst adt

#include <stdio.h>
#include <stdlib.h>

// define the structure for an AVL node
typedef struct AVL_NODE {
    int key;                       // store the key value of the node
    struct AVL_NODE *left;         // pointer to the left child
    struct AVL_NODE *right;        // pointer to the right child
    struct AVL_NODE *parent;       // pointer to the parent node
    int height;                    // height of the node for balance calculations
} AVL_NODE;

// define the structure for an AVL tree
typedef struct AVL {
    AVL_NODE *root;                // pointer to the root of the AVL tree
    int size;                      // current number of nodes in the tree
    int maxSize;                   // maximum number of nodes allowed
} AVL;

// create an avl node (similar to createBSTNode)
AVL_NODE* createAVLNode(int key, AVL_NODE* L, AVL_NODE* R, AVL_NODE* P) {
    AVL_NODE *new_node = (AVL_NODE *)malloc(sizeof(AVL_NODE));  // allocate memory for a new node
    if (new_node == NULL) {                                     // check if memory allocation failed
        printf("Memory allocation failed.\n");                  // print error message
        exit(1);                                                // exit the program
    }
    new_node->key = key;                                        // set the key of the new node
    new_node->left = L;                                         // set the left child of the new node
    new_node->right = R;                                        // set the right child of the new node
    new_node->parent = P;                                       // set the parent of the new node
    new_node->height = 1;                                       // initialize the height as 1 for leaf node

    return new_node;                                            // return the created node
}

// create an avl tree (similar to createBST)
AVL* createAVL(int max) {
    AVL* new_tree = (AVL *)malloc(sizeof(AVL));                 // allocate memory for a new AVL tree
    if (new_tree == NULL) {                                     // check if memory allocation failed
        printf("Memory allocation failed.\n");                  // print error message
        exit(1);                                                // exit the program
    }
    new_tree->root = NULL;                                      // set the root of the new tree to null
    new_tree->size = 0;                                         // initialize the size of the tree to 0
    new_tree->maxSize = max;                                    // set the maximum size of the tree

    return new_tree;                                            // return the created AVL tree
}

// function to calculate the height of a node
int heightOf(AVL_NODE *node) {
    return node ? node->height : 0;                             // return the height or 0 if the node is null
}

// update height based on child nodes
void updateHeight(AVL_NODE *node) {
    int leftHeight = heightOf(node->left);                      // get the height of the left child
    int rightHeight = heightOf(node->right);                    // get the height of the right child
    node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);  // update the height of the node
}

// calculate balance factor of a node
int balanceFactor(AVL_NODE *node) {
    return heightOf(node->left) - heightOf(node->right);        // return the difference in heights of left and right children
}

// left rotate a subtree rooted at 'node'
void leftRotate(AVL *A, AVL_NODE *node) {
    AVL_NODE *rightChild = node->right;                         // get the right child of the node
    node->right = rightChild->left;                             // set the right child to the left subtree of rightChild

    if (rightChild->left) {                                     // if the left child of rightChild exists
        rightChild->left->parent = node;                        // update its parent to be the current node
    }

    rightChild->parent = node->parent;                          // update rightChild's parent to the node's parent

    if (!node->parent) {                                        // if the node has no parent, it's the root
        A->root = rightChild;                                   // set rightChild as the new root
    } else if (node == node->parent->left) {                    // if node is a left child
        node->parent->left = rightChild;                        // set rightChild as the new left child
    } else {                                                    // if node is a right child
        node->parent->right = rightChild;                       // set rightChild as the new right child
    }

    rightChild->left = node;                                    // set node as the left child of rightChild
    node->parent = rightChild;                                  // update node's parent to be rightChild

    updateHeight(node);                                         // update the height of the node
    updateHeight(rightChild);                                   // update the height of rightChild
}

// right rotate a subtree rooted at 'node'
void rightRotate(AVL *A, AVL_NODE *node) {
    AVL_NODE *leftChild = node->left;                           // get the left child of the node
    node->left = leftChild->right;                              // set the left child to the right subtree of leftChild

    if (leftChild->right) {                                     // if the right child of leftChild exists
        leftChild->right->parent = node;                        // update its parent to be the current node
    }

    leftChild->parent = node->parent;                           // update leftChild's parent to the node's parent

    if (!node->parent) {                                        // if the node has no parent, it's the root
        A->root = leftChild;                                    // set leftChild as the new root
    } else if (node == node->parent->left) {                    // if node is a left child
        node->parent->left = leftChild;                         // set leftChild as the new left child
    } else {                                                    // if node is a right child
        node->parent->right = leftChild;                        // set leftChild as the new right child
    }

    leftChild->right = node;                                    // set node as the right child of leftChild
    node->parent = leftChild;                                   // update node's parent to be leftChild

    updateHeight(node);                                         // update the height of the node
    updateHeight(leftChild);                                    // update the height of leftChild
}

// function to balance the avl tree after insertion or deletion
void balance(AVL *A, AVL_NODE *node) {
