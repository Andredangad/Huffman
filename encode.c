#include "tree.h"
#include "visualtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256

void init_array(int array[], int size){
    int i;
    for(i =0; i<size;i++)
        array[i] = 0;
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
        fprintf(outfile, "%s", code_table[(unsigned char)c]);
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
    int frequency[ASCII_SIZE];
    init_array(frequency, ASCII_SIZE);
    int nb_char = 0;
    nb_char = create_frequency_array(fin, frequency);

    /* Create the Huffman tree */
    prioqueue *q = create_pq();
    int i;

    node *t = NULL;
    for(i=0;i<ASCII_SIZE;i++){
        if(frequency[i] != 0){
            node *t = create_node(i);
            t->freq = frequency[i];
            insert_pq(q,t);
        }
    }

    t = huffman(q,t);

    /* Print the Huffman tree to the file */
    print_tree(t, fout);
    fprintf(fout,"-1");

    /* Encode the file with the Huffman tree */
    char *code_table[ASCII_SIZE];
    char* buffer = (char*)malloc(100*sizeof(char));
    memset(buffer,0,100);
    create_code_table(t,code_table, buffer, 0, '0');
    free(buffer);
    int te;


    /* Print the number of encoded characters */
    fprintf(fout,"\n%d\n",nb_char);

    /* Print the encoded words to the file */
    rewind(fin);
    print_encoded_file(code_table, fin, fout);

    /* Close the FILE pointers */
    fclose(fin);
    fclose(fout);
  /*   free(pos); */
    free_pq(q);
    free_tree(t);
    free_code_table(code_table, frequency, ASCII_SIZE);
    return 0;
}