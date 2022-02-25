CC=gcc
INPUT=../input.txt
EXAMPLE=../example.txt

.PHONY: run
.PHONY: test

run: main $(INPUT)
	./main $(INPUT)

test: main $(INPUT)
	./main $(EXAMPLE)

main: main.c
	$(CC) -o main main.c
