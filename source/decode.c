/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/

/*
 * \file
 */

#include <stdio.h>
#include "decode.h"

char decode_character(unsigned long encoded_char, char *buffer,
                      _Bool verbose) {
  // try decoding with cipher 2^0 to 2^8:
  for (unsigned int cipher = 1; cipher <= 256; cipher <<= 1) {
    unsigned long test_case = encoded_char / cipher;

    // looking for ASCII: 65(A) - 90(Z) + 32(space):
    if ((test_case >= 65 && test_case <= 90) || test_case == 32) {
      if (verbose) {
        printf("decode >> %.16s\t%lu\t%d\t%c\n",
               buffer, encoded_char, cipher, (char)test_case);
      }
      return (char)test_case;
    }
  }

  return -1;
}
