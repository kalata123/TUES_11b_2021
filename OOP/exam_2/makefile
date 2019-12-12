CC = g++

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:%.cc=%.o)

all: ${OBJS}
	${CC} -o service ${OBJS}

%.o: %.cc
	${CC} -c $<

clean:
	rm -rf *.o service