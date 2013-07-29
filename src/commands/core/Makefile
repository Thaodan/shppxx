include ../../base_src.mk
HEADER = $(INCLUDE_PATH)/commands/core
OBJ=core.o
SRCS=else.cxx end.cxx
all: $(OBJ)

$(OBJ): $(SRCS) $(HEADER) 
	$(CXX) $(CXXFLAGS) -c $< -o $@

include ../base.mk
