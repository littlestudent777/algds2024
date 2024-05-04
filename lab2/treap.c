#include "treap.h"
#define TEMP_SIZE 10
#define STR_SIZE 200


// Add a node with new key */
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Error allocating memory\n");
        exit(1);
    }
    newNode->key = key;
    newNode->priority = rand() % 100;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;
    x->right = y;
    y->left = temp;

    return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;
    y->left = x;
    x->right = temp;

    return y;
}

// Recursive insertion in a treap
Node* insertNode(Node* root, int key) {
    // If tree is clean, create a new node and return it
    if (root == NULL)
        return createNode(key);
    // If it's not - compare to the key and insert
    if (key < root->key) {
        // Insert in left subtree
        root->left = insertNode(root->left, key);

        // Ensure priority is respected
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }

    else if (key > root->key) {
        // Insert in right subtree
        root->right = insertNode(root->right, key);

        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }

    // Handle incorrect input
    else printf("Warning: Duplicate key was found\n It was not implimented into the tree\n");

    return root;
}

// Recursive merge with the respect for priority
Node* merge(Node* left, Node* right) {
    // If parent is a leaf, we just delete it (return NULL)
    // If there is only one ancestor, we just move it up
    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->priority < right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

// Recursive deleting from a tree
Node* deleteNode(Node* root, int key) {
    if (root != NULL) {
        if (root->key == key) {
            Node* tmp = root;
            root = merge(root->left, root->right);
            free(tmp);
        }
        else if (key < root->key) {
            root->left = deleteNode(root->left, key);
        }
        else {
            root->right = deleteNode(root->right, key);
        }
    }
    return root;
}
/*
// Print in order of LNR
void printTree(Node* root) {
    if (root != NULL) {
        printTree(root->left);
        printf("(%d, %d) ", root->key, root->priority);
        printTree(root->right);
    }
}
*/
void freeTree(Node* node) {
    if (node != NULL) {
        freeTree(node->right);
        freeTree(node->left);
        free(node);
    }
}

// Get binary tree representation as balanced string of brackets
void getBrackStr(Node* root, char* buffer) {
    /*
        x                        NLR
       / \    -> (x_key,x_pr (y_key,y_pr) (z_key,z_pr))
      y   z                                               */

    if (root != NULL) {
        char str[TEMP_SIZE];
        sprintf(str, " (%d,%d", root->key, root->priority);
        strcat(buffer, str);
        getBrackStr(root->left, buffer);
        getBrackStr(root->right, buffer);
        strcat(buffer, ")");
    }
}

void printBrackStr(Node* root) {
    char str[STR_SIZE] = "";
    getBrackStr(root, str);
    printf("%s\n", str);
}