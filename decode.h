/*************************************
*  Copyright (C) Benjamin Medicke
*  All rights reserved.
*  MIT License
**************************************/

/**
 * \file
 * @brief functions pertaining to decoding encrypeted text
 */

#ifndef DECODE_HEADER
#define DECODE_HEADER

/** @brief decode one character */
char decode_character(unsigned long encoded_char);

/** @brief print information about the decoding process of one character */
void verbose_decode(unsigned long encoded_char, char *buffer);

#endif

