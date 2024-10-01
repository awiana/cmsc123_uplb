BST_NODE *minimum(BST_NODE *node) {
    // Finds the minimum node in a subtree (i.e., leftmost node)
    if (node == NULL) return NULL;

    while (node->left != NULL) {
        node = node->left; // Move to the leftmost node
    }
    return node; // Return the node with the minimum value
}

BST_NODE *maximum(BST_NODE *node) {
    // Finds the maximum node in a subtree (i.e., rightmost node)
    if (node == NULL) return NULL;

    while (node->right != NULL) {
        node = node->right; // Move to the rightmost node
    }
    return node; // Return the node with the maximum value
}

int delete(BST *B, int key) {

    // If the tree is empty, print an error and return
    if (isEmpty(B)) {
        printf("ERROR: Tree is empty, unable to delete a key!\n");
        return -1;
    }

    BST_NODE *root = B->root;
    BST_NODE *parent = NULL;

    // Search for the node containing the key
    while (root != NULL && root->key != key) {
        parent = root; // Keep track of the parent

        // Traverse the tree to find the key
        if (key > root->key) {
            root = root->left; // Go left if the key is smaller
        } else {
            root = root->right; // Go right if the key is larger
        }
    }

    // If the node is not found, print an error and return
    if (root == NULL) {
        printf("ERROR: No key found!\n");
        return -1;
    }

    // Node to delete found, now check the case of deletion
    // Case 1: The node has no child (it's a leaf node)
    if (root->left == NULL && root->right == NULL) {
        if (root == B->root) {
            B->root = NULL; // If it's the root node, set root to NULL
        } else if (parent->left == root) {
            parent->left = NULL; // If it's the left child of its parent, set the parent's left to NULL
        } else {
            parent->right = NULL; // If it's the right child, set the parent's right to NULL
        }
        free(root); // Free the memory of the deleted node
    }

    // Case 2: The node has one child
    else if (root->left == NULL || root->right == NULL) {
        BST_NODE *child;

        // If the node has only a right child, use the right child
        if (root->left == NULL) {
            child = root->right;
        }
        // Otherwise, use the left child
        else {
            child = root->left;
        }

        // If deleting the root node, replace it with its child
        if (root == B->root) {
            B->root = child;
        } 
        // If it's a left child, update the parent's left pointer
        else if (parent->left == root) {
            parent->left = child;
        } 
        // If it's a right child, update the parent's right pointer
        else {
            parent->right = child;
        }
        free(root); // Free the memory of the deleted node
    }

    // Case 3: The node has two children
    else {
        BST_NODE *succ = root->right;
        BST_NODE *parent_succ = root;

        // Find the successor, which is the minimum node in the right subtree
        while (succ->left != NULL) {
            parent_succ = succ;
            succ = succ->left; // Keep moving left until the successor is found
        }

        // Replace the key of the node to be deleted with the successor's key
        root->key = succ->key;

        // Fix the parent's child pointer to bypass the deleted successor
        if (parent_succ->left == succ) {
            parent_succ->left = succ->right; // Successor's right child replaces it in the tree
        } else {
            parent_succ->right = succ->right; // Successor was a direct child of the root
        }

        free(succ); // Free the memory of the successor node
    }
    
    // Decrease the size of the tree after deletion
    B->size--;
    return 0; // Return success
}

void clear(BST *B) {
    if (B == NULL || B->root == NULL) {
        return; // If the tree or root is NULL, do nothing
    }

    BST_NODE *node = B->root;

    // Recursively clear the left subtree
    if (node->left != NULL) {
        B->root = node->left;
        clear(B);
    }

    // Recursively clear the right subtree
    if (node->right != NULL) {
        B->root = node->right;
        clear(B);
    }

    // Free the current node
    free(node);

    // After clearing all nodes, reset the root and size of the tree
    B->root = NULL;
    B->size = 0;
}

   case '-': // Add the deletion case
                scanf("%d", &key);
                printf("Deleting key: %d\n", key);
                if (delete(B, key) == 0) {
                    printf("Key %d successfully deleted.\n", key);
                } else {
                    printf("Failed to delete key %d.\n", key);
                }
                break;
