CompileAll: main.c
	gcc -o ls ls.c -lpthread
	gcc -o rm rm.c -lpthread
	gcc -o cat cat.c -lpthread
	gcc -o date date.c -lpthread
	gcc -o mkdir mkdir.c -lpthread

	gcc -o main main.c -lpthread

run:
	./main
