#include "tree.h"
#include "visualtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

node *read_tree(FILE *infile) {
    char c;
    if((c = getc(infile)) == EOF)
      return NULL;
    node *n = create_node(' ');    
    if(c == '0')
      n = create_node(getc(infile));
    else{
      n->left = read_tree(infile);
      n->right = read_tree(infile);
    }
    return n;
    
}

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Usage: concordance <in_file>\n");
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        fprintf(stderr, "Error opening file for reading: %s\n", argv[1]);
        return 1;
    }
    node *n = NULL;
    n = read_tree(fin);
    write_tree(n);
    char pos[100]; 
    tab(n,0, pos);
    fclose(fin);
    return 0;
}