#ifndef TREE_H
#define TREE_H

typedef struct _node {
    char data;               /* data stored : char    */
    struct _node *left;      /* pointer to the left child   */
    struct _node *right;     /* pointer to the right child  */
} node;

/*
 * Allocate memory for a new node.
 */
node *create_node(char data);

void display_prefix(node *t);
void display_infix(node *t);
void display_suffix(node *t);
node *scan_tree(void);
int count_nodes(node *t);
int count_leaves(node *t);
int count_only_children(node *t);
int height(node *t);
void write_tree(node *t);
void free_tree(node *t);
#endif /* TREE_H */
