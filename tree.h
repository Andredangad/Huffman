#ifndef TREE_H
#define TREE_H

typedef struct _node {
    char data;               /* data stored : char    */
    int freq;                
    struct _node *left;      /* pointer to the left child   */
    struct _node *right;     /* pointer to the right child  */
} node;

typedef struct _link {
struct _node *node;
struct _link *next;     /* pointer to the right child  */
} link;

typedef struct _prioqueue {
    struct _link *first;
    int size;
} prioqueue;

node *create_node(char data, int i);
void display_prefix(node *t);
void free_tree(node *t);
void tab(node *t, int i, char* pos, char* code_table[]);
prioqueue *create_pq();
void insert_pq(prioqueue *q, int inx, int tab);
void display_pq(prioqueue *q);
#endif /* TREE_H */
