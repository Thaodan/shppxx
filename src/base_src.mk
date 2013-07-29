CURRENT_MAKEFILE_LIST := $(MAKEFILE_LIST)
INCLUDE_PATH = $(dir $(lastword $(CURRENT_MAKEFILE_LIST)))include
CXX=g++
override CXXFLAGS+=-I$(INCLUDE_PATH) -std=c++11 -Wall -pipe
