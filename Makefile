CXX = clang++
CXXFLAGS = -Wall -g -std=c++17

SOURCES = $(wildcard *.cpp)
EXECUTABLES = $(SOURCES:.cpp=)

all: $(EXECUTABLES)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES)