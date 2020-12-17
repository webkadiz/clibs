CFLAGS = -Wall -Wextra -Wpedantic -Wconversion

build:
	gcc $(CFLAGS) src/*.c -o dist/string.o -c
	cp src/*.h dist

%.test: build
	gcc $(CFLAGS) dist/string.o tests/$@.c -o tests/$@ 
	exec tests/$@

build-tests: build
	for test in tests/*.test.c; \
	do \
		bin_name=$$(echo $$test | cut -d'.' -f 1,2); \
		gcc $(CFLAGS) dist/string.o $$test -o $$bin_name; \
	done

run-tests: build-tests
	for test in tests/*.test; \
	do \
		./$$test; \
	done

clean:
	rm dist/*
	rm tests/*.test