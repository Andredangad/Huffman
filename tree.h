#ifndef TREE_H
#define TREE_H

#include <stdio.h>
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

node *create_node(char data);
node *read_tree(FILE *infile);
void print_tree(node *t, FILE *outfile);
void display_prefix(node *t);
void free_tree(node *t);
void create_code_table(node *t, char *code_table[], char buffer[], int index, char elt);
prioqueue *create_pq();
void insert_pq(prioqueue *q, node *t);
void display_pq(prioqueue *q);
node *huffman(prioqueue *q, node *t);
void display_infix_word(node *t);
void free_pq(prioqueue *q);
void free_code_table(char *code_table[], int frequency[], int size);
#endif /* TREE_H */
