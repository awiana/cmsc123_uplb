#include <stdio.h>  // include standard input-output library for printing
#include <stdlib.h> // include standard library for memory allocation

// define the structure for an AVL_NODE
typedef struct AVL_NODE {
    int data; // store the value of the node
    struct AVL_NODE *left; // pointer to the left child node
    struct AVL_NODE *right; // pointer to the right child node
    int height; // height of the node in the tree
} AVL_NODE;

// define the structure for the AVL tree itself
typedef struct AVL {
    AVL_NODE *root; // pointer to the root node of the tree
} AVL;

// function prototypes
AVL_NODE* createNode(int data);
void leftRotate(AVL *A, AVL_NODE *node);
void rightRotate(AVL *A, AVL_NODE *node);
int heightOf(AVL_NODE *node);
int getBalance(AVL_NODE *node);
void AVLInsert(AVL *A, AVL_NODE *node);
AVL_NODE* insertNode(AVL_NODE* root, AVL_NODE* node);
void inOrderTraversal(AVL_NODE *node);

// function to create a new AVL_NODE
AVL_NODE* createNode(int data) {
    AVL_NODE *newNode = (AVL_NODE *)malloc(sizeof(AVL_NODE)); // allocate memory for a new node
    newNode->data = data; // set the data of the new node
    newNode->left = newNode->right = NULL; // initialize left and right children to NULL (no children yet)
    newNode->height = 1; // set the height of the new node to 1 (since it's a new leaf node)
    return newNode; // return the newly created node
}

// function to perform a left rotation around a given node
void leftRotate(AVL *A, AVL_NODE *node) {
    AVL_NODE *newRoot = node->right; // make the right child the new root
    node->right = newRoot->left; // move the left child of the new root to be the right child of the old root
    newRoot->left = node; // make the old root the left child of the new root

    // update the heights of the nodes after rotation
    node->height = heightOf(node); // update the height of the old root
    newRoot->height = heightOf(newRoot); // update the height of the new root

    // if the rotated node was the root of the AVL tree, update the tree's root
    if (A->root == node) {
        A->root = newRoot; // set the new root of the tree
    }
}

// function to perform a right rotation around a given node
void rightRotate(AVL *A, AVL_NODE *node) {
    AVL_NODE *newRoot = node->left; // make the left child the new root
    node->left = newRoot->right; // move the right child of the new root to be the left child of the old root
    newRoot->right = node; // make the old root the right child of the new root

    // update the heights of the nodes after rotation
    node->height = heightOf(node); // update the height of the old root
    newRoot->height = heightOf(newRoot); // update the height of the new root

    // if the rotated node was the root of the AVL tree, update the tree's root
    if (A->root == node) {
        A->root = newRoot; // set the new root of the tree
    }
}

// function to calculate the height of a node
int heightOf(AVL_NODE *node) {
    if (node == NULL) { // check if the node is NULL (doesn't exist)
        return 0; // if it is NULL, its height is 0
    }
    return node->height; // return the height of the existing node
}

// function to calculate the balance factor of a node
int getBalance(AVL_NODE *node) {
    if (node == NULL) { // check if the node is NULL
        return 0; // if it is NULL, its balance factor is 0
    }
    // calculate the balance factor as height of left subtree - height of right subtree
    return heightOf(node->left) - heightOf(node->right); 
}

// function to insert a node into the AVL tree
void AVLInsert(AVL *A, AVL_NODE *node) {
    // Insert the node (standard BST insertion)
    A->root = insertNode(A->root, node); // insert the new node in the correct position

    // Update the height of the ancestor node
    node->height = heightOf(node); // update the height of the inserted node

    // Get the balance factor
    int balance = getBalance(node); // calculate the balance factor

    // Perform rotations if the node becomes unbalanced
    if (balance > 1 && node->left != NULL && node->left->data > node->data) {
        rightRotate(A, node); // case where left child is greater, do right rotation (left-left case)
    } else if (balance < -1 && node->right != NULL && node->right->data < node->data) {
        leftRotate(A, node); // case where right child is lesser, do left rotation (right-right case)
    } else if (balance > 1 && node->left != NULL && node->left->data < node->data) {
        leftRotate(A, node->left); // case where left child is lesser, do left rotation on left child (left-right case)
        rightRotate(A, node); // then do right rotation
    } else if (balance < -1 && node->right != NULL && node->right->data > node->data) {
        rightRotate(A, node->right); // case where right child is greater, do right rotation on right child (right-left case)
        leftRotate(A, node); // then do left rotation
    }
}

// Helper function to insert a node in the BST
AVL_NODE* insertNode(AVL_NODE* root, AVL_NODE* node) {
    if (root == NULL) { // if the current tree is empty
        return node; // return the new node as the root
    }
    if (node->data < root->data) { // if the new node's data is less than the current node's data
        root->left = insertNode(root->left, node); // insert into the left subtree
    } else if (node->data > root->data) { // if the new node's data is greater than the current node's data
        root->right = insertNode(root->right, node); // insert into the right subtree
    }
    return root; // return the unchanged root pointer
}

// Function to perform in-order traversal of the AVL tree
void inOrderTraversal(AVL_NODE *node) {
    if (node != NULL) { // check if the node is not NULL
        inOrderTraversal(node->left); // traverse the left subtree
        printf("%d ", node->data); // print the data of the current node
        inOrderTraversal(node->right); // traverse the right subtree
    }
}

// Example usage
int main() {
    AVL tree; // create an AVL tree
    tree.root = NULL; // initialize the tree's root to NULL (empty tree)

    // Create nodes with values
    AVL_NODE* node1 = createNode(10); // create a new node with value 10
    AVL_NODE* node2 = createNode(20); // create a new node with value 20
    AVL_NODE* node3 = createNode(30); // create a new node with value 30
    

    // Insert nodes into the AVL tree
    AVLInsert(&tree, node1); // insert the first node into the tree
    AVLInsert(&tree, node2); // insert the second node into the tree
    AVLInsert(&tree, node3); // insert the third node into the tree

    // Print the AVL tree using in-order traversal
    printf("In-order traversal of the AVL tree: ");
    inOrderTraversal(tree.root); // call the in-order traversal function
    printf("\n"); // print a new line

    return 0; // end of the program
}
