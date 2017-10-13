#ifndef DECODE_HEADER
#define DECODE_HEADER
/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/
/**
 * \file
 * @brief functions pertaining to decoding encrypeted text
 */

/** @brief decode and optionally print information about the decoding process of one character */
char decode_character(unsigned long encoded_char, char *buffer, _Bool verbose);

#endif

