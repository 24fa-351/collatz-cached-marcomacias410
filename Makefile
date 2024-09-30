main: main.c cache.c cache.h 
	gcc -o main main.c cache.c
clean:
	rm main