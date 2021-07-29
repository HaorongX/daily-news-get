main.out:
	rm -f main.out
	gcc src/command-parse/main.c src/command-parse/function_objects/*.* src/command-parse/command/*.* -o main.out
