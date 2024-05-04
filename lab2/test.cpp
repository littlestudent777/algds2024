#include "pch.h"
#include "..\lab_2_treap\treap.h"
#include <string.h>

// Tests for createNode function
TEST(CreateNode_ReturnKey, PositiveKey) {
    Node* node = createNode(1);
    ASSERT_EQ(node->key, 1);
    ASSERT_EQ(node->left, (Node*)NULL);
    ASSERT_EQ(node->right, (Node*)NULL);
    free(node);
}
TEST(createNode_ReturnKey, NegativeKey) {
    Node* node = createNode(-1);
    EXPECT_EQ(node->key, -1);
    EXPECT_EQ(node->left, (Node*)NULL);
    EXPECT_EQ(node->right, (Node*)NULL);
    free(node);
}

// Tests for insertNode function
TEST(insertNode_ReturnValidStr, SingleInsertion) {
    Node* root = NULL;
    root = insertNode(root, 1);
    char str[STR_SIZE] = "";
    getBrackStr(root, str);
    EXPECT_STREQ(" (1 () ())", str);
    freeTree(root);
}
TEST(insertNode_ReturnValidStr, TwoInsertions) {
    Node* root = NULL;
    root = insertNode(root, 1);
    root = insertNode(root, 2);
    char str[STR_SIZE] = "";
    getBrackStr(root, str);
    EXPECT_TRUE(strcmp(" (1 () (2 () ()))", str) || strcmp(" (2 (1 () ()) ())", str));
    freeTree(root);
}
TEST(insertNode_ReturnValidStr, IncorrectKeyInput) {
    Node* root = NULL;
    root = insertNode(root, 1);
    root = insertNode(root, 1);
    char str[STR_SIZE] = "";
    getBrackStr(root, str);
    EXPECT_STREQ(" (1 () ())", str);
    freeTree(root);
}

// Тесты для функции deleteNode
TEST(deleteNode_ReturnValidStr, SingleDeletion) {
    Node* root = NULL;
    root = insertNode(root, 1);
    root = deleteNode(root, 1);
    char str[STR_SIZE] = "";
    getBrackStr(root, str);
    EXPECT_STREQ(" ()", str);
    freeTree(root);
}

TEST(deleteNode_ReturnValidStr, SeveralDeletions) {
    Node* root = NULL;
    for (int i = 0; i <= 4; i++) {
        root = insertNode(root, i);
    }
    for (int i = 0; i <= 3; i++) {
        root = deleteNode(root, i);
    }
    char str[STR_SIZE] = "";
    getBrackStr(root, str);
    EXPECT_STREQ(" (4 () ())", str);
    freeTree(root);
}