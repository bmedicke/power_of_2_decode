#include <stdio.h> // printf().
#include <stdlib.h> // return value macros.
#include <unistd.h> // getopt.

#include "decode.h" // decode(), verbose_decode().
#include "helpers.h" // print_manual().

#define CHUNKSIZE 16

int main(int argc, char *argv[]) {
  char buffer[CHUNKSIZE];

  int option = 0; // getopt.
  int verbose = 0;

  // file descriptors:
  FILE* input_fd;
  FILE* output_fd;
  FILE* statistic_fd;

  // filenames:
  char* input_file = NULL;
  char* output_file = NULL;
  char* statistic_file = NULL;

  // handle options and their arguments:
  while ((option = getopt(argc, argv, "hvi:o:s:")) != -1) {
    switch (option) {
      case 'h': // print the manual:
        print_manual();
        return EXIT_SUCCESS;
        break;
      case 'v': // be more verbose for debugging:
        verbose = 1;
        break;
      case 'i': // file to read from:
        input_file = optarg;
        break;
      case 's': // file to save statistics to:
        statistic_file = optarg;
        break;
      case 'o': // file to write decoded message to:
        output_file = optarg;
        break;
      default: // clarify usage:
        print_manual();
        return EXIT_FAILURE;
    }
  }

if (input_file == NULL || output_file == NULL || statistic_file == NULL) {
    print_manual();
    return EXIT_FAILURE;
  }

  input_fd = fopen(input_file, "r"); // read from file.
  output_fd = fopen(output_file, "w"); // write to file.
  statistic_fd = fopen(statistic_file, "w"); // write to file.

  if (input_fd) {
    // read until EOF:
    while (fread(buffer, 1, sizeof buffer, input_fd) > 0) {
      unsigned int encoded_char = strtoul(buffer, NULL, 2);
      if (verbose){
        verbose_decode(encoded_char, buffer);
      }
      char decoded_char = decode(encoded_char);
      fprintf(output_fd, "%c", decoded_char);
    }
  }  else { // wrong input file.
    print_manual();
    return EXIT_FAILURE;
  }

  // clean up after ourselves:
  fclose(input_fd);
  fclose(output_fd);
  fclose(statistic_fd);
  return EXIT_SUCCESS;
}

