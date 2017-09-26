#include <stdio.h> // printf().
#include <stdlib.h> // return value macros.
#include <unistd.h> // getopt.

#include "decode.h" // decode(), verbose_decode().
#include "helpers.h" // print_manual().

#define CHUNKSIZE 16
#define DEBUG 0

int main(int argc, char *argv[]) {
  char buffer[CHUNKSIZE];
  FILE* file;
  int option = 0; // getopt.
  char* input_file = "";

  // handle options and arguments:
  while ((option = getopt(argc, argv, "hi:o:s:")) != -1) {
    switch (option) {
      case 'h':
        print_manual();
        return EXIT_SUCCESS;
        break;
      case 'i':
        input_file = optarg;
        break;
      default:
        print_manual();
        return EXIT_FAILURE;
    }
  }

  const char* filemode = "r";
  file = fopen(input_file, filemode);

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
  }  else { // wrong input file.
    print_manual();
    return EXIT_FAILURE;
  }

  fclose(file);
  return EXIT_SUCCESS;
}

