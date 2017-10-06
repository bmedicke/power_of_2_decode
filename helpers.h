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

/** @brief inform user about proper usage of the program.  */
void print_manual(void);

/** @brief reads encoded and writes decoded text to a file */
_Bool write_decoded_text(FILE *input_fd, FILE *output_fd, _Bool verbose);
// TODO: make input_fd const?

#endif

