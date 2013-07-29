OBJS+=$(CURDIR)/$(OBJ)
HEADERS+=$(HEADER)
clean: 
	rm -f $(OBJ)

.PHONY: all clean
