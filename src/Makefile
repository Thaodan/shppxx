CXX=g++
TARGET=shppc
OBJS=main.o help.o follow.o parser.o commands/end.o commands/else.o
HEADER=shpp.hxx help.hxx
override CXXFLAGS+=-std=c++11 -Wall 
LINK_FLAGS = -lboost_regex -lboost_filesystem -lboost_system

all: $(TARGET)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c  $<  -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(OBJS)

$(TARGET): $(OBJS) $(HEADER)
	$(CXX) $(CXXFLAGS) $(LINK_FLAGS) $(OBJS) -o $@


.PHONY: all clean
