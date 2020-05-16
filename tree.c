#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

node *create_node(char data) {
  node *n = (node *)malloc(sizeof(node));
  assert(n != NULL);
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  return n;
}

void display_prefix(node *t){

  if(t==NULL){
    return;
  }
  printf("%c\n",t->data);
  display_prefix(t->left);
  display_prefix(t->right);

}




 void free_tree(node *t) {
    node* temp = t;
    if (!temp){
       return;

    }
    free_tree(temp->left);
    free_tree(temp->right);

    free(temp);

}