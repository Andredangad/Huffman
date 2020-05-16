#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*     node *p = NULL;


      node *p;
  int x;
  scanf("%d", &x);
  if(x == 0){
    return NULL;
  }
  p = create_node(x);

  p->left = scan_tree();
  p->right = scan_tree();

  return p; */

node *read_text(FILE *infile) {

     node *p;
  char c = getc(infile);
    p = create_node('a');
  if(c == EOF){
    
        return NULL;

  }
  if (c == '0'){

    p = create_node(c);

}
else{
  p->left = read_text(infile);
   p->right = read_text(infile);

}




 


  return p;

/*   node *t;
  if (c == '0'){

        c = getc(infile);
        t = create_node(c);
  
}




     while ((c = getc(infile))!= EOF) {
       
       if (c == '0'){

        c = getc(infile);
        create_node(c);
       }
       else if()
       printf("%c\n", c);

    } */

}




int main(int argc, char **argv) {
  node *p;
      if (argc < 2) {
        fprintf(stderr, "Usage: concordance <in_file>\n");
        return 1;
    }

      FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
        fprintf(stderr, "Error opening file for reading: %s\n", argv[1]);
        return 1;
    }
p = read_text(fin);
display_prefix(p);
write_tree(p);
  fclose(fin);
    

  return 0;
}
