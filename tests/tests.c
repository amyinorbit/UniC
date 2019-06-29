//===--------------------------------------------------------------------------------------------===
// tests_vm.c - UniC unit test suite
// This source is part of UniC
//
// Created on 2019-06-29 by Amy Parent <amy@amyparent.com>
// Copyright (c) 2018 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===

#include <stdio.h>
#include <string.h>
#include <unic/unic.h>
#include "unity.h"

void utf8_decode() {
    const char string[] = "😭";
    
    uint8_t size = 0;
    UnicodeScalar scalar = unic_utf8Read(string, sizeof(string), &size);
    TEST_ASSERT_EQUAL_UINT8(4, size);
    TEST_ASSERT_EQUAL_HEX32(0x1F62D, scalar);
}

void utf8_encode() {
    UnicodeScalar scalar = 0x1F62D;
    char string[8];
    int size = unic_utf8Write(scalar, string, 8);
    
    TEST_ASSERT_EQUAL(4, size);
    TEST_ASSERT_EQUAL_MEMORY("😭", string, 4);
}

typedef struct {const char* string; size_t size; } StringData;

void utf8_graphemes() {
    static const StringData strings[] = {
        {"Hello, world", 12},
        {"民ねざルず禁許や能", 9},
        {"🇬🇧🏴󠁧󠁢󠁳󠁣󠁴󠁿🏳️‍🌈😏", 4}
    };
    
    static const size_t count = sizeof(strings)/sizeof(StringData);
    
    for(size_t i = 0; i < count; ++i) {
        StringData data = strings[i];
        size_t size = unic_countGraphemes(data.string, strlen(data.string));
        TEST_ASSERT_EQUAL(data.size, size);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(utf8_decode);
    RUN_TEST(utf8_encode);
    RUN_TEST(utf8_graphemes);
    return UNITY_END();
}
