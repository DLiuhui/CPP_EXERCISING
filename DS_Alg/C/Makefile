SRCS:=$(wildcard *.c)	#收集所有源文件
CC:=gcc
CFLAGS:=-Wall -g
EXE:=test
OBJS:=$(SRCS:%.c=%.o)
$(EXE):$(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(CFLAGS)
clean:
	rm -rf $(OBJS) $(EXE)
