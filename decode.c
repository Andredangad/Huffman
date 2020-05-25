#include "tree.h"
#include "visualtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_in_tree(node *n, FILE *file){
  if(n == NULL)
  	return EOF;
  if(n->left == NULL && n->right == NULL){
    return n->data;
  }
  char c;
  if(fscanf(file,"%c",&c) == -1)
  	return EOF;
  if(c == '0')
  	return find_in_tree(n->left, file);
  return find_in_tree(n->right, file);
}

void print_decoded_file(node *n, FILE *fin, FILE *fout){
	char c;
    fscanf(fin, "%c",&c);
    while((c = getc(fin)) != '\n')
        getc(fin);
    while((c = find_in_tree(n, fin)) != EOF){
        fputc(c,fout);
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: concordance <in_file> <out_file>\n");
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        fprintf(stderr, "Error opening file for reading: %s\n", argv[1]);
        return 1;
    }

    FILE *fout = fopen(argv[2], "w");
    if (fout == NULL) {
        fprintf(stderr, "Error opening file for writing: %s\n", argv[2]);
        return 1;
    }

    /* Read the Huffman tree to decode */
    node *n = read_tree(fin);

    /* Print the decoded text */
    print_decoded_file(n, fin, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}