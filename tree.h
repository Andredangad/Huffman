#ifndef TREE_H
#define TREE_H

typedef struct _node {
    char data;               /* data stored : char    */
    struct _node *left;      /* pointer to the left child   */
    struct _node *right;     /* pointer to the right child  */
} node;

node *create_node(char data);
void display_prefix(node *t);
void free_tree(node *t);
void tab(node *t, int i, int pos[]);
#endif /* TREE_H */
