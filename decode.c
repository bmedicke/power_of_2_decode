#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // 16 bit int type.

#define CHUNK 16
#define FILENAME "in"

// 65 - 90
// 32 space?
int main(int argc, char *argv[])
{
  char buffer[CHUNK];
  uint16_t coded_num;
  FILE *file;
  size_t result;

  file = fopen(FILENAME, "r");
  if (file)
  {
    for (int i = 0; i < 50; i++)
    {
      result = fread(buffer, 1, sizeof buffer, file);
      coded_num = strtoul(buffer, NULL, 2);

      for (int cipher = 1; cipher < 512; cipher *= 2){
        int test_case = coded_num / cipher;
        if ((test_case <= 90 && test_case >= 65) || test_case == 32){
          printf("%.16s\t%i\t%c\t%i\n",
                 buffer, coded_num/cipher,
                 (char)(coded_num/cipher), cipher);
          break;
        }
      }
    }
  }
  return 0;
}

