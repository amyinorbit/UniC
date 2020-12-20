//===--------------------------------------------------------------------------------------------===
// properties.h - Functions used to query basic properties of Unicode scalars
// This source is part of UniC
//
// Created on 2019-06-29 by Amy Parent <amy@amyparent.com>
// Copyright (c) 2018 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include <unic/unic.h>
#include <ctype.h>

#define IN_RANGE(val, lower, upper) ((val) >= (lower) && (val) <= (upper))

bool unicode_is_private(unicode_scalar_t scalar) {
    return IN_RANGE(scalar, 0xe000, 0x0f8ff)
        || IN_RANGE(scalar, 0xf0000, 0xfffff)
        || IN_RANGE(scalar, 0x100000, 0x10FFFF);
}

bool unicode_is_combining(unicode_scalar_t scalar) {
    return IN_RANGE(scalar, 0x0300, 0x036f);
}

bool unicode_is_bmp(unicode_scalar_t scalar) {
    return IN_RANGE(scalar, 0x000000, 0x100000) && !unicode_is_private(scalar);
}

bool unicode_is_whitespace(unicode_scalar_t scalar) {
    return scalar == 0x0000
        || scalar == 0x0020
        || scalar == 0x000d
        || scalar == 0x0009
        || scalar == 0x000b
        || scalar == 0x000c;
}

bool unicode_is_identifier_head(unicode_scalar_t scalar) {
    if(scalar < 0) { return false; }
    return (scalar <= 0x7f && (scalar == '_' || isalpha(scalar & 0x7f)))
        || (scalar == 0x00a8)
        || (scalar == 0x00aa)
        || (scalar == 0x00ad)
        || (scalar == 0x00af)
        || (scalar == 0x2054)
        || IN_RANGE(scalar, 0x00b2, 0x00b5)
        || IN_RANGE(scalar, 0x00b7, 0x00ba)
        || IN_RANGE(scalar, 0x00bc, 0x00be)
        || IN_RANGE(scalar, 0x00c0, 0x00d6)
        || IN_RANGE(scalar, 0x00d8, 0x00f6)
        || IN_RANGE(scalar, 0x00f8, 0x00ff)
        || IN_RANGE(scalar, 0x0100, 0x02ff)
        || IN_RANGE(scalar, 0x0370, 0x167f)
        || IN_RANGE(scalar, 0x1681, 0x180d)
        || IN_RANGE(scalar, 0x180f, 0x1dbf)
        || IN_RANGE(scalar, 0x1e00, 0x1fff)
        || IN_RANGE(scalar, 0x200b, 0x200d)
        || IN_RANGE(scalar, 0x202a, 0x202e)
        || IN_RANGE(scalar, 0x203f, 0x2040)
        || IN_RANGE(scalar, 0x2060, 0x206f)
        || IN_RANGE(scalar, 0x2070, 0x20cf)
        || IN_RANGE(scalar, 0x2100, 0x218f)
        || IN_RANGE(scalar, 0x2460, 0x24ff)
        || IN_RANGE(scalar, 0x2776, 0x2793)
        || IN_RANGE(scalar, 0x2c00, 0x2dff)
        || IN_RANGE(scalar, 0x2e80, 0x2fff)
        || IN_RANGE(scalar, 0x3004, 0x3007)
        || IN_RANGE(scalar, 0x3021, 0x302f)
        || IN_RANGE(scalar, 0x3031, 0x303f)
        || IN_RANGE(scalar, 0x3040, 0xd7ff)
        || IN_RANGE(scalar, 0xf900, 0xfd3d)
        || IN_RANGE(scalar, 0xfd40, 0xfdcf)
        || IN_RANGE(scalar, 0xfdf0, 0xfe1f)
        || IN_RANGE(scalar, 0xfe30, 0xfe44)
        || IN_RANGE(scalar, 0xfe47, 0xfffd)
        || IN_RANGE(scalar, 0x10000, 0x1fffd)
        || IN_RANGE(scalar, 0x20000, 0x2fffd)
        || IN_RANGE(scalar, 0x30000, 0x3fffd)
        || IN_RANGE(scalar, 0x40000, 0x4fffd)
        || IN_RANGE(scalar, 0x50000, 0x5fffd)
        || IN_RANGE(scalar, 0x60000, 0x6fffd)
        || IN_RANGE(scalar, 0x70000, 0x7fffd)
        || IN_RANGE(scalar, 0x80000, 0x8fffd)
        || IN_RANGE(scalar, 0x90000, 0x9fffd)
        || IN_RANGE(scalar, 0xa0000, 0xafffd)
        || IN_RANGE(scalar, 0xb0000, 0xbfffd)
        || IN_RANGE(scalar, 0xc0000, 0xcfffd)
        || IN_RANGE(scalar, 0xd0000, 0xdfffd)
        || IN_RANGE(scalar, 0xe0000, 0xefffd);
}

bool unicode_is_identifier(unicode_scalar_t scalar) {
    return unicode_is_identifier_head(scalar)
        || (scalar <= 0x7f && isdigit(scalar & 0x7f))
        || IN_RANGE(scalar, 0x0300, 0x036f)
        || IN_RANGE(scalar, 0x1dc0, 0x1dff)
        || IN_RANGE(scalar, 0x20d0, 0x20ff)
        || IN_RANGE(scalar, 0xfe20, 0xfe2f);
}

bool unicode_is_operator(unicode_scalar_t scalar) {
    if(scalar > 0x7f) { return false; }
    return (scalar & 0x7f) == '+'
        || (scalar & 0x7f) == '-'
        || (scalar & 0x7f) == '*'
        || (scalar & 0x7f) == '/'
        || (scalar & 0x7f) == '%'
        || (scalar & 0x7f) == '?'
        || (scalar & 0x7f) == '<'
        || (scalar & 0x7f) == '>'
        || (scalar & 0x7f) == '!'
        || (scalar & 0x7f) == '|'
        || (scalar & 0x7f) == '&'
        || (scalar & 0x7f) == '^'
        || (scalar & 0x7f) == '~';
}

bool unicode_is_quoted_item(unicode_scalar_t scalar) {
    if(scalar < 0 && scalar > 0x7f) { return false; }
    return scalar != '\\' && scalar != '"' && scalar != 0x0a && scalar != 0x0d;
}
