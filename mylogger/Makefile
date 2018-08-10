SOURCES:=$(wildcard *.cc)
OBJS:=$(patsubst %.cc,%.o,$(SOURCES))
ELF:=main
CC:=g++
CXXFLAGS:=-g -Wall -std=c++11
LIBS:=-llog4cpp -lpthread
$(ELF):$(OBJS)
	g++ $^ -o $@ $(LIBS)
clean:
	rm -rf $(OBJS) $(ELF)

