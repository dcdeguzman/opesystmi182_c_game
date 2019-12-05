CC = gcc

LDLIBS=-Incurses

SRCS:= $(wildcard*.c)
BINS:= $(SRCS:%.c=%)

all: ${BINS}

clean:
	@echo "Cleaning up..."
	rm -rvf*.o ${BINS}
