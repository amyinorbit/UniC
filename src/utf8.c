//===--------------------------------------------------------------------------------------------===
// utf8.c - UTF-8 encoding/decoding from Unicode Scalars
// This source is part of UniC
//
// Created on 2019-06-29 by Amy Parent <amy@amyparent.com>
// Copyright (c) 2018 Amy Parent
// Licensed under the MIT License
// =^•.•^=
//===--------------------------------------------------------------------------------------------===
#include <unic/unic.h>

unicode_scalar_t unicode_utf8_read(const char* data, size_t length, uint8_t* size) {
    uint8_t remaining = 0;
    unicode_scalar_t scalar = 0;

    if((*data & 0x80) == 0x00) {
        *size = 1;
        return *data;
    }

    if((*data & 0xe0) == 0xc0) {
        scalar = *data & 0x1f;
        remaining = 1;
    }
    else if((*data & 0xf0) == 0xe0) {
        scalar = *data & 0x0f;
        remaining = 2;
    }
    else if((*data & 0xf8) == 0xf0) {
        scalar = *data & 0x07;
        remaining = 3;
    }
    else {
        goto fail;
    }

    if(remaining > length + 1) goto fail;
    *size = remaining + 1;

    while(remaining > 0) {
        data += 1;
        remaining -= 1;
        if((*data & 0xc0) != 0x80) goto fail;
        scalar = (scalar << 6) | (*data & 0x3f);
    }
    return scalar;

fail:
    *size = 0;
    return 0;
}

const char* unicode_utf8_next(const char* data, size_t length) {
    if((*data & 0x80) == 0x00) return (length > 0 ? data + 1 : NULL);
    if((*data & 0xe0) == 0xc0) return (length > 1 ? data + 2 : NULL);
    else if((*data & 0xf0) == 0xe0) return (length > 2 ? data + 3 : NULL);
    else if((*data & 0xf8) == 0xf0) return (length > 3 ? data + 4 : NULL);
    return NULL;
}

// 0x00000000 - 0x0000007F:
//        0xxxxxxx
//
// 0x00000080 - 0x000007FF:
//    110xxxxx 10xxxxxx
//
// 0x00000800 - 0x0000FFFF:
//    1110xxxx 10xxxxxx 10xxxxxx
//
// 0x00010000 - 0x001FFFFF:
//    11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//
// 0x00200000 - 0x03FFFFFF:
//    111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
//
// 0x04000000 - 0x7FFFFFFF:
//    1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
int8_t unicode_utf8_write(unicode_scalar_t scalar, char* data, size_t length) {

    int8_t size =  unicode_utf8_size(scalar);
    if(size < 0) { return -1; }
    if(size > length) { return -1; }

    switch(size) {
    case 1:
        data[0] = scalar & 0x0000007f;
        return 1;
        break;

    case 2:
        data[0] = 0xc0 | ((scalar & 0x000007c0) >> 6);
        data[1] = 0x80 | (scalar & 0x0000003f);
        return 2;
        break;

    case 3:
        data[0] = 0xe0 | ((scalar & 0x0000f000) >> 12);
        data[1] = 0x80 | ((scalar & 0x00000fc0) >> 6);
        data[2] = 0x80 | (scalar & 0x0000003f);
        return 3;
        break;

    case 4:
        data[0] = 0xf0 | ((scalar & 0x001c0000) >> 18);
        data[1] = 0x80 | ((scalar & 0x0003f000) >> 12);
        data[2] = 0x80 | ((scalar & 0x00000fc0) >> 6);
        data[3] = 0x80 | (scalar & 0x0000003f);
        return 4;
        break;

    default:
        break;
    }
    return -1;
}

int8_t unicode_utf8_size(unicode_scalar_t scalar) {
    if (scalar < 0) { return -1; }
    if (scalar <= 0x7f) { return 1; }
    if (scalar <= 0x7ff) { return 2; }
    if (scalar <= 0xffff) { return 3; }
    if (scalar <= 0x10ffff) { return 4; }
    return -1;
}
