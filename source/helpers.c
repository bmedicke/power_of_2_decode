/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/

/**
 * \file
 */

#include <stdio.h> // printf, fprinf, FILE.
#include <stdbool.h> // booleans.
#include <stdlib.h> // strtoul, malloc/free.
#include <string.h> // strlen().

#include "helpers.h"
#include "decode.h" // decode_character()
#include "khash.h" // for a hashmap.

// create hashmap with str as keys and int as values:
KHASH_MAP_INIT_STR(known_words, unsigned int)

/** @brief Size of each encoded character in bits */
#define CHUNKSIZE 16

/**
 * @brief Size of longest possible word
 * @warning splits words if set too low.
 * @note Can be set to 1 to count characters
 */
#define MAXWORDSIZE 100

/** @brief stringification macro, used to insert macros into strings  */
#define STR(x) STR2(x)

/**
 * @brief stringification macro, used by STR() to reliably expand
 * @warning don't use directly, use STR() instead
 */
#define STR2(x) #x

void print_manual(void) {
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
  char word[MAXWORDSIZE + 1]; // 1 extra char for \0.
  while (fscanf(fd, "%" STR(MAXWORDSIZE) "s", word) == 1) {
    wordcount++;
  }
  return wordcount;
}

_Bool write_decoded_text(FILE *encoded_fd, FILE *decoded_fd, _Bool verbose) {
  if (!encoded_fd || !decoded_fd) {
    printf("Invalid files!\n");
    return false;
  } else {
    char buffer[CHUNKSIZE + 1]; // CHUNK + NUL.
    // read until EOF:
    while (fread(buffer, 1, CHUNKSIZE, encoded_fd) > 0) {
      buffer[CHUNKSIZE] = '\0';
      unsigned long encoded_char = strtoul(buffer, NULL, 2);
      char decoded_char = decode_character(encoded_char, buffer, verbose);
      if (decoded_char == -1) {
        printf("Decode failed! Make sure to use a valid input file.\n");
        return false;
      }
      fprintf(decoded_fd, "%c", decoded_char);
    }
  }
  return true;
}

_Bool write_statistics(FILE *decoded_fd, FILE *statistic_fd, _Bool verbose) {
  if (!decoded_fd || !statistic_fd) {
    printf("Invalid files!\n");
    return false;
  } else {
    unsigned long total_wordcount = count_words(decoded_fd);
    rewind(decoded_fd);

    if (total_wordcount == 0) {
      printf("No words found!\n");
      return false;
    }

    // create dynamic array with 'total_wordcount' pointers to strings:
    char **words;
    words = malloc(total_wordcount * sizeof(char *));

    char word[MAXWORDSIZE + 1]; // 1 extra char for \0.
    for (unsigned int i = 0; fscanf(decoded_fd, "%" STR(MAXWORDSIZE) "s", word) == 1; i++) {
      // create dynamic char array to hold the current word:
      words[i] = malloc(sizeof(word));
      strcpy(words[i], word);
      if (verbose) {
        printf("malloc >> [%i] %s - %lu\n", i, words[i], strlen(words[i]));
      }
    }

    int key_is_new;
    khint_t known_words_it; // hash map iterator.
    khash_t(known_words) *known_words_ptr; // hash map pointer.
    known_words_ptr = kh_init(known_words); // initialize the hash map.

    unsigned int max_wordcount = 0;
    for (unsigned int i = 0; i < total_wordcount; i++) {
      unsigned int count = 0;

      for (unsigned int j = 0; j < total_wordcount; j++) {
        if (strcmp(words[j], words[i]) == 0) {
          count++;
        }
      }

      // put current word into hashmap (if not already present):
      kh_put(known_words, known_words_ptr, words[i], &key_is_new);

      // if we encountered the word for the first time update the count:
      if (key_is_new) {
        known_words_it = kh_get(known_words, known_words_ptr, words[i]);
        kh_value(known_words_ptr, known_words_it) = count;
      }

      // keep track of the count of the highest occurring word to make sorting easier:
      if (max_wordcount < count) {
        max_wordcount = count;
      }
    }

    if (verbose) {
      printf("info >> Total wordcount: %lu\n", total_wordcount);
      printf("info >> Number of unique words: %i\n", kh_size(known_words_ptr));
      printf("info >> Highest wordcount: %i\n", max_wordcount);
    }

    // write words ordered descendingly by occurrences:
    while (max_wordcount > 0) {
      for (known_words_it = kh_begin(known_words_ptr);
           known_words_it != kh_end(known_words_ptr);
           ++known_words_it) {
        if (kh_exist(known_words_ptr, known_words_it)) {
          unsigned int count = kh_val(known_words_ptr, known_words_it);
          const char *current_word = kh_key(known_words_ptr, known_words_it);
          if (max_wordcount == count) {
            fprintf(statistic_fd, "%s: %i\n", current_word, count);
          }
        }
      }
      max_wordcount--;
    }

    // free memory of the words array elements:
    for (unsigned long i = 0; i < total_wordcount; i++) {
      free(words[i]);
    }

    free(words); // free memory of the words array itself.
    kh_destroy(known_words, known_words_ptr); // free memory of the hash map.

  }
  return true;
}

_Bool print_file(FILE *fd) {
  if (!fd) {
    printf("Error reading file!\n");
    return false;
  } else {
    char c;
    while ((c = (char)fgetc(fd)) != EOF) {
      printf("%c", c);
    }
  }
  return true;
}

