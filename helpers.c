/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/

#include <stdio.h> // printf, FILE.
#include <stdbool.h> // booleans.
#include <stdlib.h> // strtoul.
#include <string.h> // strlen().

#include "decode.h" // decode_character(), verbose_decode().

/** @brief Size of each encoded character in bits */
#define CHUNKSIZE 16

void print_manual() {
  printf( "Required arguemtns:\n"
          "\t-i <encoded input file>\n"
          "\t-o <decoded output file for decoded string>\n"
          "\t-s <file for statistics>\n"
          "Optional:\n"
          "\t-v verbose debug output\n"
          "You can also use -h to see this message.\n"
        );
}

_Bool write_decoded_text(FILE *encoded_fd, FILE *decoded_fd, _Bool verbose) {
  char buffer[CHUNKSIZE];
  // read until EOF:
  while (fread(buffer, 1, sizeof buffer, encoded_fd) > 0) {
    unsigned long encoded_char = strtoul(buffer, NULL, 2);
    if (verbose) {
      verbose_decode(encoded_char, buffer);
    }
    char decoded_char = decode_character(encoded_char);
    fprintf(decoded_fd, "%c", decoded_char);
  }
  return true; // TODO: add error handling.
}

 _Bool write_statistics(FILE *decoded_fd, FILE *statistic_fd, _Bool verbose) {
  unsigned long wordcount = 0;
  if (decoded_fd) {
    char word[100];

    // count total words.
    while (fscanf(decoded_fd, "%s", word) == 1) {
      wordcount++;
    }

    // create dynamic array with 'wordcount' pointers to strings:
    char **words;
    words = malloc(wordcount * sizeof(char *)); // MALLOC! -- 1

    rewind(decoded_fd);
    for (int i = 0; fscanf(decoded_fd, "%s", word) == 1; i++) {
      // create dynamic char array to hold the current word:
      words[i] = malloc(strlen(word) + 1); // MALLOC! -- 2
      strcpy(words[i], word);
      if (verbose) {
        printf("[%i] %s - %lu\n", i, words[i], strlen(words[i]));
      }
    }

    for (unsigned long i = 0; i < wordcount; i++) {
      printf("%s ", words[i]);
    }

    // free memory for the elements of the words array:
    for (unsigned long i = 0; i < wordcount; i++) {
      free(words[i]); // FREE! -- 2
    }

    // free memory for the words array itself:
    free(words); // FREE! -- 1
  }
   return true; // TODO: add error handling.
 }
