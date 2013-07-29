include ../../base_src.mk
HEADER = $(INCLUDE_PATH)/commands/messages
OBJ=messages.o
all: $(OBJ)

%.o: %.cxx $(HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

include ../base.mk
