#ifndef _QPT_HEADER_BUFFER_H_
#define _QPT_HEADER_BUFFER_H_

#include "types.h"

#define BUFFER_SIZE_1K  (1024)
#define BUFFER_SIZE_2K  (BUFFER_SIZE_1K * 2)
#define BUFFER_SIZE_4K  (BUFFER_SIZE_2K * 2)
#define BUFFER_SIZE_8K  (BUFFER_SIZE_4K * 2)

#define BUFFER_SIZE_MIN     BUFFER_SIZE_1K
#define BUFFER_SIZE_PAGE    BUFFER_SIZE_4K

class Buffer {
    public: 
        virtual ~Buffer() {}

        virtual uint buf_size() const = 0;
        virtual uint data_size() const = 0;
        virtual uint free_size() const = 0;

        virtual uint peek(byte *dst, uint max_len) const = 0;
        virtual uint read(byte *dst, uint max_len) = 0;
        virtual uint write(const byte *src, uint len) = 0;
};

class BlockBuffer : public Buffer {
    public: 
        BlockBuffer(uint buf_size = BUFFER_SIZE_1K);
        ~BlockBuffer();

        uint buf_size() const;
        uint data_size() const;
        uint free_size() const;

        uint peek(byte *dst, uint max_len) const;
        uint read(byte *dst, uint max_len);
        uint write(const byte *src, uint len);

    private: 
        void expand(uint min_size);

    private:  
        byte *buf;
        uint size;
        uint max_size;
};

class CircularBuffer : public Buffer {

};

#endif // buffer.h
