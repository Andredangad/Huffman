#ifndef PRIOQUEUE_H
#define PRIOQUEUE_H

#include <stdio.h>
#include "../headers/tree.h"
#include "../headers/prioqueue.h"


typedef struct _link {
struct _node *node;
struct _link *next;     /* pointer to the right child  */
} link;

typedef struct _prioqueue {
    struct _link *first;
    int size;
} prioqueue;

prioqueue *create_pq();
void insert_pq(prioqueue *q, node *t);
void display_pq(prioqueue *q);
void free_pq(prioqueue *q);
node *remove_min_pq(prioqueue *q);
node *huffman(prioqueue *q, node *t);


#endif /* TREE_H */
