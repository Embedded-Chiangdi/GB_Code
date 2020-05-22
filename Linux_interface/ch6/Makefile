.PHONY=all clean test

CC = gcc
SRCS := ${wildcard *.c}
BINS := ${SRCS:%.c=%}

ALL:${BINS}
%:%.c
	@echo "compiling..."
	${CC} $< -o $@ -g

clean:
	@echo "clean ${BINS}"
	@rm -rf ${BINS}

test:
	@echo "This is a test"
	@echo "SRCS = ${SRCS}"
	@echo "BINS = ${BINS}"