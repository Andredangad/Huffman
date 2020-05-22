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
    node *n = create_node(EOF,0);    
    if(c == '0')
      n = create_node(getc(infile),0);
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

void init_array(int array[], int size){
    int i;
    for(i =0; i<size;i++)
        array[i] = 0;
}

void print_array(int array[], int size){
    int i;
    for(i =0; i<size;i++)
        if(array[i] != 0)
        printf("%d : %d\n", i, array[i]);
}

int create_frequency_array(FILE *infile, int frequency[]){
    char c;
    int nb_char = 0;
    while((c = getc(infile)) != EOF){
        frequency[(unsigned char) c] = frequency[(unsigned char) c] +1;
        nb_char++;
    }
    return nb_char;
}

void print_encoded_file(char *code_table[], FILE *infile, FILE *outfile){
    char c;
    while((c = getc(infile)) != EOF)
        fprintf(outfile, "%s ", code_table[(unsigned char)c]);
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

    /* Create the frequency array */
    int frequency[256];
    init_array(frequency, 256);
    int nb_char = 0;
    nb_char = create_frequency_array(fin, frequency);

    /* Create the Huffman tree */
    prioqueue *q = create_pq();
    int i;

    node *t = NULL;
    for(i=0;i<256;i++){
        if(frequency[i] != 0){
            node *t = create_node(i, frequency[i]);
            insert_pq(q,t);
        }
    }
    
    display_pq(q);
    t = huffman(q,t);

    display_pq(q);

    write_tree(t);
    /* Print the Huffman tree to the file */
    print_tree(t, fout);
    
    /* Encode the file with the Huffman tree */
    char *code_table[256];
    char pos[100]; 
    
    create_code_table(t,0, pos, code_table);

    /* Print the number of encoded characters */
    fprintf(fout,"\n%d\n",nb_char);

    /* Print the encoded words to the file */
    rewind(fin);
    print_encoded_file(code_table, fin, fout);

    /* Close the FILE pointers */
    fclose(fin);
    fclose(fout);
    free_pq(q);
    free_tree(t);
    free_code_table(code_table, frequency);
    return 0;
}