//===--------------------------------------------------------------------------------------------===
// unic.h - UniC - basic unicode functionality for C programs
// This source is part of UniC
//
// Created on 2019-06-29 by Amy Parent <amy@amyparent.com>
// Copyright (c) 2018 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#ifndef unic_unic_h
#define unic_unic_h
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef uint32_t UnicodeScalar;
typedef struct sUnicodeGrapheme UnicodeGrapheme;

struct sUnicodeGrapheme {
    const char* start;
    const char* end;
};

UnicodeScalar unic_utf8Get(const char* data, size_t length);
int8_t unic_utf8Write(UnicodeScalar scalar, char* data, size_t length);
int8_t unit_utf8Size(UnicodeScalar scalar);

bool unic_shouldBreak(UnicodeScalar lhs, UnicodeScalar rhs);

bool unic_isPrivate(UnicodeScalar scalar);
bool unic_isCombining(UnicodeScalar scalar);
bool unic_isBMP(UnicodeScalar scalar);
bool unic_isWhitespace(UnicodeScalar scalar);
bool unic_isIdentifierHead(UnicodeScalar scalar);
bool unic_isIdentifier(UnicodeScalar scalar);
bool unic_isOperator(UnicodeScalar scalar);
bool unic_isQuotedItem(UnicodeScalar scalar);

#endif