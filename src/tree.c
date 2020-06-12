#include "../headers/tree.h"
#include "../headers/prioqueue.h"
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
    code_table[a] = (char *)malloc(sizeof(char) * 30);
    strcpy(code_table[a], buffer);
  
  }
  else{
    create_code_table(t->left, code_table, buffer, index + 1, '0');
    create_code_table(t->right, code_table, buffer, index + 1, '1');
  }
}


void display_infix_word(node *t){
 if(t==NULL){
    return;
  }
  display_infix_word(t->left);
  printf("%d\n",t->freq);
  display_infix_word(t->right);
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

