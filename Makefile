fib: forky.c patterns.c
	gcc -o forky forky.c patterns.c

clean:
	rm forky

test: forky
	bash test.sh
