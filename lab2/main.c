#include "treap.h"
#include <time.h>

int main() {
    srand(time(NULL));

    // Make an example of a treap
    Node* root = NULL;
    int i;
    for (i = 1; i <= 10; i++) {
        root = insertNode(root, i);
    }
    printBrackStr(root);
    printf("\n");
    // Erase an element and print the result
    root = deleteNode(root, 6);
    printf("Result after deleting key == 6:\n");
    printBrackStr(root);

    freeTree(root);
    return 0;
}
