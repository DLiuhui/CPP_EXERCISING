SRCS:=$(wildcard *.cc)	#收集所有源文件
CC:=g++
CXXFLAGS:=-Wall -g -std=c++11
OBJS:=$(SRCS:%.cc=%.o)
TARGETS:=$(SRCS:%.cc=%)
all:$(TARGETS)
	@for i in $(TARGETS);do g++ -o $${i} $${i}.cc $(CXXFLAGS);done
clean:
	rm -rf $(TARGETS)
