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


#include <stdio.h> // printf(), FILE.
#include <stdlib.h> // return value macros, malloc.
#include <unistd.h> // getopt.
#include <stdbool.h> // booleans.

#include "helpers.h" // print_manual(), write_decoded_text().

/** @brief the main entry point  */

int main(int argc, char *argv[]) {
  _Bool verbose = 0; // verbosity switch.

  // filenames:
  char *encoded_file = NULL;
  char *decoded_file = NULL;
  char *statistic_file = NULL;

  // file descriptors:
  FILE *encoded_fd;
  FILE *decoded_fd;
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
        encoded_file = optarg;
        break;
      case 'o': // file to write decoded message to:
        decoded_file = optarg;
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
  if (encoded_file == NULL || decoded_file == NULL || statistic_file == NULL) {
    print_manual();
    return EXIT_FAILURE;
  }

  encoded_fd = fopen(encoded_file, "r"); // read from file.
  decoded_fd = fopen(decoded_file, "w"); // write to file.
  statistic_fd = fopen(statistic_file, "w"); // write to file.

  if (encoded_fd && decoded_fd &&
      write_decoded_text(encoded_fd, decoded_fd, verbose)) {
    // TODO: that's a bit sketchy.
  } else { // wrong encoded or decoded file.
    print_manual();
    return EXIT_FAILURE;
  }

  // close decoded and reopen it for reading:
  fclose(decoded_fd);
  decoded_fd = fopen(decoded_file, "r");

  if (write_statistics(decoded_fd, statistic_fd, verbose)){
    // TODO: that's a bit sketchy as well.
  } else {
    print_manual();
    return EXIT_FAILURE;
  }

  // clean up after ourselves:
  fclose(encoded_fd);
  fclose(decoded_fd);
  fclose(statistic_fd);
  return EXIT_SUCCESS;
}

