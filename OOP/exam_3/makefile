CC = g++

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:%.cc=%.o)

all: ${OBJS}
	${CC} -o factory ${OBJS}

%.o: %.cc
	${CC} -c $<

clean:
	rm -rf *.o factory