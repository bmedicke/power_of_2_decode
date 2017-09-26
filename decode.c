#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // for 16bit uint.

#define CHUNKSIZE 16
#define FILENAME "in"

int main(int argc, char *argv[]) {
  char buffer[CHUNKSIZE];
  uint16_t encoded_char;
  FILE* file;

  const char* filemode = "r";
  file = fopen(FILENAME, filemode);

  if (file) {
    for (int i = 0; i < 50; i++) {
      fread(buffer, 1, sizeof buffer, file);
      encoded_char = strtoul(buffer, NULL, 2);

      // try decoding with cipher 2^0 to 2^8:
      for (int cipher = 1; cipher <= 256; cipher *= 2){
        int test_case = encoded_char / cipher;

        // expecting ASCII: 65(A) - 90(Z) + 32(space):
        if ((test_case <= 90 && test_case >= 65) || test_case == 32){
          printf("%.16s\t%i\t%c\t%i\n",
              buffer, encoded_char/cipher,
              (char)(encoded_char/cipher), cipher);
          break; // cipher found, skipping to next chunk.
        }
      }
    }
  }
  return 0;
}

