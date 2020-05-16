#include "tree.h"
#include "visualtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void encode_file(char *code_table[], FILE *infile, FILE *outfile){
    char c;
    while((c = getc(infile)) != EOF)
        fprintf(outfile, "%s ", code_table[(int) c]);
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

    node *n = NULL;
    n = read_tree(fin);

    write_tree(n);

    char *code_table[256];
    code_table[97] = "0";
    code_table[98] = "10";
    code_table[99] = "1100";
    code_table[100] = "1101";
    code_table[114] = "111";

    char *str = "abracadabra";

    int pos[100]; 
    tab(n,0, pos);
    rewind(fin);
    encode_file(pos, fin, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}