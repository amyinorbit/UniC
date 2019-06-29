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

typedef uint32_t UnicodeScalar;
typedef struct sUnicodeGrapheme UnicodeGrapheme;

struct sUnicodeGrapheme {
    const char* start;
    const char* end;
};

bool shouldBreakBetween(UnicodeScalar lhs, UnicodeScalar rhs);

#endif