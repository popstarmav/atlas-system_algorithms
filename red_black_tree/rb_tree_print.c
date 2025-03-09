#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rb_trees.h"

static int print_t(const rb_tree_t *tree, int is_left, int offset, int depth, char **s)
{
    char b[20];
    int width = 5, left, right, i;
    int is_root = !depth;

    if (!tree)
        return 0;

    sprintf(b, "%c(%03d)", (tree->color == RED ? 'R' : 'B'), tree->n);
    
    left = print_t(tree->left, 1, offset, depth + 1, s);
    right = print_t(tree->right, 0, offset + left + width, depth + 1, s);

    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {
        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    } else if (depth && !is_left) {
        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';
        s[depth - 1][offset + left + width/2] = '.';
    }

    if (is_root && tree->right) {
        s[depth][offset + left + width + right/2] = '.';
        for (i = 0; i < right - width/2; i++)
            s[depth][offset + left + width + i] = '-';
    }

    return left + width + right;
}

void rb_tree_print(const rb_tree_t *tree)
{
    char **s;
    int height = 10;

    if (!tree)
        return;

    s = malloc(sizeof(char *) * height);
    for (int i = 0; i < height; i++) {
        s[i] = malloc(sizeof(char) * 255);
        memset(s[i], ' ', 254);
        s[i][254] = '\0';
    }

    print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < height; i++) {
        char *p = s[i];
        while (*p) p++;
        while (p > s[i] && *(p-1) == ' ') p--;
        *p = '\0';
        printf("%s\n", s[i]);
        free(s[i]);
    }
    free(s);
}
