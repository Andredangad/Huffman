
#include "../headers/prioqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

prioqueue *create_pq()
{
  prioqueue *q = (prioqueue *)malloc(sizeof(prioqueue));
  q->first = NULL;
  q->size = 0;
  return q;
}

void display_pq(prioqueue *q)
{
  link *ptr;
  if (q->size == 0)
  {
    printf("NULL\n");
    return;
  }
  else
  {
    for (ptr = q->first; ptr != NULL; ptr = ptr->next)
    {
      printf("%c = ", ptr->node->data);
      printf("%d\n", ptr->node->freq);
    }
  }
}

node *remove_min_pq(prioqueue *q)
{
  assert(q->size > 0);
  link *tmp;
  if (q->first == NULL)
    return NULL;
  node *n = q->first->node;
  tmp = q->first;
  q->first = q->first->next;
  free(tmp);
  q->size--;
  return n;
}
/* Insert in order in the priority queue */
void insert_pq(prioqueue *q, node *t)
{
  link *new_link = (link *)malloc(sizeof(link));
  new_link->node = t;
  new_link->next = NULL;

  if (q->size == 0)
  {
    new_link->next = q->first;
    q->first = new_link;
    q->size++;
    return;
  }

  if (q->first->node->freq >= t->freq)
  {
    new_link->next = q->first;
    q->first = new_link;
    q->size++;
    return;
  }

  link *pred = q->first;
  link *ptr = pred->next;

  while (ptr != NULL && ptr->node->freq < t->freq)
  {
    pred = pred->next;
    ptr = ptr->next;
  }

  if (ptr == NULL)
  {
    pred->next = new_link;
  }

  else
  {
    new_link->next = ptr;
    pred->next = new_link;
  }
  q->size++;
}

node *huffman(prioqueue *q, node *t){
  while(q->size >= 2){
    node *t1 = remove_min_pq(q);
    node *t2 = remove_min_pq(q);
    t = create_node(EOF);
    t->freq = t1->freq + t2->freq;
    t->left = t1;
    t->right = t2;
    insert_pq(q,t);
  }
  return q->first->node;
}

void free_pq(prioqueue *q)
{
  free(q->first);
  free(q);
}