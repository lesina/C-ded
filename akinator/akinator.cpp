#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cerrno>
#include <cstring>
#include "akinator.h"

//-----------------------------------------
//! Makes tree from tree file
//! \param  [in]    tree    pointer to tree
//! \return resulted tree
//-----------------------------------------

binTree *makeTree(binTree *tree) {
    char *str = (char *) calloc(MAX_LEN, sizeof(char));
    assert(str);

    errno = 0;
    FILE *file = fopen("tree", "r");
    ASSERT_FILE(file)

    fscanf(file, "{ %s {", str);
    tree = treeConstruct(tree, str);

    collectTree(tree, file);

    fclose(file);
    return tree;
}

//--------------------------------------------
//! Collects all the information from tree file
//! \param  [in]    tree    pointer to tree
//! \param  [in]    file    pointer to tree file
//--------------------------------------------

void collectTree(binTree *tree, FILE *file) {
    char *str = (char *) calloc(MAX_LEN, sizeof(char));
    assert(str);
    char *word = (char *) calloc(MAX_LEN, sizeof(char));
    assert(word);

    node *elem = tree->root;

    fscanf(file, "%s", word);
    while (strcmp(word, "{") && strcmp(word, ",")) {
        strncat(str, word, MAX_LEN);
        strncat(str, "_", MAX_LEN);
        fscanf(file, "%s", word);
    }
    if (!strcmp(str, "NULL")) {
        tree->root->left = NULL;
    } else {
        tree->root->left = nodeConstruct(tree->root->left, str);
    }

    if (!strcmp(word, "{")) {
        tree->root = tree->root->left;
        collectTree(tree, file);
        tree->root = elem;
        fscanf(file, "%s", word);
    }

    if (!strcmp(word, ",")) {
        str = (char *) calloc(MAX_LEN, sizeof(char));
        fscanf(file, "%s", word);
        while (strcmp(word, "{") && strcmp(word, "}")) {
            strncat(str, word, MAX_LEN);
            strncat(str, "_", MAX_LEN);
            fscanf(file, "%s", word);
        }

        if (!strcmp(str, "NULL")) {
            tree->root->right = NULL;
        } else {
            tree->root->right = nodeConstruct(tree->root->right, str);
        }
    }

    if (!strcmp(word, "{")) {
        tree->root = tree->root->right;
        collectTree(tree, file);
        tree->root = elem;
        fscanf(file, "%s", word);
    }
}

//--------------------------------------------------
//! Main function of game-akinator
//! \param  [in]    tree    pointer to tree
//--------------------------------------------------

void game(binTree *tree) {
    char *answer = (char *) calloc(MAX_LEN, sizeof(char));
    assert(answer);
    node *root = tree->root;
    node *elem = tree->root;
    while (tree->root->left && tree->root->right) {
        printf("%s? (yes/no): ", tree->root->data);
        scanf("%s", answer);
        if (!strcmp(answer, "yes")) {
            elem = tree->root;
            tree->root = tree->root->right;
        } else if (!strcmp(answer, "no")) {
            elem = tree->root;
            tree->root = tree->root->left;
        } else {
            printf("Please, enter yes or no\n");
        }
    }
    printf("Was it %s? (yes/no): ", tree->root->data);
    scanf("%s", answer);
    if (!strcmp(answer, "no")) {
        printf("What's the answer? (print using _) ");
        scanf("%s", answer);
        node *newAnswer = NULL;
        newAnswer = nodeConstruct(newAnswer, answer);
        char *question = (char *) calloc(MAX_LEN, sizeof(char));
        assert(question);
        printf("What has the %s and doesn't have %s? (print using _) ", newAnswer->data, tree->root->data);
        scanf("%s", question);
        node *newQuestion = NULL;
        newQuestion = nodeConstruct(newQuestion, question);
        newQuestion->left = tree->root;
        newQuestion->right = newAnswer;
        if (elem->left == tree->root) {
            elem->left = newQuestion;
        } else {
            elem->right = newQuestion;
        }
        printf("Thank you for making akinator better!\n");
    } else {
        printf("I am perfect!\n");
    }
    tree->root = root;
}