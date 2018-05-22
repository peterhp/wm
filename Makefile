EXE = app
VER = 0.1.1

CXX = g++
LD	= g++
CXX_FLAGS = -I. -Wall

BUILD_DIR = build

DIRS = $(shell find . -type d)
SRCS = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: all
all: build

.PHONY: print
print:
	@echo Source Files: $(SRCS)
	@echo Object Files: $(OBJS)

pt:
	$(wildcard **.cpp)

.PHONY: build
build: $(EXE)

$(EXE): $(OBJS)
	$(LD) $(OBJS) -o $(EXE)

$(OBJS): %.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJS)
