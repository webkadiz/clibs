SRC_PATH = ./src
TESTS_PATH = ./tests
DIST_PATH = ./dist
MACRO_PATH = ./macro
CFLAGS = -Wall -Wconversion
CPPFLAGS = -D nl=

%.macro: %.c
	gcc $(CFLAGS) $(SRC_PATH)/$< -o $(MACRO_PATH)/$@ -E || true
	gcc $(CFLAGS) $(TESTS_PATH)/$< -o $(MACRO_PATH)/$@ -E || true
	tail -n 100 $(MACRO_PATH)/$@ | nl-filter

int.test.c:
	gcc $(CFLAGS) $(CPPFLAGS) $(TESTS_PATH)/int.test.c -o $(TESTS_PATH)/int.test

build-tests: int.test.c

run-tests: build-tests
	./tests/int.test

clean:
	rm tests/*.test
	rm dist/*
	rm macro/*