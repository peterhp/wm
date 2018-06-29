TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    buffer/blk_buf.cpp \
    buffer/cir_buf.cpp \
    protocol/wmp/wmp.c \
    util/crc.c

HEADERS += \
    buffer/buffer.h \
    protocol/wmp/wmp.h \
    protocol/protocol.h \
    protocol/wm_context.h \
    util/crc.h \
    util/errors.h \
    util/macros.h
