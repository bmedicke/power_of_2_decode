/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/

/**
 * \file
 * @brief The decode program.

 * This program is used to decode texts encrypted in the following fashion:\n
 * `ASCII * 2^[rand 0-8]` for each character.\n
 * Valid characters are uppercase A-Z plus space.
 */


#include <stdio.h> // printf().
#include <stdlib.h> // return value macros, malloc.
#include <unistd.h> // getopt.
#include <string.h> // strlen().
#include <stdbool.h> // booleans.

#include "decode.h" // decode_character(), verbose_decode().
#include "helpers.h" // print_manual().

/** @brief Size of each encoded character in bits */
#define CHUNKSIZE 16

/** @brief the main entry point  */

int main(int argc, char *argv[]) {
  char buffer[CHUNKSIZE];
  _Bool verbose = 0; // verbosity switch.

  // filenames:
  char *input_file = NULL;
  char *output_file = NULL;
  char *statistic_file = NULL;

  // file descriptors:
  FILE *input_fd;
  FILE *output_fd;
  FILE *statistic_fd;

  // handle options and their arguments:
  int option = 0;
  while ((option = getopt(argc, argv, "hvi:o:s:")) != -1) {
    switch (option) {
      case 'h': // print the manual:
        print_manual();
        return EXIT_SUCCESS;
      case 'v': // be more verbose for debugging:
        verbose = 1;
        break;
      case 'i': // file to read from:
        input_file = optarg;
        break;
      case 'o': // file to write decoded message to:
        output_file = optarg;
        break;
      case 's': // file to save statistics to:
        statistic_file = optarg;
        break;
      default: // clarify usage:
        print_manual();
        return EXIT_FAILURE;
    }
  }

// abort when critical options are missing or incomplete:
  if (input_file == NULL || output_file == NULL || statistic_file == NULL) {
    print_manual();
    return EXIT_FAILURE;
  }

  input_fd = fopen(input_file, "r"); // read from file.
  output_fd = fopen(output_file, "w"); // write to file.
  statistic_fd = fopen(statistic_file, "w"); // write to file.

  // TODO: extract this block to a function.
  if (input_fd) {
    // read until EOF:
    while (fread(buffer, 1, sizeof buffer, input_fd) > 0) {
      unsigned long encoded_char = strtoul(buffer, NULL, 2);
      if (verbose) {
        verbose_decode(encoded_char, buffer);
      }
      char decoded_char = decode_character(encoded_char);
      fprintf(output_fd, "%c", decoded_char);
    }
  }  else { // wrong input file.
    print_manual();
    return EXIT_FAILURE;
  }

  // close output and reopen it for reading:
  fclose(output_fd);
  output_fd = fopen(output_file, "r");

  // TODO: extract this block to a function.
  unsigned long wordcount = 0;
  if (output_fd) {
    char word[100];

    // count total words.
    while (fscanf(output_fd, "%s", word) == 1) {
      wordcount++;
    }

    // create dynamic array with 'wordcount' pointers to strings:
    char **words;
    words = malloc(wordcount * sizeof(char *)); // MALLOC! -- 1

    rewind(output_fd);
    for (int i = 0; fscanf(output_fd, "%s", word) == 1; i++) {
      // create dynamic char array to hold the current word:
      words[i] = malloc(strlen(word) + 1); // MALLOC! --2
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

  // clean up after ourselves:
  fclose(input_fd);
  fclose(output_fd);
  fclose(statistic_fd);
  return EXIT_SUCCESS;
}

