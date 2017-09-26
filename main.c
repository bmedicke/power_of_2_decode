#include <stdlib.h> // return value makros.
#include <stdio.h>

#include "decode.h"

#define CHUNKSIZE 16
#define DEBUG 0
#define FILENAME "in" // TODO: read filename from argv.


int main(int argc, char *argv[]) {
  char buffer[CHUNKSIZE];
  FILE* file;

  const char* filemode = "r";
  file = fopen(FILENAME, filemode);

  if (file) {
    // read until EOF:
    while (fread(buffer, 1, sizeof buffer, file) > 0) {
      unsigned int encoded_char = strtoul(buffer, NULL, 2);
      if (DEBUG){
        verbose_decode(encoded_char, buffer);
      } else {
        char decoded_char = decode(encoded_char);
        printf("%c", decoded_char);
      }
    }
  }

  fclose(file);
  return EXIT_SUCCESS;
}

