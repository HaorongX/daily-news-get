main.out:
	rm -f dng
	gcc src/command-parse/main.c src/command-parse/function_objects/*.* src/command-parse/command/*.* src/command-parse/public/*.*  src/command-parse/note_reader/*.* -o dng
