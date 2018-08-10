SOURCES:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc,%.o,$(SOURCES))
ELF:=main
CC:=g++
CXXFLAGS:=-g -Wall -std=c++11
$(ELF):$(OBJS)
	g++ $^ -o $@ -lpthread
clean:
	rm -rf $(OBJS) $(ELF)

