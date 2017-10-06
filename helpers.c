/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/

#include <stdio.h> // printf.

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

