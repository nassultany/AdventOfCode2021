CC=gcc
INPUT=../input.txt
EXAMPLE=../example.txt

.PHONY: run
.PHONY: test

run: main $(INPUT)
	./main $(INPUT)

test: main $(EXAMPLE)
	./main $(EXAMPLE)

main: main.c
	$(CC) -o main main.c
