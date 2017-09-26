#include "decode.h"

char decode(unsigned int encoded_char) {
  // try decoding with cipher 2^0 to 2^8:
  for (int cipher = 1; cipher <= 256; cipher *= 2){
    int test_case = encoded_char / cipher;

    // expecting ASCII: 65(A) - 90(Z) + 32(space):
    if ((test_case >= 65 && test_case <= 90) || test_case == 32){
      return (char)test_case;
    }
  }
  return -1;
}
