/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/

#include <stdio.h> // printf, fprinf, FILE.
#include <stdbool.h> // booleans.
#include <stdlib.h> // strtoul, malloc/free.
#include <string.h> // strlen().

#include "decode.h" // decode_character(), verbose_decode().

#include "3rdparty/khash.h" // for hashmap.

// create hashmap with str keys and int values:
KHASH_MAP_INIT_STR(known_words, int)

/** @brief Size of each encoded character in bits */
#define CHUNKSIZE 16

/** @brief Size of longest possible word */
#define MAXWORDSIZE 100
// TODO: don't make this constant.

void print_manual() {
  printf( "Required arguemtns:\n"
          "\t-i <encoded input file>\n"
          "\t-o <decoded output file for decoded string>\n"
          "\t-s <file for statistics>\n"
          "Optional:\n"
          "\t-v verbose debug output\n"
          "You can also use -h to see this message.\n"
        );
}

unsigned long count_words(FILE *fd) {
  unsigned long wordcount = 0;
  char word[MAXWORDSIZE];
  while (fscanf(fd, "%s", word) == 1) {
    wordcount++;
  }
  return wordcount;
}

_Bool write_decoded_text(FILE *encoded_fd, FILE *decoded_fd, _Bool verbose) {
  if (!encoded_fd || !decoded_fd) {
    return false;
  } else {
    char buffer[CHUNKSIZE];
    // read until EOF:
    while (fread(buffer, 1, sizeof buffer, encoded_fd) > 0) {
      unsigned long encoded_char = strtoul(buffer, NULL, 2);
      if (verbose) {
        verbose_decode(encoded_char, buffer);
      }
      char decoded_char = decode_character(encoded_char);
      fprintf(decoded_fd, "%c", decoded_char);
    }
  }
  return true; // TODO: add more error handling.
}

_Bool write_statistics(FILE *decoded_fd, FILE *statistic_fd, _Bool verbose) {
  if (!decoded_fd || !statistic_fd) {
    return false;
  } else {
    unsigned long total_wordcount = count_words(decoded_fd);
    rewind(decoded_fd);

    // create dynamic array with 'total_wordcount' pointers to strings:
    char **words;
    words = malloc(total_wordcount * sizeof(char *)); // MALLOC! -- 1

    char word[MAXWORDSIZE];
    for (int i = 0; fscanf(decoded_fd, "%s", word) == 1; i++) {
      // create dynamic char array to hold the current word:
      words[i] = malloc(strlen(word) + 1); // MALLOC! -- 2
      strcpy(words[i], word);
      if (verbose) {
        printf("[%i] %s - %lu\n", i, words[i], strlen(words[i]));
      }
    }

    int key_is_new;
    khint_t known_words_it; // hash map iterator.
    khash_t(known_words) *known_words_ptr; // hash map pointer.
    known_words_ptr = kh_init(known_words); // initialize hash map.

    int max_wordcount = 0;
    for (int i = 0; i < total_wordcount; i++) {
      int count = 0;

      for (int j = 0; j < total_wordcount; j++) {
        if (strcmp(words[j], words[i]) == 0) {
          count++;
        }
      }

      // put current word into hashmap (if not already present):
      known_words_it = kh_put(known_words, known_words_ptr, words[i], &key_is_new);

      // if we encountered the word for the first time update the count:
      if (key_is_new) {
        known_words_it = kh_get(known_words, known_words_ptr, words[i]);
        kh_value(known_words_ptr, known_words_it) = count;
      }

      // keep track of the count of the highest occuring word to make sorting easier:
      if (max_wordcount < count) {
        max_wordcount = count;
      }
    }

    if (verbose) {
      printf("Number of unique words: %i\n", kh_size(known_words_ptr)); 
      printf("Highest wordcount: %i\n", max_wordcount);
    }

    for (; max_wordcount > 0; max_wordcount--) {
      for (known_words_it = kh_begin(known_words_ptr);
          known_words_it != kh_end(known_words_ptr);
          ++known_words_it) {
        if (kh_exist(known_words_ptr, known_words_it)) {
          int val;
          const char* key;
          val = kh_val(known_words_ptr, known_words_it);
          key = kh_key(known_words_ptr, known_words_it);
          if (max_wordcount == val) {
            fprintf(statistic_fd, "%s: %i\n", key, val);
            printf("%s: %i\n", key, val);
          }
        }
      }
    }

    // free memory for the elements of the words array:
    for (unsigned long i = 0; i < total_wordcount; i++) {
      free(words[i]); // FREE! -- 2
    }

    // free memory for the words array itself:
    free(words); // FREE! -- 1

    // TODO: free hashmap.

  }
  return true; // TODO: add more error handling.
}

