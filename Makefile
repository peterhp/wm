EXE = app
VER = 0.1.1

CXX = g++
CXX_FLAGS = -I.

DIRS = $(shell find . -type d)
SRCS = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

.PHONY: all
all: build

.PHONY: print
print:
	@echo Source Files: $(SRCS)
	@echo Object Files: $(OBJS)

.PHONY: build
build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXE)

$(OBJS): %.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJS)
