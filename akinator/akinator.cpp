#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cerrno>
#include <cstring>
#include "akinator.h"

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