#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

node *create_node(char data, int i) {
  node *n = (node *)malloc(sizeof(node));
  assert(n != NULL);
  n->data = data;
  n->freq = i;
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

/* void printTab(int arr[], int n) { 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%s", arr[i]); 
  
    printf("\n"); 
}  */

void tab(node *t, int i, char *pos, char *code_table[]){
  if(t==NULL)
      return;
  if(is_int_node(t)){
    if(t->left){
      pos[i] = '0';
      tab(t->left, i+1, pos, code_table);
      pos[i+1] = 0;
    }
    if(t->right){
       pos[i] = '1';
        tab(t->right, i+1, pos,code_table);
    }
  } 





  else{
      printf("%c = %s\n", t->data, pos);
      unsigned char a = t->data;
      code_table[a] = (char*)malloc(50);
      strcpy(code_table[a], pos);
  }
}


  prioqueue *create_pq() {
    
    prioqueue *q = (prioqueue*)malloc(sizeof(prioqueue));
    q->size = 0;
    return q;
}

void display_pq(prioqueue *q){
    link* ptr;
    if(q->size == 0){
        printf("NULL\n");
        return;
    }
    else{
    for(ptr = q->first; ptr!=NULL;ptr = ptr->next){
      printf("%c = ",ptr->node->data);
       printf("%d\n",ptr->node->freq);
    }

    }

}

void insert_pq(prioqueue *q, int inx, int tab){
  if(tab == 0){
    return;
  }
 
  link *new_link = (link*)malloc(sizeof(link));
  node *t = create_node(inx, tab);
  new_link->node = t;


/* Cas 1 : Insertion dans une liste null*/
    if(q->first == NULL){
 
        new_link->next =  q->first;
                q->first = new_link;
        q->size++;
    
        return;
    }
     
/* Cas 2 : Insertion en début de liste */

    if(q->first->node->freq >= tab){
        
        new_link->next = q->first;
        q->first = new_link;
        q->size++;
         return; 

    }

    link *pred= q->first;
    link *ptr = pred->next;
/* Cas 3 Recherche de la bonne position*/
    while (ptr !=NULL && ptr->node->freq < tab) {

        pred = pred->next;
        ptr = ptr->next;
    }
/* Cas 3.1 Ajout à la fin*/
    if(ptr == NULL){

        pred->next = new_link;
    }
/* Cas 3.2 Sinon ajout à la bonne place*/
    else{
        new_link->next = ptr;
        pred->next = new_link;

    }
    q->size++;

}

void free_tree(node *t){
  if(t == NULL)
    return;
  free_tree(t->left);
  free_tree(t->right);
  free(t);
}