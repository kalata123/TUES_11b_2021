CC = g++

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:%.cc=%.o)

all: ${OBJS}
	${CC} -o  ${OBJS}

%.o: %.cpp
	${CC} -c $<

clean:
	rm -rf *.o 