tail: main.c
	gcc -o tail main.c

fullmake: main.c
	gcc -fsanitize=address -ggdb -gdb -o tail main.c

clean:
	rm -rvf tail
