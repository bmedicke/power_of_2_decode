/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/

/**
 * \file
 * @brief various helper functions
 */

#ifndef HELPERS_HEADER
#define HELPERS_HEADER

#include <stdbool.h> // booleans.
#include <stdio.h> // FILE.

/**
 * @brief inform user about proper usage of the program.
 */
void print_manual(void);

/**
 * @brief read encoded text and write decoded text to a file
 */
_Bool write_decoded_text(FILE *encoded_fd, FILE *decoded_fd, _Bool verbose);


/** @brief read decoded text and write statistics to a file */
_Bool write_statistics(FILE *decoded_fd, FILE *statistic_fd, _Bool verbose);

/**
 * @brief print statistics file to console
 * @warning does not rewind or restore the file descriptor!
 */
_Bool print_file(FILE *fd);

/**
 * @brief returns number of words in a file
 * @warning does not rewind or restore the file descriptor!
 */
unsigned long count_words(FILE *fd);

#endif

