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

size_t unic_countScalars(const char* string, size_t length) {
    if(!string || !length) return 0;
    const char* current = string;
    const char* end = string + length;
    size_t count = 0;
    
    while(current < end) {
        size_t remaining = end - current;
        
        uint8_t size = 0;
        unic_utf8Read(current, remaining, &size);
        if(!size) return 0;
        count += 1;
        current += size;
    }
    
    return count;
}

size_t unic_countGraphemes(const char* string, size_t length) {
    if(!string || !length) return 0;
    const char* current = string;
    const char* end = string + length;
    size_t count = 0;
    
    UnicodeScalar previous = 0x0;
    
    while(current < end) {
        size_t remaining = end - current;
        
        uint8_t size = 0;
        UnicodeScalar scalar = unic_utf8Read(current, remaining, &size);
        if(!size) return 0;
        
        if(unic_shouldBreak(previous, scalar)) count += 1;
        previous = scalar;
        current += size;
    }
    
    return count;
}
