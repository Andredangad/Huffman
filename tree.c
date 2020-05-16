#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

node *create_node(char data) {
  node *n = (node *)malloc(sizeof(node));
  assert(n != NULL);
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  return n;
}



void display_prefix(node *t){
  if(t==NULL)
    return;
  printf("%c\n",t->data);
  display_prefix(t->left);
  display_prefix(t->right);

}

int is_int_node(node* t){
  if(t->left==NULL && t->right == NULL)
    return 0;
  
  else
    return 1;

}

void printTab(int arr[], int n) { 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
} 

void tab(node *t, int i, int pos[]){
  node *p;

 
  if(t==NULL)
    return;
  if(is_int_node(t)){
      
     
      if(t->left){
        pos[i] = 0;
        tab(t->left, i+1, pos);
      }
      if(t->right){
        pos[i] = 1;
        tab(t->right, i+1, pos);
        
      }

  }
  else{

    printf("%c = ", t->data);
    printTab(pos,i);

  }


}

void free_tree(node *t){
  if(t == NULL)
    return;
  free_tree(t->left);
  free_tree(t->right);
  free(t);
}