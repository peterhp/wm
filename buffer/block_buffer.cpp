#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "micros.h"
#include "buffer/buffer.h"

BlockBuffer::BlockBuffer(uint buf_size) {
    max_size = MAX(buf_size, BUFFER_SIZE_MIN);
    buf = (byte *)malloc(sizeof(byte) * max_size);
    size = 0;
}

BlockBuffer::~BlockBuffer() {
    free(buf);
}

uint BlockBuffer::buf_size() const {
    return max_size;
}

uint BlockBuffer::data_size() const {
    return size;
}

uint BlockBuffer::free_size() const {
    return max_size - size;
}

uint BlockBuffer::peek(byte *dst, uint max_len) const {
    uint len = MIN(size, max_len);

    memcpy(dst, buf, sizeof(byte) * len);
    return len;
}

uint BlockBuffer::read(byte *dst, uint max_len) {
    uint len = MIN(size, max_len);

    memcpy(dst, buf, sizeof(byte) * len);

    size -= len;
    memcpy(buf, buf + len, sizeof(byte) * size);

    return len;
}

uint BlockBuffer::write(const byte *src, uint len) {
    if (size + len > max_size) {
        expand(size + len);
    }

    memcpy(buf + size, src, sizeof(byte) * len);
    size += len;

    return len;
}

void BlockBuffer::expand(uint min_size) {
    while (max_size < min_size) {
        max_size *= 2;
    }

    buf = (byte *)realloc(buf, sizeof(byte) * max_size);
}
