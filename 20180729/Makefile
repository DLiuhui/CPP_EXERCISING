SRCS:=$(wildcard *.cc)	#收集所有源文件
CC:=g++
CXXFLAGS:=-Wall -g -std=c++11
LIBS:=-llog4cpp -lpthread
OBJS:=$(SRCS:%.cc=%.o)
TARGETS:=$(SRCS:%.cc=%)
all:$(TARGETS)
	@for i in $(TARGETS);do $(CC) $(CXXFLAGS) $${i}.cc -o $${i} $(LIBS);done
clean:
	rm -rf $(TARGETS)
