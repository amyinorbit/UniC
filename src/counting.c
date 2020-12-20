//===--------------------------------------------------------------------------------------------===
// counting.c - Character & Scalar counting implementation
// This source is part of UniC
//
// Created on 2019-06-29 by Amy Parent <amy@amyparent.com>
// Copyright (c) 2018 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include <unic/unic.h>

size_t unicode_count_scalars(const char* string, size_t length) {
    if(!string || !length) return 0;
    const char* end = string + length;
    size_t count = 0;

    while(string < end) {
        const char* next = unicode_utf8_next(string, end - string);
        if(!next) return 0;
        count += 1;
        string = next;;
    }

    return count;
}

size_t unicode_count_graphemes(const char* string, size_t length) {
    if(!string || !length) return 0;
    const char* current = string;
    const char* end = string + length;
    size_t count = 0;

    unicode_scalar_t previous = 0x0;

    while(current < end) {
        size_t remaining = end - current;

        uint8_t size = 0;
        unicode_scalar_t scalar = unicode_utf8_read(current, remaining, &size);
        if(!size) return 0;

        if(unicode_should_break(previous, scalar)) count += 1;
        previous = scalar;
        current += size;
    }

    return count;
}
