#ifndef TREE_H
#define TREE_H

#include <stdio.h>

typedef struct _node {
    int data;               /* data stored : char    */
    int freq;                
    struct _node *left;      /* pointer to the left child   */
    struct _node *right;     /* pointer to the right child  */
} node;


node *create_node(int data);
node *read_tree(FILE *infile);
void print_tree(node *t, FILE *outfile);
void display_prefix(node *t);
void free_tree(node *t);
void create_code_table(node *t, char *code_table[], char buffer[], int index, char elt);
void display_infix_word(node *t);
void free_code_table(char *code_table[], int frequency[], int size);
#endif /* TREE_H */
