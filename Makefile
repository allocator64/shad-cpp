default: all

CXX = g++-4.9 -std=gnu++0x
CXXFLAGS = -g -O0 -isystem gmock
WARNFLAGS = -Wall -Werror -pedantic

CPPLINT = cpplint --filter=-legal/copyright,-readability/streams,-runtime/printf

SOURCES = $(shell find . -name '*.cpp' -maxdepth 1)
BINARIES = $(SOURCES:.cpp=.bin)

SOURCES_gmock = gmock/gmock-gtest-all.cc
OBJECTS_gmock = $(SOURCES_gmock:.cc=.o)

$(OBJECTS_gmock): $(SOURCES_gmock)
	$(CXX) -c $(CXXFLAGS) -o $(@) $(<)

$(BINARIES): %.bin: %.cpp $(OBJECTS_gmock)
	$(CPPLINT) $(<) && $(CXX) $(CXXFLAGS) $(WARNFLAGS) -o $(@) $(OBJECTS_gmock) $(<) && ./$(@)

with_test: $(tests_passed)

clean:
	rm $(BINARIES) $(OBJECTS_gmock)

all: $(BINARIES)

phony: all clean default
