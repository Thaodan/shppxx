CXX=g++
TARGET=shppc
OBJS=main.o help.o follow.o
HEADER=shpp.hxx help.hxx
override CXXFLAGS+=-std=c++11 -Wall

all: $(TARGET)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c  $<  -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(OBJS)

$(TARGET): $(OBJS) $(HEADER)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@


.PHONY: all clean
