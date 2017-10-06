/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/


#include <stdio.h>
#include "decode.h"

char decode_character(unsigned long encoded_char) {
  // try decoding with cipher 2^0 to 2^8:
  for (int cipher = 1; cipher <= 256; cipher *= 2) {
    int test_case = encoded_char / cipher;

    // expecting ASCII: 65(A) - 90(Z) + 32(space):
    if ((test_case >= 65 && test_case <= 90) || test_case == 32) {
      return (char)test_case;
    }
  }
  return -1;
}

void verbose_decode(unsigned long encoded_char, char *buffer) {
  // try decoding with cipher 2^0 to 2^8:
  for (int cipher = 1; cipher <= 256; cipher *= 2) {
    int test_case = encoded_char / cipher;

    // expecting ASCII: 65(A) - 90(Z) + 32(space):
    if ((test_case >= 65 && test_case <= 90) || test_case == 32) {
      printf("%.16s\t%lu\t%d\t%c\n",
             buffer, encoded_char, cipher, (char)test_case);
    }
  }
}

