#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

node *create_node(int data) {
  node *n = (node *)malloc(sizeof(node));
  assert(n != NULL);
  n->data = data;
  n->freq = 0;
  n->left = NULL;
  n->right = NULL;
  return n;
}

node *read_tree(FILE *infile) {
    char c;
    if((c = getc(infile)) == '-' && getc(infile) == '1')
      return NULL;
    node *n = create_node(EOF);
    if(c == '0')
      n = create_node(getc(infile));
    else{
      n->left = read_tree(infile);
      n->right = read_tree(infile);
    }
    return n;
}

void print_tree(node *t, FILE *outfile){
    if(t==NULL){
        return;
    }
    if(t->left != NULL || t->right != NULL)
        fprintf(outfile,"1");
    else 
        fprintf(outfile,"0");
    print_tree(t->left, outfile);
    if(t->data != EOF)
        fprintf(outfile,"%c",t->data);        
    print_tree(t->right, outfile);
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


void create_code_table(node *t, char *code_table[], char buffer[], int index, char elt){
  if (t == NULL){
    return;
  }
  if (index != 0){
    buffer[index - 1] = elt;
  }

  if (t->left == NULL && t->right == NULL){
    buffer[index] = 0;
    unsigned char a = t->data;
    code_table[a] = (char *)malloc(sizeof(char *) * 100);
    strcpy(code_table[a], buffer);
  
  
  }
  else{
    create_code_table(t->left, code_table, buffer, index + 1, '0');
    create_code_table(t->right, code_table, buffer, index + 1, '1');
  }


}

prioqueue *create_pq() {
  prioqueue *q = (prioqueue*)malloc(sizeof(prioqueue));
  q->first = NULL;
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

node *remove_min_pq(prioqueue *q){
    assert(q->size > 0);
    link *tmp;
    if(q->first == NULL)
        return NULL;
    node *n = q->first->node;
    tmp = q->first;
    q->first = q->first->next;
    free(tmp);  
    q->size--;  
    return n;
}

void display_infix_word(node *t){
 if(t==NULL){
    return;
  }
  display_infix_word(t->left);
  printf("%d\n",t->freq);
  display_infix_word(t->right);
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

void insert_pq(prioqueue *q, node *t){
  link *new_link = (link*)malloc(sizeof(link));
  new_link->node = t;
  new_link->next = NULL;

/* Cas 1 : Insertion dans une liste null*/
    if(q->size == 0){
        new_link->next =  q->first;
        q->first = new_link;
        q->size++;
        return;
    }
     
/* Cas 2 : Insertion en début de liste */
    if(q->first->node->freq >= t->freq){
        new_link->next = q->first;
        q->first = new_link;
        q->size++;
        return; 
    }

    link *pred= q->first;
    link *ptr = pred->next;
/* Cas 3 Recherche de la bonne position*/
    while (ptr !=NULL && ptr->node->freq < t->freq) {
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

void free_code_table(char *code_table[], int frequency[], int size){
  int i;
  for(i=0;i<size;i++)
    if(frequency[i] > 0)
      free(code_table[i]);
}

void free_pq(prioqueue *q){
  free(q->first);
  free(q);
}