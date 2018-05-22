#include <stdio.h>
#include <string.h>

#include "micros.h"
#include "buffer/buffer.h"

static const char *sent = "It's a test for the implimentation of buffer.\n";
static uint sent_len = strlen(sent);

static void print_stat(const Buffer *buffer) {
    char data[1024 * 4];
    memset(data, 0, sizeof(data));
    buffer->peek((byte *)data, ARRAY_SIZE(data));

    printf("Data: %d / %d\n", buffer->data_size(), buffer->buf_size());
    printf("Dump: \n%s\n", data);
}

static void test_buffer(Buffer *buffer) {
    byte buf[1024];

    printf("For current buffer...\n");
    print_stat(buffer);

    buffer->write((const byte *)sent, sent_len);
    printf("Write a sentence...\n");
    print_stat(buffer);

    buffer->read(buf, sent_len);
    printf("Read a sentence...\n");
    print_stat(buffer);

    for (uint i = 0; i < 50; ++i) {
        buffer->write((const byte *)sent, sent_len);
    }
    printf("Write 50 sentences...\n");
    print_stat(buffer);

    buffer->read(buf, sent_len * 20);
    buffer->read(buf, sent_len * 20);
    printf("Read 40 sentences...\n");
    print_stat(buffer);    
}

int main(int argc, char *argv[]) {
    Buffer *buffer = new BlockBuffer(BUFFER_SIZE_MIN);

    test_buffer(buffer);

    delete buffer;

    return 0;
}
