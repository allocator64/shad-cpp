default: all

CXX = g++-4.9 -std=gnu++0x
CXXFLAGS = -g -O0 -isystem gmock -MD -MF deps/$(subst /,%,$(@)).d
WARNFLAGS = -Wall -pedantic # -Werror

CPPLINT = : cpplint --filter=-legal/copyright,-readability/streams,-runtime/printf

SOURCES = $(shell find . -maxdepth 1 -name '*.cpp')
BINARIES = $(SOURCES:.cpp=.bin)

SOURCES_gmock = gmock/gmock-gtest-all.cc
OBJECTS_gmock = $(SOURCES_gmock:.cc=.o)

$(OBJECTS_gmock): $(SOURCES_gmock)
	$(CXX) -c $(CXXFLAGS) -o $(@) $(<)

$(BINARIES): %.bin: %.cpp $(OBJECTS_gmock)
	$(CPPLINT) $(<) && $(CXX) $(CXXFLAGS) $(WARNFLAGS) -o $(@) $(OBJECTS_gmock) $(<) -lpthread 

with_test: $(tests_passed)

clean:
	rm $(BINARIES) $(OBJECTS_gmock) deps/*.d

all: $(BINARIES)

-include deps/*.d

phony: all clean default
