/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/

#include <stdio.h> // printf, FILE.
#include <stdbool.h> // booleans.
#include <stdlib.h> // strtoul.

#include "decode.h" // decode_character(), verbose_decode().

/** @brief Size of each encoded character in bits */
#define CHUNKSIZE 16

void print_manual() {
  printf( "Required arguemtns:\n"
          "\t-i <encoded input file>\n"
          "\t-o <output file for decoded string>\n"
          "\t-s <file for statistics>\n"
          "Optional:\n"
          "\t-v verbose debug output\n"
          "You can also use -h to see this message.\n"
        );
}

_Bool write_decoded_text(FILE *input_fd, FILE *output_fd, _Bool verbose) {
  char buffer[CHUNKSIZE];
  // read until EOF:
  while (fread(buffer, 1, sizeof buffer, input_fd) > 0) {
    unsigned long encoded_char = strtoul(buffer, NULL, 2);
    if (verbose) {
      verbose_decode(encoded_char, buffer);
    }
    char decoded_char = decode_character(encoded_char);
    fprintf(output_fd, "%c", decoded_char);
  }
  return true; // TODO: add error handling.
}
