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
    node *n = create_node(' ',0);    
    if(c == '0')
      n = create_node(getc(infile),0);
    else{
      n->left = read_tree(infile);
      n->right = read_tree(infile);
    }
    return n;
}

void init_array(int array[], int size){
    int i;
    for(i =0; i<size;i++)
        array[i] = 0;
}

void print_array(int array[], int size){
    int i;
    for(i =0; i<size;i++)
        printf("%d : %d\n", i, array[i]);
}

void create_frequency_array(FILE *infile, int frequency[]){
    char c;
    while((c = getc(infile)) != EOF)
        frequency[(unsigned char) c] = frequency[(unsigned char) c] +1;
}

void encode_file(char *code_table[], FILE *infile, FILE *outfile){
    char c;
    while((c = getc(infile)) != EOF)
        fprintf(outfile, "%s ", code_table[(unsigned char) c]);
}

int main(int argc, char **argv) {
    char *code_table[256];
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

    FILE *ftree = fopen("files/tree.txt", "r");
    if (ftree == NULL) {
        fprintf(stderr, "Error opening file for reading: %s\n", "files/tree.txt");
        return 1;
    }

    int frequency[256];
    init_array(frequency, 256);
    create_frequency_array(fin, frequency);
    print_array(frequency, 256);
    prioqueue *q = create_pq();
    int i;




    
    for(i=0;i<256;i++){
        if(frequency[i] != 0){
            node *t = create_node(i, frequency[i]);
            insert_pq(q,t);
        }

    }

  
    
    node *p =NULL;
    p = huffman(q,p);
    /* display_infix_word(p); */
    write_tree(p);

    node *n = NULL;
    n = read_tree(ftree);
   /*  write_tree(n); */

    char pos[100]; 
    
    tab(n,0, pos, code_table);
   
    rewind(fin);
    encode_file(code_table, fin, fout);
    fclose(fin);
    fclose(fout);
    fclose(ftree);
    return 0;
}