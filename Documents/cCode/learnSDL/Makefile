CC=gcc

defaut:./src/main.c
	$(CC) -c src/*.c -std=c11 -m64 -g -Wall -I include && gcc *.o -o bin/debug/main -lSDL2main -lSDL2 -lSDL2_image && ./bin/debug/main

debug: ./src/main.c
	$(CC) -c src/*.c -std=c11 -m64 -g -Wall -I include && gcc *.o -o bin/debug/main -lSDL2main -lSDL2 -lSDL2_image

release: ./src/main.c
	$(CC) -c src/*.c -std=c++14 -m64 -O3 -Wall -I include && gcc *.o -o bin/release/main -s -lSDL2main -lSDL2 -lSDL2_image && ./bin/release/main

clean_obj:
	rm -r *.0

clean:
	rm -r *.o && rm ./bin/debug/main && rm ./bin/release/main

run_debug:
	./bin/debug/main
