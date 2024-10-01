pcre2_runner: src/pcre2_runner.c
	clang src/pcre2_runner.c -o pcre2_runner -lpcre2-8
	
clean:	
	rm -f pcre2_runner

.PHONY: clean
