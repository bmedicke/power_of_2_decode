#include <stdlib.h> // return value makros.
#include <stdio.h>
#include <stdint.h> // for 16bit uint.

#include "decode.h"

#define CHUNKSIZE 16
#define FILENAME "in" // TODO: read filename from argv.


int main(int argc, char *argv[]) {
  char buffer[CHUNKSIZE];
  FILE* file;

  const char* filemode = "r";
  file = fopen(FILENAME, filemode);

  if (file) {
    // TODO: calculate number of chunks from filesize.
    for (int i = 0; i < 30; i++) {
      fread(buffer, 1, sizeof buffer, file);
      uint16_t encoded_char = strtoul(buffer, NULL, 2);
      char decoded_char = decode(encoded_char);
      printf("%c", decoded_char);
      /* printf("%i\t%c\t%i\n", test_case, (char)(test_case), cipher); */
    }
  }
  fclose(file);
  return EXIT_SUCCESS;
}

