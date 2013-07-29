include base_src.mk
include ../base.mk
TARGET=shppc
TARGET_VER=0.1
OBJS=main.o help.o follow.o parser.o commands/end.o commands/else.o commands/messages.o
HEADER=shpp.hxx help.hxx commands/commands.hxx 

LINK_FLAGS = -lboost_regex -lboost_filesystem -lboost_system

all: $(TARGET)

%.o: %.cxx config.hxx
	$(CXX) $(CXXFLAGS) -c  $<  -o $@

config.hxx:
	echo "#define APPNAME  \"$(TARGET)\"" > config.hxx
	echo "#define APPVER $(TARGET_VER)" >> config.hxx
clean:
	rm -f $(TARGET)
	rm -rf $(OBJS)
	rm -f config.hxx

$(TARGET): $(OBJS) $(HEADER) config.hxx
	$(CXX) $(CXXFLAGS) $(LINK_FLAGS) $(OBJS) -o $@


.PHONY: all clean
