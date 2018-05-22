#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "buffer/buffer.h"

static const char *sent = "It's a test for the implimentation of buffer.\n";
static uint sent_len = strlen(sent);

static void print_stat(const Buffer *buffer) {
    char data[1024 * 4];
    memset(data, 0, sizeof(data));
    buffer->peek((byte *)data, ARRAY_SIZE(data));
    //data[sent_len * 2] = '\0';

    printf("Data: %d / %d\n", buffer->data_size(), buffer->buf_size());
    printf("Dump: \n%s\n", data);
    printf("\n");
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

    for (uint i = 0; i < 20; ++i) {
        buffer->write((const byte *)sent, sent_len);
        printf("Write a sentence...\n");
        print_stat(buffer);
    }

    buffer->read(buf, 350);
    printf("Read 350 words...\n");
    print_stat(buffer);

    for (uint i = 0; i < 9; ++i) {
        buffer->write((const byte *)sent, sent_len);
        printf("Write a sentence...\n");
        print_stat(buffer);
    }

    buffer->read(buf, 200);
    printf("Read 20 sentences...\n");
    print_stat(buffer);
}

int main(int argc, char *argv[]) {
    Buffer *buffer = new BlockBuffer(BUFFER_SIZE_MIN);

    test_buffer(buffer);

    delete buffer;

    // printf("Align size of (%d) is %d.\n", 0, ALIGN_SIZE(0));
    // printf("Align size of (%d) is %d.\n", 1, ALIGN_SIZE(1));
    // printf("Align size of (%d) is %d.\n", 3, ALIGN_SIZE(3));
    // printf("Align size of (%d) is %d.\n", 4, ALIGN_SIZE(4));
    // printf("Align size of (%d) is %d.\n", 7, ALIGN_SIZE(7));
    // printf("Align size of (%d) is %d.\n", 8, ALIGN_SIZE(8));
    // printf("Align size of (%d) is %d.\n", 10, ALIGN_SIZE(10));

    return 0;
}
