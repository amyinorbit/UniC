//===--------------------------------------------------------------------------------------------===
// unic.h - UniC - basic unicode functionality for C programs
// This source is part of UniC
//
// Created on 2019-06-29 by Amy Parent <amy@amyparent.com>
// Copyright (c) 2018 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#ifndef unicode_unicode_h
#define unicode_unicode_h
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef uint32_t unicode_scalar_t;
typedef struct unicode_grapheme_t unicode_grapheme_t;

struct unicode_grapheme_t {
    const char* start;
    const char* end;
};

unicode_scalar_t unicode_utf8_read(const char* data, size_t length, uint8_t* size);
const char* unicode_utf8_next(const char* data, size_t length);
int8_t unicode_utf8_write(unicode_scalar_t scalar, char* data, size_t length);
int8_t unicode_utf8_size(unicode_scalar_t scalar);

bool unicode_should_break(unicode_scalar_t lhs, unicode_scalar_t rhs);

size_t unicode_count_scalars(const char* string, size_t length);
size_t unicode_count_graphemes(const char* string, size_t length);

bool unicode_is_private(unicode_scalar_t scalar);
bool unicode_is_combining(unicode_scalar_t scalar);
bool unicode_is_bmp(unicode_scalar_t scalar);
bool unicode_is_whitespace(unicode_scalar_t scalar);
bool unicode_is_identifier_head(unicode_scalar_t scalar);
bool unicode_is_identifier(unicode_scalar_t scalar);
bool unicode_is_operator(unicode_scalar_t scalar);
bool unicode_is_quoted_item(unicode_scalar_t scalar);

#endif
