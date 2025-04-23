CXX = clang++
CXXFLAGS = -Wall -g -std=c++17

# Add -fsanitize=address if SANITIZE=1 is passed to make
# To use this, run: make SANITIZE=1
ifeq ($(SANITIZE),1)
CXXFLAGS += -fsanitize=address -g -O1
endif

SOURCES = $(wildcard *.cpp)
EXECUTABLES = $(SOURCES:.cpp=)

all: $(EXECUTABLES)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES)