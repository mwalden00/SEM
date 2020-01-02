all: control.o sem_funcs.o write.o
	gcc -o control control.o sem_funcs.o
	gcc -o write write.o sem_funcs.o

control.o: control.c sem_funcs.h sem_funcs.o
	gcc -c control.c

write.o: write.c sem_funcs.h sem_funcs.o
	gcc -c write.c

sem_funcs.o: sem_funcs.c sem_funcs.h
	gcc -c sem_funcs.c

clean:
	rm control
	rm write
	rm *.o
