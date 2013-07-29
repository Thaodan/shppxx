include base_src.mk
include ../base.mk
TARGET=shppc
TARGET_VER=0.1
COMMANDS=messages\
	core
OBJS=main.o help.o follow.o parser.o 
HEADERS=shpp.hxx help.hxx commands/commands.hxx 

LINK_FLAGS = -lboost_regex -lboost_filesystem -lboost_system

all: $(TARGET)

$(COMMANDS): 
	$(MAKE) -C commands/$(@)

all_commands.hxx: $(COMMANDS)
	rm -f $(@)
	for include in $$(find $(INCLUDE_PATH) -type f ! -iname \*~) ; do\
		echo "#include \"$$include\"" >> all_commands.hxx;\
	done

%.o: %.cxx config.hxx all_commands.hxx
	$(CXX) $(CXXFLAGS) -c  $<  -o $@
config.hxx:
	echo "#define APPNAME  \"$(TARGET)\"" > config.hxx
	echo "#define APPVER $(TARGET_VER)" >> config.hxx
clean:
	rm -f $(TARGET)
	rm -rf $(OBJS)
	rm -f config.hxx

$(TARGET): $(OBJS) $(HEADER) $(COMMANDS) config.hxx 
	$(CXX) $(CXXFLAGS) $(LINK_FLAGS) $(OBJS) $(shell find commands -type f -name \*.o) -o $@


.PHONY: all clean $(COMMANDS)
