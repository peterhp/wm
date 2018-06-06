EXE = app
VER = 0.1.1

CC	= gcc
CXX = g++
LD	= g++
CXX_FLAGS = -I. -Wall

BUILD_DIR = build

DIRS = $(shell find . -type d)
C_SRCS = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
C_OBJS = $(patsubst %.c,%.o,$(C_SRCS))
CXX_SRCS = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))
CXX_OBJS = $(patsubst %.cpp,%.o,$(CXX_SRCS))
OBJS = $(C_OBJS) $(CXX_OBJS)

.PHONY: all
all: build

.PHONY: print
print:
	@echo Source Files: $(C_SRCS) $(CXX_SRCS)
	@echo Object Files: $(C_OBJS) $(CXX_OBJS)

.PHONY: build
build: $(EXE)

$(EXE): $(OBJS)
	$(LD) $(OBJS) -o $(EXE)

$(CXX_OBJS): %.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(C_OBJS): %.o: %.c
	$(CC) $(CXX_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJS)
