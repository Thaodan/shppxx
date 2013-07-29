include base_src.mk
include ../base.mk
TARGET=shppc
TARGET_VER=0.1
COMMANDS=messages\
	core
OBJS=main.o help.o follow.o parser.o 
HEADERS=shpp.hxx help.hxx 

LINK_FLAGS = -lboost_regex -lboost_filesystem -lboost_system

all: $(TARGET)

$(COMMANDS): 
	$(MAKE) -C commands/$(@)

all_commands.hxx: 
	rm -f $(@)
	for include in $$(find $(INCLUDE_PATH) -type f ! -iname \*~) ; do\
		echo "#include \"$$include\"" >> all_commands.hxx;\
	done

%.o: %.cxx config.hxx all_commands.hxx
	$(CXX) $(CXXFLAGS) -c  $<  -o $@
config.hxx:
	echo "#define APPNAME  \"$(TARGET)\"" > config.hxx
	echo "#define APPVER $(TARGET_VER)" >> config.hxx

$(TARGET): $(OBJS) $(HEADER) $(COMMANDS) config.hxx 
	$(CXX) $(CXXFLAGS) $(LINK_FLAGS) $(OBJS) $(shell find commands -type f -name \*.o) -o $@


clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	rm -f config.hxx
	for cmd in $(COMMANDS) ; do\
		$(MAKE) -C commands/$$cmd clean;\
	done

.PHONY: all clean $(COMMANDS)
